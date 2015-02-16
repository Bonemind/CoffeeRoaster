#include "Pins.h"
#include "Stage.h"
#include "IdleStage.h"
#include "HeatingStage.h"
#include "CoolingStage.h"
#include "SerialCommand.h"

//Declarations
/**
 * The stage we are currently in
 */
Stage* currentStage;

SerialCommand serialCommand;

/**
 * Handles the setting of a new stage
 * Calls end of the previous stage and begin of the current stage
 */
void setStage() {
 //Initialization
 Serial.println("Setting stage");
 char *stageArg;
 int stageNumber;
 Stage* newStage;

 //The stage we want to set
 stageArg = serialCommand.next();
 if (stageArg == NULL) {
	Serial.println("ERROR: Missing arg");
	returnl
 }

 //Parse the arg to a number and resolve to a stage
 stageNumber = atol(stageArg);
 switch (stageNumber) {
 	case 0:
 				Serial.println("IdleStage");
 				newStage = new IdleStage;
 				break;
 	case 1:
 				Serial.println("HeatingStage");
 				//Pull the target temperature for the heating stage
 				char *tempArg;
 				tempArg = serialCommand.next();
 				if (tempArg == NULL) {
				 Serial.println("ERROR: Missing arg");
				 return;
				}
 				newStage = new HeatingStage(atol(tempArg));
 				break;
 	case 2:
 				Serial.println("CoolingStage");
 				newStage = new CoolingStage;
 				break;
 }
 //Clean up the old stage
 currentStage->end();

 //Set the new stage
 currentStage = newStage;

 //Call the new stage init
 currentStage->initialize();


 //Clean up any arguments left
 while (stageArg != NULL) {
	stageArg = serialCommand.next();
 }
}
 void unrecognized(const char *cmd) {
 	Serial.print("ERROR: ");
 	Serial.println(cmd);
 }

/**
 * The arduino default setup function
 */
void setup() {
	//Pinmode setup
	for (int i = 0; i < PinCount; i++) {
	 pinMode(PinArray[i], OUTPUT);
	}

	//Begin serial communication and setup callbacks
	Serial.begin(9600);
	serialCommand.addCommand("setstage", setStage);
	serialCommand.setDefaultHandler(unrecognized);

	//Initialize the application in an idlestage
	currentStage = new IdleStage;
	Serial.println("Ready");
}

/**
 * Default arduino main function
 * Run continuously in a loop
 */
void loop() {
  serialCommand.readSerial();
	currentStage->update();
	return;
}



