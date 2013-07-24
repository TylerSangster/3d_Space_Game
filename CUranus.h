//******************************************************************************
//CUranus.h
//Copyright (C) 2007, Marcus Trenton, Tyler Sangster, and Sebastian Harko
//Originally written for Total Space Massacre, a project for CS 432 on 
//March 22nd, 2007.
//******************************************************************************
 
#include "CHeavenlyBody.h"

//##############################################################################
/** 
* @class CUranus CUranus.h
* 
* @brief CUranus is the Uranus.
*/
//##############################################################################

#ifndef CUranus_h
#define CUranus_h 

class CUranus: public CHeavenlyBody {
    public:
        
        /**
        * @brief The display list id for a healthy Uranus.
        */
        static const int gknAliveDisplay = 326;        
        /**
        * @brief The display list id for a dying Uranus.
        */
        static const int gknDyingDisplay = 327;
        
        //----------------------------------------------------------------------
        /**
        * @brief The specification constructor which allowed a detailed 
        * creation.
        * @param akdPos The position in cartesian co-ordinates.
        * @param akdForward Where the CUranus is facing.
        * @param akdUp What direction is up for the CUranus.
        * @param kdSpeed The initial speed.
        */
        //----------------------------------------------------------------------
        CUranus(GLdouble const akdPos[3], GLdouble const akdForward[3], 
             GLdouble const akdUp[3], const GLdouble kdSpeed);
             
        //----------------------------------------------------------------------
        /**
        * @brief Minimal specification constructor for a stationary 
        * CUranus.
        *
        * @param akdPos The position in cartesian co-ordinates.
        */
        //----------------------------------------------------------------------
        CUranus(GLdouble const akdPos[3]);
        
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
        
#endif //CUranus_h
