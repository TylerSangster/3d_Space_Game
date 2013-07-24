//******************************************************************************
//CShip.cpp
//Copyright (C) 2007, Marcus Trenton, Tyler Sangster, and Sebastian Harko
//Originally written for Total Space Massacre, a project for CS 432 on 
//February 21th, 2007.
//******************************************************************************

#include <vector>
#include "CEntity.h"
#include "CWeapon.h"
#include "CShot.h"
#include "CHeavenlyBody.h"
#include "CShipManager.h"

//##############################################################################
/**
* @class CShip CShip.h
* 
* @brief CShip handles all combat statistics, weapons, and AI for a combat ship.
*/
//##############################################################################

#ifndef CShip_h
#define CShip_h
 
class CShip: public CEntity {
	public:
        
        /**
        * @brief The maximum number of weapons a ship can have.
        */
        static const int gknMaxWeapons = 2;
        /**
        * @brief The amount ship rotational movement is scaled down by.
        */
        static const GLdouble gkdRotateScale = 0.01;
        
        //----------------------------------------------------------------------
        /**
        * @brief The specification constructor which allowed a detailed 
        * creation.
        *
        * @param akdPos The position in cartesian co-ordinates.
        * @param akdForward Where the CShip is facing.
        * @param akdUp What direction is up for the CShip.
        * @param kdSpeed The initial speed.
        * @param knTeam What team is the CShip on.
        */
        //----------------------------------------------------------------------
		CShip(GLdouble const akdPos[3], GLdouble const akdForward[3], 
            GLdouble const akdUp[3], const GLdouble kdSpeed, const int knTeam);
		
		//----------------------------------------------------------------------
        /**
        * @brief Shoots the weapon of the given index, if possible.
        *
        * @param knWeaponIndex The index of the weapon to be fired.
        * @param pkcTarget The target the homing weapon is aimed at (null if not
        *   applicable).
        * @return Whether the weapon the actually fired or not.
        */
        //----------------------------------------------------------------------
		bool Shoot(const int knWeaponIndex, CEntity* const pkcTarget);
		
		//----------------------------------------------------------------------
        /**
        * @brief The ship takes the specified amount of damage.
        *
        * @param knDamage The amount of damage taken.
        */
        //----------------------------------------------------------------------		
	    void TakeDamage(const int knDamage);
	    
	    //----------------------------------------------------------------------
	    /**
	    * @brief Resolve the CShip being hit by a CShot.
	    *
	    * @param pcProjectile The CShot that is hitting the CShip.
	    */
	    //----------------------------------------------------------------------
	    void ResolveCollision(CShot* pcProjectile);
	    
	    //----------------------------------------------------------------------
	    /**
	    * @brief Resolve the CShip being hit by a CHeavenlyBody.
	    *
	    * @param pcBody The CHeavenlyBody that is hitting the CShip.
	    */
	    //----------------------------------------------------------------------
	    void ResolveCollision(CHeavenlyBody* pcBody);
	    
	    //----------------------------------------------------------------------
	    /**
	    * @brief Resolve the CShip being hit by another CShip.
	    *
	    * @param pcShip The other CShip that is hitting this CShip.
	    */
	    //----------------------------------------------------------------------
	    void ResolveCollision(CShip* pcShip);

		//----------------------------------------------------------------------
        /**
        * @brief Returns how many new CShips were created by this CShip in the
        * last game cycle.
        *
        * @return The number of new CShips.
        */
        //----------------------------------------------------------------------		    
        int GetNumberNewShips(void) {
            return m_cNewShipVector.size();
        }

		//----------------------------------------------------------------------
        /**
        * @brief Returns the newly created CShip of a given index.
        *
        * @param knIndex The index of the newly created CShip.
        * @return The number of new CShips.
        */
        //----------------------------------------------------------------------        
        CShip* GetNewShip(const int knIndex) {
            return m_cNewShipVector.at(knIndex);       
        }
        
		//----------------------------------------------------------------------
        /**
        * @brief Clears the data structure that holds the newly created CShips.
        */
        //----------------------------------------------------------------------          
        void ClearNewShips(void);
        
        //----------------------------------------------------------------------
        /**
        * @brief Updates the CShip, with the AI using the environment to make 
        * good decisions.
        *
        * @param pkcPlayerShip Who the player ships is. The player ship does not
        *   require AI since the player directly controls it.
        * @param m_kcShipVector All CShips in the level.
        * @param m_kcWeaponVector All CWeapons in the level.
        * @param m_kcShotVector All CShots in the level.
        * @param m_kcHeavenlyBodyVector All CHeavenlyBodies in the level.
        */
        //----------------------------------------------------------------------
        virtual void Update(CShip* const pkcPlayerShip, 
            const vector <CShip*>m_kcShipVector, 
            const vector <CWeapon*>m_kcWeaponVector, 
            const vector <CShot*>m_kcShotVector,
            const vector <CHeavenlyBody*>m_kcHeavenlyBodyVector);
        
