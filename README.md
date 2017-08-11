# What's this lib?
This is a library maintained by myself which includes the general functions I've ever used to solve certain problems using C programming language.

# What's the design criteria?
* Easy to port

This means these functions should run on a modern amd64 machine, but also on embedded platforms with limited standard library support, e.g., `malloc`.

* Easy to modify

The structure of the codes should be clear and easy to understand. For example, the allocation of `matrix_t` depends on `malloc` function families, but it is easy to modify it into static declared variables by investigating `matrix_create` and `matrix_destroy` functions only, or by using provided macro `MATRIX_CREATE_STATIC`.

* Easy to accelerate

In some application scenes where the performance of program is critical, this library should give a clear guide on acceleration.

* Easy to decouple

It is okay to compile entire library, but it should be also possible to use only several header and source files of this library.