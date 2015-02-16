#include "HeatingStage.h"
const int CURRTEMP = 1;

/**
 * The number of degrees to allow the oven temperature to deviate from the target temp
 */
const int HEATING_TEMP_DEVIATION = 2;

/**
 * Constructor, sets the target temperature for this heating stage
 */
HeatingStage::HeatingStage(int targetTemperature) {
	this->targetTemperature = targetTemperature;
}

/**
 * Initialize the heating stage
 * Make sure the oven's heating fan and bean stirrer are on 
 */
void HeatingStage::initialize() {
	//Set all pins to a known status
	for (int i = 0; i < PinCount; i++) {
		digitalWrite(PinArray[i], LOW);
	}
	digitalWrite(OVEN_FAN, HIGH);
	digitalWrite(BEAN_STIRRER, HIGH);
}

/**
 * Update the heating stage
 * Check the current bean and heating element temps
 * React according to temps
 */
void HeatingStage::update() {
	if (CURRTEMP < this->targetTemperature - HEATING_TEMP_DEVIATION) {
		digitalWrite(HEATING_ELEMENT, HIGH);
	} else if (CURRTEMP > this->targetTemperature + HEATING_TEMP_DEVIATION) {
		digitalWrite(HEATING_ELEMENT, LOW);
	}
}

/**
 * Cleanup after running the heating stage
 * Make sure the oven fan and bean stirrer are running
 * Make sure the heating element is off
 */
void HeatingStage::end() {
	digitalWrite(OVEN_FAN, HIGH);
	digitalWrite(BEAN_STIRRER, HIGH);
	digitalWrite(HEATING_ELEMENT, LOW);
}
