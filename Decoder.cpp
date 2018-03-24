#include <iostream>
#include "Decoder.h"
#include <fstream>
#include <bitset>

using namespace std;

ifstream fs;
Decoder::Decoder(string huff_file_path) {
	filen = huff_file_path;
	for (i = 0; i < 256; i++) {
		frequency_table[i] = 0;
	}
	fs.open(filen.c_str(), ios::in);
}


void Decoder::buildFrequencyTableFromFile() {
	
	fs.read((char *)&uniq, 1);
	
	if (uniq == 0) {
		fs.read((char *)&uniq, 1);
		if (uniq == 1) {
			ct = 256;
		} else {
			ct = 255;
		}
	} else {
		unsigned ex;
		fs.read((char *)&ex, 1);
		ct = uniq;
	}
	
	for (i = 0; i < ct; i++) {
		fs.read((char *)&uniq, 1);
		fs.read((char *)&fre, 4);
		frequency_table[uniq] = fre;
	
	}

	while (!fs.eof()) {
		fs.read((char *)&uniq, 1);
		string bit = bitset<8>(uniq).to_string();
		
		bits.push_back(bit);
	}

	bits.pop_back();


	fs.close();

}


void Decoder::decode() {
	q = new MinHeap();
	for (int i = 0; i < 256; i++) {
		if (frequency_table[i] > 0) {
			TreeNode *tn = new TreeNode(i, frequency_table[i]);
			q->insert(tn);
			//delete tn;
		}
	}
	ht = new HuffTree();
	ht->buildTree(q);
//	delete q;
	string s = "";
	ht->generateCodes(ht->getRoot(), s);
	
}


void Decoder::writeUncompressedFile(string file_path) {
	ofstream of;
	of.open(file_path);
	
	TreeNode * t = ht->getRoot();
	
	for (int j = 0; j < bits.size(); j++) {
		string tak = bits[j];
//		cout<<tak<<endl;
		for (int k = 0; k < 8; k++) {
			if (tak[k] == '1') {
				t = t->getLeft();
			}
			if (tak[k] == '0') {
				t = t->getRight();
			}
			if (t->isLeafNode()) {
				unsigned char uc = t->getVal();
				of << uc;
				t = ht->getRoot();
				frequency_table[uc]--;
				if (frequency_table[uc] == 0) {
					ct--;
				}
				if (ct == 0) {
					break;
				}
			}
		}
	}
	of.close();
	
}


Decoder::~Decoder() {


	delete ht;
	delete q;

}





























