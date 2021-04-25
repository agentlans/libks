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

#ifndef _KOLMOGOROVSMIRNOV
#define _KOLMOGOROVSMIRNOV

double ks_stat(double* a, double* b, int a_len, int b_len, double* p_value);

#endif
