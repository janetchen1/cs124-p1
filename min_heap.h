#include <vector>

typedef std::tuple<float, int, int> Leaf;

class MinHeap
{
private:
	std::vector<Leaf> _heap;
	void Heapify();
	void HeapUp(int index);
	void HeapDown(int index);
public:
	BuildHeap(Leaf* nodes, int length);

	Leaf Peek();
	Leaf ExtractMin();
	void Insert(Leaf newVal);
};

