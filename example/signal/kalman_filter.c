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

#include <stdio.h>
#include <swh/signal/kalman_filter.h>
#include <swh/util/csv.h>
#include <swh/util/matrix.h>

int main(int argc, char * argv[]) {

	matrix_t
		* Gn = matrix_create_from_csv("Gn.csv"),
		* Hn = matrix_create_from_csv("Hn.csv"),
		* CVn = matrix_create_from_csv("CVn.csv"),
		* CWn = matrix_create_from_csv("CWn.csv"),
		* initial_xs = matrix_create_from_csv("initial_xs.csv"),
		* initial_CXn = matrix_create_from_csv("initial_CXn.csv");

	kalman_filter_t * filter = kalman_filter_create(Gn->d0, Hn->d1);
	kalman_filter_set_model(filter, Gn, Hn, CVn, CWn);
	kalman_filter_set_initial(filter, initial_xs, initial_CXn);

	matrix_destroy(Gn);
	matrix_destroy(Hn);
	matrix_destroy(CVn);
	matrix_destroy(CWn);
	matrix_destroy(initial_xs);
	matrix_destroy(initial_CXn);

	matrix_t
		* observe_ys = matrix_create_from_csv("observe_ys.csv"),
		* priori_predicted_xs = matrix_create_from_csv("priori_predicted_xs.csv");

	double * ys = (double *) calloc(filter->model.Hn->d1, sizeof(double));
	for (size_t i0 = 0; i0 < observe_ys->d0; i0++) {

		for (size_t i1 = 0; i1 < observe_ys->d1; i1++) {

			ys[i1] = MA(observe_ys, i0, i1);

		}

		const double * xs = kalman_filter_observe(filter, ys);

		// printf("======\nT = %zu\n======\n", i0);

		// fprintf_matrix(stdout, filter->runtime.Kn, "Kn");
		// fprintf_matrix(stdout, filter->runtime.CXn_n_1, "CXn_n_1");
		// fprintf_matrix(stdout, filter->states[filter->current_status].CXn, "CXn");
		// fprintf_matrix(stdout, filter->states[filter->current_status].ys, "ys");

		printf("T = %zu\n", i0);
		printf("Predicted: ");
		for (size_t i = 0; i < filter->model.Gn->d0; i++) {
			printf("%le ", xs[i]);
		}
		printf("\n   Priori: ");
		for (size_t i1 = 0; i1 < priori_predicted_xs->d1; i1++) {

			printf("%le ", MA(priori_predicted_xs, i0, i1));

		}

		printf("\n\n");

	}

	free(ys);
	matrix_destroy(observe_ys);
	matrix_destroy(priori_predicted_xs);

	kalman_filter_destroy(filter);

}