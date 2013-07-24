//******************************************************************************
//CVenus.h
//Copyright (C) 2007, Marcus Trenton, Tyler Sangster, and Sebastian Harko
//Originally written for Total Space Massacre, a project for CS 432 on 
//March 22nd, 2007.
//******************************************************************************
 
#include "CHeavenlyBody.h"

//##############################################################################
/** 
* @class CVenus CVenus.h
* 
* @brief CVenus is the Venus.
*/
//##############################################################################

#ifndef CVenus_h
#define CVenus_h 

class CVenus: public CHeavenlyBody {
    public:
        
        /**
        * @brief The display list id for a healthy Venus.
        */
        static const int gknAliveDisplay = 395;        
        /**
        * @brief The display list id for a dying Venus.
        */
        static const int gknDyingDisplay = 396;
        
        //----------------------------------------------------------------------
        /**
        * @brief The specification constructor which allowed a detailed 
        * creation.
        * @param akdPos The position in cartesian co-ordinates.
        * @param akdForward Where the CVenus is facing.
        * @param akdUp What direction is up for the CVenus.
        * @param kdSpeed The initial speed.
        */
        //----------------------------------------------------------------------
        CVenus(GLdouble const akdPos[3], GLdouble const akdForward[3], 
             GLdouble const akdUp[3], const GLdouble kdSpeed);
             
        //----------------------------------------------------------------------
        /**
        * @brief Minimal specification constructor for a stationary 
        * CVenus.
        *
        * @param akdPos The position in cartesian co-ordinates.
        */
        //----------------------------------------------------------------------
        CVenus(GLdouble const akdPos[3]);
        
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
        
#endif //CVenus_h
