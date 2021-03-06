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

#include <swh/util/csv.h>
#include <stdio.h>

matrix_t * matrix_create_from_csv(const char * filename) {

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
	size_t n_non_empty = 0;
	bool non_empty_line = false;
	for (long i = 0; i < fsize; i++) {
		switch(buf[i]) {
			case ',': cc += 1; break;
			case '\r': cr += 1; if (cols == 0) { cols = cc; } if (non_empty_line) { n_non_empty += 1; } non_empty_line = false; break;
			case '\n': cn += 1; if (cols == 0) { cols = cc; } if (non_empty_line) { n_non_empty += 1; } non_empty_line = false; break;
			case ' ': break;
			default: non_empty_line = true; break;
		}
	}
	// in case of no '\r' or '\n' in last line
	if (non_empty_line) { n_non_empty += 1; }


	size_t rows = cols > 0 ? (cc / cols) : n_non_empty;

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


void matrix_write_to_csv(const char * filename, matrix_t * matrix) {

	FILE * file = fopen(filename, "w");

	for (size_t i1 = 0 ; i1 < matrix->d1; i1++) {

		for (size_t i0 = 0; i0 < matrix->d0; i0++) {

			fprintf(file, "%le%s", * matrix_at(matrix, i0, i1), i0 == matrix->d0 - 1 ? "" : ",");

		}

		fprintf(file, "\r\n");

	}

	fclose(file);

}