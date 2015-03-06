//Create a module for controllers
var RoastingAppControllers = angular.module("RoastingAppControllers", []);

//-------------------------------------------------------------------------
//Coffee
//-------------------------------------------------------------------------
//Fetches the list of coffees
RoastingAppControllers.controller("CoffeeListController", ["$scope", "Restangular", "ModalService",
	function($scope, Restangular, ModalService) {
		$scope.showModal = function(model) {
			//Check if we're creating a new element
			//If so, make a new model, if not, copy the original
			if (model === undefined) {
				model = Restangular.restangularizeElement(null, {name : ""}, "coffee");
			} else {
				model = Restangular.copy(model);
			}
			ModalService.showModal({
				templateUrl: "templates/coffeeModal.html",
				controller: "CRUDController",
				inputs: {
					model: model
				}
			}).then(function(modal) {
				modal.element.modal();
				modal.close.then(function(result) {
					$scope.update();
				});

			});
		}

		$scope.update = function() {
			coffeeList = Restangular.all("coffee");
			coffeeList.getList().then(function(coffees){
				$scope.coffees = coffees;
			});
		}
		$scope.update();
	}
]);

//CRUD controller
RoastingAppControllers.controller("CRUDController", ["$scope", "Restangular", "messageCenterService", "close", "model", "meta",
	function($scope, Restangular, messageCenterService, close, model, meta) {
		$scope.model = model;
		$scope.meta = meta;
		$scope.close = function(result) {
			close(result, 500);
		}
		$scope.save = function(result) {
			result.save().then(function() {
				messageCenterService.add("success", "Changes saved", {timeout: 7000});
			}, function() {
				messageCenterService.add("danger", "Something went wrong, please try again", {timeout: 7000});
			});
			close(result, 500);
		}

		$scope.remove = function(result) {
			result.remove().then(function() {
				messageCenterService.add("success", "Changes saved", {timeout: 7000});
			}, function() {
				messageCenterService.add("danger", "Something went wrong, please try again", {timeout: 7000});
			});
			close(result, 500);
		}

	}
]);

//Fetches the list of profiles for a coffee
RoastingAppControllers.controller("CoffeeProfilesController", ["$scope", "Restangular", "$routeParams", "ModalService",
	function($scope, Restangular, $routeParams, ModalService) {
		$scope.update = function() {
			profileList = Restangular.all("profile");
			profileList.getList({"coffee": $routeParams.id}).then(function(profiles){
				console.log(profiles);
				$scope.profiles = profiles;
			});
		}
		$scope.coffeeId = $routeParams.id;
		$scope.update();

		$scope.showModal = function(model) {
			//Check if we're creating a new element
			//If so, make a new model, if not, copy the original
			if (model === undefined) {
				model = Restangular.restangularizeElement(null, {name : "", coffee: $scope.coffeeId}, "profile");
			} else {
				model = Restangular.copy(model);
			}
			ModalService.showModal({
				templateUrl: "templates/profileModal.html",
				controller: "CRUDController",
				inputs: {
					model: model
				}
			}).then(function(modal) {
				modal.element.modal();
				modal.close.then(function(result) {
					$scope.update();
				});

			});
		}
	}
]);

//-------------------------------------------------------------------------
//Profiles
//-------------------------------------------------------------------------
//Fetches the list of stages for a profile
RoastingAppControllers.controller("ProfilesStagesController", ["$scope", "Restangular", "$routeParams", "ModalService", 
	function($scope, Restangular, $routeParams, ModalService) {
		var stageTypeList = Restangular.all("stagetype");
		stageTypeList.getList().then(function(stagetypes) {
			$scope.stageTypes = stagetypes;
		});
		
		$scope.update = function() {
			profileList = Restangular.all("stage");
			profileList.getList({"profile": $routeParams.id}).then(function(stages){
				console.log(stages);
				$scope.stages = stages;
			});
		}
		$scope.profileId = $routeParams.id;
		$scope.update();

		$scope.showModal = function(model, stageTypes) {
			//Check if we're creating a new element
			//If so, make a new model, if not, copy the original
			if (model === undefined) {
				model = Restangular.restangularizeElement(null, {stage_type : 1, duration: 0, target_temperature: 0, sequence_number: 0,  profile: $scope.profileId}, "stage");
			} else {
				model = Restangular.copy(model);
			}
			ModalService.showModal({
				templateUrl: "templates/stageModal.html",
				controller: "CRUDController",
				inputs: {
					meta:  {
						stageTypes: stageTypes
					},
					model: model
				}
			}).then(function(modal) {
				modal.element.modal();
				modal.close.then(function(result) {
					$scope.update();
				});

			});
		}
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

//-------------------------------------------------------------------------
//Stages
//-------------------------------------------------------------------------
//Fetches the list of stages
RoastingAppControllers.controller("StagesListController", ["$scope", "Restangular", "$routeParams",
	function($scope, Restangular) {
		var stageTypeList = Restangular.all("stagetype");
		stageTypeList.getList().then(function(stagetypes) {
			$scope.stageTypes = stagetypes;
		});
		profileList = Restangular.all("stage");
		profileList.getList().then(function(stages){
			console.log(stages);
			$scope.stages = stages;
		});
	}
]);

