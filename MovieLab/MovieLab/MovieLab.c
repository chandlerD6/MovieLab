/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2016                     */
/*                                                                   */
/* Author: Chandler Ditolla                                          */
/* Date: 12/04/2016                                                  */
/* SID: 18731640                                                     */
/* MovieLab.c: source file for the main function                     */
/*                                                                   */
/* Please use this template for your HW5.                            */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "Image.h"
#include "ImageList.h"
#include "Constants.h"
#include "Movie.h"
#include "FileIO.h"
#include "DIPs.h"
/* Load one movie frame from the input file */
YUVIMAGE* LoadOneFrame(const char* fname, int n, 
                       unsigned int width, unsigned height);

/* Load the movie frames from the input file */
MOVIE *LoadMovie(const char *fname, int frameNum, 
                 unsigned int width, unsigned height);

/* Save the movie frames to the output file */
int SaveMovie(const char *fname, MOVIE *movie);

/* Print the command-line arguments usage of the program */
void PrintUsage();

int main(int argc, char *argv[])
{
	int x = 0, agingflag = 0, hflipflag = 0, edgeflag = 0, cropflag = 0, fastflag = 0, rvsflag = 0, watermarkflag = 0,
		 spotlightflag = 0, zoomflag = 0, cropstart, cropend, FFWfactor, radius, percent;
	char *fin = NULL;
	char *watermarkname = NULL;
	unsigned int waterlen = 0;
	unsigned int finLen = 0;
	char *fout = NULL;
	unsigned int foutLen = 0;
	unsigned int width, height, framenum;
	MOVIE *movie = NULL;
	
	/* the while loop to check options in the command line */
	while (x < argc) {
		/* the input file name */
		if (strcmp(argv[x], "-i") == 0) {
			if (x < argc - 1) {
				finLen = strlen(argv[x + 1]) + strlen(".yuv") + 1;
				fin = (char *)malloc(sizeof(char) * finLen);
				if (fin == NULL) {
					printf("Error in memory allocation for the input file name!\n");
					free(fout);
					free(watermarkname);
					return 5;
				}
				strcpy(fin, argv[x + 1]);
				strcat(fin, ".yuv");
			} /*fi*/
			else {
				printf("Missing argument for the input file name!\n");
				free(fin);
				free(fout);
				free(watermarkname);
				return 5;
			} /*esle*/
			x += 2;
			continue;
		} /*fi*/

		/* the output file name */
		if (strcmp(argv[x], "-o") == 0) {
			if (x < argc - 1) {
				foutLen = strlen(argv[x + 1]) + strlen(".yuv") + 1;
				fout = (char *)malloc(sizeof(char) *foutLen);
				if (fout == NULL) {
					printf("Error in memory allocation for the output file name!\n");
					free(fin);
					free(watermarkname);
					return 5;
				}
				strcpy(fout, argv[x + 1]);
				strcat(fout, ".yuv");
			} /*fi*/
			else {
				printf("Missing argument for the output file name!\n");
				free(fin);
				free(fout);
				free(watermarkname);
				return 5;
			} /*esle*/
			x += 2;
			continue;
		} /*fi*/
				
		if (strcmp(argv[x], "-f") == 0) {
			if (x < argc - 1){
				if (sscanf(argv[x+1], "%d", &framenum) == 1){
			
				}
				else {
					printf("Improper frame format!\n");
					free(fin);
					free(fout);
					free(watermarkname);
					return 6;
				}
			}
			else {
				printf("No Frames argument provided!\n");
				free(fin);
				free(fout);
				free(watermarkname);
				return 6;
			}
			x += 2;
			continue;
		}

		
		/* set resolution/dimension of movie */
		if (strcmp(argv[x], "-s") == 0) {
			if (x < argc - 1) {
				if (sscanf(argv[x+1], "%dx%d", &width, &height) == 2){
				
				}
				else {
					printf("Improper WidthxHeight format!\n");
					free(fin);
					free(fout);
					free(watermarkname);
					return 7;
				}
			}
			else {
				printf("No WidthxHeight provided!\n");
				free(fin);
				free(fout);
				free(watermarkname);
				return 7;
			}
			x += 2;
			continue;
		}

		if (strcmp(argv[x], "-aging") == 0){
			agingflag = 1;
		}
		
		if (strcmp(argv[x], "-hflip") == 0){
			hflipflag = 1;	
		}
		
		if (strcmp(argv[x], "-edge") == 0){
			edgeflag = 1;	
		}	

		if (strcmp(argv[x], "-crop") == 0){
			if ( x < argc - 1) {
				if(sscanf(argv[x+1], "%d-%d", &cropstart, &cropend) == 2){
					cropflag = 1;
				}
				else {
					printf("Improper start to end conditions!\n");
					free(fin);
					free(fout);
					free(watermarkname);
					return 8;
				}
			}
			else {
				printf("No crop start-end provided!\n");
				free(fin);
				free(fout);
				free(watermarkname);
				return 8;
			}
			x += 2;
			continue;	
		}
		
		if (strcmp(argv[x], "-fast") == 0){
			if ( x < argc -1){
				if(sscanf(argv[x+1], "%d", &FFWfactor) == 1){
					fastflag = 1;
				}
				else {
					printf("Imrpoper fast forward setting!\n");
					free(fin);
					free(fout);
					free(watermarkname);
					return 9;
				}
			}
			else {
				printf("No fast condition supplied!\n");
				free(fin);
				free(fout);
				free(watermarkname);
				return 9;
			}
			x += 2;
			continue;
		}
		
		if (strcmp(argv[x], "-rvs") == 0){
			rvsflag = 1;	
		}
		
		if (strcmp(argv[x], "-watermark") == 0) {
			if ( x < argc -1) {	
				waterlen = strlen(argv[x + 1]) + strlen(".ppm") + 1;
				watermarkname = (char *)malloc(sizeof(char) * waterlen);
				if (watermarkname == NULL) {
					printf("Error in memory allocation for the watermark file name!\n");
					free(fin);
					free(fout);
					free(watermarkname);
					return 10;
				}
				strcpy(watermarkname, argv[x + 1]);
				watermarkflag = 1;
			}
			else {
				printf("No file name provided!\n");
				free(fin);
				free(fout);
				free(watermarkname);
				return 10;
			}
			x += 2;
			continue;
		}

		if (strcmp(argv[x], "-spotlight") == 0){
			if ( x < argc -1){
				if(sscanf(argv[x+1], "%d", &radius) == 1){
					spotlightflag = 1;
				}
				else {
					printf("Imrpoper radius setting!\n");
					free(fin);
					free(fout);
					free(watermarkname);
					return 11;
				}
			}
			else {
				printf("No proper radius supplied!\n");
				free(fin);
				free(fout);
				free(watermarkname);
				return 11;
			}
			x += 2;
			continue;
		}
		
		if (strcmp(argv[x], "-zoom") == 0){
			zoomflag = 1;
		}
		
		/* the help option */
		if (strcmp(argv[x], "-h") == 0) { 
			PrintUsage();
			free(fin);
			free(fout);
			free(watermarkname);
			return 0;
		} /*fi*/

		x++;
	} /*elihw*/

	if (fin == NULL) {
		printf("Missing argument for the input file name!\n");
		PrintUsage();
		free(fin);
		free(fout);
		free(watermarkname);
		return 5;
	}

	if (fout == NULL) {
		printf("Missing argument for the output file name!\n");
		PrintUsage();
		free(fin);
		free(fout);
		free(watermarkname);
		return 5;
	}
	
	if (width == 0 || height == 0){
		printf("Missing argument for widthxheight!\n");
		PrintUsage();
		free(fin);
		free(fout);
		free(watermarkname);
		return 5;
	}

	if (framenum == 0){
		printf("Missing argument for frame number!\n");
		PrintUsage();
		free(fin);
		free(fout);
		free(watermarkname);
		return 5;	
	}
	
	movie = LoadMovie(fin, framenum, width, height);

	if (agingflag == 1){
		IENTRY *entry = NULL, *temp = NULL;
		YUV2RGBMovie(movie);
		entry = movie->Frames->First;
		for ( x = 0; x < framenum; x++){
			temp = entry->Next;
			entry->RGBImage = Aging(entry->RGBImage);
			entry = temp;
		}
		printf("Operation Aging is done!\n");
		RGB2YUVMovie(movie);
	}

	if (hflipflag == 1){
		IENTRY *entry = NULL, *temp = NULL;
		YUV2RGBMovie(movie);
		entry = movie->Frames->First;
		for ( x = 0; x < framenum; x++){
			temp = entry->Next;
			entry->RGBImage = HFlip(entry->RGBImage);
			entry = temp;
		}
		printf("Operation Horizontal Flip is done!\n");
		RGB2YUVMovie(movie);
	}

	if (edgeflag == 1){	
		IENTRY *entry = NULL, *temp = NULL;
		YUV2RGBMovie(movie);
		entry = movie->Frames->First;
		for( x = 0; x < framenum; x++){
			temp = entry->Next;
			entry->RGBImage = Edge(entry->RGBImage);
			entry = temp;
		}
		printf("Operation Edge is done!\n");
		RGB2YUVMovie(movie);
	}

	if (cropflag == 1){	
		CropImageList(movie->Frames, cropstart, cropend);
		printf("Operation Crop is done! New number of frames is %d\n", movie->Frames->Length);
	}
	
	if (fastflag == 1){	
		FastImageList(movie->Frames, FFWfactor);
		printf("Operation Fast Forward is done! New number of frames is %d\n", movie->Frames->Length);
	}

	if (rvsflag == 1){	
		ReverseImageList(movie->Frames);
		printf("Operation Reverse is done!\n");
	}

	if (watermarkflag == 1){
		int topLeftY, topLeftX;
		srand(time(NULL));
		IENTRY *entry = NULL, *temp = NULL;
		IMAGE *watermark = NULL;
		watermark = LoadImage(watermarkname);
		YUV2RGBMovie(movie);
		entry = movie->Frames->First;
		for ( x = 0; x < framenum; x++){
			if ( x % 15 == 0){
				topLeftX = rand() % width;
				topLeftY = rand() % height;
			}
			temp = entry->Next;
			entry->RGBImage = Watermark(entry->RGBImage, watermark, topLeftX, topLeftY);
			entry = temp;
		}
		printf("Operation Watermark is done!\n");
		DeleteImage(watermark);
		RGB2YUVMovie(movie);
	}
	
	if (spotlightflag == 1){	
		IENTRY *entry = NULL, *temp = NULL;
		YUV2RGBMovie(movie);
		entry = movie->Frames->First;
		for( x = 0; x < framenum; x++){
			temp = entry->Next;
			entry->RGBImage = Spotlight(entry->RGBImage, 0, 0, 100);
			entry = temp;
		}
		printf("Operation Spotlight is done!\n");
		RGB2YUVMovie(movie);
	}
	
	if (zoomflag == 1){	
		IENTRY *entry = NULL, *temp = NULL;
		YUV2RGBMovie(movie);
		entry = movie->Frames->First;
		percent = 0;
		for( x = 0; x < framenum; x++){
			if( percent == 100){
				for(percent = 100; percent > 0; percent = percent -2){
					temp = entry->Next;
					if( temp == NULL){
						break;
					}
					entry->RGBImage = Zoom(entry->RGBImage, percent);
					entry = temp;
				}
			}
			temp = entry->Next;
			if (temp == NULL){
				break;
			}
			entry->RGBImage = Zoom(entry->RGBImage, percent);
			entry = temp;
			percent = percent + 2;
		}
		printf("Operation Zoom is done!\n");
		RGB2YUVMovie(movie);
	}

	SaveMovie(fout, movie);
	DeleteMovie(movie);
	movie = NULL;
		
	

	free(fin);
	free(fout);
	free(watermarkname);
	fin = NULL;
	fout = NULL;
	watermarkname = NULL;

	return 0;
}

