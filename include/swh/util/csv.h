#pragma once

#include <swh/math/matrix.h>

matrix_double_t * matrix_create_from_csv(char * filename);

void matrix_write_to_csv(char * filename, matrix_double_t * matrix);