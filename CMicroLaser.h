//******************************************************************************
//CMicroLaser.h
//Copyright (C) 2007, Marcus Trenton, Tyler Sangster, and Sebastian Harko
//Originally written for Total Space Massacre, a project for CS 432 on 
//February 21th, 2007.
//******************************************************************************

#include "CWeapon.h"
#include "CMicroLaserShot.h"

//##############################################################################
/**
* @class CMicroLaser CMicroLaser.h
*
* @brief Describes a microlaser weapon.
*/
//##############################################################################

#ifndef CMicroLaser_h
#define CMicroLaser_h

class CMicroLaser: public CWeapon {
	public:
        
        //----------------------------------------------------------------------
        /**
        * @brief Creates a CMicroLaser onboard of an CEntity.
        *
        * @param pkcHost The CEntity the CMicroLaser will be aboard.
        */
        //----------------------------------------------------------------------
        CMicroLaser(CEntity* const pkcHost);
        
        //----------------------------------------------------------------------
        /**
        * @brief Creates a CMicroLaser free-floating in space.
        *
        * @param akdPos The position of the CMicroLaser.
        * @param akdForward Where the CMicroLaser is facing.
        * @param akdUp What direction is up for the CMicroLaser.
        * @param kdSpeed The speed the CMicroLaser is moving at.
        */
        //----------------------------------------------------------------------
        CMicroLaser(GLdouble const akdPos[3], GLdouble const akdForward[3],
            GLdouble const akdUp[3], const GLdouble kdSpeed);
        
        //----------------------------------------------------------------------
        /**
        * @brief Creates the display lists for the CMicroLaser.
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
		* @brief The display list id for a normal CMicroLaser.
		*/
		static const int gknAliveDisplay = 103;
		/**
		* @brief The display list id for a dying CMicroLaser.
		*/
        static const int gknDyingDisplay = 104;
		
	protected:
        //----------------------------------------------------------------------
        /**
        * @brief Create the CMicroLaser CShots (most importantly in the 
        * appropriate location).
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
#endif //CMicroLaser_H
