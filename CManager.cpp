 /*
 * @author Tyler Sangster and Sebastian Harko
 * @date 22/02/2007
 * @version 0.1
 */

#include "CManager.h"
#include <iostream>
using namespace std;

CManager::CManager(char* fname){	
	m_cDoc.LoadFile(fname);
	m_pcRootNode = m_cDoc.RootElement();	
}


CManager::~CManager(void){
	// EMPTY DESTRUCTOR
}

int CManager::CountElements(TiXmlElement* node){
    int numElem = 0;
    for(TiXmlElement* child = node; 
	child!=NULL;
	child = child->NextSiblingElement() ){
	    numElem ++ ;
     }
    return numElem;
	
}

TiXmlElement* CManager::FindNextElement(TiXmlElement* node){
	return node->NextSiblingElement();
}

TiXmlElement* CManager::FindElement(TiXmlElement* node, char *element){
	
	bool found = false;
	string name(element);
	TiXmlElement* child = node;	
	while (!found && child!=NULL){

		if ((child->Value()!=name)){
			child = child->NextSiblingElement();
		} else{
			found = true;
		}
	}

	if (found) {

		return child;
	}
	else{
		return NULL;
	}
}



