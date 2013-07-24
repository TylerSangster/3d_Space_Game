//******************************************************************************
//CKyagRocket.h
//Copyright (C) 2007, Marcus Trenton, Tyler Sangster, and Sebastian Harko
//Originally written for Total Space Massacre, a project for CS 432 on 
//February 21th, 2007.
//******************************************************************************

#include "CWeapon.h"
#include "CKyagRocketShot.h"

//##############################################################################
/**
* @class CKyagRocket CKyagRocket.h
*
* @brief Describes a KYAG Rocket launcher.
*/
//##############################################################################

#ifndef CKyagRocket_h
#define CKyagRocket_h

class CKyagRocket: public CWeapon {
	public:
        
        //----------------------------------------------------------------------
        /**
        * @brief Creates a CKyagRocket onboard of an CEntity.
        *
        * @param pkcHost The CEntity the CMinigun will be aboard.
        */
        //----------------------------------------------------------------------
        CKyagRocket(CEntity* const pkcHost);
        
        //----------------------------------------------------------------------
        /**
        * @brief Creates a CKyagRocket free-floating in space.
        *
        * @param akdPos The position of the CKyagRocket.
        * @param akdForward Where the CKyagRocket is facing.
        * @param akdUp What direction is up for the CKyagRocket.
        * @param kdSpeed The speed the CKyagRocket is moving at.
        */
        //----------------------------------------------------------------------
        CKyagRocket(GLdouble const akdPos[3], GLdouble const akdForward[3],
            GLdouble const akdUp[3], const GLdouble kdSpeed);
        
        //----------------------------------------------------------------------
        /**
        * @brief Creates the display lists for the CKyagRocket.
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
		* @brief The display list id for a normal CProximityRocket.
		*/
		static const int gknAliveDisplay = 105;
		/**
		* @brief The display list id for a dying CProximityRocket.
		*/
        static const int gknDyingDisplay = 106;
		
	protected:
        //----------------------------------------------------------------------
        /**
        * @brief Create the CKyagRocket CShots (most importantly in the 
        *  appropriate location).
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
#endif //CKyagRocket_H
