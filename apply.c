#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "pixel.h"
#include "utils.h"

void clamp(double *value)
{
	if (*value < 0)
		*value = 0;
	if (*value > 255)
		*value = 255;
}

double  newpixel(pixel **image, int n, int m, int p, char effect[15])
{
	//these are the helper arrays for applying image effects
	const double mat_gblur[3][3] = {
		{1. / 16., 1. / 8., 1. / 16.},
		{1. / 8., 1. / 4., 1. / 8.},
		{1. / 16., 1. / 8., 1. / 16.}
	};

	const double mat_blur[3][3] = {
		{1. / 9., 1. / 9., 1. / 9.},
		{1. / 9., 1. / 9., 1. / 9.},
		{1. / 9., 1. / 9., 1. / 9.}
	};

	const double mat_sharpen[3][3] = {
		{0., -1., 0.},
		{-1., 5., -1.},
		{0., -1., 0.}
	};

	const double mat_edge[3][3] = {
		{-1., -1., -1.},
		{-1., 8., -1.},
		{-1., -1., -1.}
	};

	double newpix = 0;

	int dx[] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
	int dy[] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};

	if (strcmp(effect, "GAUSSIAN_BLUR") == 0) {
		for (int k = 0; k < 9; k++) {
			newpix = newpix + (double)image[n + dx[k]][m + dy[k]].color[p]
				* (double)mat_gblur[1 + dx[k]][1 + dy[k]];
			}
		clamp(&newpix);
	} else if (strcmp(effect, "BLUR") == 0) {
		for (int k = 0; k < 9; k++) {
			newpix = newpix + (double)image[n + dx[k]][m + dy[k]].color[p]
				* (double)mat_blur[1 + dx[k]][1 + dy[k]];
			}
		clamp(&newpix);
	} else if (strcmp(effect, "SHARPEN") == 0) {
		for (int k = 0; k < 9; k++) {
			newpix = newpix + (double)image[n + dx[k]][m + dy[k]].color[p]
				* (double)mat_sharpen[1 + dx[k]][1 + dy[k]];
			}
		clamp(&newpix);
	} else if (strcmp(effect, "EDGE") == 0) {
		for (int k = 0; k < 9; k++) {
			newpix = newpix + (double)image[n + dx[k]][m + dy[k]].color[p]
				* (double)mat_edge[1 + dx[k]][1 + dy[k]];
			}
		clamp(&newpix);
	}
	return newpix;
}

pixel **apply(pixel **image, details v)
{
	pixel **copy;
	char effect[15];

	scanf("%s", effect);

	int ok = 0;
	char option[4][15] = {"GAUSSIAN_BLUR", "BLUR", "EDGE", "SHARPEN"};

	for (int i = 0; i < 4; i++)
		if (strcmp(option[i], effect) == 0)
			ok = 1;

	if (ok == 0) {
		printf("APPLY parameter invalid\n");
	} else {
		if (v.value == 3) {
			printf("APPLY %s done\n", effect);

			copy = alloc(v.height, v.width, v.value);

			for (int i = 0; i < v.height; i++) {
				for (int j = 0; j < v.width; j++) {
					for (int k = 0; k < v.value; k++)
						copy[i][j].color[k] = image[i][j].color[k];
				}
			}

			for (int i = v.y1; i < v.y2; i++) {
				for (int j = v.x1; j < v.x2; j++) {
					int height = v.height - 2;
					int width = v.width - 2;
					int ok = 0;
					if (i >= 1 && i <= height && j >= 1 && j <= width)
						ok = 1;
					for (int k = 0; k < 3 && ok == 1; k++)
						copy[i][j].color[k] = newpixel(image, i, j, k, effect);
				}
			}

			free_mat(image, v.height, v.width);

			image = copy;
		} else {
			printf("Easy, Charlie Chaplin\n");
		}
	}

	return image;
}