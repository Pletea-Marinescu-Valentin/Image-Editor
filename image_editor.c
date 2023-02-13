#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "pixel.h"
#include "utils.h"
#include "load.h"
#include "select.h"
#include "rotate.h"
#include "crop.h"
#include "apply.h"
#include "save.h"
#include "equalize.h"

void clear(void)
{
	// clear what is left on the line after an invalid command
	char buff;
	scanf("%c", &buff);
	while (buff != '\n')
		scanf("%c", &buff);
}

int main(void)
{
	pixel **image = NULL;
	details size;
	char querry[20];
	int ok = 1;
	scanf("%s", querry);
	size.error = -1;
	while (ok == 1) {
		if (strcmp(querry, "LOAD") == 0) {
			if (image)
				free_mat(image, size.height, size.width);
			size.error = 0;
			image = load(&size);
		} else if (strcmp(querry, "SAVE") == 0) {
			if (size.error == -1) {
				printf("No image loaded\n");
				clear();
			} else {
				save(image, size);
			}
		} else if (strcmp(querry, "CROP") == 0) {
			if (size.error == -1)
				printf("No image loaded\n");
			else
				image = crop(image, &size);
		} else if (strcmp(querry, "SELECT") == 0) {
			SELECT(&size);
		} else if (strcmp(querry, "APPLY") == 0)  {
			if (size.error == -1) {
				printf("No image loaded\n");
				clear();
			} else {
				char control;
				scanf("%c", &control);
				if (control == '\n')
					printf("Invalid command\n");
				else
					image = apply(image, size);
			}
		} else if (strcmp(querry, "EXIT") == 0) {
			if (size.error == -1)
				printf("No image loaded\n");
			ok = 0;
			break;
		} else if (strcmp(querry, "EQUALIZE") == 0) {
			if (size.error == -1)
				printf("No image loaded\n");
			else
				image =  equalize(image, size);
		} else if (strcmp(querry, "ROTATE") == 0) {
			if (size.error == -1) {
				printf("No image loaded\n");
				clear();
			} else {
				if (size.x1 == 0 && size.x2 == size.width &&
					size.y1 == 0 && size.y2 == size.height)
					image = rotate_all_image(image, &size);
				else
					image = rotate_a_select(image, size);
			}
		} else {
			if (size.verify == 1) {
				printf("Invalid command\n");
				clear();
			}
		}
		scanf("%s", querry);
	}
	// at the end, the matrix loaded in memory is released
	if (image)
		free_mat(image, size.height, size.width);
	return 0;
}