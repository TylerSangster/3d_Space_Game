//******************************************************************************
//CMinigun.cpp
//Copyright (C) 2007, Marcus Trenton, Tyler Sangster, and Sebastian Harko
//Originally written for Total Space Massacre, a project for CS 432 on 
//February 21th, 2007.
//******************************************************************************

#include "CMinigun.h"

using namespace std;

//##############################################################################
/**
* @class CMinigun CMinigun.h
*
* A respectably deadly mass driver weapon. Class Minigun is responsible for 
* filling the statistics, specifying what type of shot it creates, and how the 
* weapon (not the shots) is drawn. Everything else is done by inheritance.
*
* @author Marcus Trenton and Tyler Sangster
* @date Mon 19 Feb
* @version 1.0
*/
//##############################################################################

	//--------------------------------------------------------------------------
	/**
    * The CMinigun is created on board of an entity. The CWeapon constructor
    * will handle everything except setting the weapon stats.
    *
    * @see CWeapon::CWeapon, CommonConstructor
    */
    //--------------------------------------------------------------------------
    CMinigun::CMinigun(CEntity* const pkcHost) : CWeapon(pkcHost) {
    	CommonConstructor();
    }
    
    //--------------------------------------------------------------------------
    /**
    * The weapon is free-floating. The Weapon constructor will handle everything 
    * except setting the weapon stats.
    *
    * @see CWeapon::CWeapon, CommonConstructor
    */
    //--------------------------------------------------------------------------
    CMinigun::CMinigun(GLdouble const akdPos[3], GLdouble const akdForward[3],
        GLdouble const akdUp[3], const GLdouble kdSpeed) : 
        CWeapon(akdPos, akdForward, akdUp, kdSpeed) {
    	
    	CommonConstructor();
    }
    
    //--------------------------------------------------------------------------
    /**
    * Handles creation that is present in both constructors.
    *
    * @see CMinigun
    */
    //--------------------------------------------------------------------------
    void CMinigun::CommonConstructor(void) {
        
        int nShotSpeed;
        
        //Read these from XML
        //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%    			
		m_nFirepower = 50;           
		m_nRate = 4;         
		m_dRange = 1.0;
		m_nEnergy = 150;
		nShotSpeed = 100;
		m_bHoming = false;
		m_bDetonateOnShooter = true;
		m_dScale = 0.005;
        m_adBox[gknW] = m_dScale;
        m_adBox[gknH] = m_dScale;
        m_adBox[gknL] = m_dScale;
        //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        
        //The shot speed is more convient to a human as a int. This turns the
        //speed into its actual world speed.
		m_dShotSpeed = ((GLdouble)nShotSpeed) * gkdSpeedScale;
        
        m_anDisplayId[gknAlive] = gknAliveDisplay;
		m_anDisplayId[gknDying] = gknDyingDisplay;
    }
    
    //--------------------------------------------------------------------------
    /**
    * How to draw the minigun in its alive and dying states. It tightly fits a 1 
    * length cube centered on the origin.
    *
    * @warning Stubbed and currently useless.
    */
    //--------------------------------------------------------------------------
    void CMinigun::Init(void) {	
    }
    
    //--------------------------------------------------------------------------
    /**
    * Destroys the display lists used.
    */
    //--------------------------------------------------------------------------
    void CMinigun::UnInit(void) {
        if(glIsList(gknAliveDisplay) == GL_TRUE) {
            glDeleteLists(gknAliveDisplay,1);
        }
        if(glIsList(gknDyingDisplay) == GL_TRUE) {
            glDeleteLists(gknDyingDisplay,1);
        }
    }
    
    //--------------------------------------------------------------------------
    /**
    * Create the CMinigunShots for the minigun.
    */
    //--------------------------------------------------------------------------
    void CMinigun::CreateShots(GLdouble const akdBasePos[3], 
        GLdouble const akdLocalForward[3], GLdouble const akdLocalUp[3],
        GLdouble const akdLocalRight[3], const GLdouble kdSpeed, 
        const int knFirepower, const GLdouble kdRange, 
        CEntity* const pkcTarget) {
            
        //Keep the same facing as the host CShip.
        GLdouble adForward[3];
        GLdouble adUp[3];
        for(int i = 0; i < 3; i++) {
		  adForward[i] = m_pcHost->GetForward(i);
		  adUp[i] = m_pcHost->GetUp(i);
        }
		
        //Place the shot enough ahead of the CShip so the bounding boxes do not
        //meet.
		GLdouble adPos[3];
		for(int i = 0; i < 3; i++) {
            adPos[i] = akdBasePos[i] + m_adBox[gknL]*1.5*akdLocalForward[i] +
                -0.2*m_adBox[gknW]*akdLocalRight[i];
        }
    
        //The first shot.
        m_cNewShotVector.push_back(new CMinigunShot(adPos, adForward, adUp, 
            kdSpeed, knFirepower, kdRange, m_bHoming, m_bDetonateOnShooter, 
            pkcTarget, m_pcHost));

        //Alter the positions so the shots are spaced nicely.
        for(int i = 0; i < 3; i++) {
            adPos[i] = akdBasePos[i] + m_adBox[gknL]*1.5*akdLocalForward[i] +
                +0.2*m_adBox[gknW]*akdLocalRight[i];
        }
        
        //The second shot.
        m_cNewShotVector.push_back(new CMinigunShot(adPos, adForward, adUp, 
            kdSpeed, knFirepower, kdRange, m_bHoming, m_bDetonateOnShooter, 
            pkcTarget, m_pcHost));
    }
    
