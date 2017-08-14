# 1. matrix.h
`matrix.h` is a very basic definition of matrix structures and functions.

## depends
No depends.

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

* matrix_resize
   ```C
   void matrix_resize(matrix_t * matrix, size_t d0, size_t d1);
   ```
   Resize the matrix. Overlapped elements would be kept unchanged, otherwise, zeros would be filled.

* MATRIX_CREATE_STATIC
   ```C
   #define MATRIX_CREATE_STATIC(NAME, D0, D1)
   ```
   A macro used to declare a matrix structure statically, which is usually used in embedded platform due to the lack of `malloc` support. See `example/math/static.c`.

* matrix_clear
   ```C
   void matrix_clear(matrix_t * matrix);
   ```
   Set all the elements of a matrix into 0;

* matrix_at
   ```C
   double * matrix_at(const matrix_t * matrix, size_t i0, size_t i1);
   ```
   `matrix_at` return the pointer to the element of certain position.

* MA
   ```C
   #define MA(matrix, i0, i1) (* matrix_at(matrix, i0, i1))
   ```
   `MA` defines a convenient macro to visit the element inside a matrix.

* matrix_duplicate
   ```C
   void matrix_duplicate(const matrix_t * src, matrix_t * dest);
   ```
   Copy the entire matrix from `src` to `dest`. Sizes of two matrices should be same.

* matrix_inverse
   ```C
   int matrix_inverse(const matrix_t * in, matrix_t * out);
   ```
   Calculate the inverse of the matrix `in`. Two matrices should be same sized and square.

   `EXIT_SUCCESS` would be returned if the inverse exists, otherwise, `EXIT_FAILURE`.

   This naïve implementation is inspired of the idea using elementary row operations to let (A|I) become (I|B), then B = inv(A).

   Its algorithm complexity is round O(N^3), while there are much faster approaches using BLAS libraries, in case extreme performance is needed.

* matrix_multiply
   ```C
   void matrix_multiply(const matrix_t * left, const matrix_t * right, matrix_t * out);
   ```
   Multiply two matrices, i.e., out = left * right. Its algorithm complexity is O(N^3). `d0` of `left` should be same to `d1` of `right`, `d0` of `out` same to `d1` of `right` and `d1` of `out` same to `d1` of `left`.

* matrix_multiply_k
   ```C
   void matrix_multiply_k(const matrix_t * in, const double k, matrix_t * out);
   ```
   Multiply the matrix `in` by constant `k`. Sizes of two matrices should be same.

* matrix_transpose
   ```C
   void matrix_transpose(const matrix_t * in, matrix_t * out);
   ```
   Transpose matrix `in` into `out`. `d0` of `in` should be `d1` of `out`, vice versa.

* matrix_svd_2x2
   ```C
   void matrix_svd_2x2(const double m00, const double m01, const double m10, const double m11, double * sx, double * sy, double * phi, double * theta);
   ```
   Calculate the svd of matrix `M = [m00, m01; m10, m11]` into

   `M = [cosϕ, -sinϕ; sinϕ, cosϕ] * [sx, 0; 0, sy] * [cosθ, sinθ; -sinθ, cosθ]`

* matrix_svd
   ```C
   void matrix_svd(const matrix_t * in, matrix_t * U, matrix_t * S, matrix_t * V);
   ```
   Singular value decomposition, i.e., in = U * S * V'. `S` and `V` should be smae sized and square matrices. `d0` of `V` should be same to `d0` of `in`. `U` and `in` should be same sized.

* matrix_pinv
   ```C
   void matrix_pinv(const matrix_t * in, matrix_t * out, double tol);
   ```
   Calculate the MoorePenrose pseudoinverse of matrix `in`. `d0` of `in` should be `d1` of `out`, vice versa.