void PrintUsage()
{
	printf("\nUsage: MovieLab -i <file> -o <file> -f <framenum> -s <WIDTHxHEIGHT> [options]\n"
	       "Options:\n"
	       "-aging                Activate the aging filter on every movie frame\n"
	       "-hflip                Activate horizontal flip on every movie frame\n"
	       "-edge                 Activate the edge filter on every movie frame\n"
	       "-crop <start-end>     Crop the movie frames from <start> to <end>\n"
	       "-fast <factor>        Fast forward the movie by <factor>\n"
	       "-rvs                  Reverse the frame order of the input movie\n"
	       "-watermark <file>     Add a watermark from <file> to every movie frame\n"
	       "-spotlight <radius>   Spotlight a circle of <radius> on every movie frame\n"
	       "-zoom                 Zoom in and out the input movie\n"
	       "-h                    Display this usage information\n"
	      );
}

/* Load one movie frame from the input file */
YUVIMAGE* LoadOneFrame(const char* fname, int n, 
                       unsigned int width, unsigned height)
{
	FILE *file;
	unsigned int x, y;
	unsigned char c;
	YUVIMAGE* YUVimage;

	/* Check errors */
	assert(fname);
	assert(n >= 0);

	YUVimage = CreateYUVImage(width, height);
	if (YUVimage == NULL) {
		return NULL;
	}

	/* Open the input file */
	file = fopen(fname, "r");
	if (file == NULL) {
		DeleteYUVImage(YUVimage);
		return NULL;
	}

	/* Find the desired frame */
	fseek(file, 1.5 * n * width * height, SEEK_SET);

	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			c = fgetc(file);
			SetPixelY(YUVimage, x, y, c);
		} /*rof*/
	}

	for (y = 0; y < height; y += 2) {
		for (x = 0; x < width; x += 2) {
			c = fgetc(file);
			SetPixelU(YUVimage, x, y, c);
			SetPixelU(YUVimage, x + 1, y, c);
			SetPixelU(YUVimage, x, y + 1, c);
			SetPixelU(YUVimage, x + 1, y + 1, c);
		}
	}

	for (y = 0; y < height; y += 2) {
		for (x = 0; x < width; x += 2) {
			c = fgetc(file);
			SetPixelV(YUVimage, x, y, c);
			SetPixelV(YUVimage, x + 1, y, c);
			SetPixelV(YUVimage, x, y + 1, c);
			SetPixelV(YUVimage, x + 1, y + 1, c);
		}
	}

	/* Check errors */
	assert(ferror(file) == 0);

	/* Close the input file and return */
	fclose(file);
	file = NULL;
	return YUVimage;
}

