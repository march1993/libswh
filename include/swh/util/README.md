# 1. csv.h
`csv.h` provides functions to read or write csv files. CSV file size should be *less than 2GiB*.

## depends
`swh/math/matrix.h`

## functions
* matrix_create_from_csv
   ```C
   matrix_t * matrix_create_from_csv(char * filename);
   ```

* matrix_write_to_csv
   ```C
   void matrix_write_to_csv(char * filename, matrix_t * matrix);
   ```

# 2. matrix.h
`matrix.h` provides `fprintf_matrix` to print a matrix in a decent way.

## depends
`swh/math/matrix.h`

## functions
* fprintf_matrix
   ```C
   void fprintf_matrix(FILE * stream, const matrix_t * matrix, const char * name);
   ```

