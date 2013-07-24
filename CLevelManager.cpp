
//******************************************************************************
//CShip.cpp
//Copyright (C) 2007, Marcus Trenton, Tyler Sangster, and Sebastian Harko
//Originally written for Total Space Massacre, a project for CS 432 on 
//February 21th, 2007.
//******************************************************************************

#include "CLevelManager.h"
#include <iostream>
using namespace std;
//###############################################################################
/**
 * @class CLevelManager CLevelManager.h
 *
 * CLevelManager manages levels
 * @author Tyler Sangster and Sebastian Harko
 * @version 1.0
 */
//###############################################################################

CLevelManager::~CLevelManager(void){
	//EMPTY DESTRUCTOR
}


/*
 *@brief returns the human figter ship of a player
 */
CHumanFighter CLevelManager::GetPlayerHumanFighterShip(void){
		GLdouble adPos[3];
		GLdouble adForward[3];
		GLdouble adUp[3];
		GLdouble dSpeed; 
		int nTeam;
		adPos[0] = atof(playershipDef->Attribute("posX"));
		adPos[1] = atof(playershipDef->Attribute("posY"));
		adPos[2] = atof(playershipDef->Attribute("posZ"));
		adForward[0] = atof(playershipDef->Attribute("forwardX"));
		adForward[1] = atof(playershipDef->Attribute("forwardY"));
		adForward[2] = atof(playershipDef->Attribute("forwardZ"));
		adUp[0] = atof (playershipDef->Attribute("upX"));
		adUp[1] = atof (playershipDef->Attribute("upY"));
		adUp[2] = atof (playershipDef->Attribute("upZ"));
		dSpeed  =  atof (playershipDef->Attribute("speed"));		
		nTeam	=  atoi (playershipDef->Attribute("team"));
		return CHumanFighter(adPos, adForward, adUp, dSpeed, nTeam);
}

/*
 * @brief returns the robot fighter ship of the player
 */
CRobotFighter CLevelManager::GetPlayerRobotFighterShip(void){
		GLdouble adPos[3];
		GLdouble adForward[3];
		GLdouble adUp[3];
		GLdouble dSpeed; 
		int nTeam;
		adPos[0] = atof(playershipDef->Attribute("posX"));
		adPos[1] = atof(playershipDef->Attribute("posY"));
		adPos[2] = atof(playershipDef->Attribute("posZ"));
		adForward[0] = atof(playershipDef->Attribute("forwardX"));
		adForward[1] = atof(playershipDef->Attribute("forwardY"));
		adForward[2] = atof(playershipDef->Attribute("forwardZ"));
		adUp[0] = atof (playershipDef->Attribute("upX"));
		adUp[1] = atof (playershipDef->Attribute("upY"));
		adUp[2] = atof (playershipDef->Attribute("upZ"));
		dSpeed  =  atof (playershipDef->Attribute("speed"));		
		nTeam	=  atoi (playershipDef->Attribute("team"));
		return CRobotFighter(adPos, adForward, adUp, dSpeed, nTeam);
}

/*
 * @brief returns the protonel fighter ship of the player
 */

CProtoNelFighter CLevelManager::GetPlayerProtoNelFighterShip(void){
		GLdouble adPos[3];
		GLdouble adForward[3];
		GLdouble adUp[3];
		GLdouble dSpeed; 
		int nTeam;
		adPos[0] = atof(playershipDef->Attribute("posX"));
		adPos[1] = atof(playershipDef->Attribute("posY"));
		adPos[2] = atof(playershipDef->Attribute("posZ"));
		adForward[0] = atof(playershipDef->Attribute("forwardX"));
		adForward[1] = atof(playershipDef->Attribute("forwardY"));
		adForward[2] = atof(playershipDef->Attribute("forwardZ"));
		adUp[0] = atof (playershipDef->Attribute("upX"));
		adUp[1] = atof (playershipDef->Attribute("upY"));
		adUp[2] = atof (playershipDef->Attribute("upZ"));
		dSpeed  =  atof (playershipDef->Attribute("speed"));		
		nTeam	=  atoi (playershipDef->Attribute("team"));
		return CProtoNelFighter(adPos, adForward, adUp, dSpeed, nTeam);
}


/*
 * @brief returns the type of the ship of the player
 */
const char* CLevelManager::GetPlayerShipType(void){
	return playershipDef->Attribute("ship");
}