        //----------------------------------------------------------------------
        /**
        * @brief Returns the energy of the CShip.
        *
        * @return The amount of energy.
        */
        //----------------------------------------------------------------------
        int GetEnergy() {
            return m_nEnergy;
        }
        
        //----------------------------------------------------------------------
        /**
        * @brief Returns the maximum energy of the CShip.
        *
        * @return The maximum amount of energy.
        */
        //----------------------------------------------------------------------
        int GetMaxEnergy() {
            return m_nMaxEnergy;
        }
        
        //----------------------------------------------------------------------
        /**
        * @brief Returns the health of the CShip.
        *
        * @return The amount of health.
        */
        //----------------------------------------------------------------------
        int GetHealth() {
            return m_nHealth;
        }
        
        //----------------------------------------------------------------------
        /**
        * @brief Returns the maximum health of the CShip.
        *
        * @return The maximum amount of health.
        */
        //----------------------------------------------------------------------
        int GetMaxHealth() {
            return m_nMaxHealth;
        }
        
        //----------------------------------------------------------------------
        /**
        * @brief Returns the shield of the CShip.
        *
        * @return The amount of shield.
        */
        //----------------------------------------------------------------------
        int GetShield() {
            return m_nShield;
        }
        
        //----------------------------------------------------------------------
        /**
        * @brief Returns the maximum shield of the CShip.
        *
        * @return The maximum amount of shield.
        */
        //----------------------------------------------------------------------
        int GetMaxShield() {
            return m_nMaxShield;
        }
        
        //----------------------------------------------------------------------
        /**
        * @brief Returns the number of weapons the CShip has.
        *
        * @return The number of CWeapons.
        */
        //----------------------------------------------------------------------
        int GetNumberWeapons() {
            return m_nWeapons;
        }
        
        //----------------------------------------------------------------------
        /**
        * @brief Returns the CWeapon onboard this ship of a given index.
        *
        * @param knIndex The index of the CWeapon.
        * @return The Cweapon.
        */
        //----------------------------------------------------------------------
        CWeapon* GetWeapon(int knIndex) {
            return m_apcWeapon[knIndex];
        }
        
        //----------------------------------------------------------------------
        /**
        * @brief Adds a CWeapon to the CShip, if possible.
        *
        * @param pkcWeapon The CWeapon to be added.
        * @return Whether the CWeapon was actually added.
        */
        //----------------------------------------------------------------------
        bool AddWeapon(CWeapon* pkcWeapon);
        
        //----------------------------------------------------------------------
        /**
        * @brief Removes a CWeapon of a given index from the CShip.
        *
        * @param knIndex The index of the CWeapon to be removed.
        */
        //----------------------------------------------------------------------
        void RemoveWeapon(const int knIndex);
        
        //----------------------------------------------------------------------
        /**
        * @brief Changes the score of the CShip by a given amount.
        *
        * @param knChange The change in the score.
        */
        //----------------------------------------------------------------------
        void ChangeScore(const int knChange) {
            m_nScore += knChange;
        }
        
        //----------------------------------------------------------------------
        /**
        * @brief Returns the score of the CShip.
        *
        * @return The score.
        */
        //----------------------------------------------------------------------
        int GetScore() {
            return m_nScore;
        }
        
        //----------------------------------------------------------------------
        /**
        * @brief Returns the team of the CShip.
        *
        * @return The team.
        */
        //----------------------------------------------------------------------
        int GetTeam() {
            return m_nTeam;
        }
        
        //----------------------------------------------------------------------
        /**
        * @brief Increases the speed of the CShip.
        *
        * A CShip can go from stationary to max speed in 
        * 150 game cycles / m_nEngineEff. Expends the one energy needed to
        * change speed.
        */
        //----------------------------------------------------------------------
        void Accelerate(void) {
            if(m_dSpeed < m_dMaxSpeed) {
                //It costs one energy to change speed.
                m_nEnergy--;
            }
            
            m_dSpeed += m_dMaxSpeed / 150.0 * m_nEngineEff;
            if(m_dSpeed > m_dMaxSpeed) {
                m_dSpeed = m_dMaxSpeed;
                
            }           
        }
        
        //----------------------------------------------------------------------
        /**
        * @brief Decreases the speed of the CShip.
        *
        * A CShip can go from stationary to reverse max speed in 
        * 150 game cycles / m_nEngineEff. Expends the one energy needed to
        * change speed.
        */
        //----------------------------------------------------------------------
        void Decelerate(void) {
            if(m_dSpeed > -m_dMaxSpeed) {
                //It costs one energy to change speed.
                m_nEnergy--;
            }
            
            m_dSpeed -= m_dMaxSpeed / 150.0 * m_nEngineEff;
            if(m_dSpeed < -m_dMaxSpeed) {
                m_dSpeed = -m_dMaxSpeed;
            }  
        }
        
