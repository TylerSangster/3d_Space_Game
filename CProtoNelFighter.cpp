//******************************************************************************
//CProtoNelFighter.cpp
//Copyright (C) 2007, Marcus Trenton, Tyler Sangster, and Sebastian Harko
//Originally written for Total Space Massacre, a project for CS 432 on 
//March 23rd, 2007.
//******************************************************************************
#include <iostream> //For debugging only.
#include "CProtoNelFighter.h"
#include "CMinigun.h"
#include "CProximityRocket.h"
#include "GL/glut.h"
#include "CTexture.h"

using namespace std;

//##############################################################################
/**
* @class CProtoNelFighter CProtoNelFighter.h
*
* Class CProtoNelFighter mearly has to record the stats for the ship and how to
* draw it. Everything else is taken care of by CShip.
* @author Tyler Sangster
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
	CProtoNelFighter::CProtoNelFighter(GLdouble const akdPos[3], 
        GLdouble const akdForward[3], GLdouble const akdUp[3], 
        const GLdouble kdSpeed, const int knTeam) : 
        CShip(akdPos, akdForward, akdUp, kdSpeed, knTeam) {
         
        //Temporary representation as in integer. Max speed is actually a 
        //double but for ease of XML readablity it is read as an integer and
        //later converted to be the proper double.
        int nMaxSpeed; 
            
        CShipManager *pcReader = new CShipManager("ships.xml");
        
        //Read in the statistics from XML.
        pcReader->LoadShipAttributes("ProtoNelFighter",&m_nMaxHealth,
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
        m_apcWeapon[0] = new CMinigun(this);
		m_apcWeapon[1] = new CProximityRocket(this);
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
    void CProtoNelFighter::Init(void) {   	
    	glNewList(gknAliveDisplay, GL_COMPILE);

/*	CTexture red(1,"yellow_wires.bmp");
	CTexture white(2,"green_marble.bmp");
	CTexture canada(3,"Europe.bmp");
	CTexture blue(4,"steel.bmp");
	*/
	CTexture red(1,"yellow_wires.bmp");
	//CTexture white(2,"white.bmp");
	//CTexture blood(3,"Blood.bmp");
	CTexture blue(4,"blue.bmp");
	CTexture steel(5,"green_marble.bmp");
	CTexture engine(6, "ice.bmp");

GLfloat vertices[56][3] = {
{ -.16/2, 0, .96/2 },//0
{ .16/2, 0, .96/2 },//1
{ -.20/2, .04/2, .36/2 },//2
{ .20/2, .04/2, .36/2 },//3
{ -.20/2, -.12/2, .36/2 },//4
{ .20/2, -.12/2, .36/2 },//5
{ -.16/2, -.08/2, .92/2 },//6
{ .16/2, -.08/2, .92/2 },//7
{ -.08/2, .04/2, .36/2 },//8
{ .08/2, .04/2, .36/2 },//9
{ -.04/2, .08/2, .36/2 },//10
{ .04/2, .08/2, .36/2 },//11
{ -.08/2, 0, .64/2 },//12
{ .08/2, 0, .64/2 },//13
{ -.04/2, .08/2, .64/2 },//14
{ .04/2, .08/2, .64/2 },//15
{ -.04/2, 0, .80/2 },//16
{ .04/2, 0, .80/2 },//17
{ -.12/2, .04/2, .36/2 },//18
{ .12/2, .04/2, .36/2 },//19
{ .12/2, -.08/2, .36/2 },//20
{ -.12/2, -.08/2, .36/2 },//21
{ -.12/2, .04/2, -.40/2 },//22
{ .12/2, .04/2, -.40/2 },//23
{ .12/2, -.08/2, -.40/2 },//24
{ -.12/2, -.08/2, -.40/2 },//25
{ -.36/2, 0, -.32/2 },//26
{ -.36/2, 0, -.08/2 },//27
{ .36/2, 0, -.08/2 },//28
{ .36/2, 0, -.32/2 },//29
{ -.36/2, -.04/2, -.32/2 },//30
{ -.36/2, -.04/2, -.08/2 },//31
{ .36/2, -.04/2, -.08/2 },//32
{ .36/2, -.04/2, -.32/2 },//33
{ -.36/2, .08/2, .08/2 },//34
{ -.60/2, .08/2, .08/2 },//35
{ -.60/2, -.12/2, .08/2 },//36
{ -.36/2, -.12/2, .08/2 },//37
{ -.36/2, .08/2, -.40/2 },//38
{ -.60/2, .08/2, -.40/2 },//39
{ -.60/2, -.12/2, -.40/2 },//40
{ -.36/2, -.12/2, -.40/2 },//41
{ -.48/2, -.04/2, .20/2 },//42
{ .36/2, .08/2, .08/2 },//43
{ .60/2, .08/2, .08/2 },//44
{ .60/2, -.12/2, .08/2 },//45
{ .36/2, -.12/2, .08/2 },//46
{ .36/2, .08/2, -.40/2 },//47
{ .60/2, .08/2, -.40/2 },//48
{ .60/2, -.12/2, -.40/2 },//49
{ .36/2, -.12/2, -.40/2 },//50
{ .48/2, -.04/2, .20/2 },//51
{ -.04/2, .08/2, .36/2 },//52
{ .04/2, .08/2, .36/2 },//53
{ -.04/2, .12/2, .52/2 },//54
{ .04/2, .12/2, .52/2 },//55

};

