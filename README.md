# libks

## Introduction

Two-sample two-sided Kolmogorov-Smirnov (KS) test implemented in C with no other dependencies.

Suitable for computationally intensive non-parametric model fitting.

## Install

For Unix-like systems:

- Clone this repository and run `make` in the directory.
The shared library file `libks.so` will be created in the directory.

- Run `make check` to do the tests (requires a C++ compiler).

- Run `make clean` to remove the compiled files.

## Use

There is only one function.

```c
double ks_stat(double* a, double* b, int a_len, int b_len, double* p_value);
```

a and b are the samples to be compared.

a_len and b_len are the sample sizes of a and b respectively.

The function sorts the arrays in place and computes the KS statistic and optionally the two-sided P value. If p_value pointer is not NULL, then the P value will be stored in the pointer.

Example program using the library:

```c
#include <stdio.h>

#include "ks.h"

int main() {
	double a[5] = {1, 2, 3, 4, 5};
	double b[3] = {1, 3, 5};

	double p;
	double k = ks_stat(a, b, 5, 3, &p);
	printf("%f %f\n", k, p);
	return 0;
}
```

Compile it with the library like this:

```
PATH_TO_LIBKS=/some/where
gcc main.c $PATH_TO_LIBKS/libks.so -I$PATH_TO_LIBKS/include
```

## Author, License

Copyright (C) 2021 Alan Tseng

GNU General Public License 3.0

P value code adapted from R Project

Copyright (C) 2021 The R Foundation for Statistical Computing


