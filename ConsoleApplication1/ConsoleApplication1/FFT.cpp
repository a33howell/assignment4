#include "stdafx.h"
#include "FFT.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <cstdio>

#define PI         3.141592653589793
#define TWO_PI     (2.0 * PI)
#define SWAP(a,b)  tempr=(a);(a)=(b);(b)=tempr

using namespace std;

const int BUFSIZE = 512;


/*
* Code for DFT was largely used from online d2l example
* "test.c"
*/




//  The four1 FFT from Numerical Recipes in C,
//  p. 507 - 508.
//  Note:  changed float data types to double.
//  nn must be a power of 2, and use +1 for
//  isign for an FFT, and -1 for the Inverse FFT.
//  The data is complex, so the array size must be
//  nn*2. This code assumes the array starts
//  at index 1, not 0, so subtract 1 when
//  calling the routine (see main() below).

void four1(std::vector<double> & data, int nn, int isign)
{
	unsigned long n, mmax, m, j, istep, i;
	double wtemp, wr, wpr, wpi, wi, theta;
	double tempr, tempi;

	n = nn << 1;
	j = 1;

	for (i = 1; i < n; i += 2) {
		if (j > i) {
			SWAP(data[j - 1], data[i -1]);
			SWAP(data[j], data[i]);
		}
		m = nn;
		while (m >= 2 && j > m) {
			j -= m;
			m >>= 1;
		}
		j += m;
	}

	mmax = 2;
	while (n > mmax) {
		istep = mmax << 1;
		theta = isign * (6.28318530717959 / mmax);
		wtemp = sin(0.5 * theta);
		wpr = -2.0 * wtemp * wtemp;
		wpi = sin(theta);
		wr = 1.0;
		wi = 0.0;
		for (m = 1; m < mmax; m += 2) {
			for (i = m; i <= n; i += istep) {
				j = i + mmax;
				tempr = wr * data[j] - wi * data[j + 1];
				tempi = wr * data[j + 1] + wi * data[j];
				data[j] = data[i] - tempr;
				data[j + 1] = data[i + 1] - tempi;
				data[i] += tempr;
				data[i + 1] += tempi;
			}
			wr = (wtemp = wr) * wpr - wi * wpi + wr;
			wi = wi * wpr + wtemp * wpi + wi;
		}
		mmax = istep;
	}
}





// Takes the results from a DFT or FFT, and
// calculates and displays the amplitudes of
// the harmonics.

void vectorMultiplication(std::vector<double> & x, std::vector<double> & h, std::vector<double> & y)
{
	if (x.size() != h.size() || h.size() != y.size())
		return;

	int n = x.size();

	// Calculate amplitude
	for (int i = 0; i < n; i++) {
		y[i] = x[i] * h[i];
	}
}





void convolve(std::vector<double> & x, std::vector<double> & h, std::vector<double> & y, int N) {
	int doubleN = 2 * N;
	if (doubleN != x.size() || doubleN != h.size() || doubleN != y.size())
		return;

	four1(x, N, 1);
	four1(h, N, 1);

	vectorMultiplication(x, h, y);

	four1(y, N, -1);
}