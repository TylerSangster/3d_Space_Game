//******************************************************************************
//CRobotFighter.h
//Copyright (C) 2007, Marcus Trenton, Tyler Sangster, and Sebastian Harko
//Originally written for Total Space Massacre, a project for CS 432 on 
//February 21th, 2007.
//******************************************************************************

#include "CShip.h"

//##############################################################################
/**
* @class CRobotFighter CRobotFighter.h
*
* @brief A fully functional fightercraft.
*/
//##############################################################################

#ifndef CRobotFighter_h
#define CRobotFighter_h

class CRobotFighter: public CShip {

	public:
        
        //----------------------------------------------------------------------
        /**
        * @brief Create a CRobotFighter with specified physical properties on
        *   a specified team.
        *
        * @param akdPos Where it is.
        * @param akdForward Where the CShip is facing.
        * @param akdUp What direction is up for the CShip.
        * @param kdSpeed How fast its going.
        * @param knTeam What team the ship is on.
        */
        //----------------------------------------------------------------------
        CRobotFighter(GLdouble const akdPos[3], GLdouble const akdForward[3], 
            GLdouble const akdUp[3], const GLdouble kdSpeed, 
            const int knTeam);
            
        //----------------------------------------------------------------------
        /**
        * @brief Creates the display lists.
        */
        //----------------------------------------------------------------------
        static void Init(void);
        
        //----------------------------------------------------------------------
        /**
        * @brief Destroys the display lists.
        */
        //----------------------------------------------------------------------
        static void UnInit(void);
        
        /**
        * @brief The display list id for a healthy ship.
        */
        static const int gknAliveDisplay = 1;        
        /**
        * @brief The display list id for a dying ship.
        */
        static const int gknDyingDisplay = 2;	
};
#endif //CRobotFighter_h
