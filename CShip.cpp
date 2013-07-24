//******************************************************************************
//CShip.cpp
//Copyright (C) 2007, Marcus Trenton, Tyler Sangster, and Sebastian Harko
//Originally written for Total Space Massacre, a project for CS 432 on 
//February 21th, 2007.
//******************************************************************************

#include <math.h>
#include <cstdlib>
#include "CShip.h"
#include "GL/glut.h"

using namespace std;

//##############################################################################
/**
* @class CShip CShip.h
* CShip is the base class for all ships. It handles the weapons, combat 
* statistics, and artificial intelligence. This class is still abstract from
* a practical point of view since it still doesn't know what to draw, what its 
* bounding box is, and what its scale is. All of its subclasses should be 
* concrete, instantiable classes. All of the mechanics of a ship are handled in
* this class, including firing weapons, taking damage, and planning the next
* move.
*
* @author Marcus Trenton
* @date 01/03/2007
* @version 1.0
*
* @par Acknowledgement The line-point distance algorithm is from
*   http://mathworld.wolfram.com/Point-LineDistance3-Dimensional.html
*/
//##############################################################################

	//--------------------------------------------------------------------------
	/**
    * The constructor stores the variables taken in and sets of the others to
    * zero. The others will be overwritten to be something meaningful by
    * subclasses.
    *
    * @see CEntity::CEntity, ClearNewShips
    */
    //--------------------------------------------------------------------------
	CShip::CShip(GLdouble const akdPos[3], GLdouble const akdForward[3], 
        GLdouble const akdUp[3], const GLdouble kdSpeed, const int knTeam) 
        : CEntity(akdPos, akdForward, akdUp, kdSpeed), m_nTeam(knTeam) {
	 	
	 	//Fill the array of weapons to null.
	 	m_nWeapons = 0; 
	 	for(int i = 0; i < gknMaxWeapons; i++) {
			m_apcWeapon[i] = NULL;	 		
	 	}
	 	
	 	//Create the array of newly spawned ships and fill it to null.
	 	ClearNewShips();
	 	
	 	//All ship stats are undefined until a subclass defines them.	 	 
        m_nMaxHealth = gknUndefined;    
        m_nMaxShield = gknUndefined;    
        m_nMaxEnergy = gknUndefined;    
        m_nRecharge = gknUndefined;  
        m_nWeaponEff = gknUndefined; 
        m_nShieldEff = gknUndefined; 
        m_nEngineEff = gknUndefined; 
        m_nManeuver = gknUndefined;
        m_dMaxSpeed = gknUndefined;
        
        //Needed initializations. The ships begins in perfect condition,
        //with no score, and no target.
        m_nScore = 0;
        m_pcAiTarget = NULL;
        
        //Later overwritten, here as default.
        m_nHealth = m_nMaxHealth;
        m_nShield = m_nMaxShield;
        m_nEnergy = m_nMaxEnergy;	
	}
	
	//--------------------------------------------------------------------------
	/**
    * Tell the weapon of the given ID to fire if there is enough energy. This
    * method is public so a player can directly control the weapons.
    *
    * @see CWeapon::Shoot 
    */
    //--------------------------------------------------------------------------
	bool CShip::Shoot(const int knWeaponId, CEntity* const pkcTarget) {		
		bool bFired = false;
		
		//Only fire the weapon if the weapon exists.
		if(m_apcWeapon[knWeaponId] != NULL) {		
    		//Weapon efficiecny is a percentage discount on firing cost, 
            //round down.
    		int nRequiredEnergy = m_apcWeapon[knWeaponId]->GetEnergy()*
                (100-m_nWeaponEff)/100;
    		if(m_nEnergy >= nRequiredEnergy) {
                //Calculate the offset for the shots. Each weapon should produce
                //shots to left of those to the next weapon.
                GLdouble dOffset = -(knWeaponId+1.0)/(gknMaxWeapons+1.0) + 0.5;
    			if(m_apcWeapon[knWeaponId]->Shoot(pkcTarget, dOffset)) {
    				//Pay the energy needed to fire the weapon.
    				m_nEnergy -= nRequiredEnergy;
    				bFired = true;
    			}	
    		}
        }
		
		return bFired;
	}
	
	//--------------------------------------------------------------------------
	/**
    * The the ship takes the given amount of damage. Damage first comes off
    * the shields and then off the health. If there is no health remaining
    * then the CShip is now dying.
    */
    //--------------------------------------------------------------------------
	void CShip::TakeDamage(const int knDamage) {
		if(knDamage < m_nShield) {
            m_nShield -= knDamage;
        }
        else {
            int nRemainingDamage = knDamage - m_nShield;
            m_nShield = 0;
            m_nHealth -= nRemainingDamage;
            if(m_nHealth <= 0) {
                Die();
            }
        }
	}
	
	//--------------------------------------------------------------------------
    /**
    * The ship takes damage from the CShot and, if destroyed, increments the
    * score of the CShip that killed it. The CShot is told to start dying.
    */
    //--------------------------------------------------------------------------
    void CShip::ResolveCollision(CShot* pcProjectile) {
        int nPreviousHealth = m_nHealth;
        TakeDamage(pcProjectile->GetFirepower());
        if(m_nState != gknAlive) {
            CShip* pcShooter = dynamic_cast<CShip*>(pcProjectile->GetOrigin());
            //If the shooter was a ship and this was the shot that killed it 
            //then increment the score of the shooter.
            if(pcShooter != NULL && nPreviousHealth > 0) {
                pcShooter->ChangeScore(1);
            }
        }
        pcProjectile->Die();       
    }
    
    //--------------------------------------------------------------------------
    /**
    * The CShip and the CHeavenlyBody both take damage in an amount determined
    * by the CHeavenlyBody.
    */
    //--------------------------------------------------------------------------
    void CShip::ResolveCollision(CHeavenlyBody* pcBody) {
        TakeDamage(pcBody->GetDamage());
        pcBody->TakeDamage(pcBody->GetDamage());
    }
    
    //--------------------------------------------------------------------------
	/**
	* It is uncurrently undefined what happens when a CShip hits another CShip.
	*/
	//--------------------------------------------------------------------------
	void CShip::ResolveCollision(CShip* pcShip) {
        GLdouble dMult = 1000;
        TakeDamage( ((int) (pcShip->GetScale()*dMult) ));
        pcShip->TakeDamage( ((int)(m_dScale*dMult)) );
    }
	
	//--------------------------------------------------------------------------
	/**
	* Clears the data structure that holds the newly created CShips.
	*/
	//--------------------------------------------------------------------------
	void CShip::ClearNewShips(void) {
		m_cNewShipVector.clear();		
	}
	
	//--------------------------------------------------------------------------
	/**
    * Add the weapon to the first available slot. Return true if the weapon
    * was added and false otherwise.
    */
    //--------------------------------------------------------------------------
	bool CShip::AddWeapon(CWeapon* cWeapon) {
		bool bAdded = false;
		
		for(int i = 0; i < gknMaxWeapons && !bAdded; i++) {
			if (m_apcWeapon[i] == NULL) {
				m_apcWeapon[i] = cWeapon;
				//INSERT CHANGING WEAPON ONBOARD TO TRUE
				bAdded = true;
				m_nWeapons++;				
			}			
		}
		return bAdded;
	}
	
	//--------------------------------------------------------------------------
	/**
    * Remove the weapon from the given slot and send it free-floating into
    * space. STUBBED.
    */
    //--------------------------------------------------------------------------
	void CShip::RemoveWeapon(const int knWeapon) {
		//INSERT STATEMENT TO DETACH THE WEAPON.
		
		m_apcWeapon[knWeapon] = NULL;
	}
	
	//--------------------------------------------------------------------------
	/**
    * Update the ship by gaining new energy and spending it. Also determine
    * the next action and execute it, leaving the actual movement for the
    * Entity class.
    *
    * @see CEntity::Update
    */
    //--------------------------------------------------------------------------
    void CShip::Update(CShip* const pkcPlayerShip, 
        const vector <CShip*>kcShipVector, 
        const vector <CWeapon*>kcWeaponVector, 
        const vector <CShot*>kcShotVector,
        const vector <CHeavenlyBody*>kcHeavenlyBodyVector) {
            
        //Only update if the CShip is alive.
        if(m_nState == gknAlive) {
        
            //Add new energy up to the energy limit.
            m_nEnergy += m_nRecharge;
        
            if(m_nEnergy > m_nMaxEnergy) {
                m_nEnergy = m_nMaxEnergy;
            }
        
    	   //If shields are below full strength then recharge them.
    	   if(m_nShield < m_nMaxShield) {
                int nShieldGain = 0;
                //The max a shield can be recharged is its ShieldEff but do a
                //check to see if that amount is overkill.
                if(m_nShield + m_nShieldEff > m_nMaxShield) {
                    nShieldGain = m_nMaxShield - m_nShield;
                }
                else {
                    nShieldGain = m_nShieldEff;
                }
            
                //You can only recharge up to the amount of energy present.
                //nShieldGain = min(nShieldGain, m_nEnergy);
                if(nShieldGain > m_nEnergy) {
				    nShieldGain = m_nEnergy;            	
                }
            
                m_nEnergy -= nShieldGain;
                m_nShield += nShieldGain;
            }
        
            //Do AI work only if not the player. This includes finding a target,
            //stalking it, evading threats, and shooting the target.
            if(this != pkcPlayerShip) {                
                //If the target is null or dead find another target.
                if(m_pcAiTarget == NULL) {
                    m_pcAiTarget = FindTarget(kcShipVector);
                }
                else {
                    if(m_pcAiTarget->GetState() != gknAlive) {                    
                        m_pcAiTarget = FindTarget(kcShipVector);
                    }
                }
                
                //Whether time consuming algorithms are used for the AI.
                
                //Removing this variable and setting the code is always executes
                //causes collision detection to fail in Windows.
                //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
                bool bAdvancedAI = true; 
                //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
                
                //Detect if there is a CEntity that could collide with the ship.
                CEntity* pcEvade = NULL;
                if(bAdvancedAI) {
                    pcEvade = AnticipateCollison(kcShipVector, 
                        kcShotVector, kcHeavenlyBodyVector);
                }
                
                //If there is a CEntity to evade then evade it.
                if(pcEvade != NULL) {
                    Evade(pcEvade);
                }
                //Otherwise track down and kill a target, if there is any.
                else {
                    if(m_pcAiTarget != NULL) {
                        //Move towards the target.
                        StalkTarget();
                
                        //If the target is in range and in a probable line of fire 
                        //then shoot it.
                        ShootTarget();
                    }
                }                  
            }
        }
        
        //Do the movement updating of the parent Entity.
        CEntity::Update();
    }

    //--------------------------------------------------------------------------
    /**
    * Changes the direction of the CShip. The extent of the change in direction
    * is specified in the CShip's m_nManeuver. The higher the 
    * maneuverability the quicker the CShip will turn.
    */
    //--------------------------------------------------------------------------
    void CShip::ChangeDirection(const GLdouble kdAngleRadians, 
        const GLdouble kdMagnitude) {
        
        //Update the ship's orientation based on the change in angle.
        GLdouble adNewDirection[3] = {0.0, 0.0, 0.0};
        GLdouble adRight[3];
        Cross(m_adForward, m_adUp, adRight);
        Normalize(adRight);
        
        //Determine the new direction by adding enough local up and 
        //local right.
        for(int i = 0; i < 3; i++) {
            adNewDirection[i] = m_adForward[i]
                + kdMagnitude*m_nManeuver*gkdRotateScale*
                    sin(kdAngleRadians)*m_adUp[i]
                + kdMagnitude*m_nManeuver*gkdRotateScale*
                    cos(kdAngleRadians)*adRight[i];
        }
        Normalize(adNewDirection);
        
        //Rotate the up vector as well. The bug of opposite vectors can't occur.
        GLdouble aadRotMatrix[4][4];
        GetRotMatrix(m_adForward, adNewDirection, aadRotMatrix);
        
        //Check to make sure the up vector is not getting an X-component.
        MatrixMultVector(aadRotMatrix, m_adUp);
        Normalize(m_adUp);
        for(int i = 0; i < 3; i++) {
            m_adForward[i] = adNewDirection[i];
        }
        
        //It costs one energy to change direction.
        m_nEnergy--;
    }
    
    //--------------------------------------------------------------------------
    /**
    * Search through the CShips in the level to find one that is an enemy and
    * within a spotting range.
    */
    //--------------------------------------------------------------------------
    CShip* CShip::FindTarget(const vector <CShip*>kcShipVector) {
        CShip* pcCandidate = NULL;
        
        //The maximum distance for which targets can be acquired.
        GLdouble dMaxDistance = 2.0;

	   //The distance from this ship to the candidate target.
	   GLdouble dCandidateDistanceSquared = 99999999.0;
        
        //Go through the list and find the closest ship that is within distance 
        //and on a different team.
        for(int i = 0; i < kcShipVector.size(); i++) {
            //Only consider ships that are alive and not on its team.
            if(m_nTeam != kcShipVector.at(i)->GetTeam() && 
                kcShipVector.at(i)->GetState() == gknAlive) {
                
                GLdouble adOtherPos[3];
                for(int j = 0; j < 3; j++) {
					adOtherPos[j] = kcShipVector.at(i)->GetPos(j);
                }
                GLdouble dDistanceSquared = 
                	DistanceSquared(m_adPos,adOtherPos);
                
                //The ship must be on another team, alive, within distance, and
                //closer than the existing target.
                if(dDistanceSquared <= dMaxDistance*dMaxDistance && 
                	dDistanceSquared < dCandidateDistanceSquared) {                   
                    
                    pcCandidate = kcShipVector.at(i);
    		        dCandidateDistanceSquared = dDistanceSquared;
                }
            }
        }
        
        return pcCandidate;
    }
    
    //--------------------------------------------------------------------------
    /**
    * Move the CShip towards it's target. It won't try to move forward if within
    * a certain distance and will accelerate if it should move. It will always
    * try to face the target. LATER MODIFY TO INCLUDE AVOIDING INCOMING FIRE,
    * HEAVENLY BODIES, AND OTHER SHIPS.
    */
    //--------------------------------------------------------------------------
    void CShip::StalkTarget(void) {
        GLdouble adTargetPos[3];
        GLdouble adDirection[3];
        
        GLdouble dTolerance = 0.001;
        GLdouble dDistanceSquared = 0;
        
        //Get the vector going from this ship to the target ship.
        for(int i = 0; i < 3; i++) {
            adTargetPos[i] = m_pcAiTarget->GetPos(i);
            adDirection[i] = adTargetPos[i] - m_adPos[i];
            dDistanceSquared += 
                (m_adPos[i]-adTargetPos[i])*(m_adPos[i]-adTargetPos[i]);
        }
        
        Normalize(adDirection);
        
        //If the direction is very close to the forward vector then don't 
        //bother rotating.
        GLdouble dAngle = RadToDeg(GetAngle(m_adForward, adDirection));
        if(dAngle > dTolerance) {
            //Get the axis of rotation.
            GLdouble adAxis[3];
            Cross(m_adForward, adDirection, adAxis);
            Normalize(adAxis);
            
            //Get the angle that will be rotated around the axis. The ship
            //can only rotate so far as dictated by its maneuverability.
            dAngle = min(dAngle, m_nManeuver*gkdRotateScale*50);
            GLdouble aadRotMatrix[4][4];
            AxisAngleToMatrix(adAxis, dAngle, aadRotMatrix);
            MatrixMultVector(aadRotMatrix, m_adForward);
            Normalize(m_adForward);
            MatrixMultVector(aadRotMatrix, m_adUp);
            Normalize(m_adUp);
            
            //Expend the energy needed to rotate.
            m_nEnergy--;
        }        
        
        //Get the maximum weapon range.
        GLdouble dWeaponRange = 0.0;
        for(int i = 0; i < gknMaxWeapons; i++) {
            if(m_apcWeapon[i] != NULL) {
                dWeaponRange = max(m_apcWeapon[i]->GetRange(),dWeaponRange);
            }
        }
        
        //Brake if well within the weapon range and speed > attack speed but 
        //if outside weapon range accelerate towards the target.
        GLdouble dAttackSpeed = m_dMaxSpeed / 2;
        if(dDistanceSquared < (dWeaponRange*0.75)*(dWeaponRange*0.75)) {
            if (m_dSpeed > dAttackSpeed) {
                Brake();
            }
        }
        else {
            Accelerate();
        }     
    }
    
    //--------------------------------------------------------------------------
    /**
    * Checks whether each this CShip is aimed at the target CShip. If it is
    * then it fires each weapon which is in 3/4 range.
    *
    * @par Acknowledgement The line-point distance algorithm is from
    *   http://mathworld.wolfram.com/Point-LineDistance3-Dimensional.html
    */
    //--------------------------------------------------------------------------
    void CShip::ShootTarget(void) {
        
        //The minimum distance between the shot and the target before the weapon
        //will be fired.
        GLdouble dTolerance = 0.01;
        
        //The distance between the ships.
        //GLdouble dShipDistance = 0.0;
        GLdouble dShipDistanceSquared = 0.0;
        
        //The vector going from the target ship to this ship.
        GLdouble adTargetToAi[3];
        
        GLdouble adTargetPos[3];
        for(int i = 0; i < 3; i++) {
            adTargetPos[i] = m_pcAiTarget->GetPos(i);
            dShipDistanceSquared +=
                (adTargetPos[i]-m_adPos[i])*(adTargetPos[i]-m_adPos[i]);
            adTargetToAi[i] = m_adPos[i] - adTargetPos[i];
        }
        
        //Go through each weapon and determine if it is within 3/4 range (so
        //if the target is moving away it can still be hit). If it is then
        //determine if this ship is aimed at the target.
        for(int i = 0; i < gknMaxWeapons; i++) {
            if(m_apcWeapon[i] != NULL) {
                if(dShipDistanceSquared <= 
                	(m_apcWeapon[i]->GetRange()*0.75)*
                	(m_apcWeapon[i]->GetRange()*0.75)) {
                    //Calculate the distance from the target to the weapon's
                    //shot's trajectory.
                    
                    //The vector describing the weapon's trajectory. When 
                    //mulitplied by a time scale of 0 <= t <= 1, t = 0 gives the
                    //origin of the shot and 1 gives the maximum range position.
                    GLdouble adTrajectory[3];
                    for(int j = 0; j < 3; j++) {
                        adTrajectory[j] = 
                            m_adForward[j]*m_apcWeapon[i]->GetRange();
                    }
                    
                    //The ship's position and the max range position form a line
                    //of the weapon's trajectory. Find the distance of the ship
                    //from this trajectory.
                    GLdouble adNumeratorVector[3];
                    Cross(adTrajectory, adTargetToAi, adNumeratorVector);
                    GLdouble dNumerator = 0.0;
                    GLdouble dDenominator = 0.0;                    
                    for(int j = 0; j < 3; j++) {
                        dNumerator += adNumeratorVector[j]*adNumeratorVector[j];
                        dDenominator += adTrajectory[j]*adTrajectory[j];
                    }                                   
                    dNumerator = sqrt(dNumerator);
                    dDenominator = sqrt(dDenominator);
                    
                    
                    //The minimum distance from the shot to the target.
                    GLdouble dShotDistance = dNumerator / dDenominator;
                    
                    if(dShotDistance <= dTolerance) {
                        Shoot(i, m_pcAiTarget);
                    }
                }
            }
        }
    }
    
    //--------------------------------------------------------------------------
    /**
    * Determine if there is a threatening CEntity by the distance between it
    * and this ship. In order of priority they are CHeavenlyBody, CShip, CShot.
    */
    //--------------------------------------------------------------------------
    CEntity* CShip::AnticipateCollison(const vector <CShip*>m_kcShipVector,  
        const vector <CShot*>m_kcShotVector,
        const vector <CHeavenlyBody*>m_kcHeavenlyBodyVector) {
            
        CEntity* pcEvade = NULL;
        GLdouble dEvadeDistanceSquared = 9999999999999999999999999.0;
        //Used to determine what is a safe distance from the CEntity.
        GLdouble dSafetyModifier;
        CEntity* pcCandidate;
        
        //Go through all the CHeavenlyBodies and find the closest threatening.
        dSafetyModifier = 0.7;
        for(int i = 0; i < m_kcHeavenlyBodyVector.size(); i++) {
            pcCandidate = m_kcHeavenlyBodyVector.at(i);
            
            //If the heavenly body not alive then do not bother with further
            //calculation, collision is impossible.
            if(pcCandidate->GetState() == gknAlive) {           
                //Determine the distance between the ship and heavenly body.
                GLdouble dDistanceSquared = 0.0;
                for(int j = 0; j < 3; j++) {
                    dDistanceSquared += (m_adPos[j]-pcCandidate->GetPos(j))*
                        (m_adPos[j]-pcCandidate->GetPos(j));
                }
                
                //If the distance is less than the safety margin and less than
                //any other candidate distance we have a better candidate.
                if(dDistanceSquared <= 
                    ( dSafetyModifier*(m_dScale+pcCandidate->GetScale())*
                    dSafetyModifier*(m_dScale+pcCandidate->GetScale()) ) &&
                    dDistanceSquared < dEvadeDistanceSquared) {
                    
                    pcEvade = pcCandidate;
                    dEvadeDistanceSquared = dDistanceSquared;
                }
            }
        }
        
        //If there is no threat so far then check through the ships.
        if(pcEvade == NULL) {
            //Go through all the CShips and find the closest threatening.
            dSafetyModifier = 0.75;
            
            for(int i = 0; i < m_kcShipVector.size(); i++) {
                pcCandidate = m_kcShipVector.at(i);
                
                //If the ship is alive and not this ship then process further.
                if(pcCandidate != this && pcCandidate->GetState() == gknAlive) {               
                    //Determine the distance between the ships.
                    GLdouble dDistanceSquared = 0.0;
                    for(int j = 0; j < 3; j++) {
                        dDistanceSquared += (m_adPos[j]-pcCandidate->GetPos(j))*
                            (m_adPos[j]-pcCandidate->GetPos(j));
                    }
                    
                    if(dDistanceSquared <= 
                    	(dSafetyModifier*(m_dScale+pcCandidate->GetScale())*
                    	dSafetyModifier*(m_dScale+pcCandidate->GetScale()) ) &&
                        dDistanceSquared < dEvadeDistanceSquared) {
                        
                        pcEvade = pcCandidate;
                        dEvadeDistanceSquared = dDistanceSquared;
                    }
                }
            }
            
            //If there is still no threat then check through the shots.
            if(pcEvade == NULL) {
                //Go through all the CShots and find the closest threatening.
                dSafetyModifier = 3.0;
                for(int i = 0; i < m_kcShotVector.size(); i++) {
                    CShot* pcShotCandidate = m_kcShotVector.at(i);
                    
                    //If this shot is alive and not fired by this ship process
                    //further.
                    if(pcShotCandidate->GetOrigin() != this && 
                        pcCandidate->GetState() == gknAlive) {
                    
                        //Determine the distance between the ship and the shot.
                        GLdouble dDistanceSquared = 0.0;
                        for(int j = 0; j < 3; j++) {
                            dDistanceSquared += 
                            	(m_adPos[j]-pcShotCandidate->GetPos(j))
                                *(m_adPos[j]-pcShotCandidate->GetPos(j));
                        }
                        
                        if(dDistanceSquared <= 
                        	( dSafetyModifier*
                        	(m_dScale+pcShotCandidate->GetScale())*
                        	dSafetyModifier*
                        	(m_dScale+pcShotCandidate->GetScale()) )&&
                            dDistanceSquared < dEvadeDistanceSquared) {
                            
                            pcEvade = pcShotCandidate;
                            dEvadeDistanceSquared = dDistanceSquared;
                        }
                    }
                }
            }
        }
                
        return pcEvade;   
    }
    
    //--------------------------------------------------------------------------
    /**
    * Evade the CEntity be deflecting the CShips' trajectory away from it.
    */
    //--------------------------------------------------------------------------
    void CShip::Evade(CEntity* pcThreat) {       
        //Get the vector from this ship to the threat.
        //Calculate the deflection vector, which will steer away from the
        //threat at the same time.
        GLdouble adDirection[3];
        GLdouble adDeflection[3];
        
        for(int i = 0; i < 3; i++) {
            adDirection[i] = pcThreat->GetPos(i) - m_adPos[i];
            adDeflection[i] = -adDirection[i];
        }
        
        Normalize(adDirection);        
        Normalize(adDeflection);
        
        //If the ship is facing the direction of the threat choose a random
        //angle to deflect at.
        GLdouble dTolerance = 1.0;
        if(RadToDeg(GetAngle(m_adForward, adDirection) < dTolerance)) {            
            srand((unsigned)time(0));
            GLdouble dAngle = DegToRad( ((GLdouble) (rand() % 360)) );
            ChangeDirection(dAngle, 1.0);
            
        }
        //Otherwise use the deflection vector to determine movement.
        else {
            //Get the axis of rotation.
            GLdouble adAxis[3];
            Cross(m_adForward, adDeflection, adAxis);
            Normalize(adAxis);
            
            //Get the angle that will be rotated around the axis. The ship
            //can only rotate so far as dictated by its maneuverability.
            GLdouble dAngle = RadToDeg(GetAngle(m_adForward, adDeflection));
            dAngle = min(dAngle, m_nManeuver*gkdRotateScale*50);
            GLdouble aadRotMatrix[4][4];
            AxisAngleToMatrix(adAxis, dAngle, aadRotMatrix);
            MatrixMultVector(aadRotMatrix, m_adForward);
            Normalize(m_adForward);
            MatrixMultVector(aadRotMatrix, m_adUp);
            Normalize(m_adUp);
            
            //Expend the energy needed to rotate.
            m_nEnergy--;
        }
    }
