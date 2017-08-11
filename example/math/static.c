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