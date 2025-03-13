#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "pixel.h"

pixel **alloc(int height, int width, int values)
{
	//Memory space is allocated for the image
	pixel **image;

	image = malloc(height * sizeof(pixel *));

	if (!image)
		fprintf(stderr, "malloc failled\n");

	for (int i = 0; i < height; i++) {
		image[i] = malloc(width * sizeof(pixel));
		if (!image[i]) {
			fprintf(stderr, "malloc failled\n");
			for (int j = 0; j < i; j++)
				free(image[i]);
			free(image);
		}
		for (int j = 0; j < width; j++)
			image[i][j].color = malloc(values * sizeof(double));
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
