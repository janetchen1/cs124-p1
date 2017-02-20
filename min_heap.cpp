#include <cmath>
#include <iostream>
#include "min_heap.h"

using namespace std;

void MinHeap::BuildHeap(Leaf nodes[], int length){
	_indexmap.resize(length + 1);
	for (int i = 0; i < length; ++i){
		// copy nodes into heap
		_heap.push_back(nodes[i]);

		// add index to indexmap
		int nodeID = get<1>(nodes[i]);
		int size = _heap.size();
		_indexmap[nodeID] = size - 1;
	}
	Heapify();
}

void MinHeap::Heapify(){
	int length = _heap.size();
	for (int i = length - 1; i >= 0; --i){
		HeapDown(i);
	}
}

void MinHeap::HeapDown(int index){
	int length = _heap.size();
	int smallestChild = D * index + 1;
	int largestChild = D * index + D;

	// check if current node is a leaf
	if (largestChild > length){
		return;
	}

	// locate smallest of node and its D children
	int lowest = index;

	for (int i = smallestChild; i <= min(largestChild, length - 1); i++){
		if (get<0>(_heap[lowest]) > get<0>(_heap[i])){
			lowest = i;
		}
	}

	// swap if necessary
	if (lowest != index){
		// update indexmap accordingly
		int indexID = get<1>(_heap[index]);
		int lowestID = get<1>(_heap[lowest]);
		_indexmap[indexID] = lowest;
		_indexmap[lowestID] = index;

		swap(_heap[index], _heap[lowest]);
		
		// check if swaps needed further down tree
		HeapDown(lowest);
	}
}

void MinHeap::HeapUp(int index){
	int parent = (int) floor((index - 1) / D);

	if (get<0>(_heap[parent]) > get<0>(_heap[index])){
		// update indexmap
		int indexID = get<1>(_heap[index]);
		int parentID = get<1>(_heap[parent]);
		_indexmap[indexID] = parent;
		_indexmap[parentID] = index;

		swap(_heap[index], _heap[parent]);
		HeapUp(parent);
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
	_heap.erase(_heap.end()-1);
	int nodeID = get<1>(temp);
	_indexmap[nodeID] = -1;
	HeapDown(0);

	return temp;
}

bool MinHeap::DecreaseKey(int ID, float newWeight){
	int index_of_node = _indexmap[ID];
	float curr_weight = get<0>(_heap[index_of_node]);

	if (curr_weight > newWeight){
		_heap[index_of_node] = make_tuple(newWeight, ID);
		HeapUp(index_of_node);	
		return true;
	} else {
		return false;
	}
}

/*void MinHeap::Insert(Leaf newVal){
	_heap.push_back(newVal);
	HeapUp(_heap.size() - 1);
}*/

void MinHeap::PrintHeap(){
	for (int i = 0; i < _heap.size(); i++){
		cout << "(" << get<0>(_heap[i]) << ", " << get<1>(_heap[i]) << ")  ";
	}
	cout << "\nIndexMap: ";
	for (int j = 0; j < _indexmap.size(); ++j){
		cout << j << ": " << _indexmap[j] << ", ";
	}
	cout << "\n";
}

bool MinHeap::IsEmpty(){
	return _heap.empty();
}
