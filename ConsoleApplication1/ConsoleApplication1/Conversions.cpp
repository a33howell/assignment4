#include "stdafx.h"
#include "Conversions.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <cstdio>

using namespace std;

const int BUFSIZE = 512;

std::vector<double> shortToDoubleVectorConversion(std::vector<std::vector<short int>> x) {
	std::vector<double> result;

	for (int i = 0; i < x.size(); i++) {
		for (int j = 0; j < BUFSIZE; j++)
			result.push_back((double)x[i][j]);
	}
	return result;
}





void padding(std::vector<double> & x, int N) {
	for (int n = 0; n < N; n++)
		x.push_back(0.0);
}





std::vector<std::vector<short int>> readWav(FILE * wavFile) {
	std::vector<std::vector<short int>> result;
	short int buff16[BUFSIZE];							// short int used for 16 bit as input data format is 16 bit PCM audio
	int nb;												// variable storing number of byes returned

	while (!feof(wavFile)) {
		nb = fread(buff16, 1, BUFSIZE, wavFile);		// Reading data in chunks of BUFSIZE
		std::vector<short int> temp;

		for (int i = 0; i < BUFSIZE; i++)
		{
			temp.push_back(buff16[i]);
		}
		result.push_back(temp);
	}

	return result;
}