/**
* @brief Constructor for the Level Manager.
* @see CManager
* 
*/
CLevelManager::CLevelManager(char* fname): CManager(fname) {
	playershipDef = FindElement(m_pcRootNode->FirstChildElement(),"player");
	asteroidList = FindElement(m_pcRootNode->FirstChildElement(),"asteroids");	
	asteroidDef  = asteroidList->FirstChildElement();
	heavenlybodyList = FindElement(m_pcRootNode->FirstChildElement(),"bodies");
	heavenlybodyDef  = heavenlybodyList->FirstChildElement();
	protonelList = FindElement(m_pcRootNode->FirstChildElement(),"protonelfighters");
	protonelDef  = protonelList->FirstChildElement();
	humanfighterList =  FindElement(m_pcRootNode->FirstChildElement(),"humanfighters");
	humanfighterDef  =  humanfighterList->FirstChildElement();
	robotfighterList =  FindElement(m_pcRootNode->FirstChildElement(),"robotfighters");
	robotfighterDef  =  robotfighterList->FirstChildElement();

	solList  =    FindElement(m_pcRootNode->FirstChildElement(),"sun");
	solDef  =  solList->FirstChildElement();
       	
	marsList =  FindElement(m_pcRootNode->FirstChildElement(),"mars");
	marsDef  =  marsList->FirstChildElement();

	plutoList =  FindElement(m_pcRootNode->FirstChildElement(),"pluto");
	plutoDef  =  plutoList->FirstChildElement();

	neptuneList =  FindElement(m_pcRootNode->FirstChildElement(),"neptune");
	neptuneDef  =  neptuneList->FirstChildElement();
	
	uranusList =  FindElement(m_pcRootNode->FirstChildElement(),"uranus");
	uranusDef  =  uranusList->FirstChildElement();

	mercuryList =  FindElement(m_pcRootNode->FirstChildElement(),"mercury");
	mercuryDef  =  mercuryList->FirstChildElement();
	
	venusList =  FindElement(m_pcRootNode->FirstChildElement(),"venus");
	venusDef  =  venusList->FirstChildElement();
	

}

/*
 *@brief Is there another mars object in the world ?
 
 */
bool CLevelManager::IsNextMars(void){
	if (marsDef == NULL){
		return false;
	}else{
		return true;
	}
}


/*
 *@brief Is there another pluto object in the world ?
 
 */

bool CLevelManager::IsNextPluto(void){
	if (plutoDef == NULL){
		return false;
	}else{
		return true;
	}
}


/*
 *@brief Is there another neptune object in the world ?
 
 */

bool CLevelManager::IsNextNeptune(void){
	if (neptuneDef == NULL){
		return false;
	}else{
		return true;
	}
}

/*
 *@brief Is there another uranus object in the world ?
 
 */

bool CLevelManager::IsNextUranus(void){
	if (uranusDef == NULL){
		return false;
	}else{
		return true;
	}
}

/*
 *@brief Is there another mercury object in the world ?
 
 */

bool CLevelManager::IsNextMercury(void){
	if (mercuryDef == NULL){
		return false;
	}else{
		return true;
	}
}


/*
 *@brief Is there another venus object in the world ?
 
 */

bool CLevelManager::IsNextVenus(void){
	if (venusDef == NULL){
		return false;
	}else{
		return true;
	}
}



bool CLevelManager::IsNextHeavenlyBody(void){
	if (heavenlybodyDef == NULL ){
		return false;
	}else{
		return true;
	}

}

/*
 *@brief Is there another sol object in the world ?
 
 */

bool CLevelManager::IsNextSol(void){
	if (solDef == NULL){
		return false;
	}else{
		return true;
	}
}

/*
 *@brief Is there another earth object in the world ?
 
 */

bool CLevelManager::IsNextEarth(void){
	if (earthDef == NULL){
		return false;
	}else{
		return true;
	}
}


/*
 *@brief Is there another asteroid object in the world ?
 
 */

bool CLevelManager::IsNextAsteroid(void){
	if (asteroidDef == NULL ){
		return false;
	}else{
		return true;
	}

}


/*
 *@brief Is there another robot fighter object in the world ?
 
 */

bool CLevelManager::IsNextRobotFighter(void){
	if (robotfighterDef == NULL ){
		return false;
	}else{
		return true;
	}

}


/*
 *@brief Is there another human fighter object in the world ?
 
 */

bool CLevelManager::IsNextHumanFighter(void){
	if (humanfighterDef == NULL ){
		return false;
	}else{
		return true;
	}

}


/*
 *@brief Is there another protonel object in the world ?
 
 */

bool CLevelManager::IsNextProtoNelFighter(void){
	if (protonelDef == NULL ){
		return false;
	}else{
		return true;
	}

}

/*
 *@brief Returns the next protonel object.
 
 */


