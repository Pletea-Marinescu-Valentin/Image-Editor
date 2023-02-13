#ifndef LOAD_H
#define LOAD_H

#include <stdio.h>
#include "pixel.h"
#include "utils.h"

void type(char *magicword, details *v);

pixel **read_bin(int height, int width, FILE *f, int value);

pixel **read_text(int height, int widht, FILE *f, int value);

pixel **load(details *v);

#endif