#include <swh/util/matrix.h>

void fprintf_matrix(FILE * stream, const matrix_t * matrix, const char * name) {

	fprintf(stream, "matrix: %s, %zu x %zu\n", name == NULL ? "unknown" : name, matrix->d1, matrix->d0);

	for (size_t i1 = 0; i1 < matrix->d1; i1++) {

		fprintf(stream, "%s", i1 == 0 ? "[ [ " : "  [ ");

		for (size_t i0 = 0; i0 < matrix->d0; i0++) {

			fprintf(stream, "%lf%s", MA(matrix, i0, i1), i0 == matrix->d0 - 1 ? "" : ", ");

		}

		fprintf(stream, "%s", i1 == matrix->d1 - 1 ? " ] ]\n\n" : " ]\n");
	}

}