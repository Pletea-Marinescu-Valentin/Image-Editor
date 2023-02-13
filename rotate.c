#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "pixel.h"
#include "utils.h"

void rotate_to_right(pixel **image, pixel **copy_image, details v)
{
	//the function that rotates the whole image to the right
	for (int i = 0; i < v.width; i++) {
		for (int j = 0; j < v.height; j++) {
			for (int k = 0; k < v.value; k++) {
				copy_image[i][j].color[k] =
					image[v.height - j - 1][i].color[k];
			}
		}
	}
}

void rotate_to_right_select(pixel **image, pixel **copy_image, details v)
{
	//the function that only rotates a selection
	//this performs the transpose and then inverts the columns
	int l;
	double aux;

	for (int i = v.x1; i < v.x2; i++)
		for (int j = v.y1; j < v.y2; j++)
			for (int k = 0; k < v.value; k++)
				copy_image[i - v.x1][j - v.y1].color[k] =
					image[j][i].color[k];

	l = v.x2 - v.x1;
	for (int i = 0; i < l; i++)
		for (int j = 0; j < l / 2; j++)
			for (int k = 0; k < v.value; k++) {
				aux = copy_image[i][j].color[k];
				copy_image[i][j].color[k] = copy_image[i][l - j - 1].color[k];
				copy_image[i][l - j - 1].color[k] = aux;
			}
}

pixel **rotate_all_image(pixel **image, details *v)
{
	int angle, auxangle = 0, aux;
	scanf("%d", &angle);
	pixel **copy_image = NULL;
	//negative angles can be seen as their positive complements
	if (angle < 0 && angle > -360)
		auxangle = 360 + angle;
	else
		auxangle = angle;
	if (angle > 360 || angle < -360) {
		printf("Unsupported rotation angle\n");
	} else {
		int ok = 0;
		if (auxangle % 360 == 0) {
			printf("Rotated %d\n", angle);
			ok = 1;
		}
		if (auxangle % 360 == 90) {
			printf("Rotated %d\n", angle);
			copy_image = alloc((*v).width, (*v).height, (*v).value);
			rotate_to_right(image, copy_image, *v);

			aux = (*v).width;
			(*v).width = (*v).height;
			(*v).height = aux;

			aux = (*v).x2;
			(*v).x2 = (*v).y2;
			(*v).y2 = aux;

			free_mat(image, (*v).width, (*v).height);

			image = copy_image;
			ok = 1;
		}

	//180 and 270 rotations can be seen as repeated 90 rotations
		if (auxangle % 360 == 180) {
			printf("Rotated %d\n", angle);
			for (int i = 0; i < 2; i++) {
				copy_image = alloc((*v).width, (*v).height, (*v).value);
				rotate_to_right(image, copy_image, *v);

				aux = (*v).width;
				(*v).width = (*v).height;
				(*v).height = aux;

				aux = (*v).x2;
				(*v).x2 = (*v).y2;
				(*v).y2 = aux;

				free_mat(image, (*v).width, (*v).height);
				image = copy_image;
			}
			ok = 1;
		}

		if (auxangle % 360 == 270) {
			printf("Rotated %d\n", angle);
			for (int i = 0; i < 3; i++) {
				copy_image = alloc((*v).width, (*v).height, (*v).value);
				rotate_to_right(image, copy_image, *v);

				aux = (*v).width;
				(*v).width = (*v).height;
				(*v).height = aux;

				aux = (*v).x2;
				(*v).x2 = (*v).y2;
				(*v).y2 = aux;

				free_mat(image, (*v).width, (*v).height);
				image = copy_image;
			}
			ok = 1;
		}
		if (ok == 0)
			printf("Unsupported rotation angle\n");
	}
	return image;
}

void save_new_matrix(pixel **image, pixel **temp, details v)
{
	for (int i = v.y1; i < v.y2; i++)
		for (int j = v.x1; j < v.x2; j++)
			for (int k = 0; k < v.value; k++)
				image[i][j].color[k] = temp[i - v.y1][j - v.x1].color[k];
}

void samematrix(pixel **image, pixel **temp, details v)
{
	for (int i = v.y1; i < v.y2; i++)
		for (int j = v.x1; j < v.x2; j++)
			for (int k = 0; k < v.value; k++)
				temp[i - v.y1][j - v.x1].color[k] = image[i][j].color[k];
}

pixel **rotate_a_select(pixel **image, details v)
{
	pixel **temp = NULL;
	int l, angle, auxangle = 0;
	l = v.x2 - v.x1;
	scanf("%d", &angle);
	if (v.y2 - v.y1 != l) {
		printf("The selection must be square\n");
	} else {
		if (angle < 0 && angle > -360)
			auxangle = 360 - (-1 * angle);
		else
			auxangle = angle;
		if (angle > 360 || angle < -360) {
			printf("Unsupported rotation angle\n");
		} else {
			int ok = 0;
			temp = alloc(l, l, v.value);
			if (auxangle % 360 == 0) {
				printf("Rotated %d\n", angle);
				samematrix(image, temp, v);
				ok = 1;
			}

			if (auxangle % 360 == 90) {
				printf("Rotated %d\n", angle);
				rotate_to_right_select(image, temp, v);
				ok = 1;
			}

			if (auxangle % 360 == 180) {
				printf("Rotated %d\n", angle);
				for (int i = 0; i < 2; i++) {
					rotate_to_right_select(image, temp, v);
					save_new_matrix(image, temp, v);
				}
				ok = 1;
			}

			if (auxangle % 360 == 270) {
				printf("Rotated %d\n", angle);
				for (int i = 0; i < 3; i++) {
					rotate_to_right_select(image, temp, v);
					save_new_matrix(image, temp, v);
				}
				ok = 1;
			}

			if (ok == 0)
				printf("Unsupported rotation angle\n");
			else
				save_new_matrix(image, temp, v);
			free_mat(temp, l, l);
		}
	}
	return image;
}