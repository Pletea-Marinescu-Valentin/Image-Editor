#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "pixel.h"
#include "utils.h"

// Function to determine whether the file should be saved as text (ASCII) or binary
void save_arg(char *name, int *ascii)
{
	// Buffer to store user input
	char arguments[100];
	fgets(arguments, 100, stdin); // Read input string from user

	// Check if the input contains "ascii", set ascii flag accordingly
	if (strstr(arguments, "ascii"))
		*ascii = 1; // Save as ASCII
	else
		*ascii = 0; // Save as binary

	// Extract the filename from the input
	char *token;
	token = strtok(arguments, "\n "); // Remove newline and spaces

	// Copy the filename into the provided variable
	strcpy(name, token);
}

// Function to write the magic number (file type) to the output file
void write_mag(int ascii, details v, FILE *f)
{
	// ASCII format (text)
	if (ascii == 1) {
		if (v.value == 1 && v.blackandwhite == 1)
			fprintf(f, "P1\n"); // PBM (black & white ASCII)
		else if (v.value == 1)
			fprintf(f, "P2\n"); // PGM (grayscale ASCII)
		else
			fprintf(f, "P3\n"); // PPM (color ASCII)
	} else { // Binary format
		if (v.value == 1 && v.blackandwhite == 1)
			fprintf(f, "P4\n"); // PBM (black & white binary)
		else if (v.value == 1)
			fprintf(f, "P5\n"); // PGM (grayscale binary)
		else
			fprintf(f, "P6\n"); // PPM (color binary)
	}
}

// Function to write pixel data to an ASCII (text) file
void write_text(pixel **image, details v, FILE *f)
{
	// Loop through the image pixels and write values as text
	for (int i = 0; i < v.height; i++) {
		for (int j = 0; j < v.width; j++) {
			for (int k = 0; k < v.value; k++) {
				// Round pixel value to nearest integer and write to file
				unsigned char aux;
				aux = round(image[i][j].color[k]);
				fprintf(f, "%hhu ", aux);
			}
		}
		fprintf(f, "\n"); // Newline after each row
	}
}

// Function to write pixel data to a binary file
void write_bin(pixel **image, details v, FILE *f)
{
	// Loop through image pixels and write binary values
	for (int i = 0; i < v.height; i++) {
		for (int j = 0; j < v.width; j++) {
			for (int k = 0; k < v.value; k++) {
				// Round pixel value to nearest integer and write as binary
				unsigned char aux;
				aux = round(image[i][j].color[k]);
				fwrite(&aux, sizeof(unsigned char), 1, f);
			}
		}
	}
}

// Function to save the image to a file (either ASCII or binary)
void save(pixel **image, details v)
{
	FILE *f;
	char *name = malloc(100 * sizeof(char));
	if (!name) {
		fprintf(stderr, "Memory allocation failed for filename\n");
		return;
	}

	int ascii = 0;
	save_arg(name, &ascii);

	f = fopen(name, "wt");
	if (!f) {
		fprintf(stderr, "Failed to open file %s for writing\n", name);
		free(name);
		return;
	}

	write_mag(ascii, v, f);

	if (v.blackandwhite == 1)
		fprintf(f, "%d %d\n", v.width, v.height);
	else
		fprintf(f, "%d %d\n%d\n", v.width, v.height, v.max);

	if (ascii == 1) {
		write_text(image, v, f);
		fclose(f);
		printf("Saved %s\n", name);
	} else {
		fclose(f);
		f = fopen(name, "ab");
		if (!f) {
			fprintf(stderr, "Failed to reopen file %s in binary mode\n", name);
			free(name);
			return;
		}
		write_bin(image, v, f);
		fclose(f);
		printf("Saved %s\n", name);
	}

	free(name);
}