CProtoNelFighter CLevelManager::GetNextProtoNelFighter(void){
	if (protonelDef != NULL){
		GLdouble adPos[3];
		GLdouble adForward[3];
		GLdouble adUp[3];
		GLdouble dSpeed; 
		int nTeam;
		adPos[0] = atof(protonelDef->Attribute("posX"));
		adPos[1] = atof(protonelDef->Attribute("posY"));
		adPos[2] = atof(protonelDef->Attribute("posZ"));
		adForward[0] = atof(protonelDef->Attribute("forwardX"));
		adForward[1] = atof(protonelDef->Attribute("forwardY"));
		adForward[2] = atof(protonelDef->Attribute("forwardZ"));
		adUp[0] = atof (protonelDef->Attribute("upX"));
		adUp[1] = atof (protonelDef->Attribute("upY"));
		adUp[2] = atof (protonelDef->Attribute("upZ"));
		dSpeed  =  atof (protonelDef->Attribute("speed"));		
		nTeam	=  atoi (protonelDef->Attribute("team"));
		protonelDef = FindNextElement(protonelDef);		
		return CProtoNelFighter(adPos, adForward, adUp, dSpeed, nTeam);
	}
}


/*
 *@brief Returns the next robot fighter.
 
 */

CRobotFighter CLevelManager::GetNextRobotFighter(void){
	if (robotfighterDef != NULL){			
		GLdouble adPos[3];
		GLdouble adForward[3];
		GLdouble adUp[3];
		GLdouble dSpeed; 
		int nTeam;
		adPos[0] = atof(robotfighterDef->Attribute("posX"));
		adPos[1] = atof(robotfighterDef->Attribute("posY"));
		adPos[2] = atof(robotfighterDef->Attribute("posZ"));
		adForward[0] = atof(robotfighterDef->Attribute("forwardX"));
		adForward[1] = atof(robotfighterDef->Attribute("forwardY"));
		adForward[2] = atof(robotfighterDef->Attribute("forwardZ"));
		adUp[0] = atof (robotfighterDef->Attribute("upX"));
		adUp[1] = atof (robotfighterDef->Attribute("upY"));
		adUp[2] = atof (robotfighterDef->Attribute("upZ"));
		dSpeed  =  atof (robotfighterDef->Attribute("speed"));
		nTeam	=  atoi (robotfighterDef->Attribute("team"));
		robotfighterDef = FindNextElement(robotfighterDef);		
		return CRobotFighter(adPos, adForward, adUp, dSpeed, nTeam);
	}
}


/*
 *@brief Returns the next human fighter.
 
 */

CHumanFighter CLevelManager::GetNextHumanFighter(void){
	if (humanfighterDef != NULL){				
		GLdouble adPos[3];
		GLdouble adForward[3];
		GLdouble adUp[3];
		GLdouble dSpeed; 
		int nTeam;
		adPos[0] = atof(humanfighterDef->Attribute("posX"));
		adPos[1] = atof(humanfighterDef->Attribute("posY"));
		adPos[2] = atof(humanfighterDef->Attribute("posZ"));
		adForward[0] = atof(humanfighterDef->Attribute("forwardX"));
		adForward[1] = atof(humanfighterDef->Attribute("forwardY"));
		adForward[2] = atof(humanfighterDef->Attribute("forwardZ"));
		adUp[0] = atof (humanfighterDef->Attribute("upX"));
		adUp[1] = atof (humanfighterDef->Attribute("upY"));
		adUp[2] = atof (humanfighterDef->Attribute("upZ"));
		dSpeed  =  atof (humanfighterDef->Attribute("speed"));		
		nTeam	=  atoi (humanfighterDef->Attribute("team"));
		humanfighterDef = FindNextElement(humanfighterDef);		
		return CHumanFighter(adPos, adForward, adUp, dSpeed, nTeam);
	}
}



/*
 *@brief Returns the next asteroid.
 
 */

CAsteroid CLevelManager::GetNextAsteroid(void){
	if (asteroidDef != NULL){
		GLdouble adPos[3];
		GLdouble adForward[3];
		GLdouble adUp[3];
		GLdouble dSpeed; 
		int nTeam;
		adPos[0] = atof(asteroidDef->Attribute("posX"));
		adPos[1] = atof(asteroidDef->Attribute("posY"));
		adPos[2] = atof(asteroidDef->Attribute("posZ"));
		adForward[0] = atof(asteroidDef->Attribute("forwardX"));
		adForward[1] = atof(asteroidDef->Attribute("forwardY"));
		adForward[2] = atof(asteroidDef->Attribute("forwardZ"));
		adUp[0] = atof (asteroidDef->Attribute("upX"));
		adUp[1] = atof (asteroidDef->Attribute("upY"));
		adUp[2] = atof (asteroidDef->Attribute("upZ"));
		dSpeed  =  atof (asteroidDef->Attribute("speed"));
		asteroidDef = FindNextElement(asteroidDef);		
		return CAsteroid(adPos, adForward, adUp, dSpeed);
	}
}

