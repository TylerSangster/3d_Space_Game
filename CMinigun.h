//******************************************************************************
//CMinigun.cpp
//Copyright (C) 2007, Marcus Trenton, Tyler Sangster, and Sebastian Harko
//Originally written for Total Space Massacre, a project for CS 432 on 
//February 21th, 2007.
//******************************************************************************

#include "CWeapon.h"
#include "CMinigunShot.h"

//##############################################################################
/**
* @class CMinigun CMinigun.h
*
* @brief Describes a minigun weapon.
*/
//##############################################################################

#ifndef CMinigun_h
#define CMinigun_h

class CMinigun: public CWeapon {
	public:
        
        //----------------------------------------------------------------------
        /**
        * @brief Creates a CMinigun onboard of an CEntity.
        *
        * @param pkcHost The CEntity the CMinigun will be aboard.
        */
        //----------------------------------------------------------------------
        CMinigun(CEntity* const pkcHost);
        
        //----------------------------------------------------------------------
        /**
        * @brief Creates a CMinigun free-floating in space.
        *
        * @param akdPos The position of the CMinigun.
        * @param akdForward Where the CMinigun is facing.
        * @param akdUp What direction is up for the CMinigun.
        * @param kdSpeed The speed the CMinigun is moving at.
        */
        //----------------------------------------------------------------------
        CMinigun(GLdouble const akdPos[3], GLdouble const akdForward[3],
            GLdouble const akdUp[3], const GLdouble kdSpeed);
        
        //----------------------------------------------------------------------
        /**
        * @brief Creates the display lists for the CMinigun.
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
		* @brief The display list id for a normal CMinigun.
		*/
		static const int gknAliveDisplay = 101;
		/**
		* @brief The display list id for a dying CMinigun.
		*/
        static const int gknDyingDisplay = 102;
		
	protected:
        //----------------------------------------------------------------------
        /**
        * @brief Create the CMinigun CShots (most importantly in the appropriate
        *   location).
        *
        * @param akdBasePos A position on the front face of the host 
        *   CShip.
        * @param akdLocalForward The unit forward vector for the host CShip.
        * @param akdLocalUp  The unit up vector for the host CShip.
        * @param akdLocalRight The unit right vector for the host CShip.
        * @param kdSpeed How fast the shot will move.
        * @param knFirepower How much damage the CShot will do.
        * @param kdRange How far the CShot will go.
        * @param pkcTarget Which CEntity the CShot will home towards (null if 
        *   not applicable).
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
#endif //CMiniGun_H
