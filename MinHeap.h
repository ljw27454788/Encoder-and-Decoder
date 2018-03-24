#ifndef MINHEAP_H
#define MINHEAP_H

#include "TreeNode.h"

#define ileft(p) (2*(p)+1)
#define iright(p) (2*(p)+2)
#define iparent(ch) (((ch)-1)/2)
#include <vector>

using namespace std;

class MinHeap
{
	private:
		vector<TreeNode *> ta;
		int n;
	public:
		MinHeap();
		TreeNode * removeMin(); //returns root of heap
		void insert(TreeNode * val); //adds element to heap
		int getSize(); //returns size of heap
		~MinHeap();
};

#endif
