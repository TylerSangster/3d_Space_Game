//******************************************************************************
//CHomingMissileShot.cpp
//Copyright (C) 2007, Marcus Trenton, Tyler Sangster, and Sebastian Harko
//Originally written for Total Space Massacre, a project for CS 432 on 
//March 23rd, 2007.
//******************************************************************************

#include <cstdlib>
#include "CHomingMissileShot.h"
#include "CTexture.h"

using namespace std;

//##############################################################################
/**
* @class CHomingMissileShot CHomingMissileShot.h
* Class CHomingMissileShot is responsible for stating how it is drawn, its size, 
* and its bounding box. Everything else is handled by inheritance.
*
* @author Tyler Sangster
* @date Friday 23 March
* @version 1.0
*/
//##############################################################################
	
	//--------------------------------------------------------------------------
	/**
    * The specification constuctor for a HomingMissileShot. The CShot 
    * constructor will take care of everything except the display list, the size 
    * of the shot, and the bounding box.
    *
    * @see CShot::CShot
    */
    //--------------------------------------------------------------------------
    CHomingMissileShot::CHomingMissileShot(GLdouble const akdPos[3], 
        GLdouble const akdForward[3], GLdouble const akdUp[3], 
        const GLdouble kdSpeed, const int knFirepower, const GLdouble kdRange, 
        const bool kbHoming, const bool kbDetonateOnShooter, 
        CEntity* const pkcTarget, CEntity* const pkcOrigin) : 
        CShot(akdPos, akdForward, akdUp, kdSpeed, knFirepower, kdRange, 
        kbHoming, kbDetonateOnShooter, pkcTarget, pkcOrigin) {
        
        //Read these from XML
        //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        m_dScale = 0.008;
        m_adBox[gknW] = m_dScale/4;
        m_adBox[gknH] = m_dScale/4;
        m_adBox[gknL] = m_dScale;
        //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        
       	m_anDisplayId[gknAlive] = gknAliveDisplay;
		m_anDisplayId[gknDying] = gknDyingDisplay;		
    }
    
    //--------------------------------------------------------------------------
    /**
    * How to draw the CHomingMissile shot. Model provided by Tyler Sangster.
    */
    //--------------------------------------------------------------------------
    void CHomingMissileShot::Init(void) {	
    	glNewList(gknAliveDisplay, GL_COMPILE);
    	   GLfloat vertices[17][3] = {
    			{ 0, 0, .96/2 },//0
    			{ .24/2, 0, .24/2 },//1
    			{ -.24/2, 0, .24/2 },//2
    			{ 0, -.24/2, .24/2 },//3
    			{ 0, .24/2, .24/2 },//4
    			{ .24/2, 0, -.96/2 },//5
    			{ -.24/2, 0, -.96/2 },//6
    			{ 0, -.24/2, -.96/2 },//7
    			{ 0, .24/2, -.96/2 },//8
    			{ .48/2, 0, -.96 /2},//9
    			{ .24/2, 0, -.24 /2},//10
    			{ -.24/2, 0, -.24/2 },//11
    			{ -.48/2, 0, -.96/2 },//12
    			{ 0, -.48/2, -.96/2 },//13
    			{ 0, .48/2, -.96/2 },//14
    			{ 0, -.24/2, -.24 /2},//15
    			{ 0, .24/2, -.24/2 }};//16
            glVertexPointer(3,GL_FLOAT,0,vertices);
            GLubyte rocket1[20]  = {
    			4, 2, 6, 8,
    			8, 5, 1, 4,
    			7, 6, 2, 3,
    			3, 1, 5, 7,
    			5, 8, 6, 7};
            GLubyte rocket2[36]  = { 
                0, 1, 3,//1
                0, 3, 2,//2
                4, 1, 0,//3
                0, 2, 4,//4
                12, 11, 6,//5
                6, 11, 12,//6
                10, 9, 5,//7
                5, 9, 10,//8
                16, 14, 8,//9
                8, 14, 16,//10
                15, 13, 7,//11
                7, 13, 15//12
                };
    				
            GLfloat afGreen[3] = {0.0,1.0,0.0};
            GLfloat afNothing[3] = {0.0,0.0,0.0};
            glMaterialfv(GL_FRONT, GL_AMBIENT, afNothing);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, afNothing);
            glMaterialfv(GL_FRONT, GL_SPECULAR, afNothing);
            glMaterialf(GL_FRONT, GL_SHININESS, 10.0);
            glMaterialfv(GL_FRONT, GL_EMISSION, afGreen);
    		
            glDrawElements(GL_QUADS,20 , GL_UNSIGNED_BYTE, rocket1);
            
            GLfloat afGray[3] = {0.5,0.5,0.5};
            glMaterialfv(GL_FRONT, GL_EMISSION, afGray);
            
            glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_BYTE, rocket2);
            glEndList();
    
            glNewList(gknDyingDisplay, GL_COMPILE);
    		CTexture cDyingTexture(13, "plasma2.bmp");
    		cDyingTexture.Select();
    	
    		GLUquadricObj *q;
    		q = gluNewQuadric();
    		gluQuadricNormals(q,GLU_TRUE);
    		gluQuadricTexture(q,GLU_TRUE);
    		gluSphere(q,0.5,10,10);
        glEndList(); 	
    }
    
    //--------------------------------------------------------------------------
    /**
    * Destroys the display lists used.
    */
    //--------------------------------------------------------------------------
    void CHomingMissileShot::UnInit(void) {
        if(glIsList(gknAliveDisplay) == GL_TRUE) {
            glDeleteLists(gknAliveDisplay,1);
        }
        if(glIsList(gknDyingDisplay) == GL_TRUE) {
            glDeleteLists(gknDyingDisplay,1);
        }
    }
