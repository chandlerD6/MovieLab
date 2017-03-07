/*Movie header file by Chandler Ditolla SID:18731640*/
#ifndef MOVIE_H
#define MOVIE_H
#include "Constants.h"
#include "Image.h"
#include "ImageList.h"

/* the movie structure */
typedef struct {
ILIST *Frames; /* Pointer to the frame list */
} MOVIE;


int clip(int x);
/* Allocate the memory space for the movie and the memory space */
/* for the frame list. Return the pointer to the movie. */
MOVIE *CreateMovie(void);
/* Release the memory space for the frame list. */
/* Release the memory space for the movie. */
void DeleteMovie(MOVIE *movie);
/* Convert a YUV movie to a RGB movie */
void YUV2RGBMovie(MOVIE *movie);
/* Convert a RGB movie to a YUV movie */
void RGB2YUVMovie(MOVIE *movie);

#endif





