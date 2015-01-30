#ifndef IdleStage_h
#define IdleStage_h

#include "Stage.h"

/**
 * Defines the idle stage as a child of Stage
 */
class IdleStage : public Stage
{
	public: 
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
};

#endif
