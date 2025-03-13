#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "pixel.h"
#include "utils.h"

// Function to crop an image based on the given coordinates
pixel **crop(pixel **image, details *v)
{
	pixel **copy;
	int new_height, new_width;

	// Check if an image is loaded before attempting to crop
	if ((*v).error == -1) {
		printf("No image loaded\n");
		return NULL;
	}

	// Calculate new dimensions based on the selected crop area
	new_height = (*v).y2 - (*v).y1;
	new_width = (*v).x2 - (*v).x1;

	// Allocate memory for the cropped image
	copy = alloc(new_height, new_width, (*v).value);

	// Copy pixel data from the selected region into the new cropped image
	for (int i = (*v).y1; i < (*v).y2; i++) {
		for (int j = (*v).x1; j < (*v).x2; j++) {
			for (int k = 0; k < (*v).value; k++)
				copy[i - (*v).y1][j - (*v).x1].color[k] = image[i][j].color[k];
		}
	}

	// Free memory of the original image
	free_mat(image, (*v).height, (*v).width);

	// Update image details to reflect new cropped dimensions
	(*v).height = new_height;
	(*v).width = new_width;

	// Reset crop selection to cover the entire new image
	(*v).x1 = 0;
	(*v).x2 = (*v).width;
	(*v).y1 = 0;
	(*v).y2 = (*v).height;

	// Replace the original image with the cropped version
	image = copy;

	printf("Image cropped\n");

	return image;
}
