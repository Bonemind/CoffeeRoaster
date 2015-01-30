#ifndef Stage_h
#define Stage_h

#include "Arduino.h"
#include "Pins.h"

/**
 * Abstact stage class
 * Parent for any stages we need during roasting
 */
class Stage
{
	public:
		/**
		 * Called when we first enter a stage
		 */
		virtual void initialize() = 0;

		/**
		 * Called while a stage is being run
		 */
		virtual void update() = 0;

		/**
		 * Called when a stage should clean up after itself
		 */
		virtual void end() = 0;
};
#endif
