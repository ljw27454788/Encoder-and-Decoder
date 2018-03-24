#include <iostream>
#include <string>
#include "MinHeap.h"
#include "Encoder.h"
#include "Decoder.h"

using namespace std;

void printHelp(){
	cout << "Invalid arguments." << endl;
	cout << "Type \"huffman [mode] [arguments]\" where mode and its arguments are one of the following:" << endl;
	cout << "-e [src] [dest]: encode the source file and place the result into the specified destination" << endl;
	cout << "-d [src] [dest]: decode the source file and place the result into the specified destination" << endl;
	exit(1);
}


int main (int argc, char** argv){
//	printHelp();
	string ed = argv[1];
	string takei = argv[2];
	string takeo = argv[3];

	if (ed == "-e") {
		
		Encoder *e = new Encoder(takei);
		e->buildFrequencyTable();
		e->encode();
		e->writeEncodedFile(takeo);
		//delete e;
	}
	if (ed == "-d") {
		Decoder *d = new Decoder(takei);
		d->buildFrequencyTableFromFile();
		d->decode();
		d->writeUncompressedFile(takeo);

		delete d;
	}	
	return 0;
}
