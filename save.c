#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "pixel.h"
#include "utils.h"

void save_arg(char *name, int *ascii)
{
	//the function that determines whether the file is saved as text or binary
	char arguments[100];
	fgets(arguments, 100, stdin);

	if (strstr(arguments, "ascii"))
		*ascii = 1;
	else
		*ascii = 0;
	char *token;
	token = strtok(arguments, "\n ");

	strcpy(name, token);
}

void write_mag(int ascii, details v, FILE *f)
{
	if (ascii == 1) {
		if (v.value == 1 && v.blackandwhite == 1)
			fprintf(f, "P1\n");
		else if (v.value == 1)
			fprintf(f, "P2\n");
		else
			fprintf(f, "P3\n");
	} else {
		if (v.value == 1 && v.blackandwhite == 1)
			fprintf(f, "P4\n");
		else if (v.value == 1)
			fprintf(f, "P5\n");
		else
			fprintf(f, "P6\n");
	}
}

void write_text(pixel **image, details v, FILE *f)
{
	//writing in a text file
	for (int i = 0; i < v.height; i++) {
		for (int j = 0; j < v.width; j++) {
			for (int k = 0; k < v.value; k++) {
				unsigned char aux;
				aux = round(image[i][j].color[k]);
				fprintf(f, "%hhu ", aux);
			}
		}
		fprintf(f, "\n");
	}
}

void write_bin(pixel **image, details v, FILE *f)
{
	//writing in an binary file
	for (int i = 0; i < v.height; i++) {
		for (int j = 0; j < v.width; j++) {
			for (int k = 0; k < v.value; k++) {
				unsigned char aux;
				aux = round(image[i][j].color[k]);
				fwrite(&aux, sizeof(unsigned char), 1, f);
			}
		}
	}
}

void save(pixel **image, details v)
{
	FILE *f;
	char *name;
	int ascii = 0;

	name = malloc(100 * sizeof(char));

	save_arg(name, &ascii);

	f = fopen(name, "wt");

	write_mag(ascii, v, f);

	if (v.blackandwhite == 1)
		fprintf(f, "%d %d\n", v.width, v.height);
	else
		fprintf(f, "%d %d\n%d\n", v.width, v.height, v.max);

	if (ascii == 1) {
		printf("Saved %s\n", name);
		write_text(image, v, f);
		fclose(f);
	} else {
		fclose(f);
		FILE *f = fopen(name, "ab");
		printf("Saved %s\n", name);
		write_bin(image, v, f);
		fclose(f);
	}
	free(name);
}