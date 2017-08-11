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

	printf("mat->data: [");
	for (size_t i = 0; i < 6; i++) {

		// Not Recommended: here using `mat->data[i]` is for demonstration
		printf("%lf%s", mat->data[i], i == (6 - 1) ? "" : ", ");

	}
	printf("]\n");

	matrix_destroy(mat);

}

void example_matrix_multiply() {

	matrix_t * left = matrix_create_from_csv("left.csv");
	matrix_t * right = matrix_create_from_csv("right.csv");

	fprintf_matrix(stdout, left, "left");
	fprintf_matrix(stdout, right, "right");

	matrix_t * out = matrix_create(left->d1, right->d0);
	matrix_multiply(left, right, out);
	fprintf_matrix(stdout, out, "out");

	matrix_destroy(out);
	matrix_destroy(left);
	matrix_destroy(right);

}

int main(int argc, char * argv[]) {

	example_read_write_matrix();
	example_matrix_multiply();

	return 0;

}