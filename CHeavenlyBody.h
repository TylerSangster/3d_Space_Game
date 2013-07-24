//******************************************************************************
//CHeavenlyBody.h
//Copyright (C) 2007, Marcus Trenton, Tyler Sangster, and Sebastian Harko
//Originally written for Total Space Massacre, a project for CS 432 on 
//February 21th, 2007.
//******************************************************************************

#include "CEntity.h"
#include "CShot.h"

//##############################################################################
/** 
* @class CHeavenlyBody CHeavenlyBody.h
* 
* @brief Defines a spherical heavenly body (planet, sun, asteroid) with the
*   appropriate collision detection algorithm.
*/
//##############################################################################

#ifndef CHeavenlyBody_h
#define CHeavenlyBody_h 

class CHeavenlyBody: public CEntity {
    public:
        
        //----------------------------------------------------------------------
        /**
        * @brief The specification constructor which allowed a detailed 
        * creation.
        * @param akdPos The position in cartesian co-ordinates.
        * @param akdForward Where the CHeavenlyBody is facing.
        * @param akdUp What direction is up for the CHeavenlyBody.
        * @param kdSpeed The initial speed.
        */
        //----------------------------------------------------------------------
        CHeavenlyBody(GLdouble const akdPos[3], GLdouble const akdForward[3], 
             GLdouble const akdUp[3], const GLdouble kdSpeed);
             
        //----------------------------------------------------------------------
        /**
        * @brief Minimal specification constructor for stationary 
        * CHeavenlyBodies.
        *
        * @param akdPos The position in cartesian co-ordinates.
        */
        //----------------------------------------------------------------------
        CHeavenlyBody(GLdouble const akdPos[3]);
            
        //----------------------------------------------------------------------
        /**
        * @brief Determines whether this CHeavenlyBody collides with another 
        *   CEntity.
        *
        * @param pkcOtherEntity The other CEntity that this one could collide 
        * with.
        *
        * @return Whether they collided.
        */
        //----------------------------------------------------------------------		
	    virtual bool IsCollision(CEntity* const pkcOtherEntity);
	    
	    //----------------------------------------------------------------------
        /**
        * @brief The ship takes the specified amount of damage.
        *
        * @param knDamage The amount of damage taken.
        */
        //----------------------------------------------------------------------		
	    void TakeDamage(const int knDamage);
	    
	    //----------------------------------------------------------------------
        /**
        * @brief Returns the amount of damage the heavenly body does.
        *
        * @return The amount of damage.
        */
        //----------------------------------------------------------------------
        int GetDamage(void) {
            return m_nDamage;
        }
        
        //----------------------------------------------------------------------
	    /**
	    * @brief Resolve the CHeavenlyBody being hit by a CShot.
	    *
	    * @param pcProjectile The CShot that is hitting the CShip.
	    */
	    //----------------------------------------------------------------------
	    void ResolveCollision(CShot* pcProjectile);
        
        //----------------------------------------------------------------------
	    /**
	    * @brief Resolve the CHeavenlyBody being hit by another CHeavenlyBody.
	    *
	    * @param pcBody The CShot that is hitting the CShip.
	    */
	    //----------------------------------------------------------------------
	    void ResolveCollision(CHeavenlyBody* pcBody);	
            
    protected:
            
        /**
		* @brief How much damage is dealt to another CEntity when struck.
		*/
		int m_nDamage;
        /**
		* @brief Whether the heavenly body is immune to damage.
		*/
		bool m_bInvulnerable;
		/**
		* @brief The maximum health the heavenly body can have.
		*/
		int m_nMaxHealth;
		/**
		* @brief The current health the heavenly body has.
		*/
		int m_nHealth;
		
    private:
        
        //----------------------------------------------------------------------
        /**
        * @brief Handles creation that is present in both constructors.
        *  
        * Finishes the construction found in both constructors by setting the
        * bounding box, the display list ID's, and the scale to be undefined.
        * All of these values are flags are are later to be overwritten.
        *
        * @see CHeavenlyBody::CHeavenlyBody
        */
        //----------------------------------------------------------------------
        void CommonConstructor(void) {
            //These will be overwritten by subclasses.
            m_nDamage = gknUndefined;
            m_nMaxHealth = gknUndefined;
            m_nHealth = gknUndefined;
            m_bInvulnerable = true;
        }  
};
#endif //CHeavenlyBody
