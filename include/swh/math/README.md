# swh/math

## structure
Structure description for matrix.

```C
typedef struct matrix_tag matrix_t;
struct matrix_tag {

	size_t d0, d1;
	size_t element_size;
	double * data;

};
```
`d0` stands for the number of elements of first dimension, i.e., number of elements in a row. `d1` for number of elements in a col correspondingly. `element_size` stands for the size of single element, i.e., `sizeof(double)`. `data` points to the memory area, whose size is determined by `d0 * d1 * mat->element_size`.

## functions
* matrix_create

```C
matrix_t * matrix_create(size_t d0, size_t d1);
```
Allocate the memory for a matrix_t structure. If static declaration is required, see `MATRIX_CREATE_STATIC`.

* matrix_destroy

```C
void matrix_destroy(matrix_t * matrix);
```
Free the memory allocated for a matrix_t before.

* MATRIX_CREATE_STATIC

A macro used to declare a matrix structure statically, which is usually used in embedded platform due to the lack of `malloc` support. See `example/math/static.c`.

* matrix_clear
* matrix_at
* MA
* matrix_duplicate
* matrix_inverse
* matrix_multiply
* matrix_multiply_k