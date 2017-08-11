#include <swh/math/matrix.h>
#include <swh/util/matrix.h>

MATRIX_CREATE_STATIC(mat1, 3, 2);

int main() {

	MA(mat1, 0, 0) = 1;
	MA(mat1, 0, 1) = 2;
	MA(mat1, 1, 0) = 3;
	MA(mat1, 1, 1) = 4;
	MA(mat1, 2, 0) = 5;
	MA(mat1, 2, 1) = 6;

	fprintf_matrix(stdout, mat1, "MATRIX_CREATE_STATIC");

};