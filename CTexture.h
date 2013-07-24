//******************************************************************************
//CTexture.h
//Copyright (C) 2007, Marcus Trenton, Tyler Sangster, and Sebastian Harko
//Originally written for Total Space Massacre, a project for CS 432 on 
//February 21th, 2007.
//******************************************************************************



#ifndef CTexture_h
#define CTexture_h

/**
 * @brief Represents the structure that represents the header of a bitmap file.
 * 
 */
typedef struct{
	unsigned int   biSize;
	int 	       biWidth;
	int 	       biHeight;
	unsigned short biPlanes;
	unsigned short biBitCount;
	unsigned int   biCompression;
	unsigned int   biSizeImage;
	int	       	   biXPelsPerMeter;
	int	           biYPelsPerMeter;
	unsigned int   biClrUsed;
	unsigned int   biClrImportant; 
	char *data;
} TSM_BITMAPINFOHEADER;

//##############################################################################
/** 
* @class CTexture CTexture.h
* 
* @brief CTexture is a texture loading class.
*/
//##############################################################################


class CTexture{
	public:
		
		/*
		 * @brief Constructor for the Texture class
		 * @param nTexture The Texture Number
		 * @param szFileName The Texture bitmpa file name.
		 */
		CTexture(int nTexture, char *szFileName);
		~CTexture(void);
		
		/*
		 * @brief Select a texture.  
		 */
		 
		void Select(void);
		
		/*
		 * @brief Returns the texture ID of this texture. 
		 */
		 
		int getTextureID(void) { 
			return m_nTexture;
		}
		
		
	private:
		int m_nTexture;
};

#endif //CTexture_h
