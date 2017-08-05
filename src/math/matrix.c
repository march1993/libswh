#include <stdlib.h>
#include <string.h>

#include <swh/math/matrix.h>

#define matrix_define(TYPE, ABBR) \
matrix_##TYPE##_t * matrix_##TYPE##_create(size_t d0, size_t d1) { \
	matrix_##TYPE##_t * ret = malloc(sizeof(matrix_##TYPE##_t)); \
	ret->d0 = d0; \
	ret->d1 = d1; \
	ret->element_size = sizeof(TYPE); \
	ret->data = (TYPE *) calloc(d0 * d1, ret->element_size); \
	return ret; \
} \
void matrix_##TYPE##_destroy(matrix_##TYPE##_t * matrix) { \
	free(matrix->data); \
	free(matrix); \
} \
TYPE * matrix_##TYPE##_at(matrix_##TYPE##_t * matrix, size_t i0, size_t i1) { \
	return matrix->data + (i0 + matrix->d0 * i1); \
} \
TYPE * (* m##ABBR)(matrix_##TYPE##_t *, size_t, size_t) = matrix_##TYPE##_at;


matrix_types(matrix_define);