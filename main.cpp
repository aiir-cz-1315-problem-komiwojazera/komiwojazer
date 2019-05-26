//#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include "TSP_Data.h"
#include "BruteForce.h"
#include "pea_zp1.h"
using namespace std;


int main(int argc, char* argv[])
{
	int* mem = new int[1024];		// block of memory to free to handle out_of_memory exceptions
	
	if (argc > 1) {			// command line with arguments
		/* Settings */
		int dim;
		std::string filename_in = std::string(argv[1]);

		std::ifstream file;
		try {
			//open file to write
			file.open(filename_in, std::ios::app);
			if (!file.is_open()) {		// couldn't open file?
				throw pea_zp1::ERR_FILE_OPEN;
			}
			// generate data and solver
				TSP_Data data = TSP_Data(filename_in);
                dim = data.get_dim();
				BruteForce BF = BruteForce(&data);

				BF.BF_solve();

                BF.route_print(BF.get_best_route());
                
		}
		catch (const pea_zp1::zp1_err &err) {
			std::cerr << "pea_zp1::zp1_err error: " << err << std::endl;
		}
		catch (const std::bad_alloc &err) {
			delete[] mem;
			std::cerr << "Alloc error. Dim: " << dim << " " << err.what() << std::endl;
			file.close();
			mem = new (nothrow) int[1024];
		}
		catch (...) {
			delete[] mem;
			std::cerr << "Other error." << std::endl;
			file.close();
			return -1;
		}
	}

	delete[] mem;
	return 0;
}
