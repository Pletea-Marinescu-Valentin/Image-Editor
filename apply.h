#ifndef APPLY_H
#define APPLY_H

#include <stdio.h>
#include "pixel.h"
#include "utils.h"

void clamp(double *value);

double  newpixel(pixel **image, int n, int m, int p, char effect[15]);

pixel **apply(pixel **image, details v);

#endif