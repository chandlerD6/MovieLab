/* DIPs.c: hw5, for EECS 22, 2016 fall
 * Author: Chandler Ditolla SID: 18731640
 * Date:   12/4/2016
 */
#include <assert.h> /* assert */
#include <string.h> /* memcpy */
#include <stdlib.h> /* abs */
#include "DIPs.h"

IMAGE *Aging(IMAGE *image){
	assert(image);
	int x, y;
	for(y = 0; y < image->Height; y++ ) {
		for(x = 0; x < image->Width; x++ ) {
			SetPixelB(image, x, y, (GetPixelR(image, x, y) + GetPixelG(image, x, y) + GetPixelB(image, x, y))/5);
			SetPixelR(image, x, y, (unsigned char) (GetPixelB(image, x, y) * 1.6));
			SetPixelG(image, x, y, (unsigned char) (GetPixelB(image, x, y) * 1.6));
		}
	}
	return image;
}


IMAGE *Edge(IMAGE *image) {
	assert(image);
	IMAGE *tmpImage = CreateImage(image->Width, image->Height);
	assert(tmpImage);

	int x, y, m, n;
    memcpy(tmpImage->R, image->R, image->Width * image->Height * sizeof(unsigned char));
    memcpy(tmpImage->G, image->G, image->Width * image->Height * sizeof(unsigned char));
    memcpy(tmpImage->B, image->B, image->Width * image->Height * sizeof(unsigned char));
	for (y = 1; y < image->Height - 1; y++) {
		for (x = 1; x < image->Width - 1; x++) {
			int tmpR = 0;
			int tmpG = 0;
			int tmpB = 0;
			for (m = -1; m <= 1; m++) {
				for (n = -1; n <= 1; n++) {
					tmpR += (GetPixelR(tmpImage, x, y) - GetPixelR(tmpImage, x + n, y + m));
					tmpG += (GetPixelG(tmpImage, x, y) - GetPixelG(tmpImage, x + n, y + m));
					tmpB += (GetPixelB(tmpImage, x, y) - GetPixelB(tmpImage, x + n, y + m));
				}
			}
			SetPixelR(image, x, y, (tmpR > MAX_PIXEL) ? MAX_PIXEL : (tmpR < 0) ? 0 : tmpR);
			SetPixelG(image, x, y, (tmpG > MAX_PIXEL) ? MAX_PIXEL : (tmpG < 0) ? 0 : tmpG);
			SetPixelB(image, x, y, (tmpB > MAX_PIXEL) ? MAX_PIXEL : (tmpB < 0) ? 0 : tmpB);
		}
	}
	for (y = 0; y < image->Height; y++) {
		x = 0;
		SetPixelR(image, x, y, 0);
		SetPixelG(image, x, y, 0);
		SetPixelB(image, x, y, 0);
		x = image->Width - 1;
		SetPixelR(image, x, y, 0);
		SetPixelG(image, x, y, 0);
		SetPixelB(image, x, y, 0);
	}
	for (x = 0; x < image->Width; x++) {
		y = 0;
		SetPixelR(image, x, y, 0);
		SetPixelG(image, x, y, 0);
		SetPixelB(image, x, y, 0);
		y = image->Height - 1;
		SetPixelR(image, x, y, 0);
		SetPixelG(image, x, y, 0);
		SetPixelB(image, x, y, 0);
	}
	DeleteImage(tmpImage);
	tmpImage = NULL;
    return image;
}

IMAGE *HFlip(IMAGE *image) {
	assert(image);
	int x, y;
	unsigned char r, g, b;
	for (y = 0; y < image->Height; y ++) {
		for (x = 0; x < image->Width / 2; x ++) {
			r = GetPixelR(image, image->Width - 1 - x, y);
			g = GetPixelG(image, image->Width - 1 - x, y);
			b = GetPixelB(image, image->Width - 1 - x, y);
			SetPixelR(image, image->Width - 1 - x, y, GetPixelR(image, x, y));
			SetPixelG(image, image->Width - 1 - x, y, GetPixelG(image, x, y));
			SetPixelB(image, image->Width - 1 - x, y, GetPixelB(image, x, y));
			SetPixelR(image, x, y, r);
			SetPixelG(image, x, y, g);
			SetPixelB(image, x, y, b);
		}
	}
    return image;
}


