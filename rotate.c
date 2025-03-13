#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "pixel.h"
#include "utils.h"

// Function to rotate the entire image 90 degrees to the right
void rotate_to_right(pixel **image, pixel **copy_image, details v)
{
	// Loop through the original image and assign the rotated values to copy_image
	for (int i = 0; i < v.width; i++) {
		for (int j = 0; j < v.height; j++) {
			for (int k = 0; k < v.value; k++) {
				copy_image[i][j].color[k] = image[v.height - j - 1][i].color[k];
			}
		}
	}
}

// Function to rotate a selected portion of the image 90 degrees to the right
void rotate_to_right_select(pixel **image, pixel **copy_image, details v)
{
	int l;
	double aux;

	// Transpose the selection (swap rows and columns)
	for (int i = v.x1; i < v.x2; i++)
		for (int j = v.y1; j < v.y2; j++)
			for (int k = 0; k < v.value; k++)
				copy_image[i - v.x1][j - v.y1].color[k] = image[j][i].color[k];

	// Invert columns to complete the 90-degree rotation
	l = v.x2 - v.x1;
	for (int i = 0; i < l; i++)
		for (int j = 0; j < l / 2; j++)
			for (int k = 0; k < v.value; k++) {
				aux = copy_image[i][j].color[k];
				copy_image[i][j].color[k] = copy_image[i][l - j - 1].color[k];
				copy_image[i][l - j - 1].color[k] = aux;
			}
}

// Function to rotate the **entire** image by a given angle
pixel **rotate_all_image(pixel **image, details *v)
{
	int angle, auxangle = 0, aux;
	scanf("%d", &angle);
	pixel **copy_image = NULL;

	// Convert negative angles to their positive equivalents
	if (angle < 0 && angle > -360)
		auxangle = 360 + angle;
	else
		auxangle = angle;

	// Validate angle
	if (angle > 360 || angle < -360) {
		printf("Unsupported rotation angle\n");
	} else {
		int ok = 0;

		// Rotation by 0° (no change)
		if (auxangle % 360 == 0) {
			printf("Rotated %d\n", angle);
			ok = 1;
		}

		// Rotation by 90°
		if (auxangle % 360 == 90) {
			printf("Rotated %d\n", angle);
			copy_image = alloc((*v).width, (*v).height, (*v).value);
			rotate_to_right(image, copy_image, *v);

			// Swap width and height
			aux = (*v).width;
			(*v).width = (*v).height;
			(*v).height = aux;

			// Swap x2 and y2
			aux = (*v).x2;
			(*v).x2 = (*v).y2;
			(*v).y2 = aux;

			// Free old image and assign new rotated image
			free_mat(image, (*v).width, (*v).height);
			image = copy_image;
			ok = 1;
		}

		// Rotation by 180° (two consecutive 90° rotations)
		if (auxangle % 360 == 180) {
			printf("Rotated %d\n", angle);
			for (int i = 0; i < 2; i++) {
				copy_image = alloc((*v).width, (*v).height, (*v).value);
				rotate_to_right(image, copy_image, *v);

				// Swap width and height
				aux = (*v).width;
				(*v).width = (*v).height;
				(*v).height = aux;

				// Swap x2 and y2
				aux = (*v).x2;
				(*v).x2 = (*v).y2;
				(*v).y2 = aux;

				free_mat(image, (*v).width, (*v).height);
				image = copy_image;
			}
			ok = 1;
		}

		// Rotation by 270° (three consecutive 90° rotations)
		if (auxangle % 360 == 270) {
			printf("Rotated %d\n", angle);
			for (int i = 0; i < 3; i++) {
				copy_image = alloc((*v).width, (*v).height, (*v).value);
				rotate_to_right(image, copy_image, *v);

				// Swap width and height
				aux = (*v).width;
				(*v).width = (*v).height;
				(*v).height = aux;

				// Swap x2 and y2
				aux = (*v).x2;
				(*v).x2 = (*v).y2;
				(*v).y2 = aux;

				free_mat(image, (*v).width, (*v).height);
				image = copy_image;
			}
			ok = 1;
		}

		// If the rotation angle is not supported
		if (ok == 0)
			printf("Unsupported rotation angle\n");
	}
	return image;
}

// Function to save a rotated selection back into the main image
void save_new_matrix(pixel **image, pixel **temp, details v)
{
	for (int i = v.y1; i < v.y2; i++)
		for (int j = v.x1; j < v.x2; j++)
			for (int k = 0; k < v.value; k++)
				image[i][j].color[k] = temp[i - v.y1][j - v.x1].color[k];
}

// Function to copy selected area into a temporary matrix before rotation
void samematrix(pixel **image, pixel **temp, details v)
{
	for (int i = v.y1; i < v.y2; i++)
		for (int j = v.x1; j < v.x2; j++)
			for (int k = 0; k < v.value; k++)
				temp[i - v.y1][j - v.x1].color[k] = image[i][j].color[k];
}

// Function to rotate only a selected area
pixel **rotate_a_select(pixel **image, details v)
{
	pixel **temp = NULL;
	int l, angle, auxangle = 0;
	l = v.x2 - v.x1;
	scanf("%d", &angle);

	// Ensure selection is square
	if (v.y2 - v.y1 != l) {
		printf("The selection must be square\n");
	} else {
		// Convert negative angles
		if (angle < 0 && angle > -360)
			auxangle = 360 - (-1 * angle);
		else
			auxangle = angle;

		// Validate angle
		if (angle > 360 || angle < -360) {
			printf("Unsupported rotation angle\n");
		} else {
			int ok = 0;
			temp = alloc(l, l, v.value);

			// Rotation by 0° (no change)
			if (auxangle % 360 == 0) {
				printf("Rotated %d\n", angle);
				samematrix(image, temp, v);
				ok = 1;
			}

			// Rotation by 90°
			if (auxangle % 360 == 90) {
				printf("Rotated %d\n", angle);
				rotate_to_right_select(image, temp, v);
				ok = 1;
			}

			// Rotation by 180° (two 90° rotations)
			if (auxangle % 360 == 180) {
				printf("Rotated %d\n", angle);
				for (int i = 0; i < 2; i++) {
					rotate_to_right_select(image, temp, v);
					save_new_matrix(image, temp, v);
				}
				ok = 1;
			}

			// Rotation by 270° (three 90° rotations)
			if (auxangle % 360 == 270) {
				printf("Rotated %d\n", angle);
				for (int i = 0; i < 3; i++) {
					rotate_to_right_select(image, temp, v);
					save_new_matrix(image, temp, v);
				}
				ok = 1;
			}

			if (ok) save_new_matrix(image, temp, v);
			else printf("Unsupported rotation angle\n");

			free_mat(temp, l, l);
		}
	}
	return image;
}
