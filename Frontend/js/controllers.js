//Create a module for controllers
var RoastingAppControllers = angular.module("RoastingAppControllers", []);

//Fetches the list of coffees
RoastingAppControllers.controller("CoffeeListController", ["$scope", "Restangular", 
	function($scope, Restangular) {
		coffeeList = Restangular.all("coffee");
		coffeeList.getList().then(function(coffees){
			console.log(coffees);
			$scope.coffees = coffees;
		});
	}
]);

//Fetches the list of profiles for a coffee
RoastingAppControllers.controller("CoffeeProfilesController", ["$scope", "Restangular", "$routeParams",
	function($scope, Restangular, $routeParams) {
		profileList = Restangular.all("profile");
		profileList.getList({"coffee": $routeParams.id}).then(function(profiles){
			console.log(profiles);
			$scope.profiles = profiles;
		});
	}
]);

//Fetches the list of stages for a profile
RoastingAppControllers.controller("ProfilesStagesController", ["$scope", "Restangular", "$routeParams",
	function($scope, Restangular, $routeParams) {
		$scope.stageTypes = [ "Idle", "Heating", "Cooling"];
		profileList = Restangular.all("stage");
		profileList.getList({"profile": $routeParams.id}).then(function(stages){
			console.log(stages);
			$scope.stages = stages;
		});
	}
]);

//Fetches the list of stages
RoastingAppControllers.controller("StagesListController", ["$scope", "Restangular", "$routeParams",
	function($scope, Restangular) {
		$scope.stageTypes = [ "Idle", "Heating", "Cooling"];
		profileList = Restangular.all("stage");
		profileList.getList().then(function(stages){
			console.log(stages);
			$scope.stages = stages;
		});
	}
]);

//Fetches the list of profiles
RoastingAppControllers.controller("ProfilesListController", ["$scope", "Restangular", "$routeParams",
	function($scope, Restangular) {
		profileList = Restangular.all("profile");
		profileList.getList().then(function(profiles){
			console.log(profiles);
			$scope.profiles = profiles;
		});
	}
]);
