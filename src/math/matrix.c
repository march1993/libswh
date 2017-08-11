#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <swh/math/matrix.h>


matrix_t * matrix_create(size_t d0, size_t d1) {

	matrix_t * ret = malloc(sizeof(matrix_t));

	ret->d0 = d0;
	ret->d1 = d1;
	ret->element_size = sizeof(double);
	ret->data = (double *) calloc(d0 * d1, ret->element_size);

	return ret;

}

void matrix_clear(matrix_t * matrix) {

	memset(matrix->data, 0, matrix->d0 * matrix->d1 * matrix->element_size);

}

void matrix_destroy(matrix_t * matrix) {

	free(matrix->data);
	free(matrix);

}

double * matrix_at(const matrix_t * matrix, size_t i0, size_t i1) {

	assert(i0 < matrix->d0);
	assert(i1 < matrix->d1);

	return matrix->data + (i0 + matrix->d0 * i1);

}


void matrix_duplicate(const matrix_t * src, matrix_t * dest) {

	assert(src->d0 == dest->d0);
	assert(src->d1 == dest->d1);

	memcpy(dest->data, src->data, src->d0 * src->d1 * src->element_size);

}


void matrix_inverse(const matrix_t * in, matrix_t * out) {

	// TODO:

}

void matrix_multiply(const matrix_t * left, const matrix_t * right, matrix_t * out) {

	assert(left->d0 == right->d1);
	assert(out->d1 == left->d1);
	assert(out->d0 == right->d0);

	for (size_t i1 = 0; i1 < left->d1; i1++)
	for (size_t i0 = 0; i0 < right->d0; i0++) {

		double sum = 0;
		for (size_t j0 = 0; j0 < left->d0; j0++) {

			sum += MA(left, j0, i1) * MA(right, i0, j0);

		}

		MA(out, i0, i1) = sum;

	}

}

void matrix_multiply_k(const matrix_t * in, const double k, matrix_t * out) {

	assert(in->d0 == out->d0);
	assert(in->d1 == out->d1);

	for (size_t i1 = 0; i1 < in->d1; i1++)
	for (size_t i0 = 0; i0 < in->d0; i0++) {

		MA(out, i0, i1) = k * MA(in, i0, i1);

	}

}