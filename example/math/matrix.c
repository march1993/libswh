#include <stdio.h>
#include <swh/math/matrix.h>

int main(int argc, char * argv[]) {

	matrix_t * mat = matrix_create(3, 2, int);

	for (size_t i = 0; i < 6; i++) {

		mi(mat, i % 3, i / 3) = i;
		printf("writing to 0x%p\n", &mi(mat, i % 3, i / 3));

	}

	printf("mat->data: [");
	for (size_t i = 0; i < 6; i++) {

		// Not Recommended: here using `mat-> data` is for demonstration
		printf("%d%s", * ((int *) mat->data + i), i == (6 - 1) ? "" : ", ");

	}
	printf("]\n");

	matrix_destroy(mat);

	return 0;

}