#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include "pea_zp1.h"

class TSP_Data
{
	int dim;									// number of cities
	float** dist_data;							// distances (pointer to 2D tab)
	
	bool data_import(std::fstream* file);		

public:
	TSP_Data(std::string filename);
//	TSP_Data(int num, float max = 200.0f);
	~TSP_Data();
	
	void print();
	float distance(int, int);
	int get_dim();
};

