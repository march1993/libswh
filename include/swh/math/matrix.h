#pragma once

#include <stdlib.h>

typedef struct matrix_tag matrix_t;
struct matrix_tag {

	size_t d0, d1;
	size_t element_size;
	double * data;

};

extern matrix_t * matrix_create(size_t d0, size_t d1);
extern void matrix_clear(matrix_t * matrix);
extern void matrix_destroy(matrix_t * matrix);
extern double * matrix_at(const matrix_t * matrix, size_t i0, size_t i1);

#define MA(matrix, i0, i1) (* matrix_at(matrix, i0, i1))

extern void matrix_duplicate(const matrix_t * src, matrix_t * dest);
extern void matrix_inverse(const matrix_t * in, matrix_t * out);
extern void matrix_multiply(const matrix_t * left, const matrix_t * right, matrix_t * out);
extern void matrix_multiply_k(const matrix_t * in, const double k, matrix_t * out);