GLubyte ship1[120] = {0, 1, 3, 2,//0 c=7 0->9
14, 15, 11, 10,//1
18, 19, 23, 22,//2
26, 27, 28, 29,//3
38, 39, 35, 34,//4
43, 44, 48, 47,//5
// 56, 57, 58, 59,//6
// 59, 58, 57, 56,//7
// 60, 61, 62, 63,//8
// 63, 62, 61, 60,//9
6, 7, 1, 0,//10 c=24 10->19
19, 20, 24, 23,//11
22, 23, 24, 25,//12
22, 25, 21, 18,//13
26, 29, 33, 30,//14
31, 32, 28, 27,//15
34, 37, 41, 38,//16
39, 40, 36, 35,//17
47, 50, 46, 43,//18
49, 48, 44, 45,//19
5, 3, 1, 7,//20  c=14
0, 2, 4, 6,//21 c=30
4, 5, 7, 6, //22 c=8 22->28
10, 11, 9, 8,//23
2, 3, 5, 4,//24
20, 21, 25, 24,//25
33, 32, 31, 30,//26
40, 41, 37, 36,//27
45, 46, 50, 49,//28
41, 40, 39, 38,//29 c=28
47, 48, 49, 50,//30 c=28
10, 8, 12, 14,//31 c=19
9, 11, 15, 13,//32 c=27
16, 17, 15, 14};//32 c=3


red.Select();

glBegin(GL_QUADS);
for(int i = 0; i<=24; i+=4){

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
for(int i = 24; i<=96; i+=4){

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

engine.Select();

glBegin(GL_QUADS);
for(int i = 96; i<=104; i+=4){

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

glBegin(GL_QUADS);
for(int i = 104; i<=116; i+=4){

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
/*
blood.Select();
for(int i = 0;i<=30; i+=3){
glBegin(GL_TRIANGLES);
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
glEnd();
}*/


	glEndList();

	glNewList(gknDyingDisplay, GL_COMPILE);
		CTexture texture(13, "green_fire.bmp");
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
    void CProtoNelFighter::UnInit(void) {
        if(glIsList(gknAliveDisplay) == GL_TRUE) {
            glDeleteLists(gknAliveDisplay,1);
        }
        if(glIsList(gknDyingDisplay) == GL_TRUE) {
            glDeleteLists(gknDyingDisplay,1);
        }
    }
