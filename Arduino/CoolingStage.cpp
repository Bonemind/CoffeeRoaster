#include "CoolingStage.h"
/**
 * The time we need to sleep until all beans have propably dropped
 */
const int TIME_TO_ALL_DROPPED = 10 * 1000;

int startTime = 0;

/**
 * Initialize the cooling stage
 * Set the pins correctly
 * The oven fan should be running to cool the heating element
 */
void CoolingStage::initialize() {
	//Set all pins to a known state
	for (int i = 0; i < PinCount; i++) {
		digitalWrite(PinArray[i], LOW);
	}

	//Open the hatch, drop the beans, and start cooling
	//Also make sure the heating element fan is on so it gets cooled
	digitalWrite(BEAN_STIRRER, HIGH);
	digitalWrite(ELECTROMAGNET, HIGH);
	digitalWrite(COOLING_FAN, HIGH);
	digitalWrite(OVEN_FAN, HIGH);
	startTime = millis();
}

/**
 * Update the cooling stage
 * Checks if all beans have dropped, if so, turn off the stirrer and electromaget
 */
void CoolingStage::update() {
	//Check if we have waited long enough for the beans to have dropped
	if (startTime + TIME_TO_ALL_DROPPED < millis()) {
		//All beans should have dropped by now, so turn off the stirrer and electromagnet
		digitalWrite(BEAN_STIRRER, LOW);
		digitalWrite(ELECTROMAGNET, LOW);
	}
}

/**
 * Cleanup after running the idle stage
 * Turn of all pins since nothing needs to do anything
 */
void CoolingStage::end() {
	for (int i = 0; i < PinCount; i++) {
		digitalWrite(PinArray[i], LOW);
	}
}
