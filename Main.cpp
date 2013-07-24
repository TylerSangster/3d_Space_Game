//******************************************************************************
//Main.cpp
//Copyright (C) 2007, Marcus Trenton, Tyler Sangster, and Sebastian Harko
//Originally written for Total Space Massacre, a project for CS 432 on 
//February 21th, 2007.
//******************************************************************************

//##############################################################################
/**
* @file Main.cpp
*
* @brief Handles the input, level creation, and sets up GLUT.
*
* Main.cpp Initializes GLUT, does the preliminary processing of user input, and
* specifies what the first world of the game is.
*
* 
* @date 01/03/2007
* @version 1.0
*/
//##############################################################################

#include <iostream>
#include <time.h>
#include <math.h>
#include <GL/glut.h>
#include "CLevel.h"
#include "Global.h"

/**
 *@brief If the game is over it should print a message. We want to print this message only once.
 * 
 */
bool gbGameOver;

/**
* @brief How many total clock ticks must pass until the program can update 
*   again.
*/

clock_t nEndWait;   // not used , using the clock() function in the timer function causes it to 
		    // crash on Linux. Reported to work in windows.

/**
* @brief The current level.
*
* @bug This must be a pointer for the ability to delete and recreate CLevels 
* properly. When this was stack variable and I did the command gcTSM = CLevel();
* The constructor was called before the destructor resulting in the newly 
* created weapons and ships being deleted. Using pointers and explicitely 
* calling delete and new solved this.
*/
CLevel* gpcTSM;
/**
* @brief How many refreshes and game cycles occur in a second.
*/
const int gknFrameRate = 20;
/**
* @brief The array that holds keyboard input.
*/
bool gabKeyPressed[gknShipInputKeys];
/**
* @brief The window height.
*
* @warning Non-constant global variable, a necessary evil.
*/
GLint gnWindowHeight = 550;
/**
* @brief The window width.
*
* @warning Non-constant global variable, a necessary evil.
*/
GLint gnWindowWidth = 550;
/**
* @brief Is there any change in direction for the ship?
*
* @warning Non-constant global variable, a necessary evil.
*/
bool gbMotionInput;
/**
* @brief Represents the change in direction. 
* 
* The angle on the local up-right plane measured counter-clockwise from right.
*
* @warning Non-constant global variable, a necessary evil.
*/
GLdouble gdAngleRadians;
/**
* @brief How far the change in direction is for the player's ship.
*
* @warning Non-constant global variable, a necessary evil.
*/
GLdouble gdMagnitude;

//------------------------------------------------------------------------------
/**
* @brief Draws to the screen.
* 
* Draws the screen by telling the CWorld to draw itself.
*/
//------------------------------------------------------------------------------
void Display(void){
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gpcTSM->Draw();
	
	glFlush();
	glutSwapBuffers();	
}

//------------------------------------------------------------------------------
/**
* @brief Upon reshaping the window maintain a square viewport.
*
* @param nNewWidth The new width of the window.
* @param nNewHeight The new height of the window.
*
* Whenever the window is reshaped find the largest square in the rectangle.
* That largest square becomes the viewport.
*/
//------------------------------------------------------------------------------
/*
void Reshape(int nNewWidth, int nNewHeight) {
    //Update the global variables
    gnWindowHeight = nNewHeight;
    gnWindowWidth = nNewWidth;
    
    //Find the smallest length. It is now the length of viewport square.
    int nSquareLength = min(nNewWidth, nNewHeight);
    
    //The difference between the largest side and the smallest.
    int nDifference = max(nNewWidth, nNewHeight) - nSquareLength;
	
	//Keep the Tic-Tac-Toe board centered by moving the bottom-left corner of 
    //viewport. Take half the difference to be the offset of the largest side.
    
    //Width is the smallest side.
    if (nNewWidth < nNewHeight) {
        glViewport(0, nDifference / 2, nSquareLength, nSquareLength);  
    }
    //Height is the smallest side.
    else {
        glViewport(nDifference / 2, 0, nSquareLength, nSquareLength);       
    }
}
*/
//------------------------------------------------------------------------------
/**
* @brief Use a glut timer and a C clock to update the program.
* 
* Updates the level and sets the timer to execute in a very shot period of 
* time. C's clock function is used to ensure update is called every at the
* desired frame rate.
*/
//------------------------------------------------------------------------------
void Timer(int nV){   
    //Calling the clock() function did not work very 
    //well on Linux. It caused it to freeze from time to time
    //We did not know the cause of the freeze. Spent one 
    //entire day trying to find the cause of the freeze 
    //somewhere else in the code.
    
    if (gpcTSM->Update(gabKeyPressed, 
        gbMotionInput, gdAngleRadians, gdMagnitude)) {

        // Print the game over message and after that 
        // we set the game to be over.
        if (!gbGameOver){ 
            cout << 
                "##############################################################" 
                << endl;
            cout << "You have beaten the level. You won't be so lucky next "
                    "time." << endl;       
            cout << 
                "##############################################################" 
                << endl;
        }
        gbGameOver = true;
        
    }
    glutPostRedisplay();
        
    //Reset the keyboard array to nothing pressed.
    for(int i = 0; i < gknShipInputKeys; i++) {
        gabKeyPressed[i] = false;
    }
    
    //Recall at a rediculously fast but inaccurate rate.
    glutTimerFunc(1000/gknFrameRate,Timer,nV);
}

