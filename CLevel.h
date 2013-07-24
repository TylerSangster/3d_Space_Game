//******************************************************************************
//CLevel.h
//Copyright (C) 2007, Marcus Trenton, Tyler Sangster, and Sebastian Harko
//Originally written for Total Space Massacre, a project for CS 432 on 
//February 21th, 2007.
//******************************************************************************

#include <vector>
#include "Global.h"
#include "CWeapon.h"
#include "CShot.h"
#include "CShip.h"
#include "CEntity.h"
#include "CLevelManager.h"

//##############################################################################
/**
* @class CLevel CLevel.h
*
* @brief Represents one level of the game and the engine needed to play it.
*/
//##############################################################################

#ifndef CLevel_h
#define CLevel_h 

class CLevel {	
	public:
        
        /**
    	* @brief The display list for the stars.
    	*/
        static const int gknStarDisplayId = 1000;
    	
    	//----------------------------------------------------------------------
    	/**
    	* @brief Creates the level through hard-coded variables.
    	*
    	* @param szLevelName the name of the level to be loaded.
    	*/
    	//----------------------------------------------------------------------
        CLevel(char* szLevelName);
        
    	//----------------------------------------------------------------------
    	/**
    	* @brief Destroys all data held in the level.
    	*/
    	//----------------------------------------------------------------------        
        ~CLevel(void);
	    
        //----------------------------------------------------------------------
    	/**
    	* @brief Creates all the display lists used in the level.
    	*/
    	//----------------------------------------------------------------------
        void Init(void);
        
        //----------------------------------------------------------------------
    	/**
    	* @brief Destroys all of the display lists used in the level.
    	*/
    	//----------------------------------------------------------------------
        void UnInit(void);
        
        //----------------------------------------------------------------------
    	/**
    	* @brief Updates level by 1 game cycle.
    	*
        * @param akbKeyPressed What keys were pressed.
        * @param kbMotionInput Whether there is input from motion of the mouse.
        * @param kdAngleRadians The angle of new motion. The plane is the
        *   local up and right with 0 being local right.
        * @param kdMagnitude How far the new motion is.
        *
        * @return Whether the player has completed the level.
    	*/
    	//----------------------------------------------------------------------       
        bool Update(bool const akbKeyPressed[gknShipInputKeys], 
            const bool kbMotionInput, const GLdouble kdAngleRadians, 
            const GLdouble kdMagnitude);
        
        //----------------------------------------------------------------------
    	/**
    	* @brief Draws the level.
    	*/
    	//----------------------------------------------------------------------
        void Draw(void);
             
	 
    protected:
	
        //----------------------------------------------------------------------
    	/**
    	* @brief Processes player input
    	*
        * @param akbKeyPressed What keys were pressed.
        * @param kbMotionInput Whether there is input from motion of the mouse.
        * @param kdAngleRadians The angle of new motion. The plane is the
        *   local up and right with 0 radians being local right.
        * @param kdMagnitude How far the new motion is.
    	*/
    	//----------------------------------------------------------------------        
        void ProcessPlayerInput(bool const akbKeyPressed[gknShipInputKeys], 
            const bool kbMotionInput, const GLdouble kdAngleRadians, 
            const GLdouble kdMagnitude);
        
        //----------------------------------------------------------------------
    	/**
    	* @brief Records new CEntities.
    	*/
    	//----------------------------------------------------------------------
        void RecordNewEntities(void);
        
        //----------------------------------------------------------------------
    	/**
    	* @brief Updates all of the CEntities.
    	*/
    	//----------------------------------------------------------------------
        void UpdateEntities(void);
        
        //----------------------------------------------------------------------
    	/**
    	* @brief Performs collision detection.
    	*/
    	//----------------------------------------------------------------------
        void CollisionDetection(void);
        
        //----------------------------------------------------------------------
    	/**
    	* @brief Deletes certain types of dead CEntities.
    	*/
    	//----------------------------------------------------------------------
        void DeleteEntities(void);
        
        //----------------------------------------------------------------------
    	/**
    	* @brief Determines if the player has completed the level.
    	*
    	* @return Whether the player has completed the level.
    	*/
    	//----------------------------------------------------------------------
        bool VictoryCheck(void);
        
        //----------------------------------------------------------------------
    	/**
    	* @brief Sets up the camera that follows that player ship.
    	*/
    	//----------------------------------------------------------------------
        void SetCamera(void);
        
        //----------------------------------------------------------------------
    	/**
    	* @brief Generate the display list to draw all the stars.
    	*/
    	//----------------------------------------------------------------------
        void InitStars(void);
        
	/**
	 * @brief State of the game. We want to print the game over message only onced.
	 */
	bool m_bGameOver;
	
        /**
    	* @brief The player's ship.
    	*/
        CShip* m_pcPlayerShip;
        
        /**
    	* @brief The vector that holds all the CShips in the level.
    	*/
        vector <CShip*>m_cShipVector;
        /**
    	* @brief The vector that holds all the CShots in the level.
    	*/
        vector <CShot*>m_cShotVector;
        /**
    	* @brief The vector that holds all the CWeapons in the level.
    	*/
        vector <CWeapon*>m_cWeaponVector;
        /**
    	* @brief The vector that holds all the CHeavenlyBodies in the level.
    	*/
    	vector <CHeavenlyBody*>m_cHeavenlyBodyVector;
        
        // more types of entities to be added later
};

#endif // CLevel_h




