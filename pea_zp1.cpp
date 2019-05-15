#include "pea_zp1.h"

/* Generate random value in [min, max] (uniform distribution) */
int pea_zp1::zp1_rand(int min, int max) {
	std::random_device rd;				// non-deterministic generator
	std::mt19937 gen(rd());				// random engine seeded with rd()
	std::uniform_int_distribution<> dist(min, max);
	return dist(gen);
}



