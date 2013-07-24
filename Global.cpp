//******************************************************************************
//Global.cpp
//Copyright (C) 2007, Marcus Trenton, Tyler Sangster, and Sebastian Harko
//Originally written for Total Space Massacre, a project for CS 432 on 
//February 21th, 2007.
//******************************************************************************

#include <iostream> //For debugging only.
#include "Global.h"
#include <math.h>

using namespace std;

//##############################################################################
/**
* @file Global.cpp
* Global.cpp contains functions that are used frequently throughout the program.
* All These functions are mathimatical or geometrical.
*
*
* @date 01/03/2007
* @version 1.0
*
* @par Acknowledgements
* Ray-Rectangle intersection algorithm adpated from 
* http://answers.google.com/answers/threadview?id=18979
*/
//##############################################################################

//------------------------------------------------------------------------------
/**
* Transforms an angle from degrees to radians. Radians are used for the
* trigonometry functions while OpenGL uses degrees.
* 
* @see RadToDeg
*/
//------------------------------------------------------------------------------
inline GLdouble DegToRad(GLdouble const kdDegrees) {
    return M_PI / 180.0 * kdDegrees;
}

//------------------------------------------------------------------------------
/**
* Transforms an angle from radians to degrees. Radians are used for the
* trigonometry functions while OpenGL uses degrees.
* 
* @see DegToRad
*/
//------------------------------------------------------------------------------
inline GLdouble RadToDeg(GLdouble const kdRadians) {
    return 180.0 / M_PI * kdRadians;
}

//------------------------------------------------------------------------------
/**
* Turns the spherical angles (X and Y Euler angles) into a vector that points
* in that direction. Z is roll so it does not affect position, only orientation.
* It is much faster than using GetEulerRotMatrix
*
* @warning Only use if the roll is 0, otherwise use GetEulerRotMatrix and 
*   MatrixMultVector.
*
* @see GetEulerRotMatrix and MatrixMultVector
*/
//------------------------------------------------------------------------------
void EulerToDirection(GLdouble const akdEulerAngle[2],GLdouble adDirection[3]) {
	adDirection[gknX] = sin(DegToRad(akdEulerAngle[gknY]))*
        cos(DegToRad(akdEulerAngle[gknX]));
	adDirection[gknY] = sin(DegToRad(akdEulerAngle[gknX]));
	adDirection[gknZ] = cos(DegToRad(akdEulerAngle[gknY]))*
	   cos(DegToRad(akdEulerAngle[gknX]));
}

//------------------------------------------------------------------------------
/**
* Multiplies a 4X4 matrix by a 4-vector and overwrites the vector with the 
* results.
*
* @see MatrixMultMatrix
*/
//------------------------------------------------------------------------------
inline void MatrixMultVector(GLdouble const aakdMatrix[4][4], 
	GLdouble adVector[4]) {
        
    GLdouble adTemp[4];
    for(int i = 0; i < 4; i++){
        adTemp[i] = 0.0;
    }
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            adTemp[i] += aakdMatrix[i][j]*adVector[j];   
        }
    } 
    for(int i = 0; i < 4; i++) {
            adVector[i] = adTemp[i];
    }   
}

//------------------------------------------------------------------------------
/**
* Multiplies 2 4X4 matrices in the order provided and stores the result in 
* another matrix.
*
* @see MatrixMultVector
*/
//------------------------------------------------------------------------------
inline void MatrixMultMatrix(GLdouble const aakdOp1[4][4],
	GLdouble const aakdOp2[4][4], GLdouble aadResult[4][4]) {
     	
     for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            aadResult[i][j] = 0.0;
            for(int k = 0; k < 4; k++) {
                aadResult[i][j] += aakdOp1[i][k] * aakdOp2[k][j];
            } 
        }     
     }
}

