//******************************************************************************
//CHumanFighter.cpp
//Copyright (C) 2007, Marcus Trenton, Tyler Sangster, and Sebastian Harko
//Originally written for Total Space Massacre, a project for CS 432 on 
//February 21th, 2007.
//******************************************************************************

#include "CHumanFighter.h"
#include "CMinigun.h"
#include "CKyagRocket.h"
#include "GL/glut.h"
#include "CTexture.h"
#include "CMicroLaser.h"
#include "CDoomRay.h"
#include "CProximityRocket.h"
#include "CHomingMissile.h"

using namespace std;

//##############################################################################
/**
* @class CHumanFighter CHumanFighter.h
*
* Class HumanFighter mearly has to record the stats for the ship and how to
* draw it. Everything else is taken care of by CShip.
*
* @author Tyler Sangster
* @date Mon 19 Feb
* @version 1.0
*/
//##############################################################################

	//--------------------------------------------------------------------------
	/**
    * Let the CShip deal with most of the variables while this constructor
    * reads in the statistics from XML.
    *
    * @see CShip::CShip
    */
    //--------------------------------------------------------------------------
	CHumanFighter::CHumanFighter(GLdouble const akdPos[3], 
        GLdouble const akdForward[3], GLdouble const akdUp[3], 
        const GLdouble kdSpeed, const int knTeam) : 
        CShip(akdPos, akdForward, akdUp, kdSpeed, knTeam) {
         
        //Temporary representation as in integer. Max speed is actually a 
        //double but for ease of XML readablity it is read as an integer and
        //later converted to be the proper double.
        int nMaxSpeed; 
            
        CShipManager *pcReader = new CShipManager("ships.xml");
        
        //Read in the statistics from XML.
        pcReader->LoadShipAttributes("HumanFighter",&m_nMaxHealth,
		  &m_nMaxShield, &m_nMaxEnergy ,&m_nRecharge, &m_nShieldEff, 
          &m_nWeaponEff, &m_nEngineEff, &m_nManeuver, &nMaxSpeed,
		  &m_dScale, &m_adBox[gknH], &m_adBox[gknW], &m_adBox[gknL]);
		
		//Max speed converted from an int to a scaled double.
		m_dMaxSpeed = ((GLdouble)nMaxSpeed) * gkdSpeedScale;
		
        //A ship starts with maximum energy, health, and shields.  
		m_nHealth = m_nMaxHealth;
        m_nShield = m_nMaxShield;
        m_nEnergy = m_nMaxEnergy;				
        
        //The starting weapons.
  		m_apcWeapon[0] = new CDoomRay(this);
	    m_apcWeapon[1] = new CHomingMissile(this);
        m_nWeapons = 2;
                   
        m_anDisplayId[gknAlive] = gknAliveDisplay;
		m_anDisplayId[gknDying] = gknDyingDisplay;		   		 		
	 }
	 
	//--------------------------------------------------------------------------
	/**
    * How to draw the CHumanFighter. It tightly fits a 1 length cube centered on 
    * the origin. Model provided by Tyler Sangster.
    */
    //--------------------------------------------------------------------------
    void CHumanFighter::Init(void) {   	
    	glNewList(gknAliveDisplay, GL_COMPILE);
	
            GLfloat vertices[46][3] =   {
    			{ 0, 0, .96/2 },
    			{ -.16/2, 0, .48/2 },
    			{ .16/2, 0, .48/2 },
    			{ .16/2, 0, -.56/2 },
    			{ -.16/2, 0, -.56/2 },
    			{ 0, .08/2, .48/2 },
    			{ 0, .08/2, -.16/2 },
    			{ 0, -.08/2, .96/2 },
    			{ -.16/2, -.08/2, .48/2 },
    			{ .16/2, -.08/2, .48/2 },
    			{ 0, -.16/2, .48/2 },
    			{ 0, 0, -.80/2 },
    			{ 0, -.20/2, -.56/2 },
    			{ -.16/2, -.08/2, -.56/2 },
    			{ .16/2, -.08/2, -.56/2 },
    			{ 0, .20/2, -.56/2 },
    			{ 0, .20/2, -.96/2 },
    			{ -.56/2, -.04/2, -.52/2 },
    			{ .56/2, -.04/2, -.52/2 },
    			{ -.20/2, -.04/2, -.16/2 },
    			{ -.28/2, -.04/2, -.16/2 },
    			{ -.28/2, -.04/2, -.24/2 },
    			{ -.20/2, -.04/2, -.24/2 },
    			{ -.24/2, .04/2, -.20/2 },
    			{ 0, .12/2, -.28/2 },
    			{ -.12/2, .08/2, -.56/2 },
    			{ .12/2, .08/2, -.56/2 },
    			{ 0, .20/2, -.44/2 },
    			{ -.16/2, -.04/2, -.16/2 },
    			{ -.32/2, -.04/2, -.16/2 },
    			{ -.24/2, -.04/2, 0 },
    			{ -.32/2, -.04/2, -.60/2 },
    			{ -.16/2, -.04/2, -.60/2 },
    			{ -.24/2, -.12/2, -.60/2 },
    			{ -.24/2, -.12/2, -.12/2 },
    			{ .16/2, -.04/2, -.16/2 },
    			{ .32/2, -.04/2, -.16/2 },
    			{ .16/2, -.04/2, -.60/2 },
    			{ .32/2, -.04/2, -.60/2 },
    			{ .24/2, -.04/2, 0 },
    			{ .24/2, -.12/2, -.60/2 },
    			{ .24/2, -.12/2, -.12/2 },
    			{ .32/2, 0, -.52/2 },
    			{ .16/2, 0, -.52/2 },
    			{ -.32/2, 0, -.52/2 },
    			{ -.16/2, 0, -.52/2 },
    			};

            GLubyte ship1[72] = { 
                5, 1, 0,
                0, 2, 5,
                7, 8, 10,
                10, 9, 7,
                15, 16, 11,
                16, 15, 11,
                18, 3, 2,
                17, 1, 4,
                17, 13, 8,
                9, 14, 18,
                17, 8, 1,
                18, 2, 9,
                14, 3, 18,
                4, 13, 17,
                23, 20, 19,
                23, 21, 20,
                23, 22, 21,
                19, 22, 23,
                30, 34, 28,
                30, 29, 34,
                33, 31, 32,
                35, 41, 39,
                39, 41, 36,
                37, 38, 40};
		
            GLubyte ship2[108] = {	
                1, 5, 6, 4,
				3, 6, 5, 2,
				0, 1, 8, 7,
				7, 9, 2, 0,
				14, 9, 10, 12,
				13, 12, 10, 8,
				13, 8, 1, 4,
				14, 3, 2, 9,
				11, 12, 13, 4,
				4, 13, 12, 11,
				3, 14, 12, 11,
				11, 12, 14, 3,
				6, 24, 25, 4,
				3, 26, 24, 6,
				27, 15, 25, 24,
				27, 24, 25, 15,
				24, 26, 15, 27,
				15, 25, 4, 11,
				11, 4, 25, 15,
				11, 3, 26, 15,
				15, 26, 3, 11,						
				34, 29, 31, 33,
				28, 34, 33, 32,
				37, 40, 41, 35,
				41, 40, 38, 36,						
				43, 42, 38, 37,
				32, 31, 44, 45};						

            GLfloat afNothing[3] = {0.0,0.0,0.0};
            glMaterialfv(GL_FRONT, GL_AMBIENT, afNothing);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, afNothing);
            glMaterialfv(GL_FRONT, GL_SPECULAR, afNothing);
            glMaterialf(GL_FRONT, GL_SHININESS, 10.0);
            
            glBegin(GL_QUADS);		
                for(int i = 0; i<108; i+=4){                
    				GLfloat afBody1[3] = {1.0,0.0,0.0};
    				glMaterialfv(GL_FRONT, GL_EMISSION, afBody1);
    				glVertex3d(vertices[ ship2[i] ] [0], 
    					vertices[ ship2[i] ] [1],
    					vertices[ ship2[i] ] [2] );
    				
    				GLfloat afBody2[3] = {0.8,0.0,0.0};
    				glMaterialfv(GL_FRONT, GL_EMISSION, afBody2);
    				glVertex3d(vertices[ ship2[i+1] ] [0], 
    					vertices[ ship2[i+1] ] [1],
    					vertices[ ship2[i+1] ] [2] );
    				
    				GLfloat afBody3[3] = {0.4,0.0,0.0};
    				glMaterialfv(GL_FRONT, GL_EMISSION, afBody3);
    				glVertex3d(vertices[ ship2[i+2] ] [0], 
    					vertices[ ship2[i+2] ] [1],
    					vertices[ ship2[i+2] ] [2] );
    				
    				GLfloat afBody4[3] = {0.6,0.0,0.0};
    				glMaterialfv(GL_FRONT, GL_EMISSION, afBody4);
    				glVertex3d(vertices[ ship2[i+3] ] [0], 
                        vertices[ ship2[i+3] ] [1],
    					vertices[ ship2[i+3] ] [2] );				    		
                }
            glEnd();
	
            GLfloat afCockpit[3] = {0.5,1.0,1.0};
            glMaterialfv(GL_FRONT, GL_EMISSION, afCockpit);
            glBegin(GL_TRIANGLES);
                for(int i = 0;i<12; i+=3){
                	glVertex3f(vertices[ ship1[i] ] [0], 
    				vertices[ ship1[i] ] [1],
    				vertices[ ship1[i] ] [2] );
    
    				glVertex3f(vertices[ ship1[i+1] ] [0], 
    				vertices[ ship1[i+1] ] [1],
    				vertices[ ship1[i+1] ] [2] );
    
    				glVertex3f(vertices[ ship1[i+2] ] [0], 
    				vertices[ ship1[i+2] ] [1],
    				vertices[ ship1[i+2] ] [2] );                	
                }
	       
                for(int i = 18;i<72; i+=3) {				
    				GLfloat afWings1[3] = {1.0,1.0,1.0};
                    glMaterialfv(GL_FRONT, GL_EMISSION, afWings1);
    				glVertex3f(vertices[ ship1[i] ] [0], 
    					vertices[ ship1[i] ] [1],
    					vertices[ ship1[i] ] [2] );
    					
    				GLfloat afWings2[3] = {0.8,0.8,0.8};
                    glMaterialfv(GL_FRONT, GL_EMISSION, afWings2);
    				glVertex3f(vertices[ ship1[i+1] ] [0], 
    					vertices[ ship1[i+1] ] [1],
    					vertices[ ship1[i+1] ] [2] );
    					
                    GLfloat afWings3[3] = {0.7,0.7,0.7};
                    glMaterialfv(GL_FRONT, GL_EMISSION, afWings3);			
    				glVertex3f(vertices[ ship1[i+2] ] [0], 
    					vertices[ ship1[i+2] ] [1],
    					vertices[ ship1[i+2] ] [2] );
                	
                }	
            glEnd();
            
            CTexture cFlag(3,"Canada.bmp");	
            cFlag.Select();
	
            int i = 15;
            glBegin(GL_TRIANGLES);	
                glTexCoord2f(0.0,0.0);
                glVertex3f(vertices[ ship1[i] ] [0], 
                vertices[ ship1[i] ] [1],
                vertices[ ship1[i] ] [2] );
                glTexCoord2f(0.5,1.0);
                glVertex3f(vertices[ ship1[i+1] ] [0], 
                vertices[ ship1[i+1] ] [1],
                vertices[ ship1[i+1] ] [2] );
                glTexCoord2f(1.0,0.0);
                glVertex3f(vertices[ ship1[i+2] ] [0], 
                vertices[ ship1[i+2] ] [1] ,
                vertices[ ship1[i+2] ] [2] );	

                i = 12;

            	glTexCoord2f(0.0,0.0);
            	glVertex3f(vertices[ ship1[i] ] [0], 
            	vertices[ ship1[i] ] [1],
            	vertices[ ship1[i] ] [2] );
            	glTexCoord2f(0.5,1.0);
            	glVertex3f(vertices[ ship1[i+1] ] [0], 
            	vertices[ ship1[i+1] ] [1],
            	vertices[ ship1[i+1] ] [2] );
            	glTexCoord2f(1.0,0.0);
            	glVertex3f(vertices[ ship1[i+2] ] [0], 
            	vertices[ ship1[i+2] ] [1] ,
            	vertices[ ship1[i+2] ] [2] );
            glEnd();
	
        glEndList();

        glNewList(gknDyingDisplay, GL_COMPILE);
            CTexture texture(13, "firetile2.bmp");
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
    void CHumanFighter::UnInit(void) {
        if(glIsList(gknAliveDisplay) == GL_TRUE) {
            glDeleteLists(gknAliveDisplay,1);
        }
        if(glIsList(gknDyingDisplay) == GL_TRUE) {
            glDeleteLists(gknDyingDisplay,1);
        }
    }
