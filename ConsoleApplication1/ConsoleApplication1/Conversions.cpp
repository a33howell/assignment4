#include "stdafx.h"
#include "Conversions.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <cstdio>

using namespace std;

const int BUFSIZE = 512;

std::vector<double> shortToDoubleVectorConversion(std::vector<short int> x) {
	std::vector<double> result;

	for (int i = 0; i < x.size(); i++) {
		result.push_back((double)x[i]);
	}
	return result;
}





void padding(std::vector<double> & x, int N) {
	for (int n = 0; n < N; n++)
		x.push_back(0.0);
}





std::vector<short int> readWav(FILE * wavFile) {
	std::vector<short int> result;
	short int buff16[BUFSIZE];							// short int used for 16 bit as input data format is 16 bit PCM audio
	int nb;												// variable storing number of byes returned

	while (!feof(wavFile)) {
		nb = fread(buff16, 1, BUFSIZE, wavFile);		// Reading data in chunks of BUFSIZE

		for (int i = 0; i < BUFSIZE; i++)
		{
			result.push_back(buff16[i]);
		}
	}

	return result;
}