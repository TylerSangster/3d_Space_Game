//******************************************************************************
//CHomingMissile.h
//Copyright (C) 2007, Marcus Trenton, Tyler Sangster, and Sebastian Harko
//Originally written for Total Space Massacre, a project for CS 432 on 
//March 23rd, 2007.
//******************************************************************************

#include "CWeapon.h"
#include "CHomingMissileShot.h"

//##############################################################################
/**
* @class CHomingMissile CHomingMissile.h
*
* @brief Describes a homing missile weapon.
*/
//##############################################################################

#ifndef CHomingMissile_h
#define CHomingMissile_h

class CHomingMissile: public CWeapon {
	public:
        
        //----------------------------------------------------------------------
        /**
        * @brief Creates a CHomingMissile onboard of an CEntity.
        *
        * @param pkcHost The CEntity the CHomingMissile will be aboard.
        */
        //----------------------------------------------------------------------
        CHomingMissile(CEntity* const pkcHost);
        
        //----------------------------------------------------------------------
        /**
        * @brief Creates a CHomingRocket free-floating in space.
        *
        * @param akdPos The position of the CHomingMissile.
        * @param akdForward Where the CHomingMissile is facing.
        * @param akdUp What direction is up for the CHomingMissile.
        * @param kdSpeed The speed the CHomingMissile is moving at.
        */
        //----------------------------------------------------------------------
        CHomingMissile(GLdouble const akdPos[3], GLdouble const akdForward[3],
            GLdouble const akdUp[3], const GLdouble kdSpeed);
        
        //----------------------------------------------------------------------
        /**
        * @brief Creates the display lists for the CHomingMissile.
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
		* @brief The display list id for a normal CHomingMissile.
		*/
		static const int gknAliveDisplay = 111;
		/**
		* @brief The display list id for a dying CHomingMissile.
		*/
        static const int gknDyingDisplay = 112;
		
	protected:
        //----------------------------------------------------------------------
        /**
        * @brief Create the CHomingMissile CShots (most importantly in the 
        *   appropriate location).
        *
        * @param akdBasePos A position on the front face of the host 
        *   CShip.
        * @param akdLocalForward The unit forward vector for the host CShip.
        * @param akdLocalUp  The unit up vector for the host CShip.
        * @param akdLocalRight The unit right vector for the host CShip.
        * @param kdSpeed How fast the shot will move.
        * @param knFirepower How much damage the CShot will do.
        * @param kdRange How far the CShot will go.
        * @param pkcTarget Which CEntity the CShot will home towards (null if not 
        *   applicable).
        */
        //----------------------------------------------------------------------
        virtual void CreateShots(GLdouble const akdBasePos[3], 
            GLdouble const akdLocalForward[3], GLdouble const akdLocalUp[3],
            GLdouble const akdLocalRight[3], const GLdouble kdSpeed, 
            const int knFirepower, const GLdouble kdRange, 
            CEntity* const pkcTarget);
		
	private:
        
        //----------------------------------------------------------------------
        /**
        * @brief Handles creation that is present in both constructors.
        */
        //----------------------------------------------------------------------
        void CommonConstructor(void);
};
#endif //CHomingMissile_h
