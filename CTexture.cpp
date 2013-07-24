#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glut.h>
#include "CTexture.h"

void CTexture::Select(void){ 
	glBindTexture(GL_TEXTURE_2D, m_nTexture);
}

CTexture::CTexture(int nTexture, char *szFileName){
    FILE * file;
    char temp;
    long i;

    TSM_BITMAPINFOHEADER infoheader;
    
    m_nTexture = nTexture;
    
    if( (file = fopen(szFileName, "rb"))==NULL)  { 
	    printf("\n File error:%s",szFileName);
	    exit(1);
    }
	    // Open the file for reading

    fseek(file, 18, SEEK_CUR);  /* start reading width & height */
    fread(&infoheader.biWidth, sizeof(int), 1, file);

    fread(&infoheader.biHeight, sizeof(int), 1, file);

    fread(&infoheader.biPlanes, sizeof(short int), 1, file);
    
    if (infoheader.biPlanes != 1) {
	    printf("Planes from %s is not 1: %u\n", szFileName, infoheader.biPlanes);
	    exit(1);
	    
    }
    
    // read the bpp
    fread(&infoheader.biBitCount, sizeof(unsigned short int), 1, file);
    if (infoheader.biBitCount != 24) {
      printf("Bpp from %s is not 24: %d\n", szFileName, infoheader.biBitCount);
      exit(1);
      
    }

    fseek(file, 24, SEEK_CUR);

    // read the data.
    infoheader.data = (char *) malloc(infoheader.biWidth * infoheader.biHeight * 3);
    if (infoheader.data == NULL) {
	    printf("Error allocating memory for color-corrected image data\n");
	    exit(1);
	    
    }

    if ((i = fread(infoheader.data, infoheader.biWidth * infoheader.biHeight * 3, 1, file)) != 1) {
	    printf("Error reading image data from %s.\n", szFileName);
	    exit(1);
    }

    for (i=0; i<(infoheader.biWidth * infoheader.biHeight * 3); i+=3) { // reverse all of the colors. (bgr -> rgb)
	    temp = infoheader.data[i];
	    infoheader.data[i] = infoheader.data[i+2];
	    infoheader.data[i+2] = temp;
    }
	


    fclose(file); // Closes the file stream


    glBindTexture(GL_TEXTURE_2D, nTexture); // Bind the ID texture specified by the 2nd parameter

    // The next commands sets the texture parameters
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // If the u,v coordinates overflow the range 0,1 the image is repeated
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // The magnification function ("linear" produces better results)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //The minifying function

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); // We don't combine the color with the original surface color, use only the texture map.

    // Finally we define the 2d texture
    glTexImage2D(GL_TEXTURE_2D, 0, 3, infoheader.biWidth, infoheader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, infoheader.data);

    // And create 2d mipmaps for the minifying function
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, infoheader.biWidth, infoheader.biHeight, GL_RGB, GL_UNSIGNED_BYTE, infoheader.data);
    
    free(infoheader.data); // Free the memory we used to load the texture
   
}

CTexture::~CTexture(void){
}