/* Save the movie frames to the output file */
int SaveMovie(const char *fname, MOVIE *movie)
{
	int count; 
	int x, y;
	FILE *file;
	IENTRY *curr;

	/* Open the output file */
	file = fopen(fname, "w");
	if (file == NULL) {
		return 1;
	}
	 
	count = 0; 
	curr = movie->Frames->First;
	while (curr != NULL) {
		for (y = 0; y < curr->YUVImage->Height; y++) { 
			for (x = 0; x < curr->YUVImage->Width; x++) {
				fputc(GetPixelY(curr->YUVImage, x, y), file);
			}
		}

		for (y = 0; y < curr->YUVImage->Height; y += 2) { 
			for (x = 0; x < curr->YUVImage->Width; x += 2) {
				fputc(GetPixelU(curr->YUVImage, x, y), file);
			}
		}

		for (y = 0; y < curr->YUVImage->Height; y += 2) { 
			for (x = 0; x < curr->YUVImage->Width; x += 2) {
				fputc(GetPixelV(curr->YUVImage, x, y), file);
			}
		}
		
		curr = curr->Next;	 
		count++;
	}

	fclose(file);
	file = NULL;

	printf("The movie file %s has been written successfully!\n", fname);
	printf("%d frames are written to the file %s in total.\n", count, fname); 
	return 0;
}

/* EOF */
/* Load the movie frames from the input file */
MOVIE *LoadMovie(const char *fname, int frameNum, 
                 unsigned int width, unsigned height){
	MOVIE *movie = NULL;
	ILIST *list = NULL;
	YUVIMAGE *YUVimage = NULL;
	int x;
	movie = CreateMovie();
	list = CreateImageList();
	assert(movie);
	assert(list);
	for (x = 0; x < frameNum; x++){
		YUVimage = LoadOneFrame(fname, x, width, height);
		AppendYUVImage(list,YUVimage);
	}
	movie->Frames = list;

	return movie;
	
	
}
