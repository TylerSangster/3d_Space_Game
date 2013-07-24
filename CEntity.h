//******************************************************************************
//CEntity.h
//Copyright (C) 2007, Marcus Trenton, Tyler Sangster, and Sebastian Harko
//Originally written for Total Space Massacre, a project for CS 432 on 
//February 21th, 2007.
//******************************************************************************


//##############################################################################
/** 
* @class CEntity CEntity.h
* 
* @brief Defines an physical entity that has a position, orientation, bounding
* box, and the capability to move.
*/
//##############################################################################
 
#include <math.h>
#include "Global.h"

#ifndef CEntity_h
#define CEntity_h

using namespace std;

class CEntity{
	public:
        
        /**
        * @brief Represents the alive state of a CEntity.
        */
        static const int gknAlive = 0;
        /**
        * @brief Represents the dying state of a CEntity.
        * 
        * A dying ship would be drawn as exploding, a dying laser shot would be 
        * drawn as exploding energy.
        */
        static const int gknDying = 1;
        /**
        * @brief Represents the dead state of a CEntity. 
        *
        * Dead CEntities are no longer affect the level and are not drawn or 
        * meaningfully updated.
        */
        static const int gknDead = 2;
        /**
        * @brief How much the speed read in XML is scaled by. 
        *
        * Integers are easy for humans to understand and doubles easier for the
        * engine.
        */
        static const GLdouble gkdSpeedScale = 0.0004;
        /**
        * @brief How many game cycles it takes a CEntity to go from dying to 
        * dead.
        */
        static const int gknDyingDuration = 15;
    	/**
    	* @brief The scaling factor that increases the scale when CEntity is 
    	* dying.
    	*/
    	static const GLdouble gkdDyingScale = 1.1;
    	
    	//----------------------------------------------------------------------
		/**
		* @brief Returns the distance between the two positions.
		*
		* @param akdPos1 Input: The first position.
		* @param akdPos2 Input: The second position.
		* 
		* @return The distance.
		*
		* Calculates the square of the distance between two points. Since a 
		* square root takes a lot of calculation, it makes sense to not to use 
		* them when possible and used the square distance instead.
		*/
		//----------------------------------------------------------------------
		static inline GLdouble DistanceSquared(GLdouble const akdPos1[3], 
			GLdouble const akdPos2[3]) {
				
			GLdouble dDistance = 0.0;
			for(int i = 0; i < 3; i++) {
				dDistance += (akdPos1[i]-akdPos2[i])*(akdPos1[i]-akdPos2[i]);		
			}
			return dDistance;
		}

		//----------------------------------------------------------------------
		/**
		* @brief Returns the square of the distance between the two positions.
		*
		* @param akdPos1 Input: The first position.
		* @param akdPos2 Input: The second position.
		* 
		* @return The square of the distance.
		* Calculate the distance between two points.
		*
		* @warning This takes substantially more computing time than calculating 
		* 	the square of the distance.
		*/
		//----------------------------------------------------------------------
		static inline GLdouble Distance(GLdouble const akdPos1[3], 
			GLdouble const akdPos2[3]) {
			
			return sqrt(DistanceSquared(akdPos1, akdPos2));
		}
       
        //----------------------------------------------------------------------      
        /**
        * @brief The default constructor which uses defaults for variables.
        */
        //----------------------------------------------------------------------
        CEntity();
        
        //----------------------------------------------------------------------
        /**
        * @brief The specification constructor which allowed a detailed 
        * creation.
        * @param akdPos The position in cartesian co-ordinates.
        * @param akdForward Where the CEntity is facing.
        * @param akdUp What direction is up for the CEntity.
        * @param kdSpeed The initial speed.
        */
        //----------------------------------------------------------------------
        CEntity(GLdouble const akdPos[3], GLdouble const akdForward[3], 
            GLdouble const akdUp[3], const GLdouble kdSpeed);
        
        //----------------------------------------------------------------------
        /**
        * @brief Starts the process of dying.
        */
        //----------------------------------------------------------------------
        virtual void Die(void);
            
