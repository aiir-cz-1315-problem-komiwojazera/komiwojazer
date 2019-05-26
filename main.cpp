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

				BF.BF_solve(0, 30);
                BF.route_print(BF.get_best_route());
                std::cout << "cost " << BF.get_best_cost() << std::endl;
                
                BruteForce BF1 = BruteForce(&data);
                BF1.BF_solve(31, 60);
                BF1.route_print(BF1.get_best_route());
                std::cout << "cost " << BF1.get_best_cost() << std::endl;
                
                BruteForce BF2 = BruteForce(&data);
                BF2.BF_solve(61, 90);
                BF2.route_print(BF2.get_best_route());
                std::cout << "cost " << BF2.get_best_cost() << std::endl;
    
                BruteForce BF3 = BruteForce(&data);
                BF3.BF_solve(91, 120);
                BF3.route_print(BF3.get_best_route());
                std::cout << "cost " << BF3.get_best_cost() << std::endl;
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
