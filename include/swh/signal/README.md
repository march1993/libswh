# 1. kalman_filter.h
Basic Kalman Filter(KF) using pseudo-inverse.


## depends
`swh/math/matrix.h`

## model
```
Xn = Gn * X(n-1) + Vn
Yn = Hn * Xn + Wn

Vn ~ N(0, CVn)
Wn ~ N(0, CWn)
```
`Xn` is the process variable. `Yn` is observations. `Vn` is the process noise. `Wn` is the measurement noise.

## structure
Structure description for KF instance.

```C
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

```
`kalman_filter_state_t` is used to store the variables for certain state.

`kalman_filter_model_t` is used to store the model, which is kept unchanged after initialization.

`kalman_filter_runtime_t` is used for calculation, but also can be displayed as intermediate results.

Marco `kalman_filter_n_state` indicates how many states should be stored in the filter.

`kalman_filter_t` is the structure which the following functions accept.

## functions

* kalman_filter_create
   ```C
   kalman_filter_t * kalman_filter_create(size_t nx, size_t ny);
   ```
   Create a filter based on the length of process length `nx` and measurement length `ny`.

* kalman_filter_set_model
   ```C
   void kalman_filter_set_model(kalman_filter_t * filter, matrix_t * Gn, matrix_t * Hn, matrix_t * CVn, matrix_t * CWn);
   ```
   Set the model matrix for a kalman filter instance.

* kalman_filter_set_initial
   ```C
   void kalman_filter_set_initial(kalman_filter_t * filter, matrix_t * xs, matrix_t* CXn);
   ```
   Set the initial process variable and process noise covariance.

* kalman_filter_destroy
   ```C
   void kalman_filter_destroy(kalman_filter_t * filter);
   ```
   Free the memory allocated for a kalman_filter_t before.

* kalman_filter_observe
   ```C
   const double * kalman_filter_observe(kalman_filter_t * filter, const double y[filter->model.ny]);
   ```
   Predict the process variable as return value based on the observation `y[]`.

   > It should be mentioned that for the first observation, `xs` and `CXn` would be directly used as prediction.

   ```C
   if (filter->first_observation) {
      // xn_n_1 = xs
      // CXn_n_1 = CXn
      // filter->first_observation = false;
   } else {
     // xn_n_1 = Gn * xs
     // CXn_n_1 = Gn * CXn * Gn'
   }
   ```


