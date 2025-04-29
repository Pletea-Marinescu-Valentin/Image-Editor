#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "pixel.h"

pixel **alloc(int height, int width, int values)
{
	// Memory space is allocated for the image
	pixel **image = malloc(height * sizeof(pixel *));
	if (!image) {
		fprintf(stderr, "Memory allocation failed for rows\n");
		return NULL;
	}

	for (int i = 0; i < height; i++) {
		image[i] = malloc(width * sizeof(pixel));
		if (!image[i]) {
			fprintf(stderr, "Memory allocation failed for columns\n");
			for (int j = 0; j < i; j++)
				free(image[j]);
			free(image);
			return NULL;
		}

		for (int j = 0; j < width; j++) {
			image[i][j].color = malloc(values * sizeof(double));
			if (!image[i][j].color) {
				fprintf(stderr, "Memory allocation failed for pixel colors\n");
				for (int k = 0; k < j; k++)
					free(image[i][k].color);
				free(image[i]);
				for (int k = 0; k < i; k++) {
					for (int l = 0; l < width; l++)
						free(image[k][l].color);
					free(image[k]);
				}
				free(image);
				return NULL;
			}
		}
	}

	return image;
}

void free_mat(pixel **image, int height, int width)
{
	//Free memory space for the image
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++)
			free(image[i][j].color);
		free(image[i]);
	}
	free(image);
}
