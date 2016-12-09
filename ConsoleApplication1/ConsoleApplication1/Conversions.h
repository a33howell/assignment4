#ifndef CONVERSIONS_H
#define CONVERSIONS_H

#include "stdafx.h"
#include <vector>

std::vector<double> shortToDoubleVectorConversion(std::vector<short int> x);
void padding(std::vector<double> & x, int N);
std::vector<short int> readWav(FILE * wavFile);

#endif