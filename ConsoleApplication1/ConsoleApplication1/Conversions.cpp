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





/* Code copied from "convolve.c" example on d2l */
void convolve(std::vector<double> & x, int N, std::vector<double> & h, int M, std::vector<double> & y, int P) {
	int n, m;

	/* Make sure the output buffer is the right size: P = N + M - 1 */
	if (P != (N + M - 1)) {
		printf("Invalid inputs for convolve\n");
		return;
	}

	/* Clear the output buffer y[] to all zero values */
	for (n = 0; n < P; n++)
		y.push_back(0.0);

	/* Do the convolution */
	/* Outer loop: process each input value x[n] in turn */
	for (n = 0; n < N; n++) {
		/* Inner loop: process x[n] with each sample of h */
		cout << "N = " << N << ", n = " << n << endl;
		for (m = 0; m < M; m++)
			y[n + m] += x[n] * h[m];
	}
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