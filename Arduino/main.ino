#include "Pins.h"
#include "TempPins.h"
#include "max6675.h"
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

/**
 * Serial command parser
 */
SerialCommand serialCommand;

/**
 * The Air temperture sensor
 */
MAX6675 AirtempSensor(T1SCK, T1CS, T1SO);

/**
 * The bean temp sensor
 */
MAX6675 BeantempSensor(T1SCK, T1CS, T1SO);

/**
 * The current air temprature
 * Globally defined in TempPins.h
 */
double Airtemp = 0.0;

/**
 * The current bean temprature
 * Globally defined in TempPins.h
 */
double Beantemp = 0.0;

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
	return;
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
 delete currentStage;

 //Set the new stage
 currentStage = newStage;

 //Call the new stage init
 currentStage->initialize();


 //Clean up any arguments left
 while (stageArg != NULL) {
	stageArg = serialCommand.next();
 }
}

 /**
  * Handles unknown messages
  */
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
	/* currentStage = new HeatingStage(30); */
	Serial.println("Ready");
	Airtemp = 0.0;
	Beantemp = 0.0;
	currentStage->initialize();
}

/**
 * Default arduino main function
 * Run continuously in a loop
 */
void loop() {
  Airtemp = AirtempSensor.readCelsius();
  Beantemp = BeantempSensor.readCelsius();
  serialCommand.readSerial();
	currentStage->update();
	return;
}



