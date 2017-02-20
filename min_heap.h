#include <vector>
#include <tuple>
//#include <map>

// Leaf stores <weight, ID_node>
typedef std::tuple<float, int> Leaf;

#define D 2 // number of children per node

class MinHeap
{
private:
	std::vector<Leaf> _heap;
	// map to make DecreaseKey more efficient
	std::vector<int> _indexmap;
	void Heapify();
	void HeapUp(int index);
	void HeapDown(int index);
public:
	void BuildHeap(Leaf nodes[], int length);

	Leaf Peek();
	Leaf ExtractMin();
	//void Insert(Leaf newVal);
	bool DecreaseKey(int ID, float newWeight);
	void PrintHeap();
	bool IsEmpty();
};