IMAGE *Watermark(IMAGE *image, const IMAGE *watermark, unsigned int topLeftX, unsigned int topLeftY){
	int x, y, i, j, newH, newW, imageH, imageW, watermarkH, watermarkW;
	imageH = image->Height;
	imageW = image->Width;
	watermarkH = watermark->Height;
	watermarkW = watermark->Width;
	newH = imageH;
	newW = imageW;
	if (imageH > watermarkH + topLeftY){
		newH = (watermarkH + topLeftY);
	}
	if (imageW > watermarkW + topLeftX){
		newW = (watermarkW + topLeftX);
	}
	j = 0;
	for( y = topLeftY; y < newH; y++){
		i = 0;
		for( x = topLeftX; x < newW; x++){
			if (GetPixelR(watermark, i, j) == 0 && GetPixelG(watermark, i, j) == 0 && GetPixelB(watermark, i, j) == 0){
				SetPixelR(image, x, y, clip( 1.45*GetPixelR(image, i, j)));
				SetPixelG(image, x, y, clip( 1.45*GetPixelG(image, i, j)));
				SetPixelB(image, x, y, clip( 1.45*GetPixelB(image, i, j)));
			}
			i++;
		}
		j++;
	}
	return image;
}
IMAGE *Spotlight(IMAGE *image, int centerX, int centerY, unsigned int radius){
	
	assert(image);
        int x, y;
        IMAGE *temp = NULL;
        temp = CreateImage(image->Width, image->Height);
        assert(temp);
        for( y = 0; y < image->Height; y++){
                for( x = 0; x < image->Width; x++){
                        SetPixelR(temp, x, y, GetPixelR(image, x, y));
                        SetPixelG(temp, x, y, GetPixelG(image, x, y));
                        SetPixelB(temp, x, y, GetPixelB(image, x, y));
                }
        }
        for(y = 0; y < image->Height; y++){
                for(x = 0; x < image->Width; x++){
			if( (x - radius)*(x - radius) + (y - radius)*(y - radius) >= radius*radius){
				SetPixelR(image, x, y, 0);
                                SetPixelG(image, x, y, 0);
                                SetPixelB(image, x, y, 0);
                        }
        	}
	}
        DeleteImage(temp);
        temp = NULL;
        return image;
}


IMAGE *Zoom(IMAGE *image, unsigned int percentage){
    int x, y, x1, y1, x2, y2, i, j, tmpR, tmpG, tmpB;
    const int NEW_WIDTH = image->Width * percentage / 100;
    const int NEW_HEIGHT = image->Height * percentage / 100;
    if (percentage == 100){
	return image;	
    }
    IMAGE *image_tmp = CreateImage(NEW_WIDTH, NEW_HEIGHT);
    if (!image_tmp) return image;
    if (percentage < 100) {
        for(x = 0; x < NEW_WIDTH; x ++){
            for(y = 0; y < NEW_HEIGHT; y++){
                x1 = (int)(x / (percentage / 100.00));
                y1 = (int)(y / (percentage / 100.00));
                x2 = (int)((x + 1) / (percentage / 100.00));
                y2 = (int)((y + 1) / (percentage / 100.00));
                tmpR = tmpB = tmpG = 0;
                for(i = x1; i < x2; i ++){
                    for(j = y1; j < y2; j ++){
                        tmpR += GetPixelR(image, i, j); 
                        tmpG += GetPixelG(image, i, j); 
                        tmpB += GetPixelB(image, i, j); 
                    }   
                }   
                SetPixelR(image_tmp, x, y, tmpR / ((x2 - x1) * (y2 - y1)));
                SetPixelG(image_tmp, x, y, tmpG / ((x2 - x1) * (y2 - y1)));
                SetPixelB(image_tmp, x, y, tmpB / ((x2 - x1) * (y2 - y1)));
            }   
        }
    }
    
    for( x = 0; x < image->Width; x++){
	for( y = 0; y < image->Height; y++){
		SetPixelR(image, x, y, 0);
		SetPixelG(image, x, y, 0);
		SetPixelB(image, x, y, 0);
    	}
    }
    i = 0;
    for( x = (image->Width-NEW_WIDTH)/2 ; x < (image->Width-NEW_WIDTH)/2 + NEW_WIDTH ; x++){
	j = 0;
	for( y = (image->Height-NEW_HEIGHT)/2 ; y < (image->Height-NEW_HEIGHT)/2 + NEW_HEIGHT ; y++){
		SetPixelR(image, x, y, GetPixelR(image_tmp, i, j));
		SetPixelG(image, x, y, GetPixelG(image_tmp, i, j));
		SetPixelB(image, x, y, GetPixelB(image_tmp, i, j));
		j++;	
	}
	i++;
    }
    DeleteImage(image_tmp);
    image_tmp = NULL;
    return image;
}
