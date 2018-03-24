#include <iostream>
#include <stdio.h>
#include <fstream>
#include "Encoder.h"


ifstream f;
//FILE * f;
Encoder::Encoder (string filepath) {
	filen = filepath;
	f.open(filen.c_str(), ios::in);
	//f = fopen(filen, "r");
}

void Encoder::buildFrequencyTable() {
	unsigned c;
	f.read((char *)&c, 1);
	while (!f.eof()) {
		frequency_table[c]++;
		tx.push_back(c);
		f.read((char *)&c, 1);
	}
	f.close();
	
/*	int c = fgetc(f);
	if (c != EOF) {
		frequency_table[c] = frequency_table[c] + 1;
		unsigned char uc = c;
		tx.push_back(uc);
	}
	while ((c = fgetc(f)) != EOF) {
		if (1) {
			frequency_table[c] = frequency_table[c] + 1;
		}
		unsigned char uc = c;
		cout << "c" << "\n";
		tx.push_back(uc);
	}
	fclose(f);
	cout << "wo";

*/
}

void Encoder::encode() {
	MinHeap * q = new MinHeap();
	for (int i = 0; i < 256; i++) {
		if (frequency_table[i] > 0) {
			TreeNode *tn = new TreeNode(i, frequency_table[i]);
			q->insert(tn);
			//delete tn;
		}
	}
	
	ht = new HuffTree();
	ht->buildTree(q);
	string s = "";
	ht->generateCodes(ht->getRoot(), s);
	//delete q;

}

void Encoder::writeEncodedFile(string output_file_path) {
	ofstream mf;
	
	mf.open(output_file_path);
	int num = 0;
	
	for (int i = 0; i < 256; i++) {
		if (frequency_table[i] > 0) {
			num++;
		}
	}
	
	unsigned char b[2];
	b[0] = num & 0xFF;
	b[1] = (num >> 8) & 0xFF;
	mf << b[0];
	mf << b[1];


	//char and freq
	for (int i = 0; i < 256; i++) {
		if (frequency_table[i] > 0) {
			unsigned char bye = i & 0xFF;
			mf << bye;
			unsigned char by[4];
			unsigned int fre = frequency_table[i];
			by[0] = fre & 0xFF;
			by[1] = (fre >> 8) & 0xFF;
			by[2] = (fre >> 16) & 0xFF;
			by[3] = (fre >> 24) & 0xFF;
			mf << by[0];
			mf << by[1];
			mf << by[2];
			mf << by[3];
		}
	}
	
	
	unsigned char bit_buffer = 0;
	int z = 0;
	for (int i = 0; i < tx.size(); i++) {
		if (1) {
			unsigned char u = tx[i];
			string code = ht->getCharCode(u);
			
			for(char&y : code) {
				bit_buffer = bit_buffer << 1;
				bit_buffer = bit_buffer | (y - '0');
				z++;
				if (z == 8) {
					mf << bit_buffer;
					z = 0;
					bit_buffer = 0;
				}
			}
		}
		
	}
	while (z < 8) {
		bit_buffer = bit_buffer << 1;
		bit_buffer = bit_buffer | ('0' - '0');
		z++;
	}
	mf << bit_buffer;

	mf.close();
	//delete ht;
}


Encoder::~Encoder() {

}
