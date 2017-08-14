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

#pragma once

#include <stdlib.h>
#include <stdbool.h>

typedef struct matrix_tag matrix_t;
struct matrix_tag {

	size_t d0, d1;
	size_t element_size;
	double * data;

};

extern matrix_t * matrix_create(size_t d0, size_t d1);
extern void matrix_destroy(matrix_t * matrix);
extern void matrix_resize(matrix_t * matrix, size_t d0, size_t d1);

#define MATRIX_CREATE_STATIC(NAME, D0, D1) \
static double NAME##_data[D0 * D1]; \
static matrix_t NAME##_struct = { .d0 = D0, .d1 = D1, .element_size = sizeof(double), .data = NAME##_data }; \
static matrix_t * NAME = & NAME##_struct;

extern void matrix_clear(matrix_t * matrix);
extern double * matrix_at(const matrix_t * matrix, size_t i0, size_t i1);

#define MA(matrix, i0, i1) (* matrix_at(matrix, i0, i1))

extern void matrix_duplicate(const matrix_t * src, matrix_t * dest);
extern int matrix_inverse(const matrix_t * in, matrix_t * out);
extern void matrix_multiply(const matrix_t * left, const matrix_t * right, matrix_t * out);
extern void matrix_multiply_k(const matrix_t * in, const double k, matrix_t * out);
extern void matrix_transpose(const matrix_t * in, matrix_t * out);
extern double matrix_svd_eps;
extern void matrix_svd_2x2(const double m00, const double m01, const double m10, const double m11, double * sx, double * sy, double * phi, double * theta);
extern void matrix_svd(const matrix_t * in, matrix_t * U, matrix_t * S, matrix_t * V);
extern void matrix_pinv(const matrix_t * in, matrix_t * out);
