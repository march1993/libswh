#include <swh/util/csv.h>
#include <stdio.h>

matrix_double_t * matrix_create_from_csv(char * filename) {

	FILE * file = fopen(filename, "r");


	fclose(file);

}


void matrix_write_to_csv(char * filename, matrix_double_t * matrix) {

	FILE * file = fopen(filename, "w");

	for (size_t i1 = 0 ; i1 < matrix->d1; i1++) {

		for (size_t i0 = 0; i0 < matrix->d0; i0++) {

			fprintf(file, "%lf%s", * md(matrix, i0, i1), i0 == matrix->d0 - 1 ? "" : ",");

		}

		fprintf(file, "\r\n");

	}

	fclose(file);

}