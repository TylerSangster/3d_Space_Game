//******************************************************************************
//CAsteroid.h
//Copyright (C) 2007, Marcus Trenton, Tyler Sangster, and Sebastian Harko
//Originally written for Total Space Massacre, a project for CS 432 on 
//March 13th, 2007.
//******************************************************************************

#include "CHeavenlyBody.h"

//##############################################################################
/** 
* @class CAsteroid CAsteroid.h
* 
* @brief A CAsteroid is a deadly space obstacle that can be destroyed.
*/
//##############################################################################

#ifndef CAsteroid_h
#define CAsteroid_h 

class CAsteroid: public CHeavenlyBody {
    public:
        
        /**
        * @brief The display list id for a healthy asteroid.
        */
        static const int gknAliveDisplay = 301;        
        /**
        * @brief The display list id for a dying asteroid.
        */
        static const int gknDyingDisplay = 302;
        
        //----------------------------------------------------------------------
        /**
        * @brief The specification constructor which allows a detailed 
        * creation.
        * @param akdPos The position in cartesian co-ordinates.
        * @param akdForward Where the CAsteroid is facing.
        * @param akdUp What direction is up for the CAsteroid.
        * @param kdSpeed The initial speed.
        */
        //----------------------------------------------------------------------
        CAsteroid(GLdouble const akdPos[3], GLdouble const akdForward[3], 
             GLdouble const akdUp[3], const GLdouble kdSpeed);
             
        //----------------------------------------------------------------------
        /**
        * @brief Minimal specification constructor for a stationary 
        * CAsteroid.
        *
        * @param akdPos The position in cartesian co-ordinates.
        */
        //----------------------------------------------------------------------
        CAsteroid(GLdouble const akdPos[3]);
        
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
        
#endif //CAsteroid_h
