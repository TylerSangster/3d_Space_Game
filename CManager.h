//******************************************************************************
//CManager.h
//Copyright (C) 2007, Marcus Trenton, Tyler Sangster, and Sebastian Harko
//Originally written for Total Space Massacre, a project for CS 432 on 
//February 21th, 2007.
//******************************************************************************

#include "TinyXml/tinyxml.h"

#ifndef CManager_h
#define CManager_h

//##############################################################################
/**
* @class CManager CManager.h
*
* @brief Represent a class that reads a level or ship information.
*/
//##############################################################################



class CManager{
	public:
		/**
		 * Constructor
		 *@param fname Specifies the name of the file containing the ship descriptions
		 */
		
		CManager(char* fname);
		
		/**
		 * Destructor
		 */
		~CManager(void);


	protected:
		// XML parsing stuf
		int CountElements(TiXmlElement* node);
		TiXmlDocument m_cDoc; 	
		TiXmlElement* m_pcRootNode; 
		TiXmlElement* FindElement(TiXmlElement* node, char *element);
		TiXmlElement* FindNextElement(TiXmlElement* node);
};

#endif //CManager_h
