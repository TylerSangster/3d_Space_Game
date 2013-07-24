//******************************************************************************
//CMercury.h
//Copyright (C) 2007, Marcus Trenton, Tyler Sangster, and Sebastian Harko
//Originally written for Total Space Massacre, a project for CS 432 on 
//March 22nd, 2007.
//******************************************************************************
 
#include "CHeavenlyBody.h"

//##############################################################################
/** 
* @class CMercury CMercury.h
* 
* @brief CMercury is the Earth.
*/
//##############################################################################

#ifndef CMercury_h
#define CMercury_h 

class CMercury: public CHeavenlyBody {
    public:
        
        /**
        * @brief The display list id for a healthy Earth.
        */
        static const int gknAliveDisplay = 328;        
        /**
        * @brief The display list id for a dying Earth.
        */
        static const int gknDyingDisplay = 329;
        
        //----------------------------------------------------------------------
        /**
        * @brief The specification constructor which allowed a detailed 
        * creation.
        * @param akdPos The position in cartesian co-ordinates.
        * @param akdForward Where the CMercury is facing.
        * @param akdUp What direction is up for the CMercury.
        * @param kdSpeed The initial speed.
        */
        //----------------------------------------------------------------------
        CMercury(GLdouble const akdPos[3], GLdouble const akdForward[3], 
             GLdouble const akdUp[3], const GLdouble kdSpeed);
             
        //----------------------------------------------------------------------
        /**
        * @brief Minimal specification constructor for a stationary 
        * CMercury.
        *
        * @param akdPos The position in cartesian co-ordinates.
        */
        //----------------------------------------------------------------------
        CMercury(GLdouble const akdPos[3]);
        
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
        
#endif //CMercury_h