//------------------------------------------------------------------------------
/**
* @brief Records the change in state of the mouse button in a global variable.
*
* @param nX Where the mouse's x co-ordinate is in the window.
* @param nY Where the mouse's y co-ordinate is in the window (stupidly reversed
*   so 0 is at the top).
*/
//------------------------------------------------------------------------------
void Motion(int nX, int nY) {
    nY = gnWindowHeight - nY;
    
    //Calculate where the mouse is relative to the centre of the viewport.
    nY -= gnWindowHeight/2;
    nX -= gnWindowWidth/2;
    
    //Now find the distance the mouse is from the centre.
    GLdouble dDistance = sqrt(nX*nX + nY*nY);
    
    //If that distance is less than a quarter the width then the mouse is not 
    //far enough to trigger an action. If it is more then the determine the 
    //angle.
    gdAngleRadians = atan2((double) nY, (double) nX);
    
    //If the mouse is not further than this distance from the centre of the
    //screen there is no change in the ship's motion.
    GLdouble dNoMotionRadius = gnWindowWidth/64;
    
    if(dDistance >= dNoMotionRadius) {        
        gbMotionInput = true;
    }
    else {
        gbMotionInput = false;
    }
    
    //How intense the motion is depends on how far the mouse is from the centre.
    //Minimum motion (0) is reached gnWindowWidth/8 from the centre.
    //Maximum motion (1) is reached gnWindowWidth/2 from the centre.
    gdMagnitude = (dDistance - dNoMotionRadius) / 
        (gnWindowWidth - dNoMotionRadius);
    //If the user in the the corners then the magnitude will be greater than 1.
    //That shouldn't be, so a maximum is set a 1.
    gdMagnitude = min(1.0, gdMagnitude);
}

//------------------------------------------------------------------------------
/**
* @brief Responds to a key being pressed.
*
* @param unKey What key was pressed.
* @param nX Where the mouse's x co-ordinate is in the window.
* @param nY Where the mouse's y co-ordinate is in the window (stupidly reversed
*   so 0 is at the top).
*
* Some most keys are dealt with by using a global variable. The keys that have
* no mouse equivalent are in a global key array. Those that do have a mouse
* equivalent use the same variables as the mouse. Those that don't use global
* variables (for storage at least) are game commands like restart and quit.
*/
//------------------------------------------------------------------------------
void KeyPressed(unsigned char unKey, int nX, int nY) {
    switch(unKey)
    {
        //The braking keys.
        case '5':
        case 's':
            gabKeyPressed[gknBrake] = true;
            break;
        //The acceleration keys.
        case '8':
        case 'w':
            gabKeyPressed[gknAccelerate] = true;
            break;
        //The deceleration keys.
        case '2':
        case 'x':
            gabKeyPressed[gknDecelerate] = true;
            break;
        //The fire left weapon keys.
        case 'a':
        case '4':
            gabKeyPressed[gknFireLeft] = true;
            break;
        //The fire right weapon keys.
        case 'd':
        case '6':
            gabKeyPressed[gknFireRight] = true;
            break;
        //The quit key.
        case 'n':
            gpcTSM->UnInit(); //Delete the display lists.
            exit(0);
            break;
        //The restart level key.
        case 'y':
            delete gpcTSM;
            gpcTSM = new CLevel("map.xml");            
            break;    
    }
}

//------------------------------------------------------------------------------
/**
* @brief Responds to keys being released.
*
* @param unKey What key was pressed.
* @param nX Where the mouse's x co-ordinate is in the window.
* @param nY Where the mouse's y co-ordinate is in the window (stupidly reversed
*   so 0 is at the top).
*
* The only keys that being released really matters are the weapon firing keys.
* This method tells them to stop firing.
*/
//------------------------------------------------------------------------------
void KeyReleased(unsigned char unKey, int nX, int nY) {
    switch(unKey)
    {
        case 'a':
        case '4':
            gabKeyPressed[gknFireLeft] = false;
            break;
        case 'd':
        case '6':
            gabKeyPressed[gknFireRight] = false;
            break;           
    }
}

//------------------------------------------------------------------------------
/**
* @brief Initializes things that are not directly initialize by GLUT.
* 
* Initializes the CWorld, timer, and the camera.
*/
//------------------------------------------------------------------------------
void Init(void) {    
    //Initialize the CLevel so it call the other classes display lists.
    gpcTSM->Init();
    gpcTSM = new CLevel("map.xml");
	
	//Reset the keyboard array to nothing pressed.
    for(int i = 0; i < gknShipInputKeys; i++) {
        gabKeyPressed[i] = false;
    }
	
	//Setup the timed refreshing.
	glutTimerFunc(100,Timer,gknFrameRate);
    nEndWait = 0; //Refresh as soon as possible.
	
	//Initially set up the camera.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(52.0, 1, 0.01, 25);
	
	glMatrixMode(GL_MODELVIEW);
}



//------------------------------------------------------------------------------
/**
* @brief Initialize GLUT, initialize more stuff, and start the infinite loop.
*
* @param nNumberArgs How many arguements where passed via command prompt.
* @param aszArg The array of arguements passed via command prompt.
*/
//------------------------------------------------------------------------------
int main(int nNumberArgs, char** aszArg) {     
	glutInit(&nNumberArgs,aszArg);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);      
	glutInitWindowSize(gnWindowWidth,gnWindowHeight);
	glutInitWindowPosition(0,0); 
	glutCreateWindow("Total Space Massacre");
	glutDisplayFunc(Display);
	
	glutKeyboardFunc(KeyPressed);
	glutKeyboardUpFunc(KeyReleased);
	glutPassiveMotionFunc(Motion);
	glutMotionFunc(Motion);
	glutReshapeFunc(Reshape);
	
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0); //We have just one light source: the sun.
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	Init();	
	glutMainLoop();
}
