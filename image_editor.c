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

// Function to clear any remaining input after an invalid command
void clear(void)
{
	char buff;
	scanf("%c", &buff);
	while (buff != '\n')
		scanf("%c", &buff);
}

int main(void)
{
	pixel **image = NULL;  // Pointer to hold the image data
	details size;          // Struct to store image properties
	char querry[20];       // Buffer for storing user commands
	int ok = 1;

	scanf("%s", querry);
	size.error = -1;  // Default error state (no image loaded)

	while (ok == 1) {
		if (strcmp(querry, "LOAD") == 0) {
			// Free previously loaded image before loading a new one
			if (image)
				free_mat(image, size.height, size.width);
			size.error = 0;
			image = load(&size);
		} else if (strcmp(querry, "SAVE") == 0) {
			// Save the image if one is loaded
			if (size.error == -1) {
				printf("No image loaded\n");
				clear();
			} else {
				save(image, size);
			}
		} else if (strcmp(querry, "CROP") == 0) {
			// Crop the image if one is loaded
			if (size.error == -1)
				printf("No image loaded\n");
			else
				image = crop(image, &size);
		} else if (strcmp(querry, "SELECT") == 0) {
			// Handle selection of an image area
			SELECT(&size);
		} else if (strcmp(querry, "APPLY") == 0)  {
			// Apply effects only if an image is loaded
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
			// Exit the program
			if (size.error == -1)
				printf("No image loaded\n");
			ok = 0;
			break;
		} else if (strcmp(querry, "EQUALIZE") == 0) {
			// Apply histogram equalization if the image is grayscale
			if (size.error == -1)
				printf("No image loaded\n");
			else
				image = equalize(image, size);
		} else if (strcmp(querry, "ROTATE") == 0) {
			// Apply rotation to either the entire image or a selected area
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
			// Handle invalid commands
			if (size.verify == 1) {
				printf("Invalid command\n");
				clear();
			}
		}

		// Read the next command
		scanf("%s", querry);
	}

	// Free memory allocated for the image before exiting
	if (image)
		free_mat(image, size.height, size.width);

	return 0;
}
