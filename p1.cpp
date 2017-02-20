#include <iostream>
#include <time.h>
#include <cmath>
#include <numeric>
#include <stdio.h>
#include <stdlib.h>
#include "min_heap.h"

using namespace std;

int dimension;
float weight1();
float weight23(int, vector<float>, vector<float>);
//float weight(int, float*, float*);

int main( int argc, char *argv[])
{
	if (argc != 5){
		printf("Incorrect number of parameters\n");
		return 0;
	}

	dimension = atoi(argv[4]);
	int numpoints = atoi(argv[2]);
	int numtrials = atoi(argv[3]);

	// number greater than the max possible edge length given dimension; will function as infinity
	float max_edge = ceil(sqrt(dimension)) + 1;

	srand((unsigned)time(NULL));

	vector< vector<float> > nodes;

	// other cases: create NxDim array, assign random vals, calculate weights after
	if (dimension != 0) {
		vector<float> verticeRow;

		for (int i = 0; i < numpoints; i++){
			for (int j = 0; j < dimension; j++){
				float new_coord = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				cout << "cd: " << new_coord << "\n";
				verticeRow.push_back(new_coord);
			}
			nodes.push_back(verticeRow);
		}

		for (int i = 0; i < numpoints; i++){
			for (int j = 0; j < numpoints; j++){
				float ex = weight23(dimension, nodes[i], nodes[j]);
				printf("%f ", ex);
		    }
		    printf("\n");
		}
	}

	// create vector to store weight of each trial's MST
	vector<float> trial_weights(numtrials);

	// init MinHeap object
	MinHeap mh;

	// run Prim's numtrials times:
	for (int tr = 0; tr < numtrials; ++tr){		
		// convert weight/coordinate arrays into a Leaf array with exception of 0th vertice, which will be root
		Leaf node_leaves[numpoints - 1];
		for (int j = 0; j < numpoints - 1; ++j){
			node_leaves[j] = make_tuple(max_edge, j + 1);
		}

		mh.BuildHeap(node_leaves, numpoints - 1);

		// using first vertice (id: 0) as root, init prev & distance vectors
		vector<int> prev(numpoints, 0);
		prev[0] = -1;

		vector<float> dist(numpoints, -1);		
		dist[0] = 0;

		// decrease keys as necessary
		for (int i = 1; i < numpoints; ++i){
			if (dimension == 0) {
				float wght = weight1();
				cout << wght << " ";
				mh.DecreaseKey(i, wght);
			} else {
				mh.DecreaseKey(i, weight23(dimension, nodes[0], nodes[i]));
			}
		}
	
		while (!mh.IsEmpty()){
			Leaf u = mh.ExtractMin();
			float u_wgt = get<0>(u);
			int u_id = get<1>(u);
			
			dist[u_id] = u_wgt;

			// for each node remaining in heap, update weight and prev per Prim's
			vector<int> remaining = mh.IDsRemaining();
			for (int i = 0; i < remaining.size(); i++){
				int v = remaining[i];
				bool swapped;
				if (dimension == 0) {
					float wght = weight1();
					cout << wght << " ";
					swapped = mh.DecreaseKey(v, wght);
				} else {
					swapped = mh.DecreaseKey(v, weight23(dimension, nodes[u_id], nodes[v]));
				}
				if (swapped){
					prev[v] = u_id;
				}
			}
		}

		cout << "\ndist[]: ";
		for (int k = 0; k < dist.size(); ++k){
			cout << dist[k] << " ";
		}

		// all nodes added, find MST weight
		float sum = accumulate(dist.begin(), dist.end(), 0.0f);
		trial_weights[tr] = sum;
		cout << "\nTrial " << tr << " MST Weight: " << trial_weights[tr] << "\n";
	}
}

// calculates distance from one node to another in given dimension space [cases ii and iii] OR
// returns randomly generated weight [case i]
// float weight(int dimension, int inp1, int inp2){
// 	if (dimension == 1){
// 		return (static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
// 	} else {
// 		float differences = 0;
// 		for (int i = 0; i < dimension; ++i){
// 			differences += pow((nodes[inp1][i] - nodes[inp2][i]), 2);
// 		}
// 		return sqrt(differences);		
// 	}
// }

float weight1(){
	return (static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
}

float weight23(int dimension, vector<float> node1, vector<float> node2){
	float differences = 0;
	for (int i = 0; i < dimension; ++i){
		differences += pow((node1[i] - node2[i]), 2);
	}
	return sqrt(differences);	
}



/*float weight(int dimension, float node1[] = [], float node2[] = []){
	if (dimension == 1){
		return nstatic_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	} else {
		float differences = 0;
		for (int i = 0; i < dimension; i++){
			differences += pow((node1[i] - node2[i]), 2);
		}
		return sqrt(differences);		
	}
}*/
