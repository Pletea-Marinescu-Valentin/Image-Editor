#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "pixel.h"
#include "utils.h"

// Function to apply histogram equalization to a grayscale image
pixel **equalize(pixel **image, details v)
{
	int area = v.height * v.width;  // Total number of pixels in the image
	int hist[256] = {0};            // Histogram array to store pixel intensity counts
	int curr = 0;                   // Cumulative sum of histogram values
	int grayscale[256] = {0};        // Lookup table for equalized pixel values

	// Check if the image is grayscale (black and white)
	if (v.blackandwhite == 0 && v.value == 1) {
		printf("Equalize done\n");

		// Compute histogram of the image
		for (int i = 0; i < v.height; i++) {
			for (int j = 0; j < v.width; j++) {
				for (int k = 0; k < v.value; k++)
					hist[(int)image[i][j].color[k]]++;
			}
		}

		// Compute the cumulative distribution function (CDF) for equalization
		for (int i = 0; i < 256; i++) {
			curr += hist[i];  // Accumulate histogram values
			grayscale[i] = round((((double)curr) * 255) / area);  // Normalize to 0-255 range
		}

		// Apply histogram equalization to the image
		for (int i = 0; i < v.height; i++) {
			for (int j = 0; j < v.width; j++) {
				for (int k = 0; k < v.value; k++) {
					image[i][j].color[k] = (double)grayscale
						[(int)image[i][j].color[k]];
				}
			}
		}

	} else {
		// If the image is not grayscale, print an error message
		printf("Black and white image needed\n");
	}

	return image;
}
