#ifndef HeatinStage_h
#define HeatingStage_h

#include "Stage.h"

/**
 * Defines the idle stage as a child of Stage
 */
class HeatingStage: public Stage
{
	public: 
		/**
		 * Constructor, sets the target temp for the current stage
		 */
		HeatingStage(int targetTemperature);

		/**
		 * Startup of the stage
		 */
		void initialize();

		/**
		 * Update during stage running
		 */
		void update();

		/**
		 * Cleanup after the stage was completed
		 */
		void end();
	
	private:
		/**
		 * The temperature the beans should reach in this stage
		 */
		int targetTemperature;
};

#endif
