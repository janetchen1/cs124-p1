#include <iostream>
#include <vector>
#include <time.h>

use namespace std;

float weight(vector<float> node1, vector<float> node2, int dimension);

int main()
{
	int dimention = 5;
	int n = 10;

	vector<float> nodes(dimension, 0)[n];
	srand((unsigned)time(NULL));
	for (int i = 0; i < n; i++){
		for (int j = 0; j < dimension; j++){
        	nodes[i][j] = rand() % 1;
        	printf("%f ", nodes[i][j]);
    	}
    	printf("\n");
	}


}

float weight(vector<float> node1, vector<float> node2, int dimension){
	
	float differences = 0;
	for (i = 0; i < dimension; i++){
		differences += (node1[i] - node2[i])^2;
	}
	return sqrt(differences);
}