#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <cstdio>
#include "Conversions.h"

using namespace std;

typedef struct header_file
{
	char chunk_id[4];
	int chunk_size;
	char format[4];
	char subchunk1_id[4];
	int subchunk1_size;
	short int audio_format;
	short int num_channels;
	int sample_rate;
	int byte_rate;
	short int block_align;
	short int bits_per_sample;
	char subchunk2_id[4];
	int subchunk2_size;						// subchunk2_size specifies the number of samples.
} header;

typedef struct header_file* header_p;

const int BUFSIZE = 512;					// BUFSIZE can be changed according to the frame size required (eg:512)





/*
* Code found online
* http://stackoverflow.com/questions/874134/find-if-string-ends-with-another-string-in-c
*/
bool hasEnding(std::string const &fullString, std::string const &ending) {
	if (fullString.length() >= ending.length()) {
		return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
	}
	else {
		return false;
	}
}





/*
* CODE LARGELY BORROWED FROM ONLINE D2L TUTORIAL SLIDES
* CPSC 501 Fall 2016 UCalgary
*/
int main(int argc, char* argv[]) {
	if (argc != 4) {
		cout << "There were not exactly 3 command line arguments" << endl;
		return 0;								// End program if there aren't exactly 3 command line arguments
	}

	if (!(hasEnding(argv[1], ".wav") && hasEnding(argv[2], ".wav") && hasEnding(argv[3], ".wav"))) {
		cout << "One of the arguments was not a .wav file" << endl;
		return 0;								// End program if input strings aren't .wav files
	}

	cout << "Starting clock" << endl;
	clock_t t;									// Time clock is started
	t = clock();

	cout << "Input file: " << argv[1] << endl;
	FILE * inFile = fopen(argv[1], "rb");		// Open wave file X in read mode
	cout << "IR File: " << argv[2] << endl;
	FILE * irFile = fopen(argv[2], "rb");		// Open wave file H in read mode
	cout << "Output File: " << argv[3] << endl;
	FILE * outfile = fopen(argv[3], "wb");		// Create output ( wave format) file in write mode

	short int buff16[BUFSIZE];								// short int used for 16 bit as input data format is 16 bit PCM audio
	header_p meta = (header_p)malloc(sizeof(header));		// header_p points to a header struct that contains the wave file metadata fields
	


	if (inFile && irFile && outfile) {
		fread(meta, 1, sizeof(header), inFile);				// Initial header information is written into outfile 
		fwrite(meta, 1, sizeof(*meta), outfile);

		std::vector<std::vector<short int>> resultX;		// Data from Input and IR files is read into short int vectors
		std::vector<size_t> nbValuesX;
		std::vector<std::vector<short int>> resultH;
		std::vector<size_t> nbValuesH;
		resultX = readWav(inFile);				// See "Conversions.cpp" for code
		resultH = readWav(irFile);				// See "Conversions.cpp" for code
		cout << "Reading complete" << endl;

		// Input and IR data is converted into double vectors
		std::vector<double> x = shortToDoubleVectorConversion(resultX);
		std::vector<double> h = shortToDoubleVectorConversion(resultH);
		std::vector<double> y;

		// Convolution occurs (See "Conversions.cpp" for code)
		int xLength = x.size();
		int hLength = h.size();
		convolve(x, xLength, h, hLength, y, xLength + hLength - 1);
		cout << "Convolution complete" << endl;

		for (int i = 0; i < y.size(); i++) {				// Data is converted back into short ints and written into outfile
			short int num = (short int) y[i];
			fwrite(&num, 1, 16, outfile);
		}
		cout << "Writing complete" << endl;

	} else {									// Error message for invalid input
		cout << "Invalid inputs.  Could not open the .wav files" << endl;
	}

	t = clock() - t;							// Clock is stopped and time is printed
	printf("Convolution completed in %d clicks (%f seconds).\n", t, ((float)t) / CLOCKS_PER_SEC);
	return 0;
}