#include "Pins.h"
#include "Stage.h"
#include "IdleStage.h"
#include "HeatingStage.h"

//Declarations
/**
 * The stage we are currently in
 */
Stage* currentStage;

/**
 * The arduino default setup function
 */
void setup() {
	//Pinmode setup
	for (int i = 0; i < PinCount; i++) {
	 pinMode(PinArray[i], OUTPUT);
	}

	//Initialize the application in an idlestage
	currentStage = new HeatingStage(5);
}

/**
 * Default arduino main function
 * Run continuously in a loop
 */
void loop() {
	currentStage->initialize();
	delay(2 * 1000);
	currentStage->update();
	delay(2 * 1000);
	currentStage->end();
	delay(2 * 1000);
	return;
}
