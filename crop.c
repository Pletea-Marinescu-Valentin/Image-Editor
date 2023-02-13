#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "pixel.h"
#include "utils.h"

pixel **crop(pixel **image, details *v)
{
	pixel **copy;
	int new_height, new_width;

	if ((*v).error == -1) {
		printf("No image loaded\n");
		return NULL;
	}

	new_height = (*v).y2 - (*v).y1;
	new_width = (*v).x2 - (*v).x1;
	copy = alloc(new_height, new_width, (*v).value);

	for (int i = (*v).y1; i < (*v).y2; i++) {
		for (int j = (*v).x1; j < (*v).x2; j++) {
			for (int k = 0; k < (*v).value; k++)
				copy[i - (*v).y1][j - (*v).x1].color[k] = image[i][j].color[k];
		}
	}

	free_mat(image, (*v).height, (*v).width);

	(*v).height = new_height;
	(*v).width = new_width;

	(*v).x1 = 0;
	(*v).x2 = (*v).width;
	(*v).y1 = 0;
	(*v).y2 = (*v).height;

	image = copy;

	printf("Image cropped\n");

	return image;
}
