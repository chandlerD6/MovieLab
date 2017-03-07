/*Movie.c by Chandler Ditolla SID:18731640*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "Movie.h"

int clip(int x){
	if( 0 <= x && x  <= 255){
		return x;
	}	
	else if( x < 0){
		return 0;
	}
	
	return 255;
	
	
}


/* Allocate the memory space for the movie and the memory space */
/* for the frame list. Return the pointer to the movie. */
MOVIE *CreateMovie(void){
	MOVIE *movie = NULL;
	movie = malloc(sizeof(MOVIE));
	assert(movie);
	
	return movie;
	
}

/* Release the memory space for the frame list. */
/* Release the memory space for the movie. */
void DeleteMovie(MOVIE *movie){
	assert(movie);
	assert(movie->Frames);
	DeleteImageList(movie->Frames);
	movie->Frames = NULL;
	free(movie);
	movie = NULL;
}

/* Convert a YUV movie to a RGB movie */
void YUV2RGBMovie(MOVIE *movie){
	int x, y, C, D, E;
	IENTRY *entry = NULL, *temp = NULL;
	assert(movie);
	entry = movie->Frames->First;
	
	while(entry){
		temp = entry->Next;
		
		entry->RGBImage = CreateImage(entry->YUVImage->Width, entry->YUVImage->Height);
		
		for(y = 0; y < entry->YUVImage->Height; y++){
			for(x = 0; x < entry->YUVImage->Width; x++){
				C = GetPixelY(entry->YUVImage, x, y) - 16;
				D = GetPixelU(entry->YUVImage, x, y) - 128;
				E = GetPixelV(entry->YUVImage, x, y) - 128;
				SetPixelR(entry->RGBImage, x, y, clip((298 * C + 409 * E + 128) >> 8));
				SetPixelG(entry->RGBImage, x, y, clip((298 * C - 100 * D - 208 * E + 128) >> 8));
				SetPixelB(entry->RGBImage, x, y, clip((298 * C + 516 * D + 128) >> 8));
			}
		}
		DeleteYUVImage(entry->YUVImage);
		entry->YUVImage = NULL;
		entry = temp;	
	}
	
	
	
		
}

/* Convert a RGB movie to a YUV movie */
void RGB2YUVMovie(MOVIE *movie){
	int x, y, R, G, B;
	IENTRY *entry = NULL, *temp = NULL;
	assert(movie);
	entry = movie->Frames->First;
	
	while(entry){
		temp = entry->Next;
		
		entry->YUVImage = CreateYUVImage(entry->RGBImage->Width, entry->RGBImage->Height);
		
		for(y = 0; y < entry->RGBImage->Height; y++){
			for(x = 0; x < entry->RGBImage->Width; x++){
				R = GetPixelR(entry->RGBImage, x, y);
				G = GetPixelG(entry->RGBImage, x, y);
				B = GetPixelB(entry->RGBImage, x, y);
				SetPixelY(entry->YUVImage, x, y, clip(((66 * R + 129 * G + 25 * B + 128) >> 8) + 16));
				SetPixelU(entry->YUVImage, x, y, clip(((-38 * R - 74 * G + 112 * B + 128) >> 8) + 128));
				SetPixelV(entry->YUVImage, x, y, clip(((112 * R - 94 * G - 18 * B + 128) >> 8) + 128));
			}
		}
		DeleteImage(entry->RGBImage);
		entry->RGBImage = NULL;
		entry = temp;	
	}
}

