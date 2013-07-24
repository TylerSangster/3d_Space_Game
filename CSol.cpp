//******************************************************************************
//CSol.cpp
//Copyright (C) 2007, Marcus Trenton, Tyler Sangster, and Sebastian Harko
//Originally written for Total Space Massacre, a project for CS 432 on 
//March 22nd, 2007.
//******************************************************************************

#include <GL/glut.h>
#include "CSol.h"
#include "CTexture.h"

using namespace std;

//##############################################################################
/**
* @class CSol CSol.h
* CSol is the Earth's sun. It provides light and is indestructible.
*
* @author Marcus Trenton
* @date 11/03/2007
* @version 1.0
*/
//##############################################################################

    //--------------------------------------------------------------------------
	/**
    * The constructor stores the variables taken in and sets of the others to
    * zero. The others will be overwritten to be something meaningful by
    * subclasses.
    *
    * @see CHeavenlyBody::CHeavenlyBody
    */
    //--------------------------------------------------------------------------
    CSol::CSol(GLdouble const akdPos[3], GLdouble const akdForward[3], 
        GLdouble const akdUp[3], const GLdouble kdSpeed) :
        CHeavenlyBody(akdPos, akdForward, akdUp, kdSpeed) {
        
        CommonConstructor();          
    }
    
    //----------------------------------------------------------------------
    /**
    * Minimal specification constructor for a stationary CSol.
    *
    * @param akdPos The position in cartesian co-ordinates.
    */
    //----------------------------------------------------------------------
    CSol::CSol(GLdouble const akdPos[3]) : CHeavenlyBody(akdPos) {
        CommonConstructor();
    }
    
    //----------------------------------------------------------------------
    /** 
    * Reads in the statistics from XML and sets initial values.
    */
    //----------------------------------------------------------------------
    void CSol::CommonConstructor(void) {
        //Read these from XML
        //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        m_nDamage = 10000000;
        m_bInvulnerable = true;
		m_nMaxHealth = 1;		
        m_dScale = 1.0;
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
    void CSol::Init(void) {
    	
        glNewList(gknAliveDisplay, GL_COMPILE);
        	GLfloat afPos[3] = {0.0, 0.0, 0.0};
			glLightfv(GL_LIGHT0, GL_POSITION, afPos);
			GLfloat afSunLight[3] = {1.0, 1.0, 1.0};
			glLightfv(GL_LIGHT0, GL_AMBIENT, afSunLight);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, afSunLight);
			glLightfv(GL_LIGHT0, GL_SPECULAR, afSunLight);
			glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0);
			glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0);
			glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0);
			
            CTexture texture(400,"sol.bmp");
            texture.Select();		 
            GLUquadricObj *q;
            q = gluNewQuadric();
            gluQuadricTexture(q,GLU_TRUE);
            gluSphere(q,0.5,15,15);
			
        glEndList();
        
        glNewList(gknDyingDisplay, GL_COMPILE);
	
            CTexture texture2(401,"sol.bmp");
            texture2.Select();		 
            GLUquadricObj *w;
            w = gluNewQuadric();
            gluQuadricTexture(w,GLU_TRUE);
            gluSphere(w,0.5,15,15);
			
        glEndList();
    }
    
    //--------------------------------------------------------------------------
    /**
    * Destroys the display lists used.
    */
    //--------------------------------------------------------------------------
    void CSol::UnInit(void) {
        if(glIsList(gknAliveDisplay) == GL_TRUE) {
            glDeleteLists(gknAliveDisplay,1);
        }
        if(glIsList(gknDyingDisplay) == GL_TRUE) {
            glDeleteLists(gknDyingDisplay,1);
        }
    }
