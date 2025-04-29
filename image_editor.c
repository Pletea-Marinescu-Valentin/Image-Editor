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

// Function to handle memory cleanup for the image and details struct
void cleanup(pixel **image, details *size)
{
	if (image)
		free_mat(image, size->height, size->width);
}

int main(void)
{
	pixel **image = NULL;  // Pointer to hold the image data
	details size = {0};    // Initialize struct to store image properties
	char querry[20];       // Buffer for storing user commands
	int ok = 1;

	size.error = -1;  // Default error state (no image loaded)

	while (ok == 1) {
		scanf("%s", querry);

		if (strcmp(querry, "LOAD") == 0) {
			// Free previously loaded image before loading a new one
			cleanup(image, &size);
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
			if (size.error == -1) {
				printf("No image loaded\n");
				clear();
			} else {
				char control;
				scanf("%c", &control);
				if (control == '\n') {
					printf("Invalid command\n");
				} else {
					// Apply the effect
					image = apply(image, size);
				}
			}
		} else if (strcmp(querry, "EXIT") == 0) {
			// Exit the program
			ok = 0;
			break;
		} else if (strcmp(querry, "EQUALIZE") == 0) {
			// Apply histogram equalization if the image is grayscale
			if (size.error == -1) {
				printf("No image loaded\n");
			} else {
				image = equalize(image, size);
			}
		} else if (strcmp(querry, "ROTATE") == 0) {
			// Apply rotation to either the entire image or a selected area
			if (size.error == -1) {
				printf("No image loaded\n");
				clear();
			} else {
				// Check if the entire image is selected
				if (size.x1 == 0 && size.x2 == size.width &&
					size.y1 == 0 && size.y2 == size.height) {
					image = rotate_all_image(image, &size);
				} else {
					image = rotate_a_select(image, size);
				}
			}
		} else {
			// Handle invalid commands
			if (size.verify == 1) {
				printf("Invalid command\n");
				clear();
			}
		}
	}

	// Cleanup before exiting
	cleanup(image, &size);
	return 0;
}
