#include "CAsteroid.h"
#include "CManager.h"
#include "CProtoNelFighter.h"
#include "CRobotFighter.h"
#include "CHumanFighter.h"
#include "CEarth.h"
#include "CSol.h"

#include "CMars.h"
#include "CPluto.h"
#include "CNeptune.h"
#include "CUranus.h"
#include "CMercury.h"
#include "CVenus.h"

#ifndef CLevelManager_h
#define CLevelManager_h

class CLevelManager:public CManager{
	public:
		CLevelManager(char* fname);
		~CLevelManager(void);

		bool IsNextMars(void);
		CMars GetNextMars(void);
		
		bool IsNextPluto(void);
		CPluto GetNextPluto(void);

		bool IsNextNeptune(void);
		CNeptune GetNextNeptune(void);

		bool IsNextUranus(void);
		CUranus GetNextUranus(void);

		bool IsNextMercury(void);
		CMercury GetNextMercury(void);

		bool IsNextVenus(void);
		CVenus GetNextVenus(void);
		
		bool IsNextEarth(void);
		CEarth GetNextEarth(void);	
		
		bool IsNextSol(void);
		CSol GetNextSol(void);
		
		bool IsNextAsteroid(void);
		CAsteroid GetNextAsteroid(void);
		
		bool IsNextProtoNelFighter(void);
		CProtoNelFighter GetNextProtoNelFighter(void);
		
		bool IsNextRobotFighter(void);
		CRobotFighter GetNextRobotFighter(void);

		bool IsNextHumanFighter(void);
		CHumanFighter GetNextHumanFighter(void);

		bool IsNextHeavenlyBody(void);
		CHeavenlyBody GetNextHeavenlyBody(void);
		
		CHumanFighter    GetPlayerHumanFighterShip(void);
		CRobotFighter    GetPlayerRobotFighterShip(void);
		CProtoNelFighter GetPlayerProtoNelFighterShip(void);
		const char* GetPlayerShipType(void);

	private:
		
		TiXmlElement* playershipDef;
		
		TiXmlElement* solList;
		TiXmlElement* solDef;

		TiXmlElement* earthList;
		TiXmlElement* earthDef;

		TiXmlElement* marsList;
		TiXmlElement* marsDef;

		TiXmlElement* plutoList;
		TiXmlElement* plutoDef;

		TiXmlElement* neptuneList;
		TiXmlElement* neptuneDef;

		TiXmlElement* uranusList;
		TiXmlElement* uranusDef;

		TiXmlElement* mercuryList;
		TiXmlElement* mercuryDef;
		
		TiXmlElement* venusList;
		TiXmlElement* venusDef;

		TiXmlElement* robotfighterList;
		TiXmlElement* robotfighterDef;

		TiXmlElement* humanfighterList;
		TiXmlElement* humanfighterDef;
			
		TiXmlElement* asteroidList;
		TiXmlElement* asteroidDef;

		TiXmlElement* protonelList;
		TiXmlElement* protonelDef;

		TiXmlElement* heavenlybodyList;
		TiXmlElement* heavenlybodyDef;

};

#endif  // CLevelManager_h
