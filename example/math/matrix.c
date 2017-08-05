#include <stdio.h>
#include <swh/math/matrix.h>

int main(int argc, char * argv[]) {

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

	return 0;

}