#ifndef CONVERSIONS_H
#define CONVERSIONS_H

#include "stdafx.h"
#include <vector>

std::vector<double> shortToDoubleVectorConversion(std::vector<std::vector<short int>> x);
void convolve(std::vector<double> & x, int N, std::vector<double> & h, int M, std::vector<double> & y, int P);
std::vector<std::vector<short int>> readWav(FILE * wavFile);

#endif