//******************************************************************************
//CPluto.cpp
//Copyright (C) 2007, Marcus Trenton, Tyler Sangster, and Sebastian Harko
//Originally written for Total Space Massacre, a project for CS 432 on 
//March 22nd, 2007.
//******************************************************************************

#include "CPluto.h"
#include "CTexture.h"

using namespace std;

//##############################################################################
/**
* @class CPluto CPluto.h
* CPluto is the Pluto. Please don't allow aliens conquer it. They might raise
* taxes.
*
* @author Sebastian Harko
* @version 1.0
*/
//##############################################################################

    //--------------------------------------------------------------------------
	/**
    * The specification constructor. The constructor stores the variables taken 
    * in and sets of the others to defaults.
    *
    * @see CHeavenlyBody::CHeavenlyBody
    */
    //--------------------------------------------------------------------------
    CPluto::CPluto(GLdouble const akdPos[3], GLdouble const akdForward[3], 
        GLdouble const akdUp[3], const GLdouble kdSpeed) :
        CHeavenlyBody(akdPos, akdForward, akdUp, kdSpeed) {
        
        CommonConstructor();          
    }
    
    //----------------------------------------------------------------------
    /**
    * Minimal specification constructor for a stationary CPluto.
    *
    * @param akdPos The position in cartesian co-ordinates.
    */
    //----------------------------------------------------------------------
    CPluto::CPluto(GLdouble const akdPos[3]) : CHeavenlyBody(akdPos) {
        CommonConstructor();
    }
    
    //----------------------------------------------------------------------
    /** 
    * Reads in the statistics from XML and setsinitial values.
    */
    //----------------------------------------------------------------------
    void CPluto::CommonConstructor(void) {
        //Read these from XML
        //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        m_nDamage = 10000000;
        m_bInvulnerable = true;
		m_nMaxHealth = 1;		
        m_dScale = 0.5;
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
    * Creates the display list to draw a CSol.
    */
    //----------------------------------------------------------------------
    void CPluto::Init(void) {
        glNewList(gknAliveDisplay, GL_COMPILE);
	
            CTexture texture(400,"pluto.bmp");
            texture.Select();		 
            GLUquadricObj *q;
            q = gluNewQuadric();
            gluQuadricTexture(q,GLU_TRUE);
            gluSphere(q,0.5,10,10);
			
        glEndList();
        
        glNewList(gknDyingDisplay, GL_COMPILE);
	
            CTexture texture2(401,"pluto.bmp");
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
    void CPluto::UnInit(void) {
        if(glIsList(gknAliveDisplay) == GL_TRUE) {
            glDeleteLists(gknAliveDisplay,1);
        }
        if(glIsList(gknDyingDisplay) == GL_TRUE) {
            glDeleteLists(gknDyingDisplay,1);
        }
    }
