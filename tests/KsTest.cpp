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

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <cassert>
#include <cmath>

extern "C" {
#include "ks.h"
};

bool close_enough(double predicted, double actual) {
	return fabs(predicted - actual) < 1E-7;
}

int main() {
	// Read file containing inputs and outputs for testing
	std::ifstream f("TestingData.txt", std::ifstream::in);
	std::string s;
	int n1, n2;
	std::vector<double> x1, x2;
	double statistic, actual_p;
	int line = 0;

	double a[100];
	double b[100];
	while (std::getline(f, s)) {
		line++;
		std::istringstream ss(s);
		// Format of each line: n1, n2, x1 elements, x2 elements, statistic, P value
		ss >> n1 >> n2;
		double x;
		for (int i = 0; i < n1; ++i) {
			ss >> x;
			a[i] = x;
		}
		for (int i = 0; i < n2; ++i) {
			ss >> x;
			b[i] = x;
		}
		ss >> statistic >> actual_p;

		// Do the KS test and compare with actual values
		double p = -1;
		double ks = ks_stat(a, b, n1, n2, &p);
		assert(close_enough(ks, statistic) && close_enough(p, actual_p));

		x1.clear();
		x2.clear();
	}
	f.close();
	return 0;
}

