#include <stdlib.h>
#include <string.h>

#include <swh/math/matrix.h>

matrix_t * matrix_create(size_t d0, size_t d1, size_t element_size) {

	matrix_t * ret = malloc(sizeof(matrix_t));
	ret->d0 = d0;
	ret->d1 = d1;
	ret->data = (void *) calloc(d0 * d1, element_size);

	return ret;

}

void matrix_destroy(matrix_t * matrix) {

	free(matrix->data);
	free(matrix);

}