        //----------------------------------------------------------------------
        /**
        * @brief Slows the speed of the CShip.
        *
        * If the CShip is travel at less than two game cycle of acceleration
        * or deceleration it will completely stop. Expends the one energy needed 
        * to change speed.
        */
        //----------------------------------------------------------------------
        void Brake(void) {
            if(m_dSpeed < 2.0 * m_dMaxSpeed / 150.0 * m_nEngineEff && 
                m_dSpeed > -2.0 * m_dMaxSpeed / 150.0 * m_nEngineEff) {
                m_dSpeed = 0.0;
            }
            else {
                if(m_dSpeed > 0.0) {
                    Decelerate();
                }
                else {
                    Accelerate();
                }
            }
        }
        
        //----------------------------------------------------------------------
        /**
        * @brief Changes the direction of the ship.
        *
        * @param kdAngleRadians The angle on the local up-right plane, measure
        *   from right, that will determine the new forward direction.
        * @param kdMagnitude How far the new motion is.
        */
        //----------------------------------------------------------------------
        void ChangeDirection(const GLdouble kdAngleRadians, 
            const GLdouble kdMagnitude);
		
	protected:
        //----------------------------------------------------------------------
        /**
        * @brief Finds an enemy CShip for this CShip to kill.
        *
        * @param kcShipVector All the CShips in the level.
        */
        //----------------------------------------------------------------------
        CShip* FindTarget(const vector <CShip*>kcShipVector);
        
        //----------------------------------------------------------------------
        /**
        * @brief Moves this CShip towards its target.
        */
        //----------------------------------------------------------------------
        void StalkTarget(void);
        
        //----------------------------------------------------------------------
        /**
        * @brief Shoots at the target, if feasible.
        */
        //----------------------------------------------------------------------
        void ShootTarget(void);
        
        //----------------------------------------------------------------------
        /**
        * @brief Determines if a collision is likely with another CEntity.
        *
        * @param m_kcShipVector The vector of ships in the level.
        * @param m_kcShotVector The vector of shots in the level.
        * @param m_kcHeavenlyBodyVector The vector of heavenly bodies in the 
        *   level.
        *
        * @return The worst CEntity that threatens this ship with collision
        *   (null if there is none).
        */
        //----------------------------------------------------------------------
        CEntity* AnticipateCollison(const vector <CShip*>m_kcShipVector,  
            const vector <CShot*>m_kcShotVector,
            const vector <CHeavenlyBody*>m_kcHeavenlyBodyVector);
        
        //----------------------------------------------------------------------
        /**
        * @brief Takes evasion action to avoid the threatening CEntity.
        *
        * @param pcThreat The CEntity to be evaded.
        *
        */
        //----------------------------------------------------------------------
        void Evade(CEntity* pcThreat);
		
		/**
		* @brief The score the ship has accumulated.
		*/
        int m_nScore;
        /**
		* @brief The current health of the CShip.
		*
		* When the health of the ship is <= 0 then the CShip is destroyed.
		* Unlike shields, health doesn't regenerate with time.
		*/
        int m_nHealth;
        /**
		* @brief The maximum health the CShip can have.
		*/
        int m_nMaxHealth;
        /**
		* @brief The current shield strength of the CShip.
		*
		* When the shields of a CShip hit 0 then the CShip starts losing health.
		* Shields regenerate with time.
		*/
        int m_nShield;
        /**
		* @brief The maximum strength the shields can be at.
		*/
        int m_nMaxShield;
        /**
		* @brief The current amount of energy the ship has.
		*
		* Energy is used to fire weapons, regenerate shields, and power the
		* engines. If the energy is too low then a ship can not do those 
        * actions.
		*/
        int m_nEnergy;
        /**
		* @brief The maximum amount of energy the ship has.
		*/
        int m_nMaxEnergy;
        /**
		* @brief How much energy the ship regains each game cycle.
		*/
        int m_nRecharge;
        /**
		* @brief How efficient a ship is with weapons.
		* 
		* Weapon efficiency is the % discount on energy cost for firing a 
        * weapon.
		*/
        int m_nWeaponEff;
        /**
		* @brief How efficient a ship is with shields.
		*
		* The more efficient a ship is with shields the faster shields will
		* regenerate each game cycles.
		*/
        int m_nShieldEff;
        /**
		* @brief How efficient the ship's engines are.
		*
		* The more efficient the engines are the quicker the change in speed is.
		*/
        int m_nEngineEff;
        /**
		* @brief How fast the ship can change direction.
		*/
        int m_nManeuver;
        /**
		* @brief The fastest the ship can go.
		*/
        GLdouble m_dMaxSpeed;
        /**
		* @brief What team the ship is on.
		*/
        int m_nTeam;
		/**
		* @brief The array of weapons the ship has.
		*/
	 	CWeapon* m_apcWeapon[gknMaxWeapons];         
        /**
		* @brief How many weapons the ship has.
		*/	 	
	 	int m_nWeapons;
	 	/**
        * @brief What CShip the AI is trying to kill.
        */
        CShip* m_pcAiTarget;
        /**
        * @brief How many new ships have been created by this ship during the 
        * last game cycle.
        */
        vector <CShip*>m_cNewShipVector;
};

#endif //CShip.h