/*
 *@brief Returns the next sun. 
 */

CSol CLevelManager::GetNextSol(void){
	if (solDef != NULL){
		GLdouble adPos[3];
		GLdouble adForward[3];
		GLdouble adUp[3];
		GLdouble dSpeed; 
		int nTeam;
		adPos[0] = atof(solDef->Attribute("posX"));
		adPos[1] = atof(solDef->Attribute("posY"));
		adPos[2] = atof(solDef->Attribute("posZ"));
		solDef = FindNextElement(solDef);		
		return CSol(adPos);
	}	
}

/*
 *@brief Returns the next earth.
 
 */

CEarth CLevelManager::GetNextEarth(void){
	if (earthDef != NULL){
		GLdouble adPos[3];
		GLdouble adForward[3];
		GLdouble adUp[3];
		GLdouble dSpeed;
		int nTeam;	
		adPos[0] = atof (earthDef->Attribute("posX"));
		adPos[1] = atof (earthDef->Attribute("posY"));
		adPos[2] = atof (earthDef->Attribute("posZ"));
		earthDef = FindNextElement(earthDef);
		return CEarth(adPos);
	}
}



/*
 *@brief Returns the next mars.
 
 */

CMars CLevelManager::GetNextMars(void){
	if (marsDef != NULL){
		GLdouble adPos[3];
		GLdouble adForward[3];
		GLdouble adUp[3];
		GLdouble dSpeed;
		int nTeam;	
		adPos[0] = atof (marsDef->Attribute("posX"));
		adPos[1] = atof (marsDef->Attribute("posY"));
		adPos[2] = atof (marsDef->Attribute("posZ"));
		marsDef = FindNextElement(marsDef);
		return CMars(adPos);
	}
}


/*
 *@brief Returns the next pluto.
 
 */


CPluto CLevelManager::GetNextPluto(void){
	if (plutoDef != NULL){
		GLdouble adPos[3];
		GLdouble adForward[3];
		GLdouble adUp[3];
		GLdouble dSpeed;
		int nTeam;	
		adPos[0] = atof (plutoDef->Attribute("posX"));
		adPos[1] = atof (plutoDef->Attribute("posY"));
		adPos[2] = atof (plutoDef->Attribute("posZ"));
		plutoDef = FindNextElement(plutoDef);
		return CPluto(adPos);
	}
}





/*
 *@brief Returns the next neptune.
 
 */


CNeptune CLevelManager::GetNextNeptune(void){
	if (neptuneDef != NULL){
		GLdouble adPos[3];
		GLdouble adForward[3];
		GLdouble adUp[3];
		GLdouble dSpeed;
		int nTeam;	
		adPos[0] = atof (neptuneDef->Attribute("posX"));
		adPos[1] = atof (neptuneDef->Attribute("posY"));
		adPos[2] = atof (neptuneDef->Attribute("posZ"));
		neptuneDef = FindNextElement(neptuneDef);
		return CNeptune(adPos);
	}
}



/*
 *@brief Returns the next uranus.
 
 */

CUranus CLevelManager::GetNextUranus(void){
	if (uranusDef != NULL){
		GLdouble adPos[3];
		GLdouble adForward[3];
		GLdouble adUp[3];
		GLdouble dSpeed;
		int nTeam;	
		adPos[0] = atof (uranusDef->Attribute("posX"));
		adPos[1] = atof (uranusDef->Attribute("posY"));
		adPos[2] = atof (uranusDef->Attribute("posZ"));
		uranusDef = FindNextElement(uranusDef);
		return CUranus(adPos);
	}
}



/*
 *@brief Returns the next mercury.
 
 */


CMercury CLevelManager::GetNextMercury(void){
	if (mercuryDef != NULL){
		GLdouble adPos[3];
		GLdouble adForward[3];
		GLdouble adUp[3];
		GLdouble dSpeed;
		int nTeam;	
		adPos[0] = atof (mercuryDef->Attribute("posX"));
		adPos[1] = atof (mercuryDef->Attribute("posY"));
		adPos[2] = atof (mercuryDef->Attribute("posZ"));
		mercuryDef = FindNextElement(mercuryDef);
		return CMercury(adPos);
	}
}


/*
 *@brief Returns the next venus.
 
 */

CVenus CLevelManager::GetNextVenus(void){
	if (venusDef != NULL){
		GLdouble adPos[3];
		GLdouble adForward[3];
		GLdouble adUp[3];
		GLdouble dSpeed;
		int nTeam;	
		adPos[0] = atof (venusDef->Attribute("posX"));
		adPos[1] = atof (venusDef->Attribute("posY"));
		adPos[2] = atof (venusDef->Attribute("posZ"));
		venusDef = FindNextElement(venusDef);
		return CVenus(adPos);
	}
}




