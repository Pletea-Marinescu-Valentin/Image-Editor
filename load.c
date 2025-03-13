#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "pixel.h"
#include "utils.h"

// Determines the type of the image file based on its magic number
void type(char *magicword, details *v)
{
    // Check if the file is a text-based PPM/PGM/PBM format
    if (strcmp(magicword, "P1") == 0 || strcmp(magicword, "P2") == 0 || strcmp(magicword, "P3") == 0)
        (*v).type = 1; // Text format

    // Check if the file is a binary-based PPM/PGM/PBM format
    if (strcmp(magicword, "P4") == 0 || strcmp(magicword, "P5") == 0 || strcmp(magicword, "P6") == 0)
        (*v).type = 2; // Binary format

    // Determine if the image is black & white, grayscale, or RGB
    if (strcmp(magicword, "P1") == 0 || strcmp(magicword, "P4") == 0) {
        (*v).value = 1;
        (*v).blackandwhite = 1; // Black & White image
    }

    if (strcmp(magicword, "P2") == 0 || strcmp(magicword, "P5") == 0) {
        (*v).value = 1;
        (*v).blackandwhite = 0; // Grayscale image
    }

    if (strcmp(magicword, "P3") == 0 || strcmp(magicword, "P6") == 0) {
        (*v).value = 3;
        (*v).blackandwhite = 0; // RGB color image
    }
}

// Reads a binary image file and stores pixel data into a 2D pixel matrix
pixel **read_bin(int height, int width, FILE *f, int value)
{
    pixel **image = alloc(height, width, value);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            for (int k = 0; k < value; k++) {
                unsigned char aux;
                fread(&aux, sizeof(unsigned char), 1, f); // Read binary pixel data
                image[i][j].color[k] = aux;
            }
        }
    }
    return image;
}

// Reads a text-based image file and stores pixel data into a 2D pixel matrix
pixel **read_text(int height, int width, FILE *f, int value)
{
    pixel **image = alloc(height, width, value);
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            for (int k = 0; k < value; k++) {
                unsigned char aux;
                fscanf(f, "%hhu", &aux); // Read pixel value from text file
                image[i][j].color[k] = aux;
            }
        }
    }
    return image;
}

// Loads an image from a file and determines its format
pixel **load(details *v)
{
    pixel **image = NULL;
    char name[100], magicword[3];
    int pos;
    FILE *f;

    // Read the filename from user input
    scanf("%s", name);
    f = fopen(name, "rt"); // Open file in text mode initially

    if (!f) {
        printf("Failed to load %s\n", name);
        (*v).error = -1;
        return NULL;
    }

    fscanf(f, "%s", magicword); // Read the magic number (file type identifier)
    type(magicword, v); // Determine file type and properties

    // Read image dimensions and max pixel value (if applicable)
    if (strcmp(magicword, "P1") == 0 || strcmp(magicword, "P4") == 0) {
        fscanf(f, "%d%d", &(*v).width, &(*v).height);
    } else {
        fscanf(f, "%d%d", &(*v).width, &(*v).height);
        fscanf(f, "%d", &(*v).max);
    }

    pos = ftell(f); // Remember the position where pixel data starts

    if ((*v).type == 1) { // Text-based file handling
        printf("Loaded %s\n", name);
        image = read_text((*v).height, (*v).width, f, (*v).value);
    }

    if ((*v).type == 2) { // Binary file handling
        fclose(f);
        f = fopen(name, "rb"); // Reopen in binary mode
        fseek(f, pos + 1, SEEK_SET); // Move to the correct position
        printf("Loaded %s\n", name);
        image = read_bin((*v).height, (*v).width, f, (*v).value);
    }

    fclose(f); // Close the file after reading

    // Set initial selection area to cover the entire image
    (*v).x1 = 0;
    (*v).x2 = (*v).width;
    (*v).y1 = 0;
    (*v).y2 = (*v).height;
    
    return image;
}
