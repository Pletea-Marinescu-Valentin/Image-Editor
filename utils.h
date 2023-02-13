#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include "pixel.h"

pixel **alloc(int height, int width, int values);

void free_mat(pixel **image, int height, int width);

#endif