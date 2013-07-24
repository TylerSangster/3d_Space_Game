//******************************************************************************
//CShot.cpp
//Copyright (C) 2007, Marcus Trenton, Tyler Sangster, and Sebastian Harko
//Originally written for Total Space Massacre, a project for CS 432 on 
//February 21th, 2007.
//******************************************************************************

#include <math.h>
#include <GL/glut.h>
#include <cstdlib>
#include "CShot.h"

using namespace std;

//##############################################################################
/**
* @class CShot CShot.h
*
* Class Shot is responsible for holding data relevant as to how far, how
* much damage it can do, is homing, and can in detonate on the laucher. It 
* should still be considered an abstract class still it still doesn't know what
* to draw and its bounding box.
*
* @author Marcus Trenton and Tyler Sangster
* @date Mon 19 Feb
* @version 1.0
*/
//##############################################################################
	
	//--------------------------------------------------------------------------
	/**
    * The Entity constructor will handle the physical location variables.
    * This simple needs to record the target (a CEntity or NULL) and initialize
    * some variables.
    *
    * @see CEntity::CEntity
    */
    //--------------------------------------------------------------------------
	CShot::CShot(GLdouble const akdPos[3], GLdouble const akdForward[3],
        GLdouble const akdUp[3], const GLdouble kdSpeed, const int knFirepower, 
        const GLdouble kdRange, const bool kbHoming, 
        const bool kbDetonateOnShooter, CEntity* const pkcTarget, 
        CEntity* const pkcOrigin) :
		CEntity(akdPos, akdForward, akdUp, kdSpeed), m_nFirepower(knFirepower), 
        m_dRange(kdRange), m_bHoming(kbHoming), 
        m_bDetonateOnShooter(kbDetonateOnShooter), m_pcTarget(pkcTarget), 
        m_pcOrigin(pkcOrigin) {
        		
		ClearNewShots();		
		m_dDistance = 0;		
	}
	
	//--------------------------------------------------------------------------
	/**
    * Clears the data structure of shots created in the last game cycle from
    * this CShot.
    */
    //--------------------------------------------------------------------------
	void CShot::ClearNewShots(void) {
		m_cNewShotVector.clear();
	}
	
	//--------------------------------------------------------------------------
	/**
    * Updates the shot by recording how far it has gone against it range. If
    * the projectile is homing it also adjusts its forward vector to move 
    * toward the target.
    * Also calls upon the CEntity parent to do the actual moving.
    *
    * @see CEntity::Update
    */
    //--------------------------------------------------------------------------
	void CShot::Update(void) {       
        
        //Only update if the CShot isn't dead
        if(m_nState == gknAlive) {
        
            if(m_dDistance < m_dRange) {            
                m_dDistance += m_dSpeed;
            }
            else {
                m_nState = gknDead;
            }
            
            //If the CShot is homing then home in on the target.
            if(m_bHoming && m_pcTarget != NULL) {
                GLdouble adTargetPos[3];
                GLdouble adDirection[3];
                
                GLdouble dTolerance = 0.001;
                
                //Get the vector going from this ship to the target ship.
                for(int i = 0; i < 3; i++) {
                    adTargetPos[i] = m_pcTarget->GetPos(i);
                    adDirection[i] = adTargetPos[i] - m_adPos[i];
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
                    
                    //Get the angle that will be rotated around the axis. 
                    //The ship can only rotate so far as dictated by dMaxTurn.
                    GLdouble dMaxTurn = 0.3;
                    dAngle = min(dAngle, dMaxTurn);
                    GLdouble aadRotMatrix[4][4];
                    AxisAngleToMatrix(adAxis, dAngle, aadRotMatrix);
                    MatrixMultVector(aadRotMatrix, m_adForward);
                    Normalize(m_adForward);
                    MatrixMultVector(aadRotMatrix, m_adUp);
                    Normalize(m_adUp);
                }                  
            }
        }
        
        CEntity::Update();               
    }
    
    //--------------------------------------------------------------------------
    /**
    * Determines whether a CShot collided with a CEntity taking into account
    * whether it is supposed to detonate onto the CEntity that lauched it.
    * This is used to prevent proximity rockets from detonating on the ship that
    * launched it.
    */
    //--------------------------------------------------------------------------		
    bool CShot::IsCollision(CEntity* const pkcOtherEntity) {
        bool bResult = false;
        
        if(m_bDetonateOnShooter || pkcOtherEntity != m_pcOrigin) {
            bResult = CEntity::IsCollision(pkcOtherEntity);
        }
        return bResult;
    }
