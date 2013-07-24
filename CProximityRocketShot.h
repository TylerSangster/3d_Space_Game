//******************************************************************************
//CProximityRocketShot.h
//Copyright (C) 2007, Marcus Trenton, Tyler Sangster, and Sebastian Harko
//Originally written for Total Space Massacre, a project for CS 432 on 
//March 23rd, 2007.
//******************************************************************************

#include "CShot.h"

//##############################################################################
/**
* @class CProximityRocketShot CProximityRocketShot.h
*
* @brief A projectile launched by a CProximityRocket.
*/
//##############################################################################

#ifndef CProximityRocketShot_h
#define CProximityRocketShot_h

class CProximityRocketShot: public CShot {

	public:

        //----------------------------------------------------------------------
        /**
        * @brief Creates a new CProximityRocketShot from the given location and 
        *   combat variables.
        *
        * @param akdPos Where it is.
        * @param akdForward Where the CProximityRocketShot is facing.
        * @param akdUp What direction is up for the CProximityRocketShot.
        * @param kdSpeed How fast it's going.
        * @param knFirepower How much damage it'll do.
        * @param kdRange How far it can go.
        * @param kbHoming Does the it home on a target?
        * @param kbDetonateOnShooter Can it detonate on the CEntity that shot it?
        * @param pkcTarget Its homing target (null if not applicable).
        * @param pkcOrigin Who ordered its launch.
        */
        //----------------------------------------------------------------------
		CProximityRocketShot(GLdouble const akdPos[3], 
            GLdouble const akdForward[3], GLdouble const akdUp[3], 
            const GLdouble kdSpeed, const int knFirepower, 
            const GLdouble kdRange, const bool kbHoming, 
            const bool kbDetonateOnShooter, CEntity* const pkcTarget, 
            CEntity* const pkcOrigin);
		
		//----------------------------------------------------------------------
		/**
		* @brief Creates the display lists for all CProximityRocketShots.
		*/
		//----------------------------------------------------------------------
		static void Init(void);

		//----------------------------------------------------------------------
        /**
        * @brief Destroys the display lists.
        */
        //----------------------------------------------------------------------
        static void UnInit(void);
		
		/**
		* @brief What display list to use to draw itself when it's alive.
		*/
        static const int gknAliveDisplay = 209;
        /**
		* @brief What display list to use to draw itself when it's dying.
		*/
        static const int gknDyingDisplay = 210;

};
#endif //CProximityRocketShot_h
