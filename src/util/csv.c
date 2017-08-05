#include <swh/util/csv.h>
#include <stdio.h>

matrix_t * matrix_create_from_csv(char * filename) {

	FILE * file = fopen(filename, "rb");

	if (file == NULL) {
		fprintf(stderr, "File %s not found.\n", filename);

		return matrix_create(0, 0);
	}

	fseek(file, 0, SEEK_END);
	long fsize = ftell(file);
	fseek(file, 0, SEEK_SET);

	char * buf = malloc(fsize + 1);
	fread(buf, fsize, 1, file);
	buf[fsize] = 0;
	fclose(file);

	size_t cc = 0, cr = 0, cn = 0;
	size_t cols = 0;
	for (long i = 0; i < fsize; i++) {
		switch(buf[i]) {
			case ',': cc += 1; break;
			case '\r': cr += 1; if (cols == 0) { cols = cc; } break;
			case '\n': cn += 1; if (cols == 0) { cols = cc; } break;
			default: break;
		}
	}

	size_t rows = cc / cols;

	if (rows * cols != cc) {

		fprintf(stderr, "File %s is not a valid CSV. (cols: %zu, rows: %zu, cc: %zu)\n", filename, cols, rows, cc);

		return matrix_create(0, 0);

	}

	cols += 1;

	matrix_t * ret = matrix_create(cols, rows);

	long cur = 0;
	for (size_t i1 = 0; i1 < rows; i1++)
	for (size_t i0 = 0; i0 < cols; i0++) {

		if (buf[cur] == '\r' || buf[cur] == '\n') {

			buf[cur] = ' ';
			cur += 1;

		}

		long end = cur;

		while (buf[end] != ',' && buf[end] != '\r' && buf[end] !='\n' && buf[end] != 0) {

			end += 1;

		}

		buf[end] = 0;
		MA(ret, i0, i1) = atof(buf + cur);
		buf[end] = ' ';
		cur = end;

	}


	return ret;

}


void matrix_write_to_csv(char * filename, matrix_t * matrix) {

	FILE * file = fopen(filename, "w");

	for (size_t i1 = 0 ; i1 < matrix->d1; i1++) {

		for (size_t i0 = 0; i0 < matrix->d0; i0++) {

			fprintf(file, "%le%s", * matrix_at(matrix, i0, i1), i0 == matrix->d0 - 1 ? "" : ",");

		}

		fprintf(file, "\r\n");

	}

	fclose(file);

}