//------------------------------------------------------------------------------
/**
* Turns an unit axis and an angle into a rotational matrix. Quaternions are
* used to create the matrix. The transformation matrix is provided by 
* Interactive Computer Graphics: A Top-Down Approach Using OpenGL 4th Edition
*
* @see GetQuatRotMatrix, Normalize, EulerToAxisAngle
*/
//------------------------------------------------------------------------------
inline void AxisAngleToMatrix(GLdouble const akdAxis[3], const GLdouble kdAngle, 
    GLdouble aadMatrix[4][4]) {
    
    GLdouble dSin = sin(DegToRad(kdAngle)/2.0);
    GLdouble dCos = cos(DegToRad(kdAngle)/2.0);
    
    aadMatrix[0][0] = 
        1-2*dSin*dSin*(akdAxis[gknY]*akdAxis[gknY]+akdAxis[gknZ]*akdAxis[gknZ]);
    aadMatrix[0][1] = 
        2*dSin*dSin*akdAxis[gknX]*akdAxis[gknY]-2*dCos*dSin*akdAxis[gknZ];
    aadMatrix[0][2] = 
        2*dSin*dSin*akdAxis[gknX]*akdAxis[gknZ]+2*dCos*dSin*akdAxis[gknY];
    aadMatrix[0][3] = 0;
    
    aadMatrix[1][0] = 
        2*dSin*dSin*akdAxis[gknX]*akdAxis[gknY] + 2*dCos*dSin*akdAxis[gknZ];
    aadMatrix[1][1] = 
        1-2*dSin*dSin*(akdAxis[gknX]*akdAxis[gknX]+akdAxis[gknZ]*akdAxis[gknZ]);
    aadMatrix[1][2] = 
        2*dSin*dSin*akdAxis[gknY]*akdAxis[gknZ] - 2*dCos*dSin*akdAxis[gknX];
    aadMatrix[1][3] = 0;
    
    aadMatrix[2][0] = 
        2*dSin*dSin*akdAxis[gknX]*akdAxis[gknZ] - 2*dCos*dSin*akdAxis[gknY];
    aadMatrix[2][1] = 
        2*dSin*dSin*akdAxis[gknY]*akdAxis[gknZ] + 2*dCos*dSin*akdAxis[gknX];
    aadMatrix[2][2] = 
        1-2*dSin*dSin*(akdAxis[gknX]*akdAxis[gknX]+akdAxis[gknY]*akdAxis[gknY]);
    aadMatrix[2][3] = 0;
    
    aadMatrix[3][0] = 0;
    aadMatrix[3][1] = 0;
    aadMatrix[3][2] = 0;
    aadMatrix[3][3] = 1;
}

//------------------------------------------------------------------------------
/**
* Normalize a vector so it has unit length.
*/
//------------------------------------------------------------------------------ 
inline void Normalize(GLdouble adVector[3]) {
    double dNorm = sqrt(adVector[gknX]*adVector[gknX] + 
        adVector[gknY]*adVector[gknY] + adVector[gknZ]*adVector[gknZ]);
    if(dNorm != 0.0) {
        for(int i = 0; i < 3; i++) {
            adVector[i] /= dNorm;
        }
    }
}

