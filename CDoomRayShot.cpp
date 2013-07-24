//******************************************************************************
//CDoomRayShot.cpp
//Copyright (C) 2007, Marcus Trenton, Tyler Sangster, and Sebastian Harko
//Originally written for Total Space Massacre, a project for CS 432 on 
//March 23rd, 2007.
//******************************************************************************
#include <cstdlib>
#include "CDoomRayShot.h"
#include "CTexture.h"

using namespace std;

//##############################################################################
/**
* @class CDoomRayShot CDoomRayShot.h
* Class The shot fired from a Doom Ray. CDoomRayShot is responsible for stating 
* how it is drawn, its size, and its bounding box. Everything else is handled by 
* inheritance.
*
* @author Marcus Trenton
* @date Friday 23 March
* @version 1.0
*/
//##############################################################################
	
	//--------------------------------------------------------------------------
	/**
	* The specification constuctor for a DoomRayShot. The CShot constructor will 
    * take care of everything except the display 
    * list, the size of the shot, and the bounding box.
    *
    * @see CShot::CShot
    */
    //--------------------------------------------------------------------------
    CDoomRayShot::CDoomRayShot(GLdouble const akdPos[3], 
        GLdouble const akdForward[3], GLdouble const akdUp[3], 
        const GLdouble kdSpeed, const int knFirepower, const GLdouble kdRange, 
        const bool kbHoming, const bool kbDetonateOnShooter, 
        CEntity* const pkcTarget, CEntity* const pkcOrigin) : 
        CShot(akdPos, akdForward, akdUp, kdSpeed, knFirepower, kdRange, 
        kbHoming, kbDetonateOnShooter, pkcTarget, pkcOrigin) {
        
        //Read these from XML
        //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        m_dScale = 0.008;
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
    void CDoomRayShot::Init(void) {
    	glNewList(gknAliveDisplay, GL_COMPILE);
    	
	    	GLfloat afLight[3] = {0.0,0.7,0.7};
	    	GLfloat afNothing[3] = {0.0,0.0,0.0};
	    	GLfloat afShine[3] = {1.0,1.0,1.0};
        	glMaterialfv(GL_FRONT, GL_AMBIENT, afNothing);
        	glMaterialfv(GL_FRONT, GL_DIFFUSE, afNothing);
        	glMaterialfv(GL_FRONT, GL_SPECULAR, afShine);
        	glMaterialf(GL_FRONT, GL_SHININESS, 10.0);
	        glMaterialfv(GL_FRONT, GL_EMISSION, afLight);

    		GLUquadricObj *w;
    		w = gluNewQuadric();
    		gluQuadricNormals(w,GLU_TRUE);
    		gluSphere(w,0.5,10,10);	
    	glEndList();

    	glNewList(gknDyingDisplay, GL_COMPILE);
	        
	        glMaterialfv(GL_FRONT, GL_AMBIENT, afNothing);
        	glMaterialfv(GL_FRONT, GL_DIFFUSE, afNothing);
        	glMaterialfv(GL_FRONT, GL_SPECULAR, afShine);
        	glMaterialf(GL_FRONT, GL_SHININESS, 10.0);
	        glMaterialfv(GL_FRONT, GL_EMISSION, afLight);
	        
    		GLUquadricObj *q;
    		q = gluNewQuadric();
    		gluQuadricNormals(q,GLU_TRUE);
    		gluSphere(q,0.5,10,10);
    	glEndList(); 	
    }
    
    //--------------------------------------------------------------------------
    /**
    * Destroys the display lists used.
    */
    //--------------------------------------------------------------------------
    void CDoomRayShot::UnInit(void) {
        if(glIsList(gknAliveDisplay) == GL_TRUE) {
            glDeleteLists(gknAliveDisplay,1);
        }
        if(glIsList(gknDyingDisplay) == GL_TRUE) {
            glDeleteLists(gknDyingDisplay,1);
        }
    }
