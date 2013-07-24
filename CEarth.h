//******************************************************************************
//CEarth.h
//Copyright (C) 2007, Marcus Trenton, Tyler Sangster, and Sebastian Harko
//Originally written for Total Space Massacre, a project for CS 432 on 
//March 22nd, 2007.
//******************************************************************************
 
#include "CHeavenlyBody.h"

//##############################################################################
/** 
* @class CEarth CEarth.h
* 
* @brief CEarth is the Earth.
*/
//##############################################################################

#ifndef CEarth_h
#define CEarth_h 

class CEarth: public CHeavenlyBody {
    public:
        
        /**
        * @brief The display list id for a healthy Earth.
        */
        static const int gknAliveDisplay = 305;        
        /**
        * @brief The display list id for a dying Earth.
        */
        static const int gknDyingDisplay = 306;
        
        //----------------------------------------------------------------------
        /**
        * @brief The specification constructor which allowed a detailed 
        * creation.
        * @param akdPos The position in cartesian co-ordinates.
        * @param akdForward Where the CEarth is facing.
        * @param akdUp What direction is up for the CEarth.
        * @param kdSpeed The initial speed.
        */
        //----------------------------------------------------------------------
        CEarth(GLdouble const akdPos[3], GLdouble const akdForward[3], 
             GLdouble const akdUp[3], const GLdouble kdSpeed);
             
        //----------------------------------------------------------------------
        /**
        * @brief Minimal specification constructor for a stationary 
        * CEarth.
        *
        * @param akdPos The position in cartesian co-ordinates.
        */
        //----------------------------------------------------------------------
        CEarth(GLdouble const akdPos[3]);
        
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
        
#endif //CEarth_h
