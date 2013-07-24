//******************************************************************************
//CRobotFighter.cpp
//Copyright (C) 2007, Marcus Trenton, Tyler Sangster, and Sebastian Harko
//Originally written for Total Space Massacre, a project for CS 432 on 
//February 21th, 2007.
//******************************************************************************



#include "CShipManager.h"

#include <string>
#include <iostream>
using namespace std;


//#################################################################
/*@brief Load some attributes into a ship
 *@author Tyler Sangster and  Sebastian Harko 
 *
 */
//##################################################################
void CShipManager::LoadShipAttributes(char* name,
		int* nMaxHealth,
		int* nMaxShield,
		int* nMaxEnergy,
		int* nRecharge,
		int* nShieldEff,
		int* nWeaponEff,
		int* nEngineEff,
		int* nManeuv,
		int* nMaxSpeed,
		double* dScale,
		double* dBoxH,
		double* dBoxW,
		double* dBoxL
		){
			
	*nMaxHealth = iGetAttribute(name,"max_health");
	
	*nMaxShield = iGetAttribute(name,"max_shield");	
	
	*nMaxEnergy = iGetAttribute(name,"max_energy");
	
	*nRecharge  = iGetAttribute(name,"recharge");
	
	*nShieldEff = iGetAttribute(name,"shield_efficiency");
	
	*nWeaponEff = iGetAttribute(name,"weapon_efficiency");
	
	*nEngineEff = iGetAttribute(name,"engine_efficiency");
	
	*nManeuv    = iGetAttribute(name,"maneuverability");
	
	*nMaxSpeed  = iGetAttribute(name,"max_speed");
	
	*dScale     = dGetAttribute(name,"scale");
	
	*dBoxH      = dGetAttribute(name,"box_height");
	
	*dBoxW      = dGetAttribute(name,"box_width");
	
	*dBoxL      = dGetAttribute(name,"box_length");
	

}
//################################################################
/*@brief Get the display ID of a ship.
 *@param shipName The name of the ship.
 */
 //###############################################################
 
int CShipManager::GetDisplayID(char *shipName){
	TiXmlElement* tag = FindElement(m_pcRootNode->FirstChildElement(),shipName);
	tag = FindElement(tag->FirstChildElement(),"Display");
	return atoi(tag->Attribute("shipID"));
}
//################################################################
/*@brief Gets the total number of ships found in a file.
 * 
 */
 //###############################################################

int CShipManager::GetNumberOfShips(void){
	return m_nNumShips;
}
//#####################################################################
/*@brief Constructor for the CShipManager class.
 * 
 */
 //#####################################################################
CShipManager::CShipManager(char* fname): CManager(fname) {		
	m_nNumShips = CountElements(m_pcRootNode->FirstChildElement());
}
//###################################################################
/*@brief Empty Destructor.
 * 
 */
 //##################################################################
CShipManager::~CShipManager(void){
	// EMPTY DESTRUCTOR
}
//#######################################################
/*@brief Gets an attribute which is an integer.
 *@param shipName The name of the ship.
 *@param attribute An attribute of the ship.
 */
 //######################################################
 
int CShipManager::iGetAttribute(char *shipName, char *attribute){
	TiXmlElement* tag = FindElement(m_pcRootNode->FirstChildElement(),shipName);
	tag = FindElement(tag->FirstChildElement(), "characteristics");
	return atoi(tag->Attribute(attribute));
	
}

//########################################################
/*@brief Gets an attribute which is a double.
 *@param shipName The name of the ship.
 *@param attribute An attribute of the ship.
 */
 //#######################################################
 
double CShipManager::dGetAttribute(char *shipName,char *attribute){
	TiXmlElement* tag = FindElement(m_pcRootNode->FirstChildElement(),shipName);
	tag = FindElement(tag->FirstChildElement(),"characteristics");
	return atof(tag->Attribute(attribute));
}


