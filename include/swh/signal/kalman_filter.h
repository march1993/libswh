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

#include <stdbool.h>
#include <swh/math/matrix.h>

typedef struct {

	matrix_t
		* xs,
		* ys,
		* CXn;

} kalman_filter_state_t;

typedef struct {

	size_t
		nx,
		ny;

	matrix_t
		* Gn,
		* Hn,
		* CVn,
		* CWn;

} kalman_filter_model_t;

typedef struct {

	matrix_t
		* Kn,
		* GnT,
		* HnT,
		* t0,
		* t1,
		* t2,
		* t3,
		* t4,
		* t5,
		* t6,
		* t7,
		* xn_n_1,
		* CXn_n_1,
		* CYn_n_1;

} kalman_filter_runtime_t;

#define kalman_filter_n_state 2

typedef struct {

	kalman_filter_model_t model;

	kalman_filter_state_t states[kalman_filter_n_state];

	size_t current_status;

	kalman_filter_runtime_t runtime;

	bool first_observation;

} kalman_filter_t;

extern kalman_filter_t * kalman_filter_create(size_t nx, size_t ny);
extern void kalman_filter_set_model(kalman_filter_t * filter, matrix_t * Gn, matrix_t * Hn, matrix_t * CVn, matrix_t * CWn);
extern void kalman_filter_set_initial(kalman_filter_t * filter, matrix_t * xs, matrix_t* CXn);
extern void kalman_filter_destroy(kalman_filter_t * filter);

extern const double * kalman_filter_observe(kalman_filter_t * filter, const double y[filter->model.ny]);
