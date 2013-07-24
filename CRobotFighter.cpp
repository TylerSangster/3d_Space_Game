//******************************************************************************
//CRobotFighter.cpp
//Copyright (C) 2007, Marcus Trenton, Tyler Sangster, and Sebastian Harko
//Originally written for Total Space Massacre, a project for CS 432 on 
//February 21th, 2007.
//******************************************************************************
#include <iostream> //For debugging only.
#include "CRobotFighter.h"
#include "CMicroLaser.h"
#include "CKyagRocket.h"
#include "GL/glut.h"
#include "CTexture.h"

using namespace std;

//##############################################################################
/**
* @class CRobotFighter CRobotFighter.h
*
* Class CRobotFighter mearly has to record the stats for the ship and how to
* draw it. Everything else is taken care of by CShip.
* @author Marcus Trenton
* @date Mon 19 Feb
* @version 0.1
*/
//##############################################################################

	//--------------------------------------------------------------------------
	/**
    * Let the CShip deal with most of the variables while this constructor uses
    * reads in the statistics from XML.
    *
    * @see CShip::CShip
    */
    //--------------------------------------------------------------------------
	CRobotFighter::CRobotFighter(GLdouble const akdPos[3], 
        GLdouble const akdForward[3], GLdouble const akdUp[3], 
        const GLdouble kdSpeed, const int knTeam) : 
        CShip(akdPos, akdForward, akdUp, kdSpeed, knTeam) {
         
        //Temporary representation as in integer. Max speed is actually a 
        //double but for ease of XML readablity it is read as an integer and
        //later converted to be the proper double.
        int nMaxSpeed; 
            
        CShipManager *pcReader = new CShipManager("ships.xml");
        
        //Read in the statistics from XML.
        pcReader->LoadShipAttributes("RobotFighter",&m_nMaxHealth,
		  &m_nMaxShield, &m_nMaxEnergy ,&m_nRecharge, &m_nShieldEff, 
          &m_nWeaponEff, &m_nEngineEff, &m_nManeuver, &nMaxSpeed,
		  &m_dScale, &m_adBox[gknH], &m_adBox[gknW], &m_adBox[gknL]);
		
		//Max speed converted from an int to a scaled double.
		m_dMaxSpeed = ((GLdouble)nMaxSpeed) * gkdSpeedScale;
		
        //A ship starts with maximum energy, health, and shields.  
		m_nHealth = m_nMaxHealth;
        m_nShield = m_nMaxShield;
        m_nEnergy = m_nMaxEnergy;				
        
        //The Robot Fighter starts with two Miniguns.
		m_apcWeapon[0] = new CMicroLaser(this);
		m_apcWeapon[1] = new CKyagRocket(this);
        m_nWeapons = 2;
                   
        m_anDisplayId[gknAlive] = gknAliveDisplay;
		m_anDisplayId[gknDying] = gknDyingDisplay;		   		 		
	 }
	 
	//--------------------------------------------------------------------------
	/**
    * How to draw the CRobotFighter. It tightly fits a 1 length cube centered on 
    * the origin.
    */
    //--------------------------------------------------------------------------
    void CRobotFighter::Init(void) {  	
    	glNewList(gknAliveDisplay, GL_COMPILE);
    	
    	CTexture red(1,"blue_wires.bmp");
		CTexture white(2,"white.bmp");
		CTexture steel(3,"steel.bmp");
		CTexture blue(4,"blue.bmp");
		CTexture ast(5,"ast.bmp");
	
		GLfloat vertices[64][3] ={   
	         { 0.24/2, 0.12/2, 0.28/2 },
	         { -0.24/2, 0.12/2, 0.28/2 },
	         { -0.24/2, 0.12/2, -0.56/2 },
	         { 0.24/2, 0.12/2, -0.56/2 },
	         { 0.24/2, -0.12/2, 0.28/2 },
	         { -0.24/2, -0.12/2, 0.28/2 },
	         { -0.24/2, -0.12/2, -0.56/2 },
	         { 0.24/2, -0.12/2, -0.56/2 },
	         { 0.24/2, 0.0/2, 0.96/2 },
	         { 0.04/2, 0.0/2, 0.96/2 },
	         { 0.04/2, 0.0/2, 0.88/2 },
	         { -0.04/2, 0.0/2, 0.88/2 },
	         { -0.04/2, 0.0/2, 0.96/2},
	         { -0.24/2, 0.0/2, 0.96/2 },
	         { 0.24/2, -0.12/2, -0.16/2 },
	         { 0.60/2, 0.0/2, -0.16/2 },
	         { 0.24/2, 0.12/2, -0.16/2 },
	         { 0.60/2, 0/2, 0.08/2 },
	         { -0.24/2, -0.12/2, -0.16/2 },
	         { -0.60/2, 0/2, -0.16/2 },
	         { -0.24/2, 0.12/2, -0.16/2 },
	         { -0.60/2, 0/2, 0.08/2 },
	         { 0.36/2, 0/2, -0.16/2 },
	         { 0.36/2, 0/2, -0.96/2 },
	         { 0.24/2, -0.12/2, -0.96/2 },
	         { 0.12/2, 0/2, -0.96/2 },
	         { 0.24/2, 0.12/2, -0.96/2 },
	         { 0.12/2, 0/2, -0.56/2 },
	         { -0.36/2, 0/2, -0.96/2 },
	         { -0.24/2, -0.12/2, -0.96/2 },
	         { -0.12/2, 0/2, -0.96/2 },
	         { -0.24/2, 0.12/2, -0.96/2 },
	         { -0.36/2, 0/2, -0.16/2 },
	         { -0.12/2, 0/2, -0.56/2 },
	         { 0.24/2, -0.36/2, -0.92/2 },
	         { 0.24/2, -0.36/2, -0.44/2 },
	         { 0.24/2, -0.12/2, -0.36/2 },
	         { 0.24/2, 0.32/2, -0.92/2 },
	         { 0.24/2, 0.32/2, -0.44/2 },
	         { 0.24/2, 0.12/2, -0.36/2 },
	         { -0.24/2, -0.36/2, -0.92/2 },
	         { -0.24/2, -0.36/2, -0.44/2 },
	         { -0.24/2, -0.12/2, -0.36/2 },
	         { -0.24/2, 0.32/2, -0.92/2 },
	         { -0.24/2, 0.32/2, -0.44/2 },
	         { -0.24/2, 0.12/2, -0.36/2 },
	         { -0.64/2, 0/2, -0.12/2 },
	         { -0.64/2, 0/2, 0.04/2 },
	         { -0.64/2, 0/2, -0.24/2 },
	         { -0.64/2, 0/2, 0.32/2 },
	         { 0.64/2, 0/2, -0.12/2 },
	         { 0.64/2, 0/2, 0.04/2 },
	         { 0.64/2, 0/2, -0.24/2 },
	         { 0.64/2, 0/2, 0.32/2 },
	         { 0.12/2, -0.12/2, -0.16/2 },
	         { 0.12/2, -0.12/2, -0.56/2 },
	         { -0.12/2, -0.12/2, -0.56/2 },
	         { -0.12/2, -0.12/2, -0.16/2 },
	         { -0.08/2, -0.12/2, 0.24/2 },
	         { 0.08/2, -0.12/2, 0.24/2 },
	         { 0.04/2, -0.24/2, -0.56/2 },
	         { -0.04/2, -0.24/2, -0.56/2 },
	         { -0.04/2, -0.24/2, -0.16/2 },
	         { 0.04/2, -0.24/2, -0.16/2 }};

		GLubyte ship1[156] =  
			{0, 1, 2, 3,		//0 c=20 0->3
		  10, 11, 1, 0,	//1         0->16
		  0, 8, 9, 10,	//2
		  1, 11, 12, 13,	//3 
		  7, 6, 5, 4,		//4 c=4 4->9
		  4, 5, 11, 10,	//5         16
		  10, 9, 8, 4,		//6
		  13, 12, 11, 5,	//7
		  54, 55, 60, 63,	//8
		  62, 61, 56, 57,	//9
		  18, 19, 21, 5,	//10 c=15 10->12
		  22, 23, 24, 14,	//11
		  32, 18, 29, 28,	//12
		  0, 16, 15, 17,	//13 c=7 13->26>
		  19, 20, 1, 21,	//14
		  6, 7, 3, 2,		//15
		  16, 26, 23, 22,  //16
		  28, 31, 20, 32,	//17
		  55, 56, 61, 60,	//18
		  34, 35, 36, 24,	//19
		  24, 36, 35, 34,	//20
		  37, 38, 39, 26,	//21
		  26, 39, 38, 37,	//22
		  40, 41, 42, 29,	//23
		  29, 42, 41, 40,	//24
		  43, 44, 45, 31,	//25
		  31, 45, 44, 43,	//26
		  28, 29, 30, 31,	//27 c=14 27->28
		  26, 25, 24, 23,	//28
		  33, 2, 31, 30,	//29 c=24 29->30
		  25, 26, 3, 27,	//30
		  24, 25, 27, 7,	//31 c=31
		  6, 33, 30, 29,	//32 c=31
		  60, 61, 62, 63,	//33 c=28
		  58, 59, 63, 62,	//34 c=11
		  47, 46, 19, 21,	//35 c=8 35->38
		  21, 19, 46, 47,	//36
		  51, 50, 15, 17,	//37
		  17, 15, 50, 51}; //38

	
		GLubyte ship2[24] =   { 
			14, 15, 16, //c=31
            20, 19, 18, //c=31
            17, 4, 8,// c = 15
            5, 21, 13,  // c = 15
            17, 8, 0,  // c=7
            13, 21, 1, // c=7
            58, 62, 57, //c=?
            59, 54, 63};//c=?

		red.Select();
		glBegin(GL_QUADS);		
		for(int i = 0; i<=36; i+=4){				
			glTexCoord2f(0.0,0.0);
			glVertex3d(vertices[ ship1[i] ] [0], 
				vertices[ ship1[i] ] [1],
				vertices[ ship1[i] ] [2] );
			
			glTexCoord2f(0.0,1.0);
			glVertex3d(vertices[ ship1[i+1] ] [0], 
				vertices[ ship1[i+1] ] [1],
				vertices[ ship1[i+1] ] [2] );
			
			glTexCoord2f(1.0,1.0);
			glVertex3d(vertices[ ship1[i+2] ] [0], 
				vertices[ ship1[i+2] ] [1],
				vertices[ ship1[i+2] ] [2] );
			
			glTexCoord2f(1.0,0.0);
			glVertex3d(vertices[ ship1[i+3] ] [0], 
				vertices[ ship1[i+3] ] [1],
				vertices[ ship1[i+3] ] [2] );					
		}
		glEnd();
		
    	steel.Select();
    	glBegin(GL_QUADS);
		for(int i = 36; i<=52; i+=4){				
			glTexCoord2f(0.0,0.0);
			glVertex3d(vertices[ ship1[i] ] [0], 
				vertices[ ship1[i] ] [1],
				vertices[ ship1[i] ] [2] );
			
			glTexCoord2f(0.0,1.0);
			glVertex3d(vertices[ ship1[i+1] ] [0], 
				vertices[ ship1[i+1] ] [1],
				vertices[ ship1[i+1] ] [2] );
			
			glTexCoord2f(1.0,1.0);
			glVertex3d(vertices[ ship1[i+2] ] [0], 
				vertices[ ship1[i+2] ] [1],
				vertices[ ship1[i+2] ] [2] );
			
			glTexCoord2f(1.0,0.0);
			glVertex3d(vertices[ ship1[i+3] ] [0], 
				vertices[ ship1[i+3] ] [1],
				vertices[ ship1[i+3] ] [2] );					
		}
		glEnd();
		
		red.Select();
		glBegin(GL_QUADS);		
		for(int i = 52; i<=108; i+=4){			
			glTexCoord2f(0.0,0.0);
			glVertex3d(vertices[ ship1[i] ] [0], 
				vertices[ ship1[i] ] [1],
				vertices[ ship1[i] ] [2] );
			
			glTexCoord2f(0.0,1.0);
			glVertex3d(vertices[ ship1[i+1] ] [0], 
				vertices[ ship1[i+1] ] [1],
				vertices[ ship1[i+1] ] [2] );
			
			glTexCoord2f(1.0,1.0);
			glVertex3d(vertices[ ship1[i+2] ] [0], 
				vertices[ ship1[i+2] ] [1],
				vertices[ ship1[i+2] ] [2] );
			
			glTexCoord2f(1.0,0.0);
			glVertex3d(vertices[ ship1[i+3] ] [0], 
				vertices[ ship1[i+3] ] [1],
				vertices[ ship1[i+3] ] [2] );			
		}
		glEnd();
		
		glBegin(GL_QUADS);
		for(int i = 108; i<=152; i+=4){			
			glTexCoord2f(0.0,0.0);
			glVertex3d(vertices[ ship1[i] ] [0], 
				vertices[ ship1[i] ] [1],
				vertices[ ship1[i] ] [2] );
			
			glTexCoord2f(0.0,1.0);
			glVertex3d(vertices[ ship1[i+1] ] [0], 
				vertices[ ship1[i+1] ] [1],
				vertices[ ship1[i+1] ] [2] );
			
			glTexCoord2f(1.0,1.0);
			glVertex3d(vertices[ ship1[i+2] ] [0], 
				vertices[ ship1[i+2] ] [1],
				vertices[ ship1[i+2] ] [2] );
			
			glTexCoord2f(1.0,0.0);
			glVertex3d(vertices[ ship1[i+3] ] [0], 
				vertices[ ship1[i+3] ] [1],
				vertices[ ship1[i+3] ] [2] );									
		}
		
		glEnd();
	

		blue.Select();
		glBegin(GL_TRIANGLES);
		for(int i = 0;i<=21; i+=3){						
					glTexCoord2f(0.0,0.0);
					glVertex3f(vertices[ ship2[i] ] [0], 
					vertices[ ship2[i] ] [1],
					vertices[ ship2[i] ] [2] );
					glTexCoord2f(0.5,1.0);
					glVertex3f(vertices[ ship2[i+1] ] [0], 
					vertices[ ship2[i+1] ] [1],
					vertices[ ship2[i+1] ] [2] );
					glTexCoord2f(1.0,0.0);
					glVertex3f(vertices[ ship2[i+2] ] [0], 
					vertices[ ship2[i+2] ] [1],
					vertices[ ship2[i+2] ] [2] );
			}
		glEnd();
		
	glEndList();
	
		glNewList(gknDyingDisplay, GL_COMPILE);
			CTexture texture(13, "Blueice.bmp");
			texture.Select();
		
			GLUquadricObj *q;
			q = gluNewQuadric();
			gluQuadricNormals(q,GLU_TRUE);
			gluQuadricTexture(q,GLU_TRUE);
			gluSphere(q,0.5,30,30);
		glEndList(); 
	}

    //--------------------------------------------------------------------------
    /**
    * Destroys the display lists used.
    */
    //--------------------------------------------------------------------------
    void CRobotFighter::UnInit(void) {
        if(glIsList(gknAliveDisplay) == GL_TRUE) {
            glDeleteLists(gknAliveDisplay,1);
        }
        if(glIsList(gknDyingDisplay) == GL_TRUE) {
            glDeleteLists(gknDyingDisplay,1);
        }
    }
