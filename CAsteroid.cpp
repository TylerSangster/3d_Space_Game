//******************************************************************************
//CAsteroid.cpp
//Copyright (C) 2007, Marcus Trenton, Tyler Sangster, and Sebastian Harko
//Originally written for Total Space Massacre, a project for CS 432 on 
//February 21th, 2007.
//******************************************************************************

#include <math.h>
#include "CAsteroid.h"
#include "CTexture.h"

using namespace std;

//##############################################################################
/**
* @class CAsteroid CAsteroid.h
* An Asteroid is a space obstacle. It can be destroyed by shots and by a ship's
* hull (destroying the ship in the process).
*
* @author Tyler Sangster
* @date 11/03/2007
* @version 1.0
*/
//##############################################################################

    //--------------------------------------------------------------------------
	/**
    * Full specification constructor for a CAsteroid. The constructor stores the 
    * variables taken in and sets of the others to defaults.
    *
    * @see CHeavenlyBody::CHeavenlyBody
    */
    //--------------------------------------------------------------------------
    CAsteroid::CAsteroid(GLdouble const akdPos[3], GLdouble const akdForward[3], 
        GLdouble const akdUp[3], const GLdouble kdSpeed) :
        CHeavenlyBody(akdPos, akdForward, akdUp, kdSpeed) {
        
        CommonConstructor();          
    }
    
    //----------------------------------------------------------------------
    /**
    * Minimal specification constructor for a stationary CAsteroid.
    *
    * @param akdPos The position in cartesian co-ordinates.
    */
    //----------------------------------------------------------------------
    CAsteroid::CAsteroid(GLdouble const akdPos[3]) : CHeavenlyBody(akdPos) {
        CommonConstructor();
    }
    
    //----------------------------------------------------------------------
    /** 
    * Reads in the statistics from XML and sets initial values for 
    * bounding boxes and display lists.
    */
    //----------------------------------------------------------------------
    void CAsteroid::CommonConstructor(void) {
        //Read these from XML
        //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        m_nDamage = 1000000;
        m_bInvulnerable = false;
		m_nMaxHealth = 500;		
        m_dScale = 0.1;
        //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        
        m_nHealth = m_nMaxHealth;
        
        m_adBox[gknW] = m_dScale;
        m_adBox[gknH] = m_dScale;
        m_adBox[gknL] = m_dScale;
        
       	m_anDisplayId[gknAlive] = gknAliveDisplay;
		m_anDisplayId[gknDying] = gknDyingDisplay;        
    }
    
    //----------------------------------------------------------------------
    /**
    * Creates the display list to draw a CAsteroid.
    */
    //----------------------------------------------------------------------
    void CAsteroid::Init(void) {
        glNewList(gknAliveDisplay, GL_COMPILE);
	
            CTexture texture(400,"ast.bmp");
            texture.Select();
		 
            GLUquadricObj *q;
            q = gluNewQuadric();
            gluQuadricTexture(q,GLU_TRUE);
            gluSphere(q,0.5,10,10);
			
        glEndList();
        
        glNewList(gknDyingDisplay, GL_COMPILE);
	
            CTexture texture2(401,"charred.bmp");
            texture2.Select();
		 
            GLUquadricObj *w;
            w = gluNewQuadric();
            gluQuadricTexture(w,GLU_TRUE);
            gluSphere(w,0.5,10,10);
			
        glEndList();
    }
    
    //--------------------------------------------------------------------------
    /**
    * Destroys the display lists used.
    */
    //--------------------------------------------------------------------------
    void CAsteroid::UnInit(void) {
        if(glIsList(gknAliveDisplay) == GL_TRUE) {
            glDeleteLists(gknAliveDisplay,1);
        }
        if(glIsList(gknDyingDisplay) == GL_TRUE) {
            glDeleteLists(gknDyingDisplay,1);
        }
    }
