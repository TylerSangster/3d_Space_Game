//******************************************************************************
//Global.h
//Copyright (C) 2007, Marcus Trenton, Tyler Sangster, and Sebastian Harko
//Originally written for Total Space Massacre, a project for CS 432 on 
//February 21th, 2007.
//******************************************************************************

#include <GL/glut.h>

//##############################################################################
/**
* @file Global.h
* @brief Contains global constants, and functions needed frequently 
*   in the program.
*
* @date 01/03/2007
* @version 0.5
* 
*/
//##############################################################################

#ifndef CGlobal_h
#define CGlobal_h

/**
* @brief The index of the X co-ordinate/rotation.
*
* As a co-ordinate it is a cartesian. As a rotation angle it represents pitch.
*/
const int gknX = 0;
/**
* @brief The index of the Y co-ordinate/rotation.
*
* As a co-ordinate it is a cartesian. As a rotation angle it represents yaw.
*/
const int gknY = 1;
/**
* @brief The index of the Z co-ordinate/rotation.
*
* As a co-ordinate it is a cartesian. As a rotation angle it represents roll.
*/
const int gknZ = 2;
/**
* @brief The array index for red.
*/
const int gknRed = 0;    	
/**
* @brief The array index for green.
*/
const int gknGreen = 1;    	
/**
* @brief The array index for blue.
*/
const int gknBlue = 2;
/**
* @brief The index of the bounding box width.
*/
const int gknW = gknX;
/**
* @brief The index of the bounding box height.
*/
const int gknH = gknY;
/**
* @brief The index of the bounding box length.
*/
const int gknL = gknZ;
/**
* @brief The sentinel value for undefined.
*/
const int gknUndefined = -1;
/**
* @brief The number of keyboard keys used for ship input.
*/
const int gknShipInputKeys = 5;
/**
* @brief The array index for the brake key.
*/
const int gknBrake = 0;
/**
* @brief The array index for the accelerate key.
*/
const int gknAccelerate = 1;
/**
* @brief The array index for the decelerate key.
*/
const int gknDecelerate = 2;
/**
* @brief The array index for the fire left weapon key.
*/
const int gknFireLeft = 3;
/**
* @brief The array index for the fire right weapon key.
*/
const int gknFireRight = 4;

//------------------------------------------------------------------------------
/**
* @brief Turns degrees to radians.
*
* @param kdDegrees How many degrees.
* @return How many radians.
*/
//------------------------------------------------------------------------------
GLdouble DegToRad(const GLdouble kdDegrees);

//------------------------------------------------------------------------------
/**
* @brief Turns radians into degrees.
*
* @param kdRadians How many radians.
* @return How many degrees.
*/
//------------------------------------------------------------------------------
GLdouble RadToDeg(const GLdouble kdRadians);

//------------------------------------------------------------------------------
/**
* @brief Turns spherical Euler angles into a direction of movement vector.
*
* @param akdEuler Input: the array of Euler angles.
* @param adDirection Output: The array representing the direction vector.
*/
//------------------------------------------------------------------------------
void EulerToDirection(GLdouble const akdEuler[2], GLdouble adDirection[3]);

//------------------------------------------------------------------------------
/**
* @brief Multiplies a 4X4 matrix by a 4-vector.
*
* @param aakdMatrix Input: the 4X4 matrix.
* @param adVector Input & Output: The original vector overwritten with the
*   output vector.
*/
//------------------------------------------------------------------------------
void MatrixMultVector(GLdouble const aakdMatrix[4][4], GLdouble adVector[4]);

//------------------------------------------------------------------------------
/**
* @brief Multiplies 2 matrices together and returns the resulting matrix.
*
* @param aakdOp1 Input: The left operand, a 4X4 matrix.
* @param aakdOp2 Input: The right operand, a 4X4 matrix.
* @param aadResult Output: The resulting 4X4 matrix. 
*/
//------------------------------------------------------------------------------
void MatrixMultMatrix(GLdouble const aakdOp1[4][4],GLdouble const aakdOp2[4][4], 
     GLdouble aadResult[4][4]);

//------------------------------------------------------------------------------
/**
* @brief Turns an unit axis and an angle into a rotational matrix.
*
* @param akdAxis Input: The axis of rotation.
* @param kdAngle Input: The angle of rotation (in degrees) about the axis.
* @param aadMatrix Output: the 4X4 rotational matrix. 
*/
//------------------------------------------------------------------------------
void AxisAngleToMatrix(GLdouble const akdAxis[3], const GLdouble kdAngle, 
    GLdouble aadMatrix[4][4]);

//------------------------------------------------------------------------------
/**
* @brief Normalizes an array of 3 elements representing a vector so it has
*   unit length.
*
* @param adVector Input & Output: The vector to be normalized which is 
*   overwritten.
*/
//------------------------------------------------------------------------------
void Normalize(GLdouble adVector[3]);

//------------------------------------------------------------------------------
/**
* @brief Tests whether a ray intersects a 3D rectangle and, if so, returns the
*   point of intersection.
*
* @param akdBase Input: The starting point of the ray.
* @param akdRay Input: The direction of the ray.
* @param aakdP Input: The verctices of the rectangle in clockwise order.
* @param adHit Output: The point of intersection.
*
* @note Unused at the moment.
*
* @returns whether there was an intersection.
*/
//------------------------------------------------------------------------------
bool RayRectIntersect(GLdouble const akdBase[3], GLdouble const akdRay[3],
    GLdouble const aakdP[4][3], GLdouble adHit[3]);

//------------------------------------------------------------------------------    
/**
* @brief Performs a cross product.
*
* @param akdVector1 Input: The first vector.
* @param akdVector2 Input: The second vector.
* @param adResult Output: The resulting vector.
*
* @returns whether there was an intersection.
*/
//------------------------------------------------------------------------------
void Cross(GLdouble const akdVector1[3], GLdouble const akdVector2[3],
    GLdouble adResult[3]);

//------------------------------------------------------------------------------    
/**
* @brief Returns the angle (in radians) between two vectors.
*
* @param akdVector1 Input: The first vector.
* @param akdVector2 Input: The second vector.
*
* @returns The angle (in radians) between the vectors.
*/
//------------------------------------------------------------------------------
GLdouble GetAngle(GLdouble const akdVector1[3], GLdouble const akdVector2[3]);

//------------------------------------------------------------------------------
/**
* @brief Given a pair of unit vectors calculates the rotation matrix
*   needed to go from one to the other.
*
* @param akdOldVector Input: The old forward vector.
* @param akdNewVector Input: The new forward vector.
* @param aadMatrix Output: The resulting rotational matrix.
*/
//------------------------------------------------------------------------------
void GetRotMatrix(GLdouble const akdOldVector[3], 
    GLdouble const akdNewVector[3], GLdouble aadMatrix[4][4]);

//------------------------------------------------------------------------------
/**
* @brief Given a pair of forward and up vectors calculates the rotation matrix
*   needed to go from one to the other.
*
* @param akdOldForward Input: The old forward vector.
* @param akdOldUp Input: The old up vector.
* @param akdNewForward Input: The new forward vector.
* @param akdNewUp Input: The new up vector.
* @param aadMatrix Output: The resulting rotational matrix.
*/
//------------------------------------------------------------------------------
void GetRotMatrix(GLdouble akdOldForward[3], GLdouble akdOldUp[3], 
    GLdouble akdNewForward[3], GLdouble akdNewUp[3], GLdouble aadMatrix[4][4]);
    
#endif // CGlobal_h
