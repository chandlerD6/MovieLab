/*Imagelist.c by Chandler Ditolla SID:18731640*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "ImageList.h"
#include "Constants.h"

/* Create a new image list */
ILIST *CreateImageList(void){
	ILIST *list = NULL;
	list = malloc(sizeof(ILIST));
	assert(list);
	
	list->Length = 0;
	list->First = NULL;
	list->Last = NULL;
	
	return list;

}

/* Delete an image list (and all entries) */
void DeleteImageList(ILIST *list){
	IENTRY *entry = NULL, *temp = NULL;
	assert(list);
	
	entry = list->First;
	while(entry){
		temp = entry->Next;
		DeleteImageEntry(entry);
		entry = temp;
	}
	free(list);
	list = NULL;

}

IENTRY *CreateImageEntry(){
	IENTRY *entry = NULL;
	
	entry = malloc(sizeof(IENTRY));
	assert(entry);
	entry->List = NULL;
	entry->Next = NULL;
	entry->Prev = NULL;
	entry->RGBImage = NULL;
	entry->YUVImage = NULL;
	return entry;
	
	
}

void DeleteImageEntry(IENTRY *entry){
	assert(entry);
	if (entry->YUVImage == NULL){
		DeleteImage(entry->RGBImage);
		entry->RGBImage = NULL;
	}
	else if (entry->RGBImage == NULL) {
		DeleteYUVImage(entry->YUVImage);
		entry->YUVImage = NULL;
	}

	free(entry);
	entry = NULL;
}

/* Insert a RGB image to the image list at the end */
void AppendRGBImage(ILIST *list, IMAGE *RGBimage){
	IENTRY *entry = NULL;
	assert(list);
	assert(RGBimage);
	entry = CreateImageEntry();
	entry->RGBImage = RGBimage;
	assert(entry);
		
	if(list->Last){
		entry->List = list;
		entry->Next = NULL;
		entry->Prev = list->Last;
		list->Last->Next = entry;
		list->Last = entry;
	}
	else{
		entry->List = list;
		entry->Next = NULL;
		entry->Prev = NULL;
		list->First = entry;
		list->Last = entry;
	}
	list->Length++;
	
}

/* Insert a YUV image to the image list at the end */
void AppendYUVImage(ILIST *list, YUVIMAGE *YUVimage){
	IENTRY *entry = NULL;
	assert(list);
	assert(YUVimage);
	entry = CreateImageEntry();
	entry->YUVImage = YUVimage;
	assert(entry);	
	
	if(list->Last){
		entry->List = list;
		entry->Next = NULL;
		entry->Prev = list->Last;
		list->Last->Next = entry;
		list->Last = entry;
	}
	else{
		entry->List = list;
		entry->Next = NULL;
		entry->Prev = NULL;
		list->First = entry;
		list->Last = entry;
	}
	list->Length++;
	
}

/* Crop an image list */
void CropImageList(ILIST *list, unsigned int start, unsigned int end){
	int i;
	IENTRY *entry = NULL, *temp2 = NULL, *temp3 = NULL;
	assert(list);
	entry = list->First;
	
	for( i = 0; i < start; i++){
		temp2 = entry->Next;
		entry = temp2;	
	}
	
	for( i = start; i <= end; i++){
		temp2 = entry->Next;
		temp3 = entry->Prev;
		DeleteImageEntry(entry);
		entry = temp2;	
		temp3->Next = temp2;
		temp2->Prev = temp3;
		list->Length--;
	}
}

/* Fast forward an image list */
void FastImageList(ILIST *list, unsigned int factor){
	int i, length = list->Length;
	IENTRY *entry = NULL, *temp2 = NULL, *temp3 = NULL;
	assert(list);
	entry = list->First;
	
	
	for( i = 0; i < length; i++){
	
		if ( i % factor == 0) {
			temp2 = entry->Next;
			entry = temp2;
		} else if ( i < length -1){
			temp2 = entry->Next;
			temp3 = entry->Prev;
			DeleteImageEntry(entry);
			entry = temp2;	
			temp3->Next = temp2;
			temp2->Prev = temp3;
			list->Length--;
		} 
		if (i % factor != 0 && i == length -1){
			temp2 = entry->Prev;
			DeleteImageEntry(entry);
			entry = temp2;
			entry->Next = NULL;
			list->Last = entry;
			list->Length--;
		}
	}
}

/* Reverse an image list */
void ReverseImageList(ILIST *list){
	assert(list);
	int i;
	IENTRY *Fentry = NULL, *tempFN = NULL, *tempFP = NULL;
	
	Fentry = list->First;
	list->Last = Fentry;		
	tempFN = Fentry->Next;
	tempFP = Fentry->Prev;
	for (i = 0; i < list->Length -1; i++){
		Fentry->Next = tempFP;
		Fentry->Prev = tempFN;
		tempFP = Fentry;
		Fentry = tempFN;
		tempFN = tempFN->Next;
		Fentry->Prev = tempFN;
		Fentry->Next = tempFP;
	}	
	list->First = Fentry;
		

}


