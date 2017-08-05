#pragma once

#include <stdlib.h>

typedef struct matrix_tag matrix_t;
struct matrix_tag {
	size_t d0, d1;
	size_t element_size;
	void * data;
};

extern matrix_t * matrix_create(size_t d0, size_t d1, size_t element_size);
extern void matrix_destroy(matrix_t * matrix);


