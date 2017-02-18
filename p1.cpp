#include <iostream>
#include <vector>
#include <time.h>

use namespace std;

float weight(vector<float> node1, vector<float> node2, int dimension);

int main()
{

}

float weight(vector<float> node1, vector<float> node2, int dimension){
	
	float differences = 0;
	for (i = 0; i < dimension; i++){
		differences += (node1[i] - node2[i])^2;
	}
	return sqrt(differences);
}