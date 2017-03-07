/*ImageList header file by Chandler Ditolla SID:18731640*/

#ifndef IMAGELIST_H
#define IMAGELIST_H
#include <stdio.h>
#include <stdlib.h>
#include "Image.h"

typedef struct ImageEntry IENTRY;
typedef struct ImageList ILIST;

struct ImageEntry {
	ILIST *List; /* Pointer to the list which this entry belongs to */
	IENTRY *Next; /* Pointer to the next entry, or NULL */
	IENTRY *Prev; /* Pointer to the previous entry, or NULL */
	IMAGE *RGBImage; /* Pointer to the RGB image, or NULL */
	YUVIMAGE *YUVImage; /* Pointer to the YUV image, or NULL */
};

struct ImageList {
	unsigned int Length; /* Length of the list */
	IENTRY *First; /* Pointer to the first entry, or NULL */
	IENTRY *Last; /* Pointer to the last entry, or NULL */
};

/* Create a new image list */
ILIST *CreateImageList(void);
/* Delete an image list (and all entries) */
void DeleteImageList(ILIST *list);
/* Creat a new image entry */
IENTRY *CreateImageEntry(void);
/* Delete an image entry */
void DeleteImageEntry(IENTRY *entry);

/* Insert a RGB image to the image list at the end */
void AppendRGBImage(ILIST *list, IMAGE *RGBimage);
/* Insert a YUV image to the image list at the end */
void AppendYUVImage(ILIST *list, YUVIMAGE *YUVimage);
/* Crop an image list */
void CropImageList(ILIST *list, unsigned int start, unsigned int end);
/* Fast forward an image list */
void FastImageList(ILIST *list, unsigned int factor);
/* Reverse an image list */
void ReverseImageList(ILIST *list);

#endif