        //----------------------------------------------------------------------
        /**
        * @brief Determines whether this CEntity collides with another CEntity.
        *
        * @param pkcOtherEntity The other CEntity that this one could collide 
        * with.
        *
        * @return Whether these CEntities collided.
        */
        //----------------------------------------------------------------------		
	    virtual bool IsCollision(CEntity* const pkcOtherEntity);

        //----------------------------------------------------------------------
        /**
        * @brief Sets the speed.
        * @param kdSpeed The new speed.
        */
        //----------------------------------------------------------------------     
        void SetSpeed(const GLdouble kdSpeed) {
            m_dSpeed = kdSpeed;
        }
        
        //----------------------------------------------------------------------
        /**
        * @brief Sets a single position co-ordinate.
        * @param knIndex Which co-ordinate is being changed.
        * @param kdValue The new co-ordinate.
        */
        //----------------------------------------------------------------------	
        void SetPos(const int knIndex, const GLdouble kdValue) {
            m_adPos[knIndex] = kdValue;
        }
        
        //----------------------------------------------------------------------
        /**
        * @brief Sets the position to the given vector.
        * @param akdPos The new position as an array of 3 co-ordinates.
        */
        //----------------------------------------------------------------------
        void SetPosV(GLdouble const akdPos[3]) {
            m_adPos[gknX] = akdPos[gknX];
            m_adPos[gknY] = akdPos[gknY];
            m_adPos[gknZ] = akdPos[gknZ];
        }	
        
        //----------------------------------------------------------------------
        /**
        * @brief Sets a specific element of the forward vector to the value.
        * @param knIndex Which element is being changed.
        * @param kdValue The value.
        */
        //----------------------------------------------------------------------
        void SetForward(const int knIndex, const GLdouble kdValue) {
            m_adForward[knIndex] = kdValue;
        }
        
        //----------------------------------------------------------------------
        /**
        * @brief Sets the forward vector to the given vector.
        * @param akdForward The new vector as an array of 3 co-ordinates.
        */
        //----------------------------------------------------------------------
        void SetForwardV(GLdouble const akdForward[3]) {
            m_adForward[gknX] = akdForward[gknX];
            m_adForward[gknY] = akdForward[gknY];
            m_adForward[gknZ] = akdForward[gknZ];
        }
        
        //----------------------------------------------------------------------
        /**
        * @brief Sets a specific element of the up vector to the value.
        * @param knIndex Which element is being changed.
        * @param kdValue The value.
        */
        //----------------------------------------------------------------------
        void SetUp(const int knIndex, const GLdouble kdValue) {
            m_adUp[knIndex] = kdValue;
        }
        
        //----------------------------------------------------------------------
        /**
        * @brief Sets the up vector to the given vector.
        * @param akdUp The new vector as an array of 3 co-ordinates.
        */
        //----------------------------------------------------------------------
        void SetUpV(GLdouble const akdUp[3]) {
            m_adUp[gknX] = akdUp[gknX];
            m_adUp[gknY] = akdUp[gknY];
            m_adUp[gknZ] = akdUp[gknZ];
        }
        
        //----------------------------------------------------------------------
        /**
        * @brief Sets the state of the CEntity.
        * @param knState The new state.
        */
        //----------------------------------------------------------------------
        void SetState(const int knState) {
            m_nState = knState;
        }
        
        //----------------------------------------------------------------------
        /**
        * @brief Returns the specified position co-ordinate.
        * @param knIndex Which co-ordinate is being returned.
        * @return The specified co-ordinate.
        */
        //----------------------------------------------------------------------
        GLdouble GetPos(const int knIndex) {
            return m_adPos[knIndex]; 
        }
        
        //----------------------------------------------------------------------
        /**
        * @brief Returns the specified forward vector element.
        *
        * @param knIndex Which index being returned.
        * @return The value at that index.
        */
        //----------------------------------------------------------------------
        GLdouble GetForward(const int knIndex) { 
            return m_adForward[knIndex];
        }
        
