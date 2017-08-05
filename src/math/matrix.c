#include <stdlib.h>
#include <string.h>

#include <swh/math/matrix.h>


matrix_t * matrix_create(size_t d0, size_t d1) {

	matrix_t * ret = malloc(sizeof(matrix_t));

	ret->d0 = d0;
	ret->d1 = d1;
	ret->element_size = sizeof(double);
	ret->data = (double *) calloc(d0 * d1, ret->element_size);

	return ret;

}

void matrix_destroy(matrix_t * matrix) {

	free(matrix->data);
	free(matrix);

}

double * matrix_at(matrix_t * matrix, size_t i0, size_t i1) {

	return matrix->data + (i0 + matrix->d0 * i1);

}

