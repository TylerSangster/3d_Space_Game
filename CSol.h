//******************************************************************************
//CSol.h
//Copyright (C) 2007, Marcus Trenton, Tyler Sangster, and Sebastian Harko
//Originally written for Total Space Massacre, a project for CS 432 on 
//March 22nd, 2007.
//******************************************************************************

#include "CHeavenlyBody.h"

//##############################################################################
/** 
* @class CSol CSol.h
* 
* @brief CSol is the Earth's sun and emits light.
*/
//##############################################################################

#ifndef CSol_h
#define CSol_h 

class CSol: public CHeavenlyBody {
    public:
        
        /**
        * @brief The display list id for a healthy sun.
        */
        static const int gknAliveDisplay = 303;        
        /**
        * @brief The display list id for a dying sun.
        */
        static const int gknDyingDisplay = 304;
        
        //----------------------------------------------------------------------
        /**
        * @brief The specification constructor which allowed a detailed 
        * creation.
        * @param akdPos The position in cartesian co-ordinates.
        * @param akdForward Where the CSol is facing.
        * @param akdUp What direction is up for the CSol.
        * @param kdSpeed The initial speed.
        */
        //----------------------------------------------------------------------
        CSol(GLdouble const akdPos[3], GLdouble const akdForward[3], 
             GLdouble const akdUp[3], const GLdouble kdSpeed);
             
        //----------------------------------------------------------------------
        /**
        * @brief Minimal specification constructor for a stationary 
        * CSol.
        *
        * @param akdPos The position in cartesian co-ordinates.
        */
        //----------------------------------------------------------------------
        CSol(GLdouble const akdPos[3]);
        
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
        
#endif //CSol_h
