#ifndef PIXEL_H
#define PIXEL_H

typedef struct {
	//color will retain the color of the pixel
	double *color;
} pixel;

typedef struct {
	int x1, x2, y1, y2, height, width, max, error, verify;
	int type, value;
	int blackandwhite;
	//"error" determines whether or not an image is loaded
} details;

#endif
