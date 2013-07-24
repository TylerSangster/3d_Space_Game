//******************************************************************************
//CWeapon.cpp
//Copyright (C) 2007, Marcus Trenton, Tyler Sangster, and Sebastian Harko
//Originally written for Total Space Massacre, a project for CS 432 on 
//February 21th, 2007.
//******************************************************************************

#include <math.h>
#include <cstdlib>
#include "CWeapon.h"

using namespace std;

//##############################################################################
/**
* @class CWeapon CWeapon.h
*
* Class Weapon is responsible for creating the statistics (they will be defined
* by subclasses) and the generic procedure for shooting and creating shots. It
* should still be considered an abstract class still it still can't draw itself
* and doesn't know what type of CShots to create (among other little details).
*
* @author Tyler Sangster
* @date Mon 19 Feb
* @version 1.0
*/
//##############################################################################

	//--------------------------------------------------------------------------
	/**
    * The CWeapon is created on board of an entity. The CEntity constructor
    * will handle the physical location and orientation variables.
    *
    * @see CEntity::CEntity, CommonConstructor
    */
    //--------------------------------------------------------------------------
    CWeapon::CWeapon(CEntity* const pkcHost) : CEntity(), m_pcHost(pkcHost) {
    	CommonConstructor();
    }
    
    //--------------------------------------------------------------------------
    /**
    * The weapon is free-floating. The Entity constructor will handle the 
    * physical location variables.
    *
    * @see CEntity::CEntity
    */
    //--------------------------------------------------------------------------
    CWeapon::CWeapon(GLdouble const akdPos[3], GLdouble const akdForward[3],
        GLdouble const akdUp[3], const GLdouble kdSpeed) : 
        CEntity(akdPos, akdForward, akdUp, kdSpeed) {
    	
    	m_pcHost = NULL;
    	CommonConstructor();
    }
    
    //--------------------------------------------------------------------------
    /**  
    * Handles creation that is present in both constructors.
    *
    * @see CWeapon
    */
    //--------------------------------------------------------------------------
    void CWeapon::CommonConstructor(void) {    
        m_nCoolDownTime = 9999;
    	ClearNewShots();
    	
    	//Overwritten by subclasses.		
		m_nFirepower = gknUndefined;           
		m_nRate = gknUndefined;         
		m_dRange = gknUndefined;
		m_nEnergy = gknUndefined;
		m_dShotSpeed = gknUndefined;
    }
        
    //--------------------------------------------------------------------------
    /**
    * Is the weapon ready to fire? It is only ready if it's onboard a ship
    * and its cooled-down time is greater than the rate of fire.
    */
    //--------------------------------------------------------------------------
    bool CWeapon::ReadyToFire(void) {
        return m_pcHost != NULL &&  m_nCoolDownTime >= m_nRate;
    }
    
    //--------------------------------------------------------------------------
    /**
    * Attempts to shoot the CWeapon. It first checks whether the CWeapon is 
    * ready to fire and if it is then create the shots.
    */
    //--------------------------------------------------------------------------
    bool CWeapon::Shoot(CEntity* const pkcTarget, const GLdouble kdOffset) {
        bool bFired = false;    	
    	
    	if(ReadyToFire()) {	
			//The shot is to be created outside the host entity, facing in the 
            //same direction, which means it is created using the host's frame
            //of reference. This retrieves the host's frame of reference.
			GLdouble adForward[3];
			GLdouble adUp[3];
			for(int i = 0; i < 3; i++) {
                adForward[i] = m_pcHost->GetForward(i);
                adUp[i] = m_pcHost->GetUp(i);
            }
			
            //The Forward, Up, and Right directions and the base position start			
            //off by treating the ship as being a 1 unit cube centered on the
        	//origin facing up the Z axis with no roll and later do all the 
            //rotations, translations, and scaling needed to produce the 
            //correct vectors and position.
            
            //Have different weapons produce shots originating from different 
            //positions on the ship.
            GLdouble adBasePos[4] = {kdOffset, 0.0, 1.0, 1.0};
            GLdouble adBaseForward[3] = {0.0, 0.0, 1.0};
            GLdouble adBaseUp[3] = {0.0, 1.0, 0.0};
            
            //Scale the positions.
            for(int i = 0; i < 3; i++) {
                adBasePos[i] *= m_pcHost->GetBox(i);
            }
            
            //Rotate all of those vectors and locations to face the correct way.
            GLdouble aadRotMatrix[4][4];       
            GetRotMatrix(adBaseForward, adBaseUp, adForward, adUp,aadRotMatrix);
            MatrixMultVector(aadRotMatrix, adBasePos);
            GLdouble adRight[3];
            Cross(adForward, adUp, adRight);
            Normalize(adRight);
            
            //Translate the base location.
            for(int i = 0; i < 3; i++) {
                adBasePos[i] += m_pcHost->GetPos(i); //Translate
            }
			
			//LATER DEAL WITH POWERUPS
			CreateShots(adBasePos, adForward, adUp, adRight, m_dShotSpeed, 
                m_nFirepower, m_dRange, pkcTarget);			
				
 			bFired = true;
            m_nCoolDownTime = 0;		
    	} 
    	return bFired;	
    }
    
    //--------------------------------------------------------------------------
    /**
	* Clears the data structure holding the newly created CShots.
	*/
	//--------------------------------------------------------------------------
	void CWeapon::ClearNewShots(void) {
        m_cNewShotVector.clear();		
	}
	
	//--------------------------------------------------------------------------
	/**
	* Updates the weapon. If it is onboard a ship then there is no need to
	* update its location. In all cases its cool-down time is increased, if
	* needed.
	*
	* @see CEntity::Update
	*/
	//--------------------------------------------------------------------------
	void CWeapon::Update(void) {        
        //Only update if the CWeapon isn't dead
        if(m_nState == gknAlive) {
		  //No point incrementing the cool-down time if the weapon has had 
          //enough time to fire again.
		  if(m_nCoolDownTime < m_nRate) {
		      	m_nCoolDownTime++;					
		  }
        }
        
		if(m_pcHost == NULL) {
			CEntity::Update();			
		}
	}
	
	//--------------------------------------------------------------------------
	/**
	* Draws the weapon only if it is free-floating.
	*
	* @see CEntity::Draw
	*/
	//--------------------------------------------------------------------------
	void CWeapon::Draw(void) {        
		if(m_pcHost == NULL) {
			CEntity::Draw();	
		}	
	}