        //----------------------------------------------------------------------
        /**
        * @brief Returns the specified up vector element.
        *
        * @param knIndex Which index being returned.
        * @return The value at that index.
        */
        //----------------------------------------------------------------------
        GLdouble GetUp(const int knIndex) { 
            return m_adUp[knIndex];
        }
        
        //----------------------------------------------------------------------
        /**
        * @brief Returns the speed.
        * @return The speed.
        */
        //----------------------------------------------------------------------
        GLdouble GetSpeed(void) {
            return m_dSpeed;
        } 
        
        //----------------------------------------------------------------------
        /**
        * @brief Returns how large the CEntity is.
        * @return The size.
        */
        //----------------------------------------------------------------------
        GLdouble GetScale(void) { 
            return m_dScale; 
        }
        
        //----------------------------------------------------------------------
        /**
        * @brief Returns how large the CEntity's bounding box in a given 
        *   direction is.
        * @return The size.
        */
        //----------------------------------------------------------------------
        GLdouble GetBox(const int gknSide) { 
            return m_adBox[gknSide]; 
        }
        
        //----------------------------------------------------------------------
        /**
        * @brief Returns the state of the CEntity.
        * @return The state.
        */
        //----------------------------------------------------------------------
        int GetState(void) { 
            return m_nState;
        }
	    
	    //----------------------------------------------------------------------
		/**
		* @brief Updates the CEntity by one game cycle.
		*/
		//----------------------------------------------------------------------
		virtual void Update(void);
		
		//----------------------------------------------------------------------
		/**
		* @brief Draws the CEntity. 
		*/
		//----------------------------------------------------------------------
		virtual void Draw(void);
		
	protected:
        
        /**
        * @brief How large the CEntity is.
        *
        * How large Entity is in the world. Every CEntity is drawn to tightly
        * fit in a 1 X 1 X 1 cube centred on the origin and then 
        * scaled to the appropriate size by this factor. For reasons of 
        * inheritance can't be delcared as const but should be treated as such.
        */
        GLdouble m_dScale;        
        /**
        * @brief The array of display list id used to draw the Entity.
        *
        * A CEntity has 2 display lists, an alive one and a dying one. The IDs
        * for those display lists are stored here.
        */
		int m_anDisplayId[2];	        
        /**
        * @brief How fast the CEntity is travelling.
        */		       
	    GLdouble m_dSpeed;       
        /**
        * @brief The position of the centre of the CEntity.
        */	
		GLdouble m_adPos[3];        
        /**
        * @brief The forward direction for the entity.
        *
        * @warning This must always be unit.
        */ 
		GLdouble m_adForward[3];		
		/**
        * @brief The the up direction for the entity.
        *
        * @warning This must always be unit.
        */
        GLdouble m_adUp[3];        
        /**
        * @brief The dimensions for the bounding box of the CEntity.
        */      
		GLdouble m_adBox[3];		
		/**
		* @brief The state the entity is in (alive, dying, dead).
		*/
		int m_nState;
		/**
		* @brief How many game cycles the CEntity has been dying.
		*/
		int m_nDyingCounter;  
        
    private:
        
        //----------------------------------------------------------------------
        /**
        * @brief Handles creation that is present in both constructors.
        *  
        * Finishes the construction found in both constructors by setting the
        * bounding box, the display list ID's, and the scale to be undefined.
        * All of these values are flags are are later to be overwritten.
        *
        * @see CEntity::CEntity
        */
        //----------------------------------------------------------------------
        void CommonConstructor(void) {
            m_nState = gknAlive;
            
            //Variables to be overwritten and given meaningful values by
            //subclasses.
            m_adBox[gknW] = gknUndefined; // bounding box
            m_adBox[gknH] = gknUndefined;
            m_adBox[gknL] = gknUndefined; 
            
            //The generic Entity doesn't have a display list
            m_anDisplayId[gknAlive] = gknUndefined;
            m_anDisplayId[gknDying] = gknUndefined;
            
    		//Initialize the scaling factor to be 1.
    		m_dScale = gknUndefined;

		//The CEntity isn't dying yet.
		m_nDyingCounter = 0;
        }	
};

#endif // CEntity_h
