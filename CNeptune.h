//******************************************************************************
//CNeptune.h
//Copyright (C) 2007, Marcus Trenton, Tyler Sangster, and Sebastian Harko
//Originally written for Total Space Massacre, a project for CS 432 on 
//March 22nd, 2007.
//******************************************************************************
 
#include "CHeavenlyBody.h"

//##############################################################################
/** 
* @class CNeptune CNeptune.h
* 
* @brief CNeptune is the Neptune.
*/
//##############################################################################

#ifndef CNeptune_h
#define CNeptune_h 

class CNeptune: public CHeavenlyBody {
    public:
        
        /**
        * @brief The display list id for a healthy Neptune.
        */
        static const int gknAliveDisplay = 324;        
        /**
        * @brief The display list id for a dying Neptune.
        */
        static const int gknDyingDisplay = 325;
        
        //----------------------------------------------------------------------
        /**
        * @brief The specification constructor which allowed a detailed 
        * creation.
        * @param akdPos The position in cartesian co-ordinates.
        * @param akdForward Where the CNeptune is facing.
        * @param akdUp What direction is up for the CNeptune.
        * @param kdSpeed The initial speed.
        */
        //----------------------------------------------------------------------
        CNeptune(GLdouble const akdPos[3], GLdouble const akdForward[3], 
             GLdouble const akdUp[3], const GLdouble kdSpeed);
             
        //----------------------------------------------------------------------
        /**
        * @brief Minimal specification constructor for a stationary 
        * CNeptune.
        *
        * @param akdPos The position in cartesian co-ordinates.
        */
        //----------------------------------------------------------------------
        CNeptune(GLdouble const akdPos[3]);
        
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
        
#endif //CNeptune_h
