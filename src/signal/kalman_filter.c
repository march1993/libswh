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

#include <swh/signal/kalman_filter.h>

kalman_filter_t * kalman_filter_create(size_t nx, size_t ny) {

	kalman_filter_t * ret = (kalman_filter_t *) malloc(sizeof(kalman_filter_t));

	ret->model.nx = nx;
	ret->model.ny = ny;
	ret->model.Gn = matrix_create(nx, nx);
	ret->model.Hn = matrix_create(nx, ny);
	ret->model.CVn = matrix_create(nx, nx);
	ret->model.CWn = matrix_create(ny, ny);

	ret->current_status = 0;
	for (size_t i = 0; i < kalman_filter_n_state; i++) {

		ret->states[i].xs = matrix_create(1, nx);
		ret->states[i].ys = matrix_create(1, ny);
		ret->states[i].CXn = matrix_create(nx, nx);

	}

	ret->runtime.Kn = matrix_create(ny, nx);
	ret->runtime.GnT = matrix_create(nx, nx);
	ret->runtime.HnT = matrix_create(ny, nx);
	ret->runtime.t0 = matrix_create(nx, nx);
	ret->runtime.t1 = matrix_create(nx, nx);
	ret->runtime.t2 = matrix_create(nx, ny);
	ret->runtime.t3 = matrix_create(ny, ny);
	ret->runtime.t4 = matrix_create(ny, nx);
	ret->runtime.t5 = matrix_create(1, ny);
	ret->runtime.t6 = matrix_create(1, ny);
	ret->runtime.t7 = matrix_create(1, nx);
	ret->runtime.xn_n_1 = matrix_create(1, nx);
	ret->runtime.CXn_n_1 = matrix_create(nx, nx);
	ret->runtime.CYn_n_1 = matrix_create(ny, ny);

	ret->first_observation = true;

	return ret;

}


void kalman_filter_set_model(kalman_filter_t * filter, matrix_t * Gn, matrix_t * Hn, matrix_t * CVn, matrix_t * CWn) {

	if (Gn != NULL) {

		matrix_duplicate(Gn, filter->model.Gn);
		matrix_transpose(filter->model.Gn, filter->runtime.GnT);

	}

	if (Hn != NULL) {

		matrix_duplicate(Hn, filter->model.Hn);
		matrix_transpose(filter->model.Hn, filter->runtime.HnT);

	}

	if (CVn != NULL) {

		matrix_duplicate(CVn, filter->model.CVn);

	}

	if (CWn != NULL) {

		matrix_duplicate(CWn, filter->model.CWn);

	}

}

void kalman_filter_set_initial(kalman_filter_t * filter, matrix_t * xs, matrix_t* CXn) {

	kalman_filter_state_t * cur = filter->states + filter->current_status;

	matrix_duplicate(xs, cur->xs);
	matrix_duplicate(CXn, cur->CXn);

	filter->first_observation = true;

}

void kalman_filter_destroy(kalman_filter_t * filter) {

	matrix_destroy(filter->model.Gn);
	matrix_destroy(filter->model.Hn);
	matrix_destroy(filter->model.CVn);
	matrix_destroy(filter->model.CWn);

	for (size_t i = 0; i < kalman_filter_n_state; i++) {

		matrix_destroy(filter->states[i].xs);
		matrix_destroy(filter->states[i].ys);
		matrix_destroy(filter->states[i].CXn);

	}

	matrix_destroy(filter->runtime.Kn);
	matrix_destroy(filter->runtime.GnT);
	matrix_destroy(filter->runtime.HnT);
	matrix_destroy(filter->runtime.t0);
	matrix_destroy(filter->runtime.t1);
	matrix_destroy(filter->runtime.t2);
	matrix_destroy(filter->runtime.t3);
	matrix_destroy(filter->runtime.t4);
	matrix_destroy(filter->runtime.t5);
	matrix_destroy(filter->runtime.t6);
	matrix_destroy(filter->runtime.t7);
	matrix_destroy(filter->runtime.xn_n_1);
	matrix_destroy(filter->runtime.CXn_n_1);
	matrix_destroy(filter->runtime.CYn_n_1);

}

const double * kalman_filter_observe(kalman_filter_t * filter, const double y[filter->model.ny]) {

	size_t idx_next = (filter->current_status + 1) % kalman_filter_n_state;

	kalman_filter_state_t
		* cur = filter->states + filter->current_status,
		* next = filter->states + idx_next;



	matrix_t * ys = next->ys;

	for (size_t i = 0; i < filter->model.ny; i++) {

		MA(ys, 0, i) = y[i];

	}

	kalman_filter_model_t * model = &filter->model;
	kalman_filter_runtime_t * rt = &filter->runtime;

	if (filter->first_observation) {

		matrix_duplicate(cur->xs, rt->xn_n_1);
		matrix_duplicate(cur->CXn, rt->CXn_n_1);

		filter->first_observation = false;

	} else {

		matrix_multiply(model->Gn, cur->xs, rt->xn_n_1);
		matrix_multiply(model->Gn, cur->CXn, rt->t0);
		matrix_multiply(rt->t0, rt->GnT, rt->t1);
		matrix_add(rt->t1, model->CVn, rt->CXn_n_1);

	}


	matrix_multiply(model->Hn, rt->CXn_n_1, rt->t2);
	matrix_multiply(rt->t2, rt->HnT, rt->t3);
	matrix_add(rt->t3, model->CWn, rt->CYn_n_1);

	matrix_multiply(rt->CXn_n_1, rt->HnT, rt->t4);
	matrix_pinv(rt->CYn_n_1, rt->t3);
	matrix_multiply(rt->t4, rt->t3, rt->Kn);

	matrix_multiply(model->Hn, rt->xn_n_1, rt->t5);
	matrix_sub(next->ys, rt->t5, rt->t6);
	matrix_multiply(rt->Kn, rt->t6, rt->t7);
	matrix_add(rt->xn_n_1, rt->t7, next->xs);

	matrix_multiply(rt->Kn, model->Hn, rt->t0);
	matrix_multiply(rt->t0, rt->CXn_n_1, rt->t1);
	matrix_sub(rt->CXn_n_1, rt->t1, next->CXn);

	filter->current_status = idx_next;

	return next->xs->data;

}

