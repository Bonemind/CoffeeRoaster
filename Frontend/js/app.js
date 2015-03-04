//Roasting app setup
var RoastingApp = angular.module("RoastingApp", [
	"ngRoute",
	"MessageCenterModule",
	"ngCookies",
	"restangular",
	"RoastingAppControllers",
	"angular-loading-bar",
	"angular-inview"
]).config(["RestangularProvider", function(RestangularProvider){
	//Configure restangular
	RestangularProvider.setBaseUrl("http://localhost:5000/api/");

	//Format the data when fetching a collection
	//We expect an array of objects, not an object with an array of objects in it
	RestangularProvider.addResponseInterceptor(function(data, operation, what, url, response, deferred) {
		var sanitized;
		// .. to look for getList operations
		if (operation === "getList") {
			// .. and handle the data and meta data
			sanitized = data.objects;
			sanitized.meta = data.meta
		} else {
			sanitized = data
		}
		return sanitized;
	});
}]);


//Setup a basic auth interceptor
//If we're unauthenticated a login dialog is shown
RoastingApp.factory("basicAuthInterceptor", ["$rootScope", "$q",
	function($rootScope, $q) {
		return {
			"responseError": function(response) {
				if (response && response.status === 401) {
					var deferred = $q.defer();
					$rootScope.$broadcast("event:auth-loginRequired");
					return $q.reject(response);
				}
				return $q.reject(response);
			}
		}
	}
]);

//Register the interceptor
RoastingApp.config(["$httpProvider", function ($httpProvider) {
	$httpProvider.interceptors.push("basicAuthInterceptor");
}]);


//Create a directive for the login dialog
//Shows and hides itself according to login events
angular.module('RoastingApp').directive('loginDialog', function () {
    return {
        templateUrl: 'templates/loginmodal.html',
        restrict: 'E',
        replace: true,
        controller: 'CredentialsController',
        link: function (scope, element, attributes, controller) {
            scope.$on('event:auth-loginRequired', function () {
                console.log("got login event");
                console.log(element);
                element.modal('show');
            });
 
            scope.$on('event:auth-loginConfirmed', function () {
                element.modal('hide');
            });
        }
    }
});

//Controller for basic auth
RoastingApp.controller("CredentialsController", ["$scope", "$http", "$cookieStore", "Base64", function($scope, $http, $cookieStore, Base64) {
	$scope.login = function (userName, password) {
		//Create a basic auth token, add the header, store a cookie
		var encodedUserNameAndPassword = Base64.encode(userName + ':' + password);
		$http.defaults.headers.common['Authorization'] = 'Basic ' + encodedUserNameAndPassword;
		$cookieStore.put('basicCredentials', encodedUserNameAndPassword);

		//Check if we are actually authenticated
		//If so, hide the login form, if note, display an error
		$http.put("http://localhost:5000/api/coffee/1/", {})
		.success(function(data, status, headers, config) {
			$scope.$broadcast('event:auth-loginConfirmed');
			$scope.password = '';
		})
		.error(function(data, status, headers, config) {
			//We get 400 back because of an empty put request
			//If it is actually 400, that means we were authenticated, we just passed non-sensible data
			if (status === 400) {
				$scope.$broadcast('event:auth-loginConfirmed');
				$scope.password = '';
				return;
			}
			$scope.error = 'Invalid Login';
		});
    };
}]);


//Declare routes
RoastingApp.config(["$routeProvider",
		function($routeProvider) {
			$routeProvider.when("/coffees", {
				templateUrl: "templates/coffeeList.html",
				controller: "CoffeeListController"
			}).when("/coffee/:id/profiles", {
				templateUrl: "templates/profileList.html",
				controller: "CoffeeProfilesController"
			}).when("/profile/:id/stages", {
				templateUrl: "templates/stageList.html",
				controller: "ProfilesStagesController"
			}).when("/profiles", {
				templateUrl: "templates/profileList.html",
				controller: "ProfilesListController"
			}).when("/stages", {
				templateUrl: "templates/stageList.html",
				controller: "StagesListController"
			});
		}]);

//A filter to turn an object into an array
RoastingApp.filter("object2array", function() {
	return function(input) {
		return _.toArray(input);
	}
});
