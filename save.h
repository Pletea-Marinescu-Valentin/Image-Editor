#ifndef SAVE_H
#define SAVE_H

#include <stdio.h>
#include "pixel.h"
#include "utils.h"

void save_arg(char *name, int *ascii);

void write_mag(int ascii, details v, FILE *f);

void write_text(pixel **image, details v, FILE *f);

void write_bin(pixel **image, details v, FILE *f);

void save(pixel **image, details v);

#endif