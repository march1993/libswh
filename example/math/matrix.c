#include <stdio.h>
#include <swh/math/matrix.h>

int main(int argc, char * argv[]) {

	matrix_int_t * mat = matrix_int_create(3, 2);

	for (size_t i = 0; i < 6; i++) {

		* mi(mat, i % 3, i / 3) = i;
		printf("writing to 0x%p\n", mi(mat, i % 3, i / 3));

	}

	printf("mat->data: [");
	for (size_t i = 0; i < 6; i++) {

		// Not Recommended: here using `mat->data[i]` is for demonstration
		printf("%d%s", mat->data[i], i == (6 - 1) ? "" : ", ");

	}
	printf("]\n");

	matrix_int_destroy(mat);

	return 0;

}