#pragma once
#include "TSP_Data.h"

#define city_set unsigned long long int
#define HK_result_tab(i, j) HK_result_tab[(i) * num_sets + (j)]
#define position(i) (((city_set)1) << (i))

class HeldKarp
{
	struct HK_result {
		HK_result* res;		// pointer to last best solution (set count - 1)
		float cost;			// cost (to last best solution + to here)
	};

	TSP_Data* data;				// distances data
	city_set full_set;			// all cities (all bits 0 to dim-1 = '1')
	int dim;					// number of cites
	int num_sets;				// number of possible cities sets

	HK_result* HK_result_tab;	// 1D table of results (2D->1D)
	int* best_route;			// table containing the best route found
	float best_cost;			// cost of the best route

	float cost(city_set, int, int);
	void route_add(int, int);
	void route_clean();

public:
	HeldKarp(TSP_Data*);
	~HeldKarp();

	void HK_solve();
	void route_print();
	float get_best_cost();
};

