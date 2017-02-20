#include <iostream>
#include <time.h>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int dimension;

float weight(float[], float[], int);

int main( int argc, char *argv[])
{
	if (argc != 5){
		printf("Incorrect number of parameters\n");
		return 0;
	}

	dimension = atoi(argv[4]);
	int n = atoi(argv[2]);
	srand((unsigned)time(NULL));

	// zero-dimension case: create NxN array with weights of all connections
	if (dimension == 0){
		float nodes[n][n];
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				if (i == j){
					nodes[i][j] = 0;
				}
				else{
					nodes[i][j] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				}
        		printf("%f ", nodes[i][j]);
        	}
        	printf("\n");
    	}
	}

	// other cases: create NxDim array, assign random vals, calculate weights after
	else{
		float nodes[n][dimension];
		for (int i = 0; i < n; i++){
			for (int j = 0; j < dimension; j++){
	        	nodes[i][j] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	    	}
		}

		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				float ex = weight(nodes[i], nodes[j], dimension);
				printf("%f ", ex);
		    }
		    printf("\n");
		}
	}
}

// calculates distance from one node to another in given dimension space
float weight(float node1[], float node2[], int dimension){
	
	float differences = 0;
	for (int i = 0; i < dimension; i++){
		differences += pow((node1[i] - node2[i]), 2);
	}
	return sqrt(differences);
}