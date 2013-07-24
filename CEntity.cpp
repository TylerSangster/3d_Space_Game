//******************************************************************************
//CEntity.cpp
//Copyright (C) 2007, Marcus Trenton, Tyler Sangster, and Sebastian Harko
//Originally written for Total Space Massacre, a project for CS 432 on 
//February 21th, 2007.
//******************************************************************************

#include <math.h>
#include <GL/glut.h>
#include "CEntity.h"

using namespace std;

//##############################################################################
/**
* @class CEntity CEntity.h
* CEntity is the base class for all physical things. Ships, weapons, and shots
* for example, are subclasses. CEntity holds the information these classes have
* in common, such as a a position, facing, bounding box, and the 
* capability to move. CEntity also knows how to move and draw itself. Basic
* collision detection is also done by this class. It is considered an abstract 
* class, the class is incomplete in that although it know how to draw and it 
* knows not what to draw, what its bounding box is, and what its scale is.
*
* @author Marcus Trenton and Tyler Sangster
* @date 01/03/2007
* @version 1.0
*/
//##############################################################################

	//--------------------------------------------------------------------------
    /**
    * Sets the position, rotation, and speed to be 0. Calls the common
    * constructor to perform more construction.
    *
    * @see CommonConstructor
    */
    //--------------------------------------------------------------------------
	CEntity::CEntity() {		
		m_adPos[gknX] = 0.0;
        m_adPos[gknY] = 0.0;
        m_adPos[gknZ] = 0.0;
        
        m_adForward[gknX] = 0.0;
        m_adForward[gknY] = 0.0;
        m_adForward[gknZ] = 1.0;
        
        m_adUp[gknX] = 0.0;
        m_adUp[gknY] = 1.0;
        m_adUp[gknZ] = 0.0;
        
        m_dSpeed = 0;
        
        CommonConstructor();
	}

    //--------------------------------------------------------------------------
    /**
    * Sets the position, rotation, and speed to the given parameters. 
    * Calls the common constructor to perform more construction.
    *
    * @see CommonConstructor
    */
    //--------------------------------------------------------------------------
    CEntity::CEntity(GLdouble const akdPos[3], GLdouble const akdForward[3], 
            GLdouble const akdUp[3], const GLdouble kdSpeed) : 
            m_dSpeed(kdSpeed) {
        
        m_adPos[gknX] = akdPos[gknX];
        m_adPos[gknY] = akdPos[gknY];
        m_adPos[gknZ] = akdPos[gknZ];
        
        m_adForward[gknX] = akdForward[gknX];
        m_adForward[gknY] = akdForward[gknY];
        m_adForward[gknZ] = akdForward[gknZ];
        
        m_adUp[gknX] = akdUp[gknX];
        m_adUp[gknY] = akdUp[gknY];
        m_adUp[gknZ] = akdUp[gknZ];
        
        CommonConstructor();               
    }
    
    //--------------------------------------------------------------------------
    /**
    * Whether this CEntity and another have collided. The algorithm uses 
    * rectangular bounding boxes to determine if a collision has occurred.
    *
    * @warning This method should be called from the object that has the 
    *   potential to do the damage, like the planet or shot. That way the method
    *   can be overwritten to allow for no collision in the case of mines 
    *   against the layers or proximity rockets against the launcher.
    */
    //--------------------------------------------------------------------------
	bool CEntity::IsCollision(CEntity* const pkcOtherEntity) {
        bool bResult = false;
        
        //Both CEntities must be alive for a collision is possible.
        if(m_nState == gknAlive && pkcOtherEntity->GetState() == gknAlive) {
            //Do a distance calculation to determine if the ships are
            //potentially close enough to collide.
            
            //The centre of the other CEntity.
            GLdouble adOtherPos[3];
            for(int i = 0; i < 3; i++) {
                adOtherPos[i] = pkcOtherEntity->GetPos(i);
            }
            
            //Calculate the distance between the CEntities.
            GLdouble dDistanceSquared = DistanceSquared(m_adPos, adOtherPos);
            
            //If that distance is greater than the combined sizes of both 
            //CEntities then the CEntities are too far away for a collision.
            //Scale is the diameter.
            if(dDistanceSquared*dDistanceSquared <= 
            	(m_dScale + pkcOtherEntity->GetScale())*
            	(m_dScale + pkcOtherEntity->GetScale())) {  
                    
                //This algorithm works by finding the 8 bounding points for the
                //either entities' bounding box. It translates one to be axes-
                //aligned and centered on the origin, where collisions are much
                //easier to detect. If the other entity's bounding points are 
                //inside the bounding box then there is a collision. The same
                //is procedure is then done for the other entity. This is not
                //a perfect algorithm but it works well enough.
                                              
                //Get all 8 bounding points for each CEntity.
                GLdouble aadE1BP[8][3];
                GLdouble aadE2BP[8][3];
                
                GLdouble adE1Right[3];
                Cross(m_adForward, m_adUp, adE1Right);
                Normalize(adE1Right);
                
                //Calculate all of the points that form the bounding box for the
                //first CEntity.
                aadE1BP[0][gknX] = m_adPos[gknX] 
                   + m_adBox[gknW]/2*adE1Right[gknX];
                aadE1BP[0][gknY] = m_adPos[gknY] 
                   + m_adBox[gknH]/2*m_adUp[gknY];
                aadE1BP[0][gknZ] = m_adPos[gknZ] 
                    + m_adBox[gknL]/2*m_adForward[gknZ];
                aadE1BP[1][gknX] = m_adPos[gknX] 
                    + m_adBox[gknW]/2*adE1Right[gknX];
                aadE1BP[1][gknY] = m_adPos[gknY] 
                    + m_adBox[gknH]/2*m_adUp[gknY];
                aadE1BP[1][gknZ] = m_adPos[gknZ] 
                    - m_adBox[gknL]/2*m_adForward[gknZ];           
                aadE1BP[2][gknX] = m_adPos[gknX] 
                    - m_adBox[gknW]/2*adE1Right[gknX];
                aadE1BP[2][gknY] = m_adPos[gknY] 
                    + m_adBox[gknH]/2*m_adUp[gknY];
                aadE1BP[2][gknZ] = m_adPos[gknZ] 
                    - m_adBox[gknL]/2*m_adForward[gknZ];
                aadE1BP[3][gknX] = m_adPos[gknX] 
                    - m_adBox[gknW]/2*adE1Right[gknX];
                aadE1BP[3][gknY] = m_adPos[gknY] 
                    + m_adBox[gknH]/2*m_adUp[gknY];
                aadE1BP[3][gknZ] = m_adPos[gknZ] 
                    + m_adBox[gknL]/2*m_adForward[gknZ];
                aadE1BP[4][gknX] = m_adPos[gknX] 
                    + m_adBox[gknW]/2*adE1Right[gknX];
                aadE1BP[4][gknY] = m_adPos[gknY] 
                    - m_adBox[gknH]/2*m_adUp[gknY];
                aadE1BP[4][gknZ] = m_adPos[gknZ] 
                    + m_adBox[gknL]/2*m_adForward[gknZ]; 
                aadE1BP[5][gknX] = m_adPos[gknX] 
                    + m_adBox[gknW]/2*adE1Right[gknX];
                aadE1BP[5][gknY] = m_adPos[gknY] 
                    - m_adBox[gknH]/2*m_adUp[gknY];
                aadE1BP[5][gknZ] = m_adPos[gknZ] 
                    - m_adBox[gknL]/2*m_adForward[gknZ];
                aadE1BP[6][gknX] = m_adPos[gknX] 
                    - m_adBox[gknW]/2*adE1Right[gknX];
                aadE1BP[6][gknY] = m_adPos[gknY] 
                    - m_adBox[gknH]/2*m_adUp[gknY];
                aadE1BP[6][gknZ] = m_adPos[gknZ] 
                    - m_adBox[gknL]/2*m_adForward[gknZ];
                aadE1BP[7][gknX] = m_adPos[gknX] 
                    - m_adBox[gknW]/2*adE1Right[gknX];
                aadE1BP[7][gknY] = m_adPos[gknY] 
                    - m_adBox[gknH]/2*m_adUp[gknY];
                aadE1BP[7][gknZ] = m_adPos[gknZ] 
                    + m_adBox[gknL]/2*m_adForward[gknZ];
                
                //Get the bounding points for the other entity.
                GLdouble adE2Forward[3];
                GLdouble adE2Up[3];
                GLdouble adE2Right[3];
                GLdouble adOtherBox[3];
                for(int i = 0; i < 3; i++) {
                    adE2Forward[i] = pkcOtherEntity->GetForward(i);
                    adE2Up[i] = pkcOtherEntity->GetUp(i);
                    adOtherBox[i] = pkcOtherEntity->GetBox(i);
                }
                Cross(adE2Forward, adE2Up, adE2Right);
                Normalize(adE2Right);
                
                //Calculate all of the points that form the bounding box for the
                //second CEntity.
                aadE2BP[0][gknX] = adOtherPos[gknX] 
                    + adOtherBox[gknW]/2*adE2Right[gknX];
                aadE2BP[0][gknY] = adOtherPos[gknY] 
                    + adOtherBox[gknH]/2*adE2Up[gknY];
                aadE2BP[0][gknZ] = adOtherPos[gknZ] 
                    + adOtherBox[gknL]/2*adE2Forward[gknZ];
                aadE2BP[1][gknX] = adOtherPos[gknX] 
                    + adOtherBox[gknW]/2*adE2Right[gknX];
                aadE2BP[1][gknY] = adOtherPos[gknY] 
                    + adOtherBox[gknH]/2*adE2Up[gknY];
                aadE2BP[1][gknZ] = adOtherPos[gknZ] 
                    - adOtherBox[gknL]/2*adE2Forward[gknZ];           
                aadE2BP[2][gknX] = adOtherPos[gknX] 
                    - adOtherBox[gknW]/2*adE2Right[gknX];
                aadE2BP[2][gknY] = adOtherPos[gknY] 
                    + adOtherBox[gknH]/2*adE2Up[gknY];
                aadE2BP[2][gknZ] = adOtherPos[gknZ] 
                    - adOtherBox[gknL]/2*adE2Forward[gknZ];
                aadE2BP[3][gknX] = adOtherPos[gknX] 
                    - adOtherBox[gknW]/2*adE2Right[gknX];
                aadE2BP[3][gknY] = adOtherPos[gknY] 
                    + adOtherBox[gknH]/2*adE2Up[gknY];
                aadE2BP[3][gknZ] = adOtherPos[gknZ] 
                    + adOtherBox[gknL]/2*adE2Forward[gknZ];
                aadE2BP[4][gknX] = adOtherPos[gknX] 
                    + adOtherBox[gknW]/2*adE2Right[gknX];
                aadE2BP[4][gknY] = adOtherPos[gknY] 
                    - adOtherBox[gknH]/2*adE2Up[gknY];
                aadE2BP[4][gknZ] = adOtherPos[gknZ] 
                    + adOtherBox[gknL]/2*adE2Forward[gknZ]; 
                aadE2BP[5][gknX] = adOtherPos[gknX] 
                    + adOtherBox[gknW]/2*adE2Right[gknX];
                aadE2BP[5][gknY] = adOtherPos[gknY] 
                    - adOtherBox[gknH]/2*adE2Up[gknY];
                aadE2BP[5][gknZ] = adOtherPos[gknZ] 
                    - adOtherBox[gknL]/2*adE2Forward[gknZ];
                aadE2BP[6][gknX] = adOtherPos[gknX] 
                    - adOtherBox[gknW]/2*adE2Right[gknX];
                aadE2BP[6][gknY] = adOtherPos[gknY] 
                    - adOtherBox[gknH]/2*adE2Up[gknY];
                aadE2BP[6][gknZ] = adOtherPos[gknZ] 
                    - adOtherBox[gknL]/2*adE2Forward[gknZ];
                aadE2BP[7][gknX] = adOtherPos[gknX] 
                    - adOtherBox[gknW]/2*adE2Right[gknX];
                aadE2BP[7][gknY] = adOtherPos[gknY] 
                    - adOtherBox[gknH]/2*adE2Up[gknY];
                aadE2BP[7][gknZ] = adOtherPos[gknZ] 
                    + adOtherBox[gknL]/2*adE2Forward[gknZ];
                            
                //Conceptually rotate and translate to get the first CEntity 
                //back to the origin, where it has a easy to check bounding box 
                //and do the same translations to the other CEntity. Check 
                //whether any of other's points are inside the first. The
                //actual rotations and translations do not have to be performed
                //on the first CEntity since we already know what the resulting
                //points will be.
                GLdouble adTransformedPoint[4] = {0.0, 0.0, 0.0, 1.0};
                GLdouble aadRotMatrix[4][4];
                GLdouble adBaseForward[3] = {0.0, 0.0, 1.0};
                GLdouble adBaseUp[3] = {0.0, 1.0, 0.0};
                GetRotMatrix(m_adForward, m_adUp, adBaseForward, adBaseUp, 
                    aadRotMatrix);
                                
                for(int i = 0; i < 8 && !bResult; i++) {
                    //Transform to the origin.
                    for(int j = 0; j < 3; j++) {
                        adTransformedPoint[j] = aadE2BP[i][j] - m_adPos[j];
                    }
                    //Rotate to have the width, height, and length axes align with
                    //the X, Y, and Z axes respectively.
                    MatrixMultVector(aadRotMatrix, adTransformedPoint);
                    //Check whether the point is in the first CEntity's bounding 
                    //box.
                    if(adTransformedPoint[gknX] <= m_adBox[gknW]/2 &&
                        adTransformedPoint[gknX] >= - m_adBox[gknW]/2 &&
                        adTransformedPoint[gknY] <=  m_adBox[gknH]/2 &&
                        adTransformedPoint[gknY] >= -  m_adBox[gknH]/2 &&
                        adTransformedPoint[gknZ] <=  m_adBox[gknL]/2 &&
                        adTransformedPoint[gknZ] >= - m_adBox[gknL]/2 ) {
                        bResult = true;
                    }
                }
                
                if(!bResult) {
                    //Now conceptually rotate the second CEntity and check whether 
                    //the first is in the bounding box.
                    GetRotMatrix(adE2Forward, adE2Up, adBaseForward, adBaseUp,
                        aadRotMatrix);
                    
                    for(int i = 0; i < 8 && !bResult; i++) {
                        //Transform to the origin.
                        for(int j = 0; j < 3; j++) {
                            adTransformedPoint[j] =aadE1BP[i][j] - adOtherPos[j];
                        }
                        //Rotate to have the width, height, and length axes 
                        //align with the X, Y, and Z axes respectively.
                        MatrixMultVector(aadRotMatrix, adTransformedPoint);
                        //Check whether the point is in the first CEntity's 
                        //bounding box.
                        if(adTransformedPoint[gknX] <= adOtherBox[gknW]/2 &&
                            adTransformedPoint[gknX] >= - adOtherBox[gknW]/2 &&
                            adTransformedPoint[gknY] <= adOtherBox[gknH]/2 &&
                            adTransformedPoint[gknY] >= - adOtherBox[gknH]/2 &&
                            adTransformedPoint[gknZ] <= adOtherBox[gknL]/2 &&
                            adTransformedPoint[gknZ] >= - adOtherBox[gknL]/2 ) {
                            bResult = true;
                        }
                    }
                }
            }
        }      

		return bResult;		
	}
	
    //--------------------------------------------------------------------------
    /**
    * Tells the CEntity that it is now dying. The CEntity changes its state
    * to dying. In the Update method after so many game cycles the CEntity 
    * becomes dead.
    *
    * @see Update
    */
    //--------------------------------------------------------------------------
    void CEntity::Die(void) {
        m_nState = gknDying;
    }
    
    //--------------------------------------------------------------------------
    /**
    * Updates the movement of the CEntity by moving forward by its speed
    * along its forwawrd vector. The entity should not update if it's dead. 
    * Also counts how many cycles the entity has been dying and switches it
    * to dead when enough have past.
    */
    //--------------------------------------------------------------------------
    void CEntity::Update() {

	//If the CEntity is alive then move it.       
    	if(m_nState == gknAlive) {                        
            //Scale by speed and move the ship.
            for(int i = 0; i < 3; i++) {
                m_adPos[i] += m_dSpeed*m_adForward[i];
            }
    	}

    	//If the CEntity is dying then increase it size. This gives the effect 
        //of exploding.
    	if(m_nState == gknDying && m_nDyingCounter <= gknDyingDuration) {
    		m_dScale *= gkdDyingScale;
    		m_nDyingCounter++;
    
    		//If the dying is complete then the CEntity is dead.
    		if(m_nDyingCounter == gknDyingDuration) {
    			m_nState = gknDead;
    		}
    	}
    }
    
    //--------------------------------------------------------------------------
    /**
    * Draws the given object by calling the appropriate display list and then
    * rotating and scaling as needed. It assumes OpenGL is ready for drawing.
    */
    //--------------------------------------------------------------------------
    void CEntity::Draw(void) {   	      
        //Only bother with method if the display list is defined and the
        //CEntity is not dead.
        if(m_nState != gknDead) {
            //Only draw the entity is the display has been defined.
        	if(m_anDisplayId[m_nState] != gknUndefined) {    	
	            //Push the previous data.
	            glPushAttrib(GL_ALL_ATTRIB_BITS);
	            glPushMatrix();
	            
	            //Scale, rotate, and translate.
	            glTranslated(m_adPos[gknX], m_adPos[gknY], m_adPos[gknZ]);
	            
	            //Get the rotational matrix.
                GLdouble adBaseForward[3] = {0.0, 0.0, 1.0};
                GLdouble adBaseUp[3] = {0.0, 1.0, 0.0};	            
	            GLdouble aadRotMatrix[4][4];
	            GetRotMatrix(adBaseForward, adBaseUp, m_adForward, m_adUp,
                    aadRotMatrix);
	            
	            //Turn it into the array format OpenGL wants.
	            GLdouble adRotArray[16];
	            for(int i = 0; i < 4; i++) {
                    for(int j = 0; j < 4; j++) {
                        adRotArray[4*j+i] = aadRotMatrix[i][j];
                    }
                }
                
                //Do the rotation.
                glMultMatrixd(adRotArray);
	            
	            glScaled(m_dScale, m_dScale, m_dScale);
	            
	            //Call the display list
	            glCallList(m_anDisplayId[m_nState]);
	            
	            //Pop the previous data.
	            glPopAttrib();
	            glPopMatrix();
        	}           
        }       
    }
