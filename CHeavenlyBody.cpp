//******************************************************************************
//CHeavenlyBody.cpp
//Copyright (C) 2007, Marcus Trenton, Tyler Sangster, and Sebastian Harko
//Originally written for Total Space Massacre, a project for CS 432 on 
//February 21th, 2007.
//******************************************************************************

#include "GL/glut.h"
#include "CHeavenlyBody.h"

using namespace std;

//##############################################################################
/**
* @class CHeavenlyBody CHeavenlyBody.h
* CHeavenlyBody represents things like planets, suns, and asteroids. It has an
* altered collision detection algorithm since heavenly bodies are spheres. 
* This class is still abstract from a practical point of view since it still 
* doesn't know what to draw, what its radius, damage, health, and whether it's
* invulnerable. All of its subclasses should be concrete, instantiable classes.
*
* @author Tyler Sangster
* @date 11/03/2007
* @version 1.0
*
* @par Acknowledgements The box-sphere collision algorithm is taken from 
*   www.ics.uci.edu/~arvo/code/BoxSphereIntersect.c
*/
//##############################################################################

    //--------------------------------------------------------------------------
	/**
    * The constructor stores the variables taken in and sets of the others to
    * defaults, to be meaningfully overwritten by subclasses.
    *
    * @see CEntity::CEntity, CommonConstructor
    */
    //--------------------------------------------------------------------------
    CHeavenlyBody::CHeavenlyBody(GLdouble const akdPos[3], 
        GLdouble const akdForward[3], GLdouble const akdUp[3], 
        const GLdouble kdSpeed) : CEntity(akdPos, akdForward, akdUp, kdSpeed) {
           
        CommonConstructor();   
    }
    
    //--------------------------------------------------------------------------
    /**
    * Minimal specification constructor for stationary CHeavenlyBodies.
    *
    * @see CommonConstructor
    */
    //--------------------------------------------------------------------------
    CHeavenlyBody::CHeavenlyBody(GLdouble const akdPos[3]) : CEntity() {
        for(int i = 0; i < 3; i++) {
            m_adPos[i] = akdPos[i];
        }
        
        CommonConstructor();
    }
    
    //--------------------------------------------------------------------------
    /**
    * Uses a modified and simplified version of Jim Arvo's "A Simple Method for 
    * Box-Sphere Intersection Testing", in "Graphics Gems", Academic Press, 
    * 1990 to perform collision detection between the sphericial CHeavenlyBody
    * and all other CEntities, which are boxes. The original code was found at
    * www.ics.uci.edu/~arvo/code/BoxSphereIntersect.c
    */
    //--------------------------------------------------------------------------		
	bool CHeavenlyBody::IsCollision(CEntity* const pkcOtherEntity) {
        //Perform the same initial checks are the parent method (distance and
        //whether each CEntity is alive).
        bool bResult = false;
        
        //Collisions are only possible if both CEntities are alive.
        if(m_nState == gknAlive && pkcOtherEntity->GetState() == gknAlive) {
            //Do a distance calculation to determine if the ships are
            //potentially close enough to collide.
            
            //The centre of the other CEntity.
            GLdouble adOtherPos[3];
            for(int i = 0; i < 3; i++) {
                adOtherPos[i] = pkcOtherEntity->GetPos(i);
            }
            
            //Calculate the distance between the CEntities.
            GLdouble dDistanceSquared = 
            	DistanceSquared(m_adPos, adOtherPos);
            
            //If that distance is greater than the combined sizes of both CEntities
            //then the CEntities are too far away for a collision.
            //Scale is the diameter.
            if(dDistanceSquared <= 
            	(m_dScale + pkcOtherEntity->GetScale())*
            	(m_dScale + pkcOtherEntity->GetScale())) {
                
                //If the other CEntity is a CHeavenlyBody then it is a sphere
                //and there is a collision.
                CHeavenlyBody* pcBody = 
                    dynamic_cast<CHeavenlyBody*>(pkcOtherEntity);
                if(pcBody != NULL) {
                    if(dDistanceSquared <= 
                    	(m_dScale/2 + pkcOtherEntity->GetScale()/2)*
                    	(m_dScale/2 + pkcOtherEntity->GetScale()/2) ) {
                    	
                    		bResult = true;	
                    	}
                }
                else {
                
                    //Rotate the other CEntity so that is axis-aligned and 
                    //translate it so it is at the origin. Perform the same 
                    //rotation on the CHeavenlyBody and then use Jim Arvo's 
                    //algorithm.
                    GLdouble adOtherForward[3];
                    GLdouble adOtherUp[3];
                    GLdouble adBaseForward[3] = {0.0, 0.0, 1.0};
                    GLdouble adBaseUp[3] = {0.0, 1.0, 0.0};
                    GLdouble adOtherBox[3];
                    for(int i = 0; i < 3; i++) {
                        adOtherForward[i] = pkcOtherEntity->GetForward(i);
                        adOtherUp[i] = pkcOtherEntity->GetUp(i);
                        adOtherBox[i] = pkcOtherEntity->GetBox(i);
                    }
                
                    //The transformed centre for the sphere.
                    GLdouble adTransformedPoint[4] = {0.0, 0.0, 0.0, 1.0};
                    GLdouble aadRotMatrix[4][4];                
                    GetRotMatrix(adOtherForward, adOtherUp, adBaseForward, 
                        adBaseUp,aadRotMatrix);
                
                    //Transform the other CEntity to the origin (conceptually 
                    //only) and move the CHeavenlyBody with it.
                    for(int i = 0; i < 3; i++) {
                        adTransformedPoint[i] =  m_adPos[i] - adOtherPos[i];
                    }
                    //Rotate to have the width, height, and length axes align 
                    //with the X, Y, and Z axes respectively.
                    MatrixMultVector(aadRotMatrix, adTransformedPoint);

                    //Jim Arvo's algorithm.
                    GLdouble dDmin = 0;
                    for(int i = 0; i < 3; i++ ) {
                        if(adTransformedPoint[i] < -adOtherBox[i]/2) {
                            dDmin += (adTransformedPoint[i] + adOtherBox[i]/2)*
                                (adTransformedPoint[i] + adOtherBox[i]/2);
                        } 
                        else {
                            if( adTransformedPoint[i] > adOtherBox[i]/2 ) { 
                                dDmin += (
                                    adTransformedPoint[i] - adOtherBox[i]/2)*
                                    (adTransformedPoint[i] - adOtherBox[i]/2);
                            }
                        }
                    }
                    if( dDmin <= (m_dScale/2)*(m_dScale/2) ) {
                        bResult = true;
                    }
                }
            }
        }
        return bResult;
    }

    //--------------------------------------------------------------------------
    /**
    * The heavenly body takes the given amount of damage if it not invulnerable.
    * Damage taken is subtracted off of health. If health becomes <= 0 the
    * heavenly body dies.
    */
    //--------------------------------------------------------------------------		
	void CHeavenlyBody::TakeDamage(const int knDamage) {
        if(!m_bInvulnerable) {
            m_nHealth -= knDamage;
            if(m_nHealth <= 0) {
                Die();
            }
        }
    }
    
    //--------------------------------------------------------------------------
    /**
    * The body takes damage from the CShot and the CShot is told to start dying.
    */
    //--------------------------------------------------------------------------
    void CHeavenlyBody::ResolveCollision(CShot* pcProjectile) {
        TakeDamage(pcProjectile->GetFirepower());
        pcProjectile->Die();       
    }
    
    //--------------------------------------------------------------------------
    /**
    * In a collision between 2 CHeavenlyBodies both CHeavenlyBodies take damage.
    */
    //--------------------------------------------------------------------------
    void CHeavenlyBody::ResolveCollision(CHeavenlyBody* pcBody) {        
        TakeDamage(pcBody->GetDamage());
        pcBody->TakeDamage(m_nDamage);
    }
