#include <swh/util/csv.h>

int main(int argc, char * argv[]) {


	matrix_t * mat = matrix_create_from_csv("data.csv");
	matrix_write_to_csv("out.csv", mat);

	return 0;

}