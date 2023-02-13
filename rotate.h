#ifndef ROTATE_H
#define ROTATE_H

#include <stdio.h>
#include "pixel.h"
#include "utils.h"

void rotate_to_right(pixel **image, pixel **copy_image, details v);

void rotate_to_right_select(pixel **image, pixel **copy_image, details v);

pixel **rotate_all_image(pixel **image, details *v);

void save_new_matrix(pixel **image, pixel **temp, details v);

void samematrix(pixel **image, pixel **temp, details v);

pixel **rotate_a_select(pixel **image, details v);

#endif