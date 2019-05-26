#include "BruteForce.h"

/* CONSTRUCTOR AND DESTRUCTOR */
BruteForce::BruteForce(TSP_Data* dt) : cost(FLT_MAX), best_cost(FLT_MAX) {
	data = dt;
	dim = data->get_dim();
	route = new int[dim + 1];
	best_route = new int[dim + 1];
	for (int i = 0; i < dim; i++) {
		route[i] = i + 1;
	}
	route[dim] = 1;
	route_copy();
}

BruteForce::~BruteForce() {
	delete[] route;
	delete[] best_route;
}

/* METHODS */

/* Print route rt */
void BruteForce::route_print(int* rt) {
	for (int i = 0; i < dim; i++) {
		std::cout << rt[i] << '-';
	}
	std::cout << rt[dim] << std::endl;
}

/* Solve TSP problem */
void BruteForce::BF_solve() {
	do {
		cost = calculate_cost();	// calculate cost for given permutation
		if (cost < best_cost) {		// if better solution - it's new best cost and route
			best_cost = cost;
			route_copy();
		}
	} while (std::next_permutation(route + 1, route + dim)); // const position of city 1 
}

void BruteForce::BF_solve(int perm_start, int perm_end) {
	for (int i = 0; i < perm_start; i++) { 
        std::next_permutation(route + 1, route + dim);
    }
    do {
		cost = calculate_cost();	// calculate cost for given permutation
		if (cost < best_cost) {		// if better solution - it's new best cost and route
			best_cost = cost;
			route_copy();
		}
        perm_start++;
	} while (std::next_permutation(route + 1, route + dim) && perm_start <= perm_end); // const position of city 1 
}

/* Calculate cost for given permutation */
float BruteForce::calculate_cost() {
	float c = 0;
	for (int i = 1; i <= dim; i++) {
		c += data->distance(route[i - 1], route[i]);
	}
	return c;
}

/* Copy permutation route to best_route */
void BruteForce::route_copy() {
	for (int i = 0; i <= dim; i++) {
		best_route[i] = route[i];
	}
}

int* BruteForce::get_route() {
	return route;
}

int* BruteForce::get_best_route() {
	return best_route;
}

float BruteForce::get_cost() {
	return cost;
}

float BruteForce::get_best_cost() {
	return best_cost;
}
