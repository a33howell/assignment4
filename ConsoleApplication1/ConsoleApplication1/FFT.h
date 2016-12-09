#ifndef FFT_H
#define FFT_H

#include "stdafx.h"
#include <vector>

void four1(std::vector<double> & data, int nn, int isign);
void vectorMultiplication(std::vector<double> & x, std::vector<double> & h, std::vector<double> & y);
void convolve(std::vector<double> & x, std::vector<double> & h, std::vector<double> & y, int N);

#endif