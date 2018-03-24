#include <iostream>
#include "TreeNode.h"

#include <string>


TreeNode::TreeNode(unsigned char v, unsigned f)
{
	val = v;
	frequency = f;
	left = NULL;
	right = NULL;
}

unsigned TreeNode::getFrequency()
{
	return frequency;
}
unsigned TreeNode::getVal()
{
	return val;
}

TreeNode *TreeNode::getLeft() {
	return left;
}

TreeNode *TreeNode::getRight() {
	return right;
}

bool TreeNode::isLeafNode() {
	if (left == NULL && right == NULL) {
		return true;
	}
	return false;
}

void TreeNode::join(TreeNode * l, TreeNode * r) {

	left = l;
	right = r;
	frequency = l->getFrequency() + r->getFrequency();
	val = 'w';

}

/*TreeNode::~TreeNode() {
//	if (left != NULL) {
//		cout<<"l\n";
//		delete left;
//	}
//	if (right != NULL) {
//		cout<<"r\n";
//		delete right;
//	}
//	if (left != NULL) {
//		cout <<"l\n";
//		delete left;
//	}

//	cout <<left<<endl;
	delete left;
	cout<<"l\n";
	delete right;
	cout<<"r\n";

}*/





