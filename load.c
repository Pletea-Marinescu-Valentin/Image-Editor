#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "pixel.h"
#include "utils.h"

void type(char *magicword, details *v)
{
	//we determine if the file is of text or binary type
	if (strcmp(magicword, "P1") == 0 || strcmp(magicword, "P2") == 0 ||
		strcmp(magicword, "P3") == 0)
		(*v).type = 1;

	if (strcmp(magicword, "P4") == 0 || strcmp(magicword, "P5") == 0 ||
		strcmp(magicword, "P6") == 0)
		(*v).type = 2;

	//aflam daca imaginea este de tip color sau nu
	if (strcmp(magicword, "P1") == 0 || strcmp(magicword, "P4") == 0) {
		(*v).value = 1;
		(*v).blackandwhite = 1;
	}

	if (strcmp(magicword, "P2") == 0 || strcmp(magicword, "P5") == 0) {
		(*v).value = 1;
		(*v).blackandwhite = 0;
	}

	if (strcmp(magicword, "P3") == 0 || strcmp(magicword, "P6") == 0) {
		(*v).value = 3;
		(*v).blackandwhite = 0;
	}
	//value ->1 (only one color, black-and-white or grayscale image is used)
	//value ->3 (3 colors are used, color image, rgb)
}

pixel **read_bin(int height, int width, FILE *f, int value)
{
	//read from binary file
	pixel **image;

	image = alloc(height, width, value);

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			for (int k = 0; k < value; k++) {
				unsigned char aux;
				fread(&aux, sizeof(unsigned char), 1, f);
				image[i][j].color[k] = aux;
			}
		}
	}

	return image;
}

pixel **read_text(int height, int widht, FILE *f, int value)
{
	//read from text file
	pixel **image;
	image = alloc(height, widht, value);
	for (int i = 0; i < height; i++)
		for (int j = 0; j < widht; j++)
			for (int k = 0; k < value; k++) {
				unsigned char aux;
				fscanf(f, "%hhu", &aux);
				image[i][j].color[k] = aux;
			}

	return image;
}

pixel **load(details *v)
{
	pixel **image = NULL;
	char name[100];
	char magicword[3];
	int poz;
	FILE *f;

	scanf("%s", name);

	f = fopen(name, "rt");

	if (!f) {
		printf("Failed to load %s\n", name);
		(*v).error = -1;
		return NULL;
	}

	fscanf(f, "%s", magicword);
	//we determine what kind of file it is

	type(magicword, v);

	if (strcmp(magicword, "P1") == 0 || strcmp(magicword, "P4") == 0) {
		fscanf(f, "%d%d", &(*v).width, &(*v).height);
	} else {
		fscanf(f, "%d%d", &(*v).width, &(*v).height);
		fscanf(f, "%d", &(*v).max);
	}

	poz = ftell(f);
	//we remember the position where the actual image starts

	if ((*v).type == 1) {
		printf("Loaded %s\n", name);
		image = read_text((*v).height, (*v).width, f, (*v).value);
		(*v).x1 = 0;
		(*v).x2 = (*v).width;
		(*v).y1 = 0;
		(*v).y2 = (*v).height;
		fclose(f);
	}

	if ((*v).type == 2) {
		fclose(f);
		f = fopen(name, "rb");
		fseek(f, poz + 1, SEEK_SET);
		printf("Loaded %s\n", name);
		image = read_bin((*v).height, (*v).width, f, (*v).value);
		(*v).x1 = 0;
		(*v).x2 = (*v).width;
		(*v).y1 = 0;
		(*v).y2 = (*v).height;
		fclose(f);
	}

	return image;
}