/*
    Copyright 2021 Alan Tseng

    This file contains code adapted from R
    Copyright (C) 2021 The R Foundation for Statistical Computing

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

#include <math.h>

/* Code from R project R-4.0.5/src/library/stats/src/ks.c */

/* Two-sided two-sample */
double psmirnov2x(double stat, int m, int n)
{
    //double md, nd, q, *u, w;
    double md, nd, q, w;
    int i, j;

    if(m > n) {
        i = n; n = m; m = i;
    }
    md = (double) m;
    nd = (double) n;
    /*
       q has 0.5/mn added to ensure that rounding error doesn't
       turn an equality into an inequality, eg abs(1/2-4/5)>3/10 

    */
    q = (0.5 + floor(stat * md * nd - 1e-7)) / (md * nd);
    /* u = (double *) R_alloc(n + 1, sizeof(double)); */
    double u[n+1];

    for(j = 0; j <= n; j++) {
        u[j] = ((j / nd) > q) ? 0 : 1;
    }
    for(i = 1; i <= m; i++) {
        w = (double)(i) / ((double)(i + n));
        if((i / md) > q)
            u[0] = 0;
        else
            u[0] = w * u[0];
        for(j = 1; j <= n; j++) {
            if(fabs(i / md - j / nd) > q) 
                u[j] = 0;
            else
                u[j] = w * u[j] + u[j - 1];
        }
    }
    return u[n];
}

