/* DIPs header file by Chandler Ditolla SID: 18731640*/
#ifndef DIPS_H_INCLUDED_
#define DIPS_H_INCLUDED_

/* Do not modify it */

#include "Image.h"
#include "Constants.h"
#include "Movie.h"
/* Age image*/
IMAGE * Aging(IMAGE *image);

/* Add a watermark to an image*/
IMAGE *Watermark(IMAGE *image, const IMAGE *watermark,
unsigned int topLeftX, unsigned int topLeftY);

/* Add a spotlight to an image*/
IMAGE *Spotlight(IMAGE *image, int centerX, int centerY, unsigned int radius);

/* Reverse image color */
IMAGE *Negative(IMAGE *image);

/* Color filter */
IMAGE *ColorFilter(IMAGE *image, int target_r, int target_g, int target_b, int threshold, int replace_r, int replace_g, int replace_b);

/* Edge detection */
IMAGE *Edge(IMAGE *image);

/* Flip image horizontally */
IMAGE *HFlip(IMAGE *image);

/* Mirror image vertically */
IMAGE *VMirror(IMAGE *image);

/* Zoom an image */
IMAGE *Zoom(IMAGE *image,unsigned int percentage);

#endif /* DIPS_H_INCLUDED_ */
