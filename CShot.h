//******************************************************************************
//CShot.h
//Copyright (C) 2007, Marcus Trenton, Tyler Sangster, and Sebastian Harko
//Originally written for Total Space Massacre, a project for CS 432 on 
//February 21th, 2007.
//******************************************************************************

#include <vector>
#include "Global.h"
#include "CEntity.h"
#include <GL/glut.h>

//##############################################################################
/**
* @class CShot CShot.h
*
* @brief Describes a generic weapon shot, which knows how to move and how 
*   much damage it can do.
*/
//##############################################################################

#ifndef CShot_h
#define CShot_h 

class CShot: public CEntity {

	public:

        //----------------------------------------------------------------------
        /**
        * @brief Create a new CShot by specifying all of its movement and
        *   combat variables.
        *
        * @param akdPos The position of CShot.
        * @param akdForward Where the CShot is facing.
        * @param akdUp What direction is up for the CShot.
        * @param kdSpeed How fast it is moving.
        * @param knFirepower How much damage it will do.
        * @param kdRange How far it can move.
        * @param kbHoming Can it home on a target?
        * @param kbDetonateOnShooter Can it collide with the CEntity that shot 
        *   it?
        * @param pkcTarget Who it homing towards (null if not applicable).
        * @param pkcOrigin Who ordered the launch of the CShot.
        */
        //----------------------------------------------------------------------
		CShot(GLdouble const akdPos[3], GLdouble const akdForward[3],
            GLdouble const akdUp[3], const GLdouble kdSpeed, 
            const int knFirepower, const GLdouble kdRange, const bool kbHoming, 
            const bool kbDetonateOnShooter, CEntity* const pkcTarget, 
            CEntity* const pkcOrigin);
        
        //----------------------------------------------------------------------
        /**
        * @brief Returns how many new CShots were created from the current CShot 
        *   in the last game cycle.
        *
        * @return The number of newly created CShots.
        */
        //----------------------------------------------------------------------
		int GetNumberNewShots(void) {
            return m_cNewShotVector.size();
        }
        
        //----------------------------------------------------------------------
        /**
        * @brief Returns the specified newly created CShot from the current 
        *   CShot in the last game cycle.
        *
        * @param knIndex The index of the new created CShot.
        * @return The specified CShot.
        */
        //----------------------------------------------------------------------
        CShot* GetNewShot(int knIndex) {
            return m_cNewShotVector.at(knIndex);
        }
        
        //----------------------------------------------------------------------
        /**
        * @brief Clears the data structure of newly created CShots.
        */
        //----------------------------------------------------------------------
        void ClearNewShots(void);
        
        //----------------------------------------------------------------------
        /**
        * @brief Expand upon the CEntity::Update by also tracking how far the
        *   CShot has travelled.
        */
        //----------------------------------------------------------------------
        virtual void Update(void);
        
        //----------------------------------------------------------------------
        /**
        * @brief Determines whether this CShot collides with another CEntity 
        *   taking into account whether the shot should detonate on the CEntity
        *   that lauched it.
        *
        * @param pkcOtherEntity The other CEntity that this one could collide 
        * with.
        *
        * @return Whether these CEntities collided.
        */
        //----------------------------------------------------------------------		
	    virtual bool IsCollision(CEntity* const pkcOtherEntity);
        
        //----------------------------------------------------------------------
        /**
        * @brief Returns the firepower of the CShot.
        *
        * @return The firepower of the CShot.
        */
        //----------------------------------------------------------------------
        int GetFirepower() {
            return m_nFirepower;
        }
        
        //----------------------------------------------------------------------
        /**
        * @brief Returns the creator of this CShot.
        *
        * @return The creator of this CShot.
        */
        //----------------------------------------------------------------------
        CEntity* GetOrigin() {
            return m_pcOrigin;
        }

	protected:

        /**
        * @brief How much damage it will do upon impact.
        */
		int m_nFirepower;  
        /**
        * @brief How far the shot can go.
        */                
		GLdouble m_dRange;
		/**
        * @brief How far it has gone.
        */
		GLdouble m_dDistance; 
		/**
        * @brief Is the shot homing?
        */
		bool m_bHoming;
		/**
        * @brief Can the shot detonate on the shooter?
        *
        * It would be very bad if proximity rockets detonate at the moment of
        * launch and if mines could be detonated by those who laid them. This
        * varaible provides a means of stopping that. A normal rocket, bullet,
        * or laser should be still be allowed to detonate for the splash damage
        * effect.
        */
		bool m_bDetonateOnShooter;          
        /**
        * @brief The data structure of new shots created during the last 
        * game cycle (A cluster bomb exploding into bomblets for example).
        */
        vector <CShot*>m_cNewShotVector;
        /**
        * @brief If the shot is homing, then this is its target (null if not
        *   applicable).
        */
        CEntity* m_pcTarget; 			        
        /**
        * @brief The Entity that ordered the shot, namely the ship. 
        *
        * This variables can be used to prevent proximity rockets from 
        * detonating at point of launch and mines from destroyer the ship that 
        * laid them.
        */
        CEntity* m_pcOrigin;	
};
#endif //CShot_h
