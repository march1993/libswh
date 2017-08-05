#pragma once

#include <stdlib.h>

typedef struct matrix_tag matrix_t;
struct matrix_tag {
	size_t d0, d1;
	size_t element_size;
	double * data;
};
extern matrix_t * matrix_create(size_t d0, size_t d1);
extern void matrix_destroy(matrix_t * matrix);
extern double * matrix_at(matrix_t * matrix, size_t i0, size_t i1);

#define MA(matrix, i0, i1) (* matrix_at(matrix, i0, i1))



