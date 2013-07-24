//******************************************************************************
//CLevel.cpp
//Copyright (C) 2007, Marcus Trenton, Tyler Sangster, and Sebastian Harko
//Originally written for Total Space Massacre, a project for CS 432 on 
//February 21th, 2007.
//******************************************************************************

#include <iostream>
#include <math.h>
#include <cstdlib>
#include <GL/glut.h>
#include "CLevel.h"

//Include all of the Entities possible.
#include "CRobotFighter.h"
#include "CHumanFighter.h"
#include "CMinigun.h"

#include "CMinigunShot.h"
#include "CMicroLaser.h"
#include "CMicroLaserShot.h"
#include "CKyagRocket.h"
#include "CKyagRocketShot.h"
#include "CAsteroid.h"
#include "CSol.h"
#include "CEarth.h"
#include "CDoomRay.h"
#include "CDoomRayShot.h"
#include "CProtoNelFighter.h"
#include "CProximityRocket.h"
#include "CProximityRocketShot.h"
#include "CHomingMissile.h"
#include "CHomingMissileShot.h"


#include "CMars.h"
#include "CPluto.h"
#include "CNeptune.h"
#include "CUranus.h"
#include "CMercury.h"
#include "CVenus.h"
using namespace std;
 
//##############################################################################
/**
* @class CLevel CLevel.h
*
* Class CLevel is responsible for storing all the data for and updating a level
* of the game world. It deals with user input, telling entities to update,
* keeping track of new CEntities, and drawing all the CEntities.
*
* @author Tyler Sangster
* @date Mon 19 Feb
* @version 1.0
*/
//##############################################################################

    //--------------------------------------------------------------------------
    /**
    * Creates the level by creating the data structures to hold all of the 
    * objects. XML coding by Sebastian Harko.
    */
    //--------------------------------------------------------------------------
    CLevel::CLevel(char* szLevelName) {              	
    	m_bGameOver = false;
    
        CLevelManager *pcLevelReader = new CLevelManager(szLevelName);     
       	
    	if (strcmp(pcLevelReader->GetPlayerShipType(),"humanfighter") == 0 )		
    		m_pcPlayerShip = 
                new CHumanFighter(pcLevelReader->GetPlayerHumanFighterShip()); 
    	else
    		if (strcmp(pcLevelReader->GetPlayerShipType(),"robotfighter") == 0)
    			m_pcPlayerShip = new CRobotFighter(
                    pcLevelReader->GetPlayerRobotFighterShip());
    		else
    			m_pcPlayerShip = new CProtoNelFighter(
                    pcLevelReader->GetPlayerProtoNelFighterShip());
    	
            m_cShipVector.push_back(m_pcPlayerShip);   
    		
    	while ( pcLevelReader->IsNextSol()){  	
    		m_cHeavenlyBodyVector.push_back( 
                new CSol (pcLevelReader->GetNextSol()));	
    	}
    
    	while ( pcLevelReader->IsNextRobotFighter()){    	
    		m_cShipVector.push_back( 
                new CRobotFighter (pcLevelReader->GetNextRobotFighter()));	
    	}
    
    	while ( pcLevelReader->IsNextProtoNelFighter()){
    	
    		m_cShipVector.push_back( 
                new CProtoNelFighter (pcLevelReader->GetNextProtoNelFighter()));	
    	}
    
        while ( pcLevelReader->IsNextAsteroid()) {
    	        m_cHeavenlyBodyVector.push_back(
                    new CAsteroid(pcLevelReader->GetNextAsteroid()));
    	}
    
    	
    	while ( pcLevelReader->IsNextMars()){
    		m_cHeavenlyBodyVector.push_back(
                new CMars(pcLevelReader->GetNextMars()));
    	}	
    
    	
    	while ( pcLevelReader->IsNextPluto()){
    		m_cHeavenlyBodyVector.push_back(
                new CPluto(pcLevelReader->GetNextPluto()));
    	}	
    
    		
    	while ( pcLevelReader->IsNextNeptune()){
    		m_cHeavenlyBodyVector.push_back(
                new CNeptune(pcLevelReader->GetNextNeptune()));
    	}
    	
    	while ( pcLevelReader->IsNextUranus()){
    		m_cHeavenlyBodyVector.push_back(
                new CUranus(pcLevelReader->GetNextUranus()));
    	}	
    	
    	while ( pcLevelReader->IsNextMercury()){
    		m_cHeavenlyBodyVector.push_back(
                new CMercury(pcLevelReader->GetNextMercury()));
    	}	
    	
    	while ( pcLevelReader->IsNextVenus()){
    		m_cHeavenlyBodyVector.push_back(
                new CVenus(pcLevelReader->GetNextVenus()));
    	}	
    	
    	while ( pcLevelReader->IsNextHumanFighter()){
    		m_cShipVector.push_back( 
                new CHumanFighter(pcLevelReader->GetNextHumanFighter()));	
    	}	
           
        //Get the existing weapons the from the existing ships and create any
        //free-floating weapons.        
        for(int i = 0; i < m_cShipVector.size(); i++) {
            for(int j = 0; j < CShip::gknMaxWeapons;j++) {
                CWeapon* pcWeapon = m_cShipVector.at(i)->GetWeapon(j);
                if(pcWeapon != NULL) {
                    m_cWeaponVector.push_back(pcWeapon);
                }
            }
        }
    }
    
    //--------------------------------------------------------------------------
    /**
    * Destroys the CLevel by deleting all CEntities contained.
    */
    //--------------------------------------------------------------------------
    CLevel::~CLevel() {     
	
        //Delete the shots.
        for(int i = 0; i < m_cShotVector.size(); i++) {
            delete m_cShotVector.at(i);
        }

        //Delete the weapons.
        for(int i = 0; i < m_cWeaponVector.size(); i++) {
            delete m_cWeaponVector.at(i);
        }
        
        //Delete the ships.
        for(int i = 0; i < m_cShipVector.size(); i++) {
            delete m_cShipVector.at(i);
        }
        
        //Delete the heavenly bodies.
        for(int i = 0; i < m_cHeavenlyBodyVector.size(); i++) {
            delete m_cHeavenlyBodyVector.at(i);
        }
    }
    
    //--------------------------------------------------------------------------
    /**
    * Initializes all display lists used in CLevel.
    * This can't be in the constructor since the CLevel constructor could be 
    * called before glutInit, thus making any display lists created by the 
    * constructor unregistered.
    *
    * @warning Call this method after glutInit is called.
    */ 
    //--------------------------------------------------------------------------
    void CLevel::Init(void) {
	
		
        CRobotFighter::Init();
	CHumanFighter::Init();	
        CMinigun::Init();
        CMinigunShot::Init();
        CMicroLaser::Init();
        CMicroLaserShot::Init();
        CKyagRocket::Init();
        CKyagRocketShot::Init();
        CAsteroid::Init();
        CSol::Init();
        CEarth::Init();
	CMars::Init();
	CPluto::Init();
	CNeptune::Init();
	CUranus::Init();
	CMercury::Init();
	CVenus::Init();
        CDoomRay::Init();
        CDoomRayShot::Init();
        CProtoNelFighter::Init();
        CProximityRocket::Init();
        CProximityRocketShot::Init();
        CHomingMissile::Init();
        CHomingMissileShot::Init();        
        InitStars();

	
    }
    
    //--------------------------------------------------------------------------
    /**
    * Initializes all display lists used in CLevel.
    * This can't be in the constructor since the CLevel constructor is called 
    * before glutInit, thus making any display lists created by the constructor 
    * unregistered.
    *
    * @warning Call this method after glutInit is called.
    */ 
    //--------------------------------------------------------------------------
    void CLevel::UnInit(void) {


        //Delete the display lists of the entities.
	
        CRobotFighter::UnInit();
        CHumanFighter::UnInit();
        CMinigun::UnInit();
        CMinigunShot::UnInit();
        CMicroLaser::UnInit();
        CMicroLaserShot::UnInit();
        CKyagRocket::UnInit();
        CKyagRocketShot::UnInit();
        CSol::UnInit();
        CEarth::UnInit();
	CMars::UnInit();
        CAsteroid::UnInit();
        CDoomRay::UnInit();
        CDoomRayShot::UnInit();
        CProtoNelFighter::UnInit();
        CProximityRocket::UnInit();
        CProximityRocketShot::UnInit();
        CHomingMissile::UnInit();
        CHomingMissileShot::UnInit();
        
        //Delete the star's display lists.
        if(glIsList(gknStarDisplayId) == GL_TRUE) {
            glDeleteLists(gknStarDisplayId,1);
        }
    }
    
    //--------------------------------------------------------------------------
    /**
    * Draws the CLevel by first setting up the GLUT camera, drawing the stars, 
    * all Entities contained within it, and finally drawing the HUD display.
    */
    //--------------------------------------------------------------------------
    void CLevel::Draw(void) {
	
        SetCamera();
        
        //Draw the stars.      
        glCallList(gknStarDisplayId);
        
        //Draw the shots.
        for(int i = 0; i < m_cShotVector.size(); i++) {

            m_cShotVector.at(i)->Draw();
        }       

        
        //Draw the weapons.
        for(int i = 0; i < m_cWeaponVector.size(); i++) {
	  
            m_cWeaponVector.at(i)->Draw();
        }

                
        //Draw the ships.
        for(int i = 0; i < m_cShipVector.size(); i++) {
	  
            m_cShipVector.at(i)->Draw();
        }

        
        //Draw the planets.
        for(int i = 0; i < m_cHeavenlyBodyVector.size(); i++) {

            m_cHeavenlyBodyVector.at(i)->Draw();   
        }

	

    }
    
    //--------------------------------------------------------------------------
    /**
    * Updates the level by first processing player input, recording new 
    * CEntities, having all CEntities update themselves, doing 
    * collision detection, and performing a victory check.
    */
    //--------------------------------------------------------------------------   
    bool CLevel::Update(bool const akbKeyPressed[gknShipInputKeys], 
        const bool kbMotionInput, const GLdouble kdAngleRadians, 
        const GLdouble kdMagnitude) {
                 
        ProcessPlayerInput(akbKeyPressed, kbMotionInput, kdAngleRadians, 
            kdMagnitude);
        RecordNewEntities();
        UpdateEntities();
        CollisionDetection();
        
        //If the player is dead then print out so.
        if(m_pcPlayerShip->GetState() == CEntity::gknDead) {
    	    if (!m_bGameOver){
                cout << 
                    "##########################################################" 
                    "#############" << endl;
                cout << "Score "<< m_pcPlayerShip->GetScore() <<". Player is" 
                    "Dead. Game Over. Press 'y' to restart or 'n' to quit." 
                    << endl;
    	       cout << 
                    "##########################################################" 
                    "#############" << endl;
    	    }
            m_bGameOver = true;
        }
        
        DeleteEntities();
       
        return VictoryCheck();
    }
    
    //--------------------------------------------------------------------------
    /**
    * Use the mouse and keyboard to detect the player's commands with movement
    * and shooting. Pressing the moving the mouse causes the player's ship to 
    * change direction and the key cause it to change speed and fire weapons.
    */
    //--------------------------------------------------------------------------
    void CLevel::ProcessPlayerInput(bool const akbKeyPressed[gknShipInputKeys], 
        const bool kbMotionInput, const GLdouble kdAngleRadians, 
        const GLdouble kdMagnitude) {
        
        //Only process player input if the player is alive.
        //If the player is dead then print out so.
        if(m_pcPlayerShip->GetState() == CEntity::gknAlive) {        
            //Accelerate or declerate the ship.
            if(akbKeyPressed[gknAccelerate]) {
                m_pcPlayerShip->Accelerate();
            }
            if(akbKeyPressed[gknDecelerate]) {
                m_pcPlayerShip->Decelerate();
            }
            if(akbKeyPressed[gknBrake]) {
                m_pcPlayerShip->Brake();
            }
            
            //Change the heading.
            if(kbMotionInput) {
                m_pcPlayerShip->ChangeDirection(kdAngleRadians,kdMagnitude);
            }
            
            //Shoot the weapons. Determine if there is a target if seeing if
            //there is enemy who is with dTolerance degrees of the player's 
            //heading.
            CShip* pcTarget = NULL;
            GLdouble dTolerance = 7.0;
            bool bFound = false;
            for(int i = 0; i < m_cShipVector.size() && !bFound; i++) {
                CShip* pcCandidate = m_cShipVector.at(i);
                
                //Only living CShips that are not on the player's team are valid
                //targets.
                if(pcCandidate->GetTeam() != m_pcPlayerShip->GetTeam() && 
                    pcCandidate->GetState() == CEntity::gknAlive) {
                    
                    GLdouble adDirection[3];
                    GLdouble adPlayerForward[3];
                    
                    //Get the vector going from this ship to the target ship.
                    for(int i = 0; i < 3; i++) {
                        adPlayerForward[i] =  m_pcPlayerShip->GetForward(i);                 
                        adDirection[i] = 
                            pcCandidate->GetPos(i) - m_pcPlayerShip->GetPos(i);
                    }
                    Normalize(adDirection);
                    
                    //If the direction is very close to the forward vector then 
                    //don't bother rotating.
                    GLdouble dAngle = RadToDeg(
                        GetAngle(adPlayerForward, adDirection));
                        
                    //Check whether the angle is within tolerance.
                    if(dAngle <= dTolerance) {
                        bFound = true;
                        pcTarget = pcCandidate;
                    }
                }
            }
            
            if(akbKeyPressed[gknFireLeft]) {
                m_pcPlayerShip->Shoot(0, pcTarget);
            }
            if(akbKeyPressed[gknFireRight]) {
                m_pcPlayerShip->Shoot(1, pcTarget);
            }
        }
    }
    
    //--------------------------------------------------------------------------
    /**
    * Records all the new CEntities created in the last game cycle.
    */
    //--------------------------------------------------------------------------
    void CLevel::RecordNewEntities(void) {
        int nNewEntities;
        
        //Get the new shots from existing shots. (Cluster bombs fragment to
        //create bomblets).              
        for(int i = 0; i < m_cShotVector.size(); i++) {
            nNewEntities = m_cShotVector.at(i)->GetNumberNewShots();
            for(int j = 0; j < nNewEntities; j++) {
                m_cShotVector.push_back(m_cShotVector.at(i)->GetNewShot(j));
            }
            m_cShotVector.at(i)->ClearNewShots();            
        }
        
        //Get more new shots from weapons.
        for(int i = 0; i < m_cWeaponVector.size(); i++) {
            nNewEntities = m_cWeaponVector.at(i)->GetNumberNewShots();
            for(int j = 0; j < nNewEntities; j++) {
                m_cShotVector.push_back(m_cWeaponVector.at(i)->GetNewShot(j));
            }
            m_cWeaponVector.at(i)->ClearNewShots();           
        }
        
        //Get more new ships from existing ships (Carriers can spawn fighters). 
        for(int i = 0; i < m_cShipVector.size(); i++) {
            nNewEntities = m_cShipVector.at(i)->GetNumberNewShips();
            for(int j = 0; j < nNewEntities; j++) {
                m_cShipVector.push_back(m_cShipVector.at(i)->GetNewShip(j));
                //Also record the weapons onboard the ships.
                for(int j = 0; j < CShip::gknMaxWeapons;j++) {
                    CWeapon* pcWeapon = m_cShipVector.at(i)->GetWeapon(j);
                    if(pcWeapon != NULL) {
                        m_cWeaponVector.push_back(pcWeapon);
                    }
                }
            }
            m_cShipVector.at(i)->ClearNewShips();            
        }        
    }
    
    //--------------------------------------------------------------------------
    /**
    * Asks each CEntity to update itself.
    */
    //--------------------------------------------------------------------------
    void CLevel::UpdateEntities(void) {
        //Update the shots.
        for(int i = 0; i < m_cShotVector.size(); i++) {
            m_cShotVector.at(i)->Update();
        }

        //Update the weapons.
        for(int i = 0; i < m_cWeaponVector.size(); i++) {
            m_cWeaponVector.at(i)->Update();
        }
        
        //Update the heavenly bodies.
        for(int i = 0; i < m_cHeavenlyBodyVector.size(); i++) {
            m_cHeavenlyBodyVector.at(i)->Update();
        }
        
        //Update the ships. Ships require more information than other entities
        //to make start decisions, so more data is given.
        for(int i = 0; i < m_cShipVector.size(); i++) {
	
            m_cShipVector.at(i)->Update(m_pcPlayerShip, m_cShipVector, 
                m_cWeaponVector, m_cShotVector, m_cHeavenlyBodyVector);
        }
    }
    
    //--------------------------------------------------------------------------
    /**
    * Determine if any CShips have collided with other CEntities and process
    * the result. CShots will do damage, CWeapons will be picked up, etc...
    */
    //--------------------------------------------------------------------------
    void CLevel::CollisionDetection(void) {
        //Detect collisions between CShots and CShips/CHeavenlyBodies.
        //Use the CShot's collision detection algorithm instead of the other's
        //since the CShot may only collide under special circumstances (such
        //as mines not detonating on the layer. The exception is the 
        //CHeavenlyBody whose detection algorithm treats itself as a sphere and
        //thus it's algorithm should be called on.
        
        //Maintain parallel vectors of collisions that are processed after all
        //collisions are detected. That way an area-of-effect
        //detonation can affect everybody the way it's supposed to.
                
        vector <CShot*>cShotsHittingBodies;
        vector <CHeavenlyBody*>cBodiesHittingShots;

        vector <CShot*>cShotsHittingShips;
        vector <CShip*>cShipsHittingShots;
        
        vector <CShip*>cShipsHittingBodies;
        vector <CHeavenlyBody*>cBodiesHittingShips;
        
        vector <CShip*>cShipsHittingShips1;
        vector <CShip*>cShipsHittingShips2;
        
        vector <CHeavenlyBody*>cBodiesHittingBodies1;
        vector <CHeavenlyBody*>cBodiesHittingBodies2;
        
        //Detect the collisions between CShots and CShips/CHeavenlyBodies.
        for(int i = 0; i < m_cShotVector.size(); i++) {              
            for(int j = 0; j < m_cShipVector.size(); j++) {
                if(m_cShotVector.at(i)->IsCollision(m_cShipVector.at(j))) {
                    cShotsHittingShips.push_back(m_cShotVector.at(i));
                    cShipsHittingShots.push_back(m_cShipVector.at(j));
                }
            }
            for(int j = 0; j < m_cHeavenlyBodyVector.size(); j++) {
                if(m_cHeavenlyBodyVector.at(j)->IsCollision(
                    m_cShotVector.at(i))) {
                        
                    cShotsHittingBodies.push_back(m_cShotVector.at(i));
                    cBodiesHittingShots.push_back(m_cHeavenlyBodyVector.at(j));
                }
            }
        }
        
        //Detect the collisions between CShips and CHeavenlyBodies/CShips.
        for(int i = 0; i < m_cShipVector.size(); i++) {              
            for(int j = 0; j < m_cHeavenlyBodyVector.size(); j++) {
                if(m_cHeavenlyBodyVector.at(j)->IsCollision(
                    m_cShipVector.at(i))) {
                        
                    cShipsHittingBodies.push_back(m_cShipVector.at(i));
                    cBodiesHittingShips.push_back(m_cHeavenlyBodyVector.at(j));
                }
            }
            for(int j = i+1; j < m_cShipVector.size(); j++) {
                //Make sure that a ship doesn't collide with itself.
                if(m_cShipVector.at(j)->IsCollision(m_cShipVector.at(i)) 
                    && i != j) {
                        
                    cShipsHittingShips1.push_back(m_cShipVector.at(i));
                    cShipsHittingShips2.push_back(m_cShipVector.at(j));
                }
            }
        }
        
        //Detect the collisions between CHeavenlyBodies and CHeavenlyBodies.
        for(int i = 0; i < m_cHeavenlyBodyVector.size(); i++) {
            for(int j = i+1; j < m_cHeavenlyBodyVector.size(); j++) {
                if(m_cHeavenlyBodyVector.at(j)->IsCollision(
                    m_cHeavenlyBodyVector.at(i)) && i != j) {
                    
                    cBodiesHittingBodies1.push_back(
                        m_cHeavenlyBodyVector.at(i));
                    cBodiesHittingBodies2.push_back(
                        m_cHeavenlyBodyVector.at(j));
                }
            }
        }
        
        //C++ can not have recursive headers, so CShips can know what CShots are
        //but CShots can not know what CShips are. Since most interesting things
        //happen to CShips, CShips know about all the other subclasses of 
        //CEntity allowing it do things such as scoring for kills.
        
        //Resolve the shot-ship collisions.
        for(int i = 0; i < cShotsHittingShips.size(); i++) {
            cShipsHittingShots.at(i)->ResolveCollision(
                cShotsHittingShips.at(i));
        }
        
        //Resolve the shot-body collisions.
        for(int i = 0; i < cShotsHittingBodies.size(); i++) {
            cBodiesHittingShots.at(i)->ResolveCollision(
                cShotsHittingBodies.at(i));
        }
        
        //Resolve the ship-body collisions.
        for(int i = 0; i < cShipsHittingBodies.size(); i++) {
            cShipsHittingBodies.at(i)->ResolveCollision(
                cBodiesHittingShips.at(i));
        }
        
        //Resolve the ship-ship collisions.
        for(int i = 0; i < cShipsHittingShips1.size(); i++) {
            cShipsHittingShips1.at(i)->ResolveCollision(
                cShipsHittingShips2.at(i));
        }
        
        //Resolve the body-body collisions.
        for(int i = 0; i < cBodiesHittingBodies1.size(); i++) {
            cBodiesHittingBodies1.at(i)->ResolveCollision(
                cBodiesHittingBodies2.at(i));
        }
    }
    
    //--------------------------------------------------------------------------
	/**
	* Delete dead shots from the list. Keep ships and heavenly bodies, since
	* they could be part of a level objective.
	*/
	//--------------------------------------------------------------------------
    void CLevel::DeleteEntities(void) {
        int nSize = m_cShotVector.size();
        for(int i = 0; i < nSize; ) {
            if(m_cShotVector.at(i)->GetState() == CEntity::gknDead) {
                m_cShotVector.erase(m_cShotVector.begin()+i);
                nSize--;
            }
            else {
                i++;
            }
        }   
    }
    
    //--------------------------------------------------------------------------
	/**
	* The player has completed the level if all enemy ships are dead. Note that
	* the player doesn't have to a live. Ah, a true patriot.
	*/
	//--------------------------------------------------------------------------
    bool CLevel::VictoryCheck(void) {
        bool bEnemyAlive = false;
        int nPlayerTeam = m_pcPlayerShip->GetTeam();
        
        for(int i = 0; i < m_cShipVector.size() && !bEnemyAlive; i++) {
            if(m_cShipVector.at(i)->GetTeam() != nPlayerTeam &&
                m_cShipVector.at(i)->GetState() != CEntity::gknDead) {
                    
                bEnemyAlive = true;
            }
        }
        
        return !bEnemyAlive;
    }
    
    //--------------------------------------------------------------------------
    /**
    * Setup the camera so that it is above and behind the player's ship in a
    * classic third-person view. Also draws the aiming recticle.
    */
    //--------------------------------------------------------------------------
    void CLevel::SetCamera(void) {
        GLdouble adPlayerPos[3];
        GLdouble adPlayerForward[3];
        GLdouble adPlayerUp[3];
        GLdouble adBaseForward[3] = {0.0, 0.0, 1.0};
        GLdouble adBaseUp[3] = {0.0, 1.0, 0.0};
        
        for(int i = 0; i < 3; i++) {
            adPlayerPos[i] = m_pcPlayerShip->GetPos(i);
            adPlayerForward[i] = m_pcPlayerShip->GetForward(i);
            adPlayerUp[i] = m_pcPlayerShip->GetUp(i);
        }
        
        //Generate the matrix that represents a rotation to match the player's
        //ship's orientation.
        GLdouble aadRotMatrix[4][4];       
        GetRotMatrix(adBaseForward, adBaseUp, adPlayerForward, adPlayerUp, 
            aadRotMatrix);
           
        //Calculate the tracking vector.
        
        //How high (as an angle) is the tracking camera.
        GLdouble dTrackAngle = 5.0;
       //The angle of the camera is above the ship. 
        GLdouble adTrackEuler[3] = {dTrackAngle, 180.0, 0.0};        
        //The above angles expressed as a vector in homogenous co-ordinates.
        //The first three elements will be overwritten but the last element
        //is needed to mark it as a vector.
        GLdouble adTrackDirection[4] = {0.0, 0.0, 0.0, 0.0}; 
        EulerToDirection(adTrackEuler, adTrackDirection);
        //Rotate the camera to match the player's ship's orientation.
        MatrixMultVector(aadRotMatrix, adTrackDirection);
                 
        //Get the position of the camera and the position looked at.
        //The line formed by camera position and looked at position is parallel
        //to the line of the ship position and movement. 
         
        //How far behind the camera tracks the player's ship in shiplengths.
        GLdouble dTrackLengths = 3.0;
        //In world units how far back the camera is.
        GLdouble dScale = dTrackLengths*m_pcPlayerShip->GetScale();
        GLdouble adCamPos[3]; //The camera's position. 
        
        //The position the camera is looking at in homogeneous co-ordinates.
        //Initially defined to be a point directly above the ship.
        GLdouble adLookPos[4] = {0.0, 
            dScale*sin(DegToRad(dTrackAngle)),0.0,1.0};
        
        //How depressed the recticle is. A depression of 1.0 is no depression
        //and the recticle will be where the shot will be at inifinite distance.
        //The lower the number, the lower the recticle will appear.
        GLdouble aRecticleDepression = 0.85;
        GLdouble adRecticlePos[4] = {0.0, 
            adLookPos[gknY]*aRecticleDepression,0.0,1.0};
        
        //Rotate that point with the ship. 
        MatrixMultVector(aadRotMatrix, adLookPos);
        MatrixMultVector(aadRotMatrix, adRecticlePos);
        
        for(int i = 0; i < 3; i++) {
            adCamPos[i] = adPlayerPos[i] + dScale*adTrackDirection[i];
            adLookPos[i] += adPlayerPos[i];
            adRecticlePos[i] += adPlayerPos[i];
        }
        
        gluLookAt(
        	//Camera position.
        	adCamPos[gknX],adCamPos[gknY],adCamPos[gknZ],
            //Where the camera is looking.
            adLookPos[gknX],adLookPos[gknY],adLookPos[gknZ],
            //The up direction.
            adPlayerUp[gknX],adPlayerUp[gknY],adPlayerUp[gknZ]);
            
        //The targeting recticle.
        //The right direction, used for the targeting recticle.
        GLdouble adPlayerRight[3];
        Cross(adPlayerForward, adPlayerUp, adPlayerRight);
        Normalize(adPlayerRight);
        GLdouble dRecticleSide = 0.001;

		GLfloat afRed[3] = {1.0,0.0,0.0};
		GLfloat afNothing[3] = {0.0,0.0,0.0};
        glMaterialfv(GL_FRONT, GL_AMBIENT, afNothing);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, afNothing);
        glMaterialfv(GL_FRONT, GL_SPECULAR, afNothing);
        glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
        glMaterialfv(GL_FRONT, GL_EMISSION, afRed);

        glBegin(GL_LINE_LOOP);
            glVertex3d(
                adRecticlePos[gknX]+dRecticleSide*
                    (adPlayerUp[gknX]+adPlayerRight[gknX]),
                adRecticlePos[gknY]+dRecticleSide*
                    (adPlayerUp[gknY]+adPlayerRight[gknY]),
                adRecticlePos[gknZ]+dRecticleSide*
                    (adPlayerUp[gknZ]+adPlayerRight[gknZ]));
            glVertex3d(
                adRecticlePos[gknX]+dRecticleSide*
                    (adPlayerUp[gknX]-adPlayerRight[gknX]),
                adRecticlePos[gknY]+dRecticleSide*
                    (adPlayerUp[gknY]-adPlayerRight[gknY]),
                adRecticlePos[gknZ]+dRecticleSide*
                    (adPlayerUp[gknZ]-adPlayerRight[gknZ]));
            glVertex3d(
                adRecticlePos[gknX]+dRecticleSide*
                    (-adPlayerUp[gknX]-adPlayerRight[gknX]),
                adRecticlePos[gknY]+dRecticleSide*
                    (-adPlayerUp[gknY]-adPlayerRight[gknY]),
                adRecticlePos[gknZ]+dRecticleSide*
                    (-adPlayerUp[gknZ]-adPlayerRight[gknZ]));
            glVertex3d(
                adRecticlePos[gknX]+dRecticleSide*
                    (-adPlayerUp[gknX]+adPlayerRight[gknX]),
                adRecticlePos[gknY]+dRecticleSide*
                    (-adPlayerUp[gknY]+adPlayerRight[gknY]),
                adRecticlePos[gknZ]+dRecticleSide*
                    (-adPlayerUp[gknZ]+adPlayerRight[gknZ]));
        glEnd();
        
        //Draw the stats on the screen, relative to the recticle.
        
        //Removing this (and commenting out the code that uses it) causes 
        //glitching on level restart in Linux.
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        GLdouble dStatTopScalar = -50.0;
        GLdouble dStatHeight = 2.0;
        GLdouble dStatWidth = 20.0;
        
        GLfloat afBlue[3] = {0.0, 0.0, 1.0};
        GLfloat afGreen[3] = {0.0, 1.0, 0.0};
        GLdouble dPercent = 0.0;
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        
	    for(int i = 0; i < 3; i++) {
	    	
	    	//Choose the proper stat colour.
	    	switch(i)
    		{
    			//Shields
        		case 0:
        			glMaterialfv(GL_FRONT, GL_EMISSION, afBlue);
        			dPercent = m_pcPlayerShip->GetShield() /
        				(GLdouble) m_pcPlayerShip->GetMaxShield();
        			break;
        		//Health
        		case 1:
        			glMaterialfv(GL_FRONT, GL_EMISSION, afRed);
        			dPercent = m_pcPlayerShip->GetHealth() /
        				(GLdouble) m_pcPlayerShip->GetMaxHealth();
        			break;
        		//Energy
        		case 2:
        			glMaterialfv(GL_FRONT, GL_EMISSION, afGreen);
        			dPercent = m_pcPlayerShip->GetEnergy() /
        				(GLdouble) m_pcPlayerShip->GetMaxEnergy();
        			break;
    		}
    		
    		//The outline for each bar that is the max level.
    		glBegin(GL_LINE_LOOP);
	    	
            glVertex3d(
                adRecticlePos[gknX]+dRecticleSide*
                    (dStatTopScalar*adPlayerUp[gknX]+
                    dStatWidth*adPlayerRight[gknX]),
                adRecticlePos[gknY]+dRecticleSide*
                    (dStatTopScalar*adPlayerUp[gknY]+
                    dStatWidth*adPlayerRight[gknY]),
                adRecticlePos[gknZ]+dRecticleSide*
                    (dStatTopScalar*adPlayerUp[gknZ]+
                    dStatWidth*adPlayerRight[gknZ]));
            glVertex3d(
                adRecticlePos[gknX]+dRecticleSide*
                    (dStatTopScalar*adPlayerUp[gknX]),
                adRecticlePos[gknY]+dRecticleSide*
                    (dStatTopScalar*adPlayerUp[gknY]),
                adRecticlePos[gknZ]+dRecticleSide*
                    (dStatTopScalar*adPlayerUp[gknZ]));
            glVertex3d(
                adRecticlePos[gknX]+dRecticleSide*
                    ((dStatTopScalar-dStatHeight)*
                    adPlayerUp[gknX]),
                adRecticlePos[gknY]+dRecticleSide*
                    ((dStatTopScalar-dStatHeight)*
                    adPlayerUp[gknY]),
                adRecticlePos[gknZ]+dRecticleSide*
                    ((dStatTopScalar-dStatHeight)*
                    adPlayerUp[gknZ]));
            glVertex3d(
                adRecticlePos[gknX]+dRecticleSide*
                    ((dStatTopScalar-dStatHeight)*
                    adPlayerUp[gknX]+dStatWidth*adPlayerRight[gknX]),
                adRecticlePos[gknY]+dRecticleSide*
                    ((dStatTopScalar-dStatHeight)*
                    adPlayerUp[gknY]+dStatWidth*adPlayerRight[gknY]),
                adRecticlePos[gknZ]+dRecticleSide*
                    ((dStatTopScalar-dStatHeight)*
                    adPlayerUp[gknZ]+dStatWidth*adPlayerRight[gknZ]));
	                    
	         glEnd();
			
			 //The fill for each bar.
	         glBegin(GL_QUADS);
	           
	           glVertex3d(
                adRecticlePos[gknX]+dRecticleSide*
                    (dStatTopScalar*adPlayerUp[gknX]+
                    dStatWidth*dPercent*adPlayerRight[gknX]),
                adRecticlePos[gknY]+dRecticleSide*
                    (dStatTopScalar*adPlayerUp[gknY]+
                    dStatWidth*dPercent*adPlayerRight[gknY]),
                adRecticlePos[gknZ]+dRecticleSide*
                    (dStatTopScalar*adPlayerUp[gknZ]+
                    dStatWidth*dPercent*adPlayerRight[gknZ]));
            glVertex3d(
                adRecticlePos[gknX]+dRecticleSide*
                    (dStatTopScalar*adPlayerUp[gknX]),
                adRecticlePos[gknY]+dRecticleSide*
                    (dStatTopScalar*adPlayerUp[gknY]),
                adRecticlePos[gknZ]+dRecticleSide*
                    (dStatTopScalar*adPlayerUp[gknZ]));
            glVertex3d(
                adRecticlePos[gknX]+dRecticleSide*
                    ((dStatTopScalar-dStatHeight)*
                    adPlayerUp[gknX]),
                adRecticlePos[gknY]+dRecticleSide*
                    ((dStatTopScalar-dStatHeight)*
                    adPlayerUp[gknY]),
                adRecticlePos[gknZ]+dRecticleSide*
                    ((dStatTopScalar-dStatHeight)*
                    adPlayerUp[gknZ]));
            glVertex3d(
                adRecticlePos[gknX]+dRecticleSide*
                    ((dStatTopScalar-dStatHeight)*
                    adPlayerUp[gknX]+dStatWidth*dPercent*adPlayerRight[gknX]),
                adRecticlePos[gknY]+dRecticleSide*
                    ((dStatTopScalar-dStatHeight)*
                    adPlayerUp[gknY]+dStatWidth*dPercent*adPlayerRight[gknY]),
                adRecticlePos[gknZ]+dRecticleSide*
                    ((dStatTopScalar-dStatHeight)*
                    adPlayerUp[gknZ]+dStatWidth*dPercent*adPlayerRight[gknZ]));
	                    
	        glEnd();
	           
	        dStatTopScalar -= 2*dStatHeight;
	    }
    }
    
    //--------------------------------------------------------------------------
    /**
    * Generate the stars that fill the celestial sky. They are just points so
    * far away a player should never reach them. They are randomly placed on
    * seed random places equally distant from the origin.
    */
    //--------------------------------------------------------------------------
    void CLevel::InitStars(void) {
        //The number of stars in the sky.
        int nStars = 2000;
        GLdouble dRadius = 10.0;
        int nSeed = 10101;       
        srand(nSeed);
        
        glNewList(gknStarDisplayId, GL_COMPILE);
        GLfloat afAmbient[3] = {1.0,1.0,1.0};
        GLfloat afNothing[3] = {0.0,0.0,0.0};
        glMaterialfv(GL_FRONT, GL_AMBIENT, afNothing);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, afNothing);
        glMaterialfv(GL_FRONT, GL_SPECULAR, afNothing);
        glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
        glMaterialfv(GL_FRONT, GL_EMISSION, afAmbient);
        
        glBegin(GL_POINTS);
        for(int i = 0; i < nStars; i++) {
            double dPhi = DegToRad(180.0 * rand() / RAND_MAX);
            double dTheta = DegToRad(360.0 * rand() / RAND_MAX);
            
            glVertex3d(
                sin(dTheta)*sin(dPhi)*dRadius, 
                cos(dTheta)*sin(dPhi)*dRadius,
                cos(dPhi)*dRadius);
        }
        glEnd();
        glEndList();
    }
