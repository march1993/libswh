#pragma once

#include <stdlib.h>

typedef struct matrix_tag matrix_t;
struct matrix_tag {
	size_t d0, d1;
	size_t element_size;
	unsigned char * data;
};

extern unsigned char * matrix_at(matrix_t * matrix, size_t i0, size_t i1);
extern matrix_t * matrix_create_0(size_t d0, size_t d1, size_t element_size);
#define matrix_create(d0, d1, type) matrix_create_0(d0, d1, sizeof(type))
extern void matrix_destroy(matrix_t * matrix);

#define mi(matrix, i0, i1) * (int *) matrix_at(matrix, i0, i1)
#define mf(matrix, i0, i1) * (float *) matrix_at(matrix, i0, i1)
#define md(matrix, i0, i1) * (double *) matrix_at(matrix, i0, i1)
