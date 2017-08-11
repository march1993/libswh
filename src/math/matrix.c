/**
The functionality of this file is described in corresponding `README.md`.
Copyright (C) 2017  https://github.com/march1993

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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


