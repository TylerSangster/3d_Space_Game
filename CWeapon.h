//******************************************************************************
//CWeapon.h
//Copyright (C) 2007, Marcus Trenton, Tyler Sangster, and Sebastian Harko
//Originally written for Total Space Massacre, a project for CS 432 on 
//February 21th, 2007.
//******************************************************************************

#include <vector>
#include "CShot.h"
#include "CEntity.h"
#include <GL/glut.h>

//##############################################################################
/**
* @class CWeapon CWeapon.h
*
* @brief A weapon that can be mounted aboard a CEntity and fire shots.
*/
//##############################################################################

#ifndef CWeapon_h
#define CWeapon_h

class CWeapon: public CEntity {
	public:
        
        //----------------------------------------------------------------------
        /**
        * @brief Creates a CWeapon onboard a CEntity.
        *
        * @param pkcHost The CEntity the CWeapon is on.
        */
        //----------------------------------------------------------------------
        CWeapon(CEntity* const pkcHost);
        
        //----------------------------------------------------------------------
        /**
        * @brief Creates a CWeapon free-floating in space.
        *
        * @param akdPos Where the CWeapon is.
        * @param akdForward Where the CWeapon is facing.
        * @param akdUp What direction is up for the CWeapon.
        * @param kdSpeed How fast the CWeapon is moving.
        */
        //----------------------------------------------------------------------
        CWeapon(GLdouble const akdPos[3], GLdouble const akdForward[3],
            GLdouble const akdUp[3], const GLdouble kdSpeed);
        
        //----------------------------------------------------------------------
        /**
        * @brief Attempt to fire the CWeapon and return if it was successful.
        *
        * @param pkcTarget The CEntity the CShot will be homing at (null if not 
        *   applicable).
        * @param kdOffset Used to space out the CShots from different CWeapons.
        * @return Whether or not the CWeapon was actually fired.
        */
        //----------------------------------------------------------------------
        virtual bool Shoot(CEntity* pkcTarget, const GLdouble kdOffset);
		
		//----------------------------------------------------------------------
		/**
		* @brief Handle the CWeapon cooling-down between firings.
		*/
		//----------------------------------------------------------------------
		virtual void Update(void);
		
		//----------------------------------------------------------------------
		/**
		* @brief Only draw the CWeapon if its free-floating in space. 
		*/
		//----------------------------------------------------------------------
		virtual void Draw(void);
		
		//----------------------------------------------------------------------
		/**
		* @brief Returns the energy needed to fire the CWeapon.
		*
		* @return The amount of energy.
		*/
		//----------------------------------------------------------------------
		int GetEnergy() {
            return m_nEnergy; 
        }
        
        //----------------------------------------------------------------------
		/**
		* @brief Returns the range of the CWeapon.
		*
		* @return The range.
		*/
		//----------------------------------------------------------------------
		GLdouble GetRange() {
            return m_dRange; 
        }
        
		//----------------------------------------------------------------------
		/**
		* @brief Returns how many new CShots have been created in the last game
		*     cycle.
		*
		* @return The number of new CShots.
		*/
		//----------------------------------------------------------------------		
		int GetNumberNewShots(void) { 
           return m_cNewShotVector.size(); 
        }
        
        //----------------------------------------------------------------------
		/**
		* @brief Returns a specified newly created CShot.
		*
		* @param knIndex The index of the CShot.
		* @return The newly created CShot.
		*/
		//----------------------------------------------------------------------
        CShot* GetNewShot(int knIndex) {
            return m_cNewShotVector.at(knIndex);
        }
        
        //----------------------------------------------------------------------
		/**
		* @brief Clears the data structure holding the newly created CShots.
		*/
		//----------------------------------------------------------------------
        void ClearNewShots(void);

	protected:
        
        //----------------------------------------------------------------------
        /**
        * @brief Determines if the CWeapon is capable of firing.
        *
        * @return Whether it's capable or not.
        */
        //----------------------------------------------------------------------
        bool ReadyToFire(void);
        
        //----------------------------------------------------------------------
        /**
        * @brief A pure virtual method for creating the CShots when the CWeapon
        *   fires.
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
            CEntity* const pkcTarget) = 0;
        
        /**
        * @brief The CEntity this weapon resides on, if any.
        */
        CEntity* m_pcHost;        
        /**
        * @brief The vector that holds the newly shots by this CWeapon during 
        * the last game cycle.
        */
        vector <CShot*>m_cNewShotVector;       
        /**
        * @brief How much time (in game cycles) the CWeapon has had to cooldown
        *   since it last fired.
        */
		int m_nCoolDownTime;
        /**
        * @brief How much time damage the CWeapon will do.
        */
		int m_nFirepower;
		/**
        * @brief How many game cycles must pass before the CWeapon can be fired
        *   again.
        */
		int m_nRate;
		/**
        * @brief How far the CWeapon's shots can travel.
        */
		GLdouble m_dRange;
		/**
        * @brief How much energy the CWeapon consumes when fired.
        */
		int m_nEnergy;
		/**
        * @brief How fast the CWeapon's shots can travel.
        */
		GLdouble m_dShotSpeed;
		/**
        * @brief If the CShots of the CWeapon can home on a target CEntity.
        */
        bool m_bHoming;
        /**
        * @brief Can the CShot detonate due to collision with the CEntity that
        *   launched it?
        *
        * It would be very bad if proximity rockets detonate at the moment of
        * launch and if mines could be detonated by those who laid them. This
        * varaible provides a means of stopping that. A normal rocket, bullet,
        * or laser should be still be allowed to detonate for the splash damage
        * effect.
        */
        bool m_bDetonateOnShooter;
		
	private:
        
        //----------------------------------------------------------------------
        /**
        * Handles creation that is present in both constructors.
        */
        //----------------------------------------------------------------------
        void CommonConstructor(void);
};
#endif //CWeapon_h
