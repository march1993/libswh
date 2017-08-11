#pragma once

#include <swh/math/matrix.h>

extern matrix_t * matrix_create_from_csv(char * filename);

extern void matrix_write_to_csv(char * filename, matrix_t * matrix);

