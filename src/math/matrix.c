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
#include <math.h>
#include <float.h>
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

void matrix_clear(matrix_t * matrix) {

	memset(matrix->data, 0, matrix->d0 * matrix->d1 * matrix->element_size);

}

void matrix_destroy(matrix_t * matrix) {

	free(matrix->data);
	free(matrix);

}

void matrix_resize(matrix_t * matrix, size_t d0, size_t d1) {

	double * buffer = (double *) calloc(d0 * d1, matrix->element_size);
	matrix_t dummy = { .d0 = d0, .d1 = d1, .data = buffer };

	for (size_t i1 = 0; i1 < d1 && i1 < matrix->d1; i1++)
	for (size_t i0 = 0; i0 < d0 && i0 < matrix->d0; i0++) {

		MA(&dummy, i0, i1) = MA(matrix, i0, i1);

	}

	free(matrix->data);
	matrix->data = buffer;
	matrix->d0 = d0;
	matrix->d1 = d1;

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

void matrix_exchange_rows(matrix_t * matrix, size_t r0, size_t r1) {

	double tmp[matrix->d0];

	size_t N = matrix->d0 * matrix->element_size;

	memcpy(tmp, &MA(matrix, 0, r0), N);
	memcpy(&MA(matrix, 0, r0), &MA(matrix, 0, r1), N);
	memcpy(&MA(matrix, 0, r1), tmp, N);

}

/**
 *	Use the idea of (A|I) ~ (I|B) (with elementary row operations), then B = inv(A)
 */
int matrix_inverse(const matrix_t * in, matrix_t * out) {

	size_t N = in->d0;

	assert(N == in->d1);
	assert(N == out->d0);
	assert(N == out->d1);

	matrix_t * tmp = matrix_create(N, N);
	matrix_duplicate(in, tmp);
	matrix_clear(out);

	for (size_t i0 = 0; i0 < N; i0++) {

		MA(out, i0, i0) = 1.0f;

	}

	bool has_inverse = true;
	for (size_t i = 0; i < N && has_inverse; i++) {

		has_inverse = false;

		// find the first non-zero element in i-th col starting from i-th row
		for (size_t j = i; j < N; j++) {

			if (fabs(MA(tmp, i, j)) >= DBL_EPSILON) {

				// found
				has_inverse = true;


				if (i != j) {

					// exchange two rows
					matrix_exchange_rows(tmp, i, j);
					matrix_exchange_rows(out, i, j);

				}

				// use i-th row to cancels the elements in the following rows
				for (j = i + 1; j < N; j++) {

					double r = MA(tmp, i, j) / MA(tmp, i, i);

					for (size_t k = 0; k < N; k++) {
						MA(tmp, k, j) -= r * MA(tmp, k, i);
						MA(out, k, j) -= r * MA(out, k, i);
					}

				}

				j = N;

			}

		}
	}

	// matrix tmp now becomes an upper triangular

	if (has_inverse) {

		for (size_t i = 0; i < N; i++) {

			size_t j = N - 1 - i;

			// normalize
			double e = MA(tmp, j, j);
			MA(tmp, j, j) = 1.0f;

			for (size_t l = 0; l < N; l++) {

				MA(out, l, j) /= e;

			}

			// use j-th row to cancels the elements in k-th row
			for (size_t k = 0; k < j; k++) {

				double r = MA(tmp, j, k) / MA(tmp, j, j);
				for (size_t l = 0; l < N; l++) {

					MA(tmp, l, k) -= r * MA(tmp, l, j);
					MA(out, l, k) -= r * MA(out, l, j);

				}

			}

		}

	}

	matrix_destroy(tmp);


	return has_inverse ? EXIT_SUCCESS : EXIT_FAILURE;
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


void matrix_transpose(const matrix_t * in, matrix_t * out) {

	assert(in->d0 == out->d1);
	assert(in->d1 == out->d0);

	for (size_t i1 = 0; i1 < in->d1; i1++)
	for (size_t i0 = 0; i0 < in->d0; i0++) {

		MA(out, i1, i0) = MA(in, i0, i1);

	}

}

void matrix_svd(const matrix_t * in, matrix_t * U, matrix_t * S, matrix_t * V) {

}

/**
 *  from Matlab
 *  [U,S,V] = svd(A,'econ');
 *  s = diag(S);
 *  if nargin < 2
 *      tol = max(size(A)) * eps(norm(s,inf));
 *  end
 *  r1 = sum(s > tol)+1;
 *  V(:,r1:end) = [];
 *  U(:,r1:end) = [];
 *  s(r1:end) = [];
 *  s = 1./s(:);
 *  X = bsxfun(@times,V,s.')*U';
 */
void matrix_pinv(const matrix_t * in, matrix_t * out) {

	assert(in->d0 == out->d1);
	assert(in->d1 == out->d0);

	matrix_t
		* U = matrix_create(in->d0, in->d1),
		* V = matrix_create(in->d0, in->d0),
		* S = matrix_create(in->d0, in->d0);

	matrix_svd(in, U, S, V);

	size_t r0 = 0;
	for (size_t i0 = 0; i0 < S->d0; i0++) {

		if (fabs(MA(S, i0, i0)) >= DBL_EPSILON) {

			r0 += 1;
			MA(S, i0, i0) = 1.0f / MA(S, i0, i0);

		} else {

			i0 = S->d0;

		}

	}

	matrix_resize(S, r0, r0);
	matrix_resize(U, r0, U->d1);
	matrix_resize(V, r0, V->d1);

	matrix_t
		* UT = matrix_create(U->d1, U->d0),
		* tmp = matrix_create(S->d0, S->d0);

	matrix_multiply(V, S, tmp);
	matrix_transpose(U, UT);
	matrix_multiply(tmp, UT, out);

	matrix_destroy(tmp);
	matrix_destroy(S);
	matrix_destroy(V);
	matrix_destroy(U);
	matrix_destroy(UT);

}