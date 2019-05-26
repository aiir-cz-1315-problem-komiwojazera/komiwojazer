#pragma once
#include <cstdlib>
#include <algorithm>
#include "TSP_Data.h"

class BruteForce {
	int* best_route;
	int* route;
	float cost;
	float best_cost;
	TSP_Data* data;
	int dim;

	
	void route_copy();
	float calculate_cost();

public:
	BruteForce(TSP_Data*);
	~BruteForce();

	void BF_solve();
	void route_print(int*);
	int* get_route();
	int* get_best_route();
	float get_cost();
	float get_best_cost();
};
