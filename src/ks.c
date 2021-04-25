/*
    Copyright 2021 Alan Tseng

    This file is part of libks.

    libks is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <float.h>
#include <math.h>
#include <stdlib.h>

extern double psmirnov2x(double stat, int m, int n);

#include "ks.h"

static inline double min(double a, double b) {
	return (a < b) ? a : b;
}

double ks_stat_sorted(const double* a, const double* b, int a_len, int b_len, double* p_val) {
	double* a_ptr = (double*) a;
	double* b_ptr = (double*) b;
	const double* a_end = a + a_len;
	const double* b_end = b + b_len;

	/* t is where the Kolmogorov-Smirnov test is evaluated. */
	double t = -DBL_MAX;
	/* Number of elements <= t */
	int nfa = 0, nfb = 0;

	double sup_d = 0; /* Will contain the Smirnov-Kolmogorov statistic */
	/*while (a_ptr < a_end || b_ptr < b_end) {*/
	while (1) {
		/* Advance the pointers so that t < *a_ptr and t < *b_ptr */
		while (a_ptr < a_end && *a_ptr <= t) {
			a_ptr++;
			nfa++;
		}
		while (b_ptr < b_end && *b_ptr <= t) {
			b_ptr++;
			nfb++;
		}
		/* Calculate difference between the empirical distribution functions */
		double da = ((double) nfa) / a_len;
		double db = ((double) nfb) / b_len;
		double d = fabs(da - db);
		if (d > sup_d) {
			sup_d = d;
		}
		/* Go to the next smallest number */
		double new_t = min(*a_ptr, *b_ptr);
		if (new_t == t) {
			break;
		} else {
			t = new_t;
		}
	}
	/* Calculate P value if necessary */
	if (p_val) {
		*p_val = 1-psmirnov2x(sup_d, a_len, b_len);
		/* The following is the algorithm on Wikipedia
		double expt = -2 * sup_d * sup_d * a_len * b_len / (a_len + b_len);
		*p_val = min(2 * exp(expt), 1);
		*/
	}
	/* Return the Kolmogorov-Smirnov statistic */
	return sup_d;
}

int comparer(const void* a, const void* b) {
	double a_num = *((double*) a);
	double b_num = *((double*) b);
	if (a_num < b_num) {
		return -1;
	} else if (a_num == b_num) {
		return 0;
	} else {
		return 1;
	}
}

/* Sorts arrays a and b in place 
 and returns the two-sample Kolmogorov-Smirnov statistic */
double ks_stat(double* a, double* b, int a_len, int b_len, double* p_value) {
	qsort(a, a_len, sizeof(double), comparer);
	qsort(b, b_len, sizeof(double), comparer);
	return ks_stat_sorted(a, b, a_len, b_len, p_value);
}

