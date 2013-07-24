//******************************************************************************
//CMicroLaserShot.cpp
//Copyright (C) 2007, Marcus Trenton, Tyler Sangster, and Sebastian Harko
//Originally written for Total Space Massacre, a project for CS 432 on 
//February 21th, 2007.
//******************************************************************************
#include <cstdlib>
#include <iostream> //For debugging only.
#include "CMicroLaserShot.h"
#include "CTexture.h"

using namespace std;

//##############################################################################
/**
* @class CMicroLaserShot CMicroLaserShot.h
* The shots created by a micro laser launcher. Class CMicroLaserShot is 
* responsible for stating how it is drawn, its size, and its bounding box. 
* Everything else is handled by inheritance.
*
* @author Marcus Trenton
* @date Mon 19 Feb
* @version 1.0
*/
//##############################################################################
	
	//--------------------------------------------------------------------------
	/**
    * The CShot constructor will take care of everything except the display 
    * list, the size of the shot, and the bounding box.
    *
    * @see CShot::CShot
    */
    //--------------------------------------------------------------------------
    CMicroLaserShot::CMicroLaserShot(GLdouble const akdPos[3], 
        GLdouble const akdForward[3], GLdouble const akdUp[3], 
        const GLdouble kdSpeed, const int knFirepower, const GLdouble kdRange, 
        const bool kbHoming, const bool kbDetonateOnShooter, 
        CEntity* const pkcTarget, CEntity* const pkcOrigin) : 
        CShot(akdPos, akdForward, akdUp, kdSpeed, knFirepower, kdRange, 
        kbHoming, kbDetonateOnShooter, pkcTarget, pkcOrigin) {
        
        //Read these from XML
        //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        m_dScale = 0.002;
        m_adBox[gknW] = m_dScale;
        m_adBox[gknH] = m_dScale;
        m_adBox[gknL] = m_dScale;
        //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        
       	m_anDisplayId[gknAlive] = gknAliveDisplay;
		m_anDisplayId[gknDying] = gknDyingDisplay;		
    }
    
    //--------------------------------------------------------------------------
    /**
    * How to draw the CMicroLaser shot. It tightly fits a 1 length cube centered 
    * on the origin.
    */
    //--------------------------------------------------------------------------
    void CMicroLaserShot::Init(void) {
    	glNewList(gknAliveDisplay, GL_COMPILE);
		
		GLfloat afNothing[3] = {0.0,0.0,0.0};
        glMaterialfv(GL_FRONT, GL_AMBIENT, afNothing);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, afNothing);
        glMaterialfv(GL_FRONT, GL_SPECULAR, afNothing);
        glMaterialf(GL_FRONT, GL_SHININESS, 10.0);
        GLfloat afColour[3] = {0.3,0.666,1.0};
        glMaterialfv(GL_FRONT, GL_EMISSION, afColour);
		
		GLUquadricObj *w;
		w = gluNewQuadric();
		gluSphere(w,0.5,10,10);	
	glEndList();

	glNewList(gknDyingDisplay, GL_COMPILE);
		CTexture cDyingTexture(13, "blue_fire2.bmp");
		cDyingTexture.Select();
	
		GLUquadricObj *q;
		q = gluNewQuadric();
		gluQuadricTexture(q,GLU_TRUE);
		gluSphere(q,0.5,10,10);
	glEndList(); 	
    }
    
    //--------------------------------------------------------------------------
    /**
    * Destroys the display lists used.
    */
    //--------------------------------------------------------------------------
    void CMicroLaserShot::UnInit(void) {
        if(glIsList(gknAliveDisplay) == GL_TRUE) {
            glDeleteLists(gknAliveDisplay,1);
        }
        if(glIsList(gknDyingDisplay) == GL_TRUE) {
            glDeleteLists(gknDyingDisplay,1);
        }
    }
