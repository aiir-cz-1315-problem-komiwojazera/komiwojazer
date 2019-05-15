#include "HeldKarp.h"

/* CONSTRUCTOR AND DESTRUCTOR */

HeldKarp::HeldKarp(TSP_Data* dt) {
	data = dt;
	dim = data->get_dim();
	if (dim >= sizeof(full_set) * 8) {	// solution shall not represent all cities in full_set 
		throw pea_zp1::ERR_DIM;			// + possible addressing problems
	}

	full_set = 0;
	for (int i = 0; i < dim; i++) {		// add all cities to full_set
		full_set = full_set | position(i);
	}
	
	num_sets = full_set + 1;			// == 2^dim
	if (num_sets <= 0) {
		throw pea_zp1::ERR_BIG;
	}
	
	HK_result_tab = new HK_result[dim * num_sets];	// table to store results
	for (int i = 0; i < dim * num_sets; i++) {
		HK_result_tab[i] = HK_result();
		(HK_result_tab[i]).res = nullptr;
		(HK_result_tab[i]).cost = -1.0f;
	}

	best_route = new int[dim + 1];
	route_clean();
}

HeldKarp::~HeldKarp()
{
	delete[] best_route;
	delete[] HK_result_tab;
}

/* METHODS */

/* Find the solution at given stage (cities set and last city) */
float HeldKarp::cost(city_set set_S, int count_S, int last_p) {

	float c = (HK_result_tab(last_p - 1, set_S)).cost; // get cost from result table
	if (c != -1.0f) {
		return c;		// solution at this stage was calculated earlier and can be used
	}

	int x_min = 1;
	float cost_min = FLT_MAX;

	if (count_S == 1) {
		c = data->distance(1, last_p);
		x_min = last_p;
	}
	else {	// more than 1 city in set
		city_set set_S2 = set_S & (~position(last_p - 1));	// new set without last city
		int count_S2 = count_S - 1;
		for (int i = 1; i <= dim; i++) {					// find solution for new set, each city may be the last one
			if (!(set_S2 & position(i - 1))) {
				continue;
			}
			float c_i = cost(set_S2, count_S2, i);
			float d_i_p = data->distance(i, last_p);
			c = c_i + d_i_p;
			if (c < cost_min) {		// better solution found!
				cost_min = c;
				x_min = i;
				HK_result_tab(last_p - 1, set_S).res = &HK_result_tab(x_min - 1, set_S);
			}
		}
		c = cost_min;
	}
	// update result data in the table:
	(HK_result_tab(last_p - 1, set_S)).cost = c;
	(HK_result_tab(last_p - 1, set_S)).res = &HK_result_tab(x_min - 1, set_S & (~position(last_p - 1)));
	return c;
}

/* Solve TSP problem for full set of cities */
void HeldKarp::HK_solve() {
	best_cost = cost(full_set, dim, 1);
	HK_result* last = HK_result_tab + full_set;	// current position
	HK_result* first = HK_result_tab;
	for (int i = dim; i > 0; i--) {				// track down the route
		int p = (last - first) / num_sets;		// which "row"(=last_p) is current position in?
		route_add(p + 1, i);
		last = last->res;
	}
}

/* Update city number at given position */
void HeldKarp::route_add(int city, int position) {
	best_route[position] = city;
}

/* Reinitialize best route to 1-1-...-1 */
void HeldKarp::route_clean() {
	for (int i = 0; i <= dim; i++) {
		best_route[i] = 1;
	}
}

/* Print best route */
void HeldKarp::route_print() {
	for (int i = 0; i < dim; i++) {
		std::cout << best_route[i] << '-';
	}
	std::cout << best_route[dim] << std::endl;
}

/* Best cost getter */
float HeldKarp::get_best_cost() {
	return best_cost;
}