//------------------------------------------------------------------------------
/**
* Algorithm adpated from http://answers.google.com/answers/threadview?id=18979
*
* @warning Do not use adHit if false is returned.
*/
//------------------------------------------------------------------------------
inline bool RayRectIntersect(GLdouble const akdBase[3], 
	GLdouble const akdRay[3], GLdouble const aakdP[4][3], GLdouble adHit[3]) {
     
    bool bResult = false;
        
    //A plane is of the form A*x + B*y + C*z = 0. Solve for the equation of the
    //plane for the rectangle.
    GLdouble dA = aakdP[1][gknY]*(aakdP[2][gknZ]-aakdP[3][gknZ]) 
        + aakdP[2][gknY]*(aakdP[3][gknZ]-aakdP[1][gknZ]) 
        + aakdP[3][gknY]*(aakdP[1][gknZ]-aakdP[2][gknZ]);
    GLdouble dB = aakdP[1][gknZ]*(aakdP[2][gknX]-aakdP[3][gknX]) 
        + aakdP[2][gknZ]*(aakdP[3][gknX]-aakdP[1][gknX]) 
        + aakdP[3][gknZ]*(aakdP[1][gknX]-aakdP[2][gknX]);
    GLdouble dC = aakdP[1][gknX]*(aakdP[2][gknY]-aakdP[3][gknY]) 
        + aakdP[2][gknX]*(aakdP[3][gknY]-aakdP[1][gknY]) 
        + aakdP[3][gknX]*(aakdP[1][gknY]-aakdP[2][gknY]);
    GLdouble dD = -aakdP[1][gknX]
        *(aakdP[2][gknY]*aakdP[3][gknZ] - aakdP[3][gknY]*aakdP[2][gknZ]) 
        -aakdP[2][gknX]*
            (aakdP[3][gknY]*aakdP[1][gknZ]-aakdP[1][gknY]*aakdP[3][gknZ]) 
        -aakdP[3][gknX]*
            (aakdP[1][gknY]*aakdP[2][gknZ]-aakdP[2][gknY]*aakdP[1][gknZ]);
        
    //Find the intersection between the ray and the plane in terms of "time"
    //for the ray.
    GLdouble dT = -(dA*akdBase[gknX] + dB*akdBase[gknY] + dC*akdBase[gknZ] + dD) 
        /(dA*akdRay[gknX]+ dB*akdRay[gknY] + dC*akdRay[gknZ]);
        
    //If time is negative then the ray does hit the plane but its corresponding
    //line would.
    if(dT >= 0) {
        //It has hit the plane.
        
        //Find the specific point.
        adHit[gknX] = akdBase[gknX] + akdRay[gknX]*dT;
        adHit[gknY] = akdBase[gknY] + akdRay[gknY]*dT;
        adHit[gknZ] = akdBase[gknZ] + akdRay[gknZ]*dT;
        
        //Check that the point rests inside of the rectangle.
        GLdouble adV1[3];
        GLdouble adV2[3];
        GLdouble adV3[3];
        GLdouble adV4[3];
        
        //Create a bunch of vectors.
        for(int i = 0; i < 3; i++) {
            adV1[i] = aakdP[2][i] - aakdP[1][i];
            adV2[i] = aakdP[4][i] - aakdP[3][i];
            adV3[i] = adHit[i] - aakdP[1][i];
            adV4[i] = adHit[i] - aakdP[3][i];
        }
        
        //Normalize all the vectors.
        Normalize(adV1);
        Normalize(adV2);
        Normalize(adV3);
        Normalize(adV4);
        
        //Find the dot product of pairs of vectors. If both are non-negative
        //then the point is inside the rectangle.
        GLdouble dDot1 = 0.0;
        GLdouble dDot2 = 0.0;
        for(int i = 0; i < 3; i++) {
            dDot1 += adV1[i]*adV3[i];
            dDot2 += adV2[i]*adV4[i];
        }
        if(dDot1 >= 0.0 && dDot2 >= 0.0) {
            bResult = true;
        }
    }
    return bResult;
}

//------------------------------------------------------------------------------
/**
* Performs a cross-product.
*
* @warning The if both input vectors are unit the resulting vector may not be.
* If unit is desired Normalize the result.
*
* @see Normalize
*/
//------------------------------------------------------------------------------
inline void Cross(GLdouble const akdVector1[3], GLdouble const akdVector2[3],
    GLdouble adResult[3]) {

    adResult[0] = akdVector1[1]*akdVector2[2] - akdVector1[2]*akdVector2[1];
    adResult[1] = -akdVector1[0]*akdVector2[2] + akdVector1[2]*akdVector2[0];
    adResult[2] = akdVector1[0]*akdVector2[1] - akdVector1[1]*akdVector2[0];
}

