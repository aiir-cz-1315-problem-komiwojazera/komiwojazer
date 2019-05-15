#include "TSP_Data.h"

/* CONSTRUCTORS AND DESTRUCTORS */

/* New data from file */
TSP_Data::TSP_Data(std::string filename) : dim(0), dist_data(nullptr) {
	std::fstream file;
	file.open(filename, std::ios::in);
	if (!file.is_open()) {		// couldn't open file?
		throw pea_zp1::ERR_FILE_OPEN;
	}
	bool import_ok = data_import(&file);
	file.close();
	if (!import_ok) {
		throw pea_zp1::ERR_DATA;
	}
}

/* Generate random data */
TSP_Data::TSP_Data(int num, float max) : dim(num), dist_data(nullptr) {
	if (dim < 3) {
		throw pea_zp1::ERR_DIM;
	}
	// new tab
	dist_data = new float*[dim];
	for (int i = 0; i < dim; i++) {
		dist_data[i] = new float[dim];
		// generate data
		for (int j = 0; j < dim; j++) {
			dist_data[i][j] = (i == j) ? 0.0f : (float) pea_zp1::zp1_rand(100, (int)(max * 10)) / 10.0f;
		}
	} 
}

TSP_Data::~TSP_Data() {
	if (dim != 0) {
		for (int i = 0; i < dim; i++) {
			delete[] dist_data[i];
		}
		delete[] dist_data;
	}
}

/* METHODS */

/* Import distance data from file */
bool TSP_Data::data_import(std::fstream* fileptr) {
	bool result = false;
	std::string line;
		
	// open file success
	int line_num = 0;
	while (!fileptr->eof()) {
		getline(*fileptr, line);
		if (fileptr->fail()) {		// couldn't get line
			break;
		}
		if (line.empty()) {			// empty line - try reading next line
			continue;
		}
		std::istringstream line_stream(line);
		if (line_num == 0) {		// first (zero) line - number of cities
			line_stream >> dim;
			line_num++;
			// new tab
			dist_data = new float*[dim];
			for (int i = 0; i < dim; i++) {
				dist_data[i] = new float[dim];
			}
		}
		else {						// next lines - distances
			for (int i = 0; i < dim; i++) {
				line_stream >> dist_data[line_num-1][i];
				if (line_stream.fail()) {	// line stream problem
					return false;
				}
				if (line_num-1 == i) {		// force 0 distance on diagonal
					dist_data[line_num-1][i] = 0;
				}
			}
			line_num++;					// reading OK - increase line number
		}
	}
	if (dim < 3 || line_num <= dim) { // less than 3 cities or not enough data
		return false;
	}
	return true;
}

/* Print distances */
void TSP_Data::print() {
	int start = 1;
	int cols_max = 8;
	int cols = cols_max;
	int cols_left = dim;
	// Divide data into blocks (max 8 columns, all rows) 
	while (cols_left > 0) {
		if (cols_left < cols_max) {
			cols = cols_left;
		}
		std::cout << "\nDistance from cities " << 1 << '-' << dim;
		std::cout << " to cities " << start << '-' << start - 1 + cols << std::endl;
		for (int i = 0; i < dim; i++) {
			// Columns header
			if (i == 0) {
				std::cout << std::setw(5) << ' ';
				for (int j = start - 1; j < start - 1 + cols; j++) {
					std::cout << std::setw(8) << std::right << j+1 << ")";
				}
				std::cout << std::endl;
			}
			// Row header
			std::cout << std::setw(5) << std::right << i+1 << ")";
			for (int j = start - 1; j < start - 1 + cols; j++) {
				// Set format and spacing
				std::cout << std::fixed << std::setprecision(1);
				std::cout << std::setw(8) << std::right;
				// Data
				std::cout << dist_data[i][j] << ' ';
			}
			std::cout << std::endl;
		}
		cols_left -= cols;
		start += cols;
	}
}

/* Distance from city i to city j */
float TSP_Data::distance(int i, int j) {
	if (i <= 0) {
		i = 0;
	}
	else if (i >= dim) {
		i = dim - 1;
	}
	else {
		i -= 1;
	}

	if (j <= 0) {
		j = 0;
	}
	else if (j >= dim) {
		j = dim - 1;
	}
	else {
		j -= 1;
	}
	return dist_data[i][j];
}

/* Get number of cities */
int TSP_Data::get_dim() {
	return dim;
}
