//******************************************************************************
//CPluto.h
//Copyright (C) 2007, Marcus Trenton, Tyler Sangster, and Sebastian Harko
//Originally written for Total Space Massacre, a project for CS 432 on 
//March 22nd, 2007.
//******************************************************************************
 
#include "CHeavenlyBody.h"

//##############################################################################
/** 
* @class CPluto CPluto.h
* 
* @brief CPluto is the Pluto.
*/
//##############################################################################

#ifndef CPluto_h
#define CPluto_h 

class CPluto: public CHeavenlyBody {
    public:
        
        /**
        * @brief The display list id for a healthy Pluto.
        */
        static const int gknAliveDisplay = 322;        
        /**
        * @brief The display list id for a dying Pluto.
        */
        static const int gknDyingDisplay = 323;
        
        //----------------------------------------------------------------------
        /**
        * @brief The specification constructor which allowed a detailed 
        * creation.
        * @param akdPos The position in cartesian co-ordinates.
        * @param akdForward Where the CPluto is facing.
        * @param akdUp What direction is up for the CPluto.
        * @param kdSpeed The initial speed.
        */
        //----------------------------------------------------------------------
        CPluto(GLdouble const akdPos[3], GLdouble const akdForward[3], 
             GLdouble const akdUp[3], const GLdouble kdSpeed);
             
        //----------------------------------------------------------------------
        /**
        * @brief Minimal specification constructor for a stationary 
        * CPluto.
        *
        * @param akdPos The position in cartesian co-ordinates.
        */
        //----------------------------------------------------------------------
        CPluto(GLdouble const akdPos[3]);
        
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
        
    private:
        
        //----------------------------------------------------------------------
        /**
        * @brief Handles creation that is present in both constructors.
        *
        * @see CHeavenlyBody::CHeavenlyBody
        */
        //----------------------------------------------------------------------
        void CommonConstructor(void);
        
};
        
#endif //CPluto_h
