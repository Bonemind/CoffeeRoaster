#include "IdleStage.h"

/**
 * Initialize the idle stage
 * Make sure all devices are off since nothing needs to happen
 */
void IdleStage::initialize() {
	for (int i = 0; i < PinCount; i++) {
		digitalWrite(PinArray[i], LOW);
	}
}

/**
 * Update the idle stage
 * No-op since the stage is not doing anything
 */
void IdleStage::update() {
	//Void
}

/**
 * Cleanup after running the idle stage
 * There is nothing to clean up, so no-op
 */
void IdleStage::end() {
	//void
}
