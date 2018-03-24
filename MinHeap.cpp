#include <iostream>
#include <climits>

#include "MinHeap.h"

#include <vector>

//implement the methods in MinHeap.h

MinHeap::MinHeap()
{
	n = 0;
}

void MinHeap::insert(TreeNode * val)
{

	ta.push_back(val);
	n++;
	int child = n-1;
	int parent = iparent(child);
	
	while (child > 0) {
		if (ta[child]->getFrequency() >= ta[parent]->getFrequency()) {
			break;
		}
		swap(ta[child], ta[parent]);
		child = parent;
		parent = iparent(child);
		
	}
}

int MinHeap::getSize()
{
	return n;	
}

TreeNode * MinHeap::removeMin()
{
	if (n < 1) {
		return NULL;
	}
	TreeNode * mink = ta[0];
	n--;
	if (n == 0) {
		return mink;
	}

	ta[0] = ta[n];
	ta.pop_back();

	int parent = 0;
	int left = ileft(parent);
	int right = iright(parent);
	
	while (left < n) {
		int mc = left;
		if ((right < n) && (ta[right]->getFrequency() < ta[left]->getFrequency())) {
			mc = right;
		}
		if (ta[parent]->getFrequency() <= ta[mc]->getFrequency()) {
			break;
		}
		swap(ta[mc], ta[parent]);
		parent = mc;
		left = ileft(parent);
		right = iright(parent);
	}
	return mink;
}

MinHeap::~MinHeap() {
	ta.clear();
}
