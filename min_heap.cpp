#include "stdafx.h"
#include "min_heap.h"

using namespace std;

MinHeap::BuildHeap(Leaf* nodes, int length) : _heap(length){
	for (int i = 0; i < length; ++i){
		_heap[i] = nodes[i];
	}
	Heapify();
}

void MinHeap::Heapify(){
	int length = _heap.size();
	for (int i = length - 1; i > 0; --i){
		HeapDown(i);
	}
}

void MinHeap::HeapDown(int index){
	int length = _heap.size();
	int lChild = 2 * index + 1;
	int rChild = 2 * index + 2;

	// check if current node is a leaf
	if (lChild >= length){
		return;
	}

	int lowest = index;

	// locate smallest of 3 nodes
	if (_heap[lowest][0] > _heap[lChild][0]){
		lowest = lChild;
	}
	if (_heap[lowest][0] > _heap[rChild][0]){
		lowest = rChild;
	}

	// swap if necessary
	if (lowest != index){
		swap(_heap[index], _heap[lowest]);
		// check if swaps needed further down tree
		HeapDown(lowest);
	}
}

void MinHeap::HeapUp(int index){
	int parent = ((int) ceil(index / 2)) - 1

	if (_heap[parent][0] > _heap[index][0]){
		swap(_heap[index], _heap[parent]);
		HeapUp(_heap[parent]);
	} else {
		// once finish one call without a swap, everything above is correct
		return;
	}
}

Leaf MinHeap::Peek(){
	return _heap[0];
}

Leaf MinHeap::ExtractMin(){
	int length = _heap.size();

	Leaf temp = Peek();
	_heap[0] = _heap[length - 1];
	_heap.erase(length - 1);
	HeapDown(0);

	return temp;
}

void MinHeap::Insert(Leaf newVal){
	_heap.push_back(newVal);
	HeapUp(_heap.size() - 1);
}
