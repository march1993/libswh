#pragma once

#include <stdlib.h>

#define matrix_types(FOO) \
	FOO(int, i) \
	FOO(float, f) \
	FOO(double, d)

#define matrix_build(TYPE, ABBR) \
	typedef struct matrix_##TYPE##_tag matrix_##TYPE##_t; \
	struct matrix_##TYPE##_tag { \
		size_t d0, d1; \
		size_t element_size; \
		TYPE * data; \
	}; \
	extern matrix_##TYPE##_t * matrix_##TYPE##_create(size_t d0, size_t d1); \
	extern void matrix_##TYPE##_destroy(matrix_##TYPE##_t * matrix); \
	extern TYPE * matrix_##TYPE##_at(matrix_##TYPE##_t * matrix, size_t i0, size_t i1); \
	extern TYPE * (* m##ABBR)(matrix_##TYPE##_t *, size_t, size_t);

matrix_types(matrix_build);

