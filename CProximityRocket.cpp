//******************************************************************************
//CProximityRocket.cpp
//Copyright (C) 2007, Marcus Trenton, Tyler Sangster, and Sebastian Harko
//Originally written for Total Space Massacre, a project for CS 432 on 
//March 23rd, 2007.
//******************************************************************************

#include "CProximityRocket.h"

using namespace std;

//##############################################################################
/**
* @class CProximityRocket CProximityRocket.h
*
* Class Proximty Rocket is responsible for filling the statistics, specifying 
* what type of shot it creates, and how the weapon (not the shots) is drawn. 
* Everything else is done by inheritance. Proximity rockets have a larger 
* bounding box than is needed for its size allowing them to hit an enemy that
* would be a near miss for an ordinary rocket.
*
* @author Tyler Sangster
* @date Mon 19 Feb
* @version 1.0
*/
//##############################################################################

	//--------------------------------------------------------------------------
	/**
    * The CProximityRocket is created on board of an entity. The CWeapon 
    * constructor will handle everything except setting the weapon stats.
    *
    * @see CWeapon::CWeapon, CommonConstructor
    */
    //--------------------------------------------------------------------------
    CProximityRocket::CProximityRocket(CEntity* const pkcHost) : 
        CWeapon(pkcHost) {
            
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
    CProximityRocket::CProximityRocket(GLdouble const akdPos[3], 
        GLdouble const akdForward[3], GLdouble const akdUp[3], 
        const GLdouble kdSpeed) : 
        CWeapon(akdPos, akdForward, akdUp, kdSpeed) {
    	
    	CommonConstructor();
    }
    
    //--------------------------------------------------------------------------
    /**
    * Handles creation that is present in both constructors.
    *
    * @see CProximityRocket
    */
    //--------------------------------------------------------------------------
    void CProximityRocket::CommonConstructor(void) {
        
        int nShotSpeed;
        
        //Read these from XML
        //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%    			
		m_nFirepower = 100;           
		m_nRate = 8;         
		m_dRange = 1.5;
		m_nEnergy = 500;
		nShotSpeed = 60;
		m_bHoming = false;
		m_bDetonateOnShooter = false;
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
    * How to draw the proximity rocket in its alive and dying states. It tightly 
    * fits a 1 length cube centered on the origin.
    *
    * @warning Stubbed and currently useless.
    */
    //--------------------------------------------------------------------------
    void CProximityRocket::Init(void) {
    }
    
    //--------------------------------------------------------------------------
    /**
    * Destroys the display lists used.
    */
    //--------------------------------------------------------------------------
    void CProximityRocket::UnInit(void) {
        if(glIsList(gknAliveDisplay) == GL_TRUE) {
            glDeleteLists(gknAliveDisplay,1);
        }
        if(glIsList(gknDyingDisplay) == GL_TRUE) {
            glDeleteLists(gknDyingDisplay,1);
        }
    }
    
    //--------------------------------------------------------------------------
    /**
    * Create the CProximityRocketShot for the proximity rocket.
    */
    //--------------------------------------------------------------------------
    void CProximityRocket::CreateShots(GLdouble const akdBasePos[3], 
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
            adPos[i] = akdBasePos[i] + m_adBox[gknL]*1.5*akdLocalForward[i];
        }
    
        m_cNewShotVector.push_back(new CProximityRocketShot(adPos, adForward, 
            adUp, kdSpeed, knFirepower, kdRange, m_bHoming, 
            m_bDetonateOnShooter, pkcTarget, m_pcHost));
    }
