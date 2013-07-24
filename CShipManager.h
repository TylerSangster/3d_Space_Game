/** @class CShipManager CShipManager.h
 * 
 * Used to read and load information that defines ships such as ship
 * health, energy and so on. 
 * 
 * @author Sebastian Harko and Tyler Sangster
 * @date 22/02/2007
 * @version 0.1
 */

#include "CManager.h"

#ifndef CShipManager_h
#define CShipManager_h

class CShipManager:public CManager {
	
	public:

		CShipManager(char* fname);
		~CShipManager(void);

		void LoadShipAttributes(char *name,
				int*, int*, int*, int*, int*, int*, int*, int*,int*,  
				double*, double*, double*, double*);
		
		/*
		 * 
		 * @returns the total number of ships
		 */
		int GetNumberOfShips(void);
		
		/*
		 * @returns An integer value attribute.
		 * @param shipName represents the name of the ship
		 * @param attribute represents the name of the attribute we want to obtain
		 */
		
		int iGetAttribute(char *shipName, char *attribute);

		/*
		 * @returns A double value attribute
		 * @param shipName represents the name of the ship.
		 * @param attribute represents the name of the attribute we want to obtain.
		 */

		double dGetAttribute(char *shipName, char *attribute);
		
		/*
		 * @returns The Display ID of the ship
		 * 
		 */
		int GetDisplayID(char *shipName);
		
	private:	
		int m_nNumShips;      // Number of ships defined in the file
};

#endif //CShipManager_h

