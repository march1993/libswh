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

int main(int argc, char * argv[]) {

	example_read_write_matrix();
	example_matrix_multiply();
	example_matrix_inverse("inv1.csv");
	example_matrix_inverse("inv2.csv");
	example_matrix_resize();

	return 0;

}