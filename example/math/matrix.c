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

#include <stdio.h>
#include <swh/math/matrix.h>
#include <swh/util/csv.h>
#include <swh/util/matrix.h>

void example_read_write_matrix() {

	matrix_t * mat = matrix_create(3, 2);

	for (size_t i = 0; i < 6; i++) {

		MA(mat, i % 3, i / 3) = i;
		printf("writing to 0x%p\n", &MA(mat, i % 3, i / 3));

	}

	fprintf_matrix(stdout, mat, "example_read_write_matrix: out");

	matrix_destroy(mat);

}

void example_matrix_multiply() {

	matrix_t * left = matrix_create_from_csv("left.csv");
	matrix_t * right = matrix_create_from_csv("right.csv");

	fprintf_matrix(stdout, left, "example_matrix_multiply: left");
	fprintf_matrix(stdout, right, "example_matrix_multiply: right");

	matrix_t * out = matrix_create(left->d1, right->d0);
	matrix_multiply(left, right, out);
	fprintf_matrix(stdout, out, "example_matrix_multiply: out");

	matrix_destroy(out);
	matrix_destroy(left);
	matrix_destroy(right);

}

void example_matrix_inverse(const char * filename) {

	matrix_t * in = matrix_create_from_csv(filename);
	matrix_t * out = matrix_create(in->d0, in->d1);

	fprintf_matrix(stdout, in, "example_matrix_inverse: in");

	bool status = matrix_inverse(in, out);
	printf("status: %s\n", status == 0 ? "EXIT_SUCCESS" : "EXIT_FAILURE, i.e., has no inverse");

	if (status == EXIT_SUCCESS) {

		fprintf_matrix(stdout, out, "example_matrix_inverse: out");

	}

	matrix_destroy(out);
	matrix_destroy(in);

}

void example_matrix_resize() {

	matrix_t * left = matrix_create_from_csv("left.csv");

	fprintf_matrix(stdout, left, "example_matrix_resize: origin");

	matrix_resize(left, left->d0 - 1, left->d1 + 1);
	fprintf_matrix(stdout, left, "example_matrix_resize: resized");

	matrix_destroy(left);

}

void example_matrix_svd_2x2() {

	double sx, sy, phi, theta;
	matrix_svd_2x2(1.0, 2.0, 3.0, 4.0, &sx, &sy, &phi, &theta);
	printf("example_matrix_2x2_svd, svd of [ [1, 2], [3, 4] ] is:\n");
	printf("sx: %lf, sy: %lf\nphi: %lf, theta: %lf\n\n", sx, sy, phi, theta);

}

void example_matrix_svd() {

	matrix_t * in = matrix_create_from_csv("pinv.csv");

	matrix_t
		* U = matrix_create(in->d0, in->d1),
		* S = matrix_create(in->d0, in->d0),
		* V = matrix_create(in->d0, in->d0),
		* t0 = matrix_create(in->d0, in->d0),
		* t1 = matrix_create(in->d0, in->d0),
		* t2 = matrix_create(in->d0, in->d1);

	fprintf_matrix(stdout, in, "example_matrix_svd: in");

	matrix_svd(in, U, S, V);

	fprintf_matrix(stdout, U, "example_matrix_svd: U");
	fprintf_matrix(stdout, S, "example_matrix_svd: S");
	fprintf_matrix(stdout, V, "example_matrix_svd: V");

	matrix_transpose(V, t0);
	matrix_multiply(S, t0, t1);
	matrix_multiply(U, t1, t2);

	fprintf_matrix(stdout, t2, "example_matrix_svd: recovered matrix");

	matrix_destroy(t0);
	matrix_destroy(t1);
	matrix_destroy(t2);
	matrix_destroy(U);
	matrix_destroy(S);
	matrix_destroy(V);
	matrix_destroy(in);

}

int main(int argc, char * argv[]) {

	example_read_write_matrix();
	example_matrix_multiply();
	example_matrix_inverse("inv1.csv");
	example_matrix_inverse("inv2.csv");
	example_matrix_resize();
	example_matrix_svd_2x2();
	example_matrix_svd();

	return 0;

}