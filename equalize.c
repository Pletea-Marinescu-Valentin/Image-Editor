#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "pixel.h"
#include "utils.h"

pixel **equalize(pixel **image, details v)
{
	int area = v.height * v.width;
	int hist[256] = {0}, curr = 0, grayscale[256] = {0};
	//we check if the image is of grayscale type
	if (v.blackandwhite == 0 && v.value == 1) {
		printf("Equalize done\n");

		for (int i = 0; i < v.height; i++) {
			for (int j = 0; j < v.width; j++) {
				for (int k = 0; k < v.value; k++)
					hist[(int)image[i][j].color[k]]++;
			}
		}
		//calculate the new value of the pixel according to the image equalization
		for (int i = 0; i < 256; i++) {
			curr = curr + hist[i];
			grayscale[i] = round((((double)curr) * 255) / area);
		}

		for (int i = 0; i < v.height; i++) {
			for (int j = 0; j < v.width; j++) {
				for (int k = 0; k < v.value; k++) {
					image[i][j].color[k] = (double)grayscale
						[(int)image[i][j].color[k]];
				}
			}
		}

	} else {
		printf("Black and white image needed\n");
	}
	return image;
}