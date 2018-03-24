#include <iostream>
#include "HuffTree.h"



HuffTree::HuffTree() {
	//r = new TreeNode(1, 1);
}

void HuffTree::buildTree(MinHeap * mh) {
	TreeNode * j;
        while (mh->getSize() > 1) {
                TreeNode * s1 = mh->removeMin();
                TreeNode * s2 = mh->removeMin();
                j = new TreeNode('0', 1);
		
                j->join(s1, s2);
		//cout << j->getFrequency() << " ";
                mh->insert(j);
		//cout << mh->getSize() << "\n";
        }
	//mh->removeMin();
        r = j;

}

void HuffTree::generateCodes(TreeNode * tn, string s) {
	
	if (tn->isLeafNode()) {
		sa[tn->getVal()] = s;
		return;
	}

	if(tn->getLeft() != NULL) {
		string w = s;
		w += "1";
		generateCodes(tn->getLeft(), w);
	}

	if (r->getRight() != NULL) {
		s += "0";
		generateCodes(tn->getRight(), s);
	}

	
}

TreeNode * HuffTree::getRoot() {
	return r;
}

string HuffTree::getCharCode(int c) {
	return sa[c];
}


void HuffTree::vi(TreeNode * tn) {

	if(tn != NULL) {
		vi(tn->getLeft());
		vi(tn->getRight());
		delete tn;
	}
}

HuffTree::~HuffTree() {
	vi(r);

}