//------------------------------------------------------------------------------    
/**
* Returns the angle (in radians) between two unit vectors.
*
* @warning The vectors must be unit.
*/
//------------------------------------------------------------------------------
inline GLdouble GetAngle(GLdouble const akdVector1[3], 
	GLdouble const akdVector2[3]) {
	
    GLdouble dDot = 0;
    GLdouble dResult;
    
    for(int i = 0; i < 3; i++) {
        dDot += akdVector1[i]*akdVector2[i];
    }
    
    if(dDot > 1.0) {
        dDot = 1.0;
    }
    else {
        if(dDot < -1.0) {
            dDot = -1.0;
        }
    }
    
    dResult = acos(dDot);

    return dResult;
}

//------------------------------------------------------------------------------
/**
* Given a pair of vectors calculates the rotation matrix needed to go from one 
* to the other. The matrix is calculated using axis-angle and quaternions.
*
* @warning This method will fail if the akdOldVector = - akdNewVector.
*
* @see GetAngle
*/
//------------------------------------------------------------------------------
inline void GetRotMatrix(GLdouble const akdOldVector[3], 
    GLdouble const akdNewVector[3], GLdouble aadMatrix[4][4]) {
        
    //Get the rotational axis and angle.
    GLdouble adAxis[3];
    Cross(akdOldVector, akdNewVector, adAxis);
    Normalize(adAxis);
    GLdouble dAngle = RadToDeg(GetAngle(akdOldVector, akdNewVector));
    
    AxisAngleToMatrix(adAxis, dAngle, aadMatrix);
}

//------------------------------------------------------------------------------
/**
* Given a pair of forward and up vectors calculates the rotation matrix
* needed to go from one to the other. This done by 2 rotations. One to get the
* forward vectors to match and the second to get the up vectors to match. The
* matrix is calculated using axis-angle and quaternions.
*
* @see GetRotMatrix, GetAngle
*/
//------------------------------------------------------------------------------
void GetRotMatrix(GLdouble akdOldForward[3], GLdouble akdOldUp[3], 
    GLdouble akdNewForward[3], GLdouble akdNewUp[3], 
    GLdouble aadResultMatrix[4][4]) {
        
    GLdouble dTolerance = 0.000001;
    
    //Get the forward rotation matrix. If akdOldForward = -akdNewForward then
    //the rotation needed align the forwards is simply 180 degrees around either
    //up vector.
    GLdouble aadForwardRotMatrix[4][4];
    if(GetAngle(akdOldForward, akdNewForward) > M_PI - dTolerance && 
        GetAngle(akdOldForward, akdNewForward) < M_PI - dTolerance ) {
        
        AxisAngleToMatrix(akdNewUp, 180.0, aadForwardRotMatrix);
    }
    else {
        GetRotMatrix(akdOldForward, akdNewForward, aadForwardRotMatrix);
    }
    
    //Rotate the old up vector to the intermediate position.
    GLdouble adIntermediateUp[3];
    for(int i = 0; i < 3; i++) {
        adIntermediateUp[i] = akdOldUp[i];
    }
    MatrixMultVector(aadForwardRotMatrix, adIntermediateUp);
    
    GLdouble aadUpRotMatrix[4][4];
    if(GetAngle(adIntermediateUp, akdNewUp) > M_PI - dTolerance && 
        GetAngle(adIntermediateUp, akdNewUp) < M_PI - dTolerance ) {
        
        AxisAngleToMatrix(akdNewForward, 180.0, aadUpRotMatrix);
    }
    else {
        GetRotMatrix(adIntermediateUp, akdNewUp, aadUpRotMatrix);
    }
    
    //Conceptually, first the forwards were aligned and then the ups were 
    //aligned. Create the matrix to represent both rotations.
    MatrixMultMatrix(aadUpRotMatrix, aadForwardRotMatrix, aadResultMatrix);
}
