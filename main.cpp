#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include "TSP_Data.h"
#include "PEA_Timer.h"
#include "HeldKarp.h"
#include "BruteForce.h"
#include "User_Menu.h"
#include "pea_zp1.h"
using namespace std;


int main(int argc, char* argv[])
{
	int* mem = new int[1024];		// block of memory to free to handle out_of_memory exceptions
	
	if (argc > 1) {			// command line with arguments
		/* Settings */
		int dim = strtol(argv[1], NULL, 10);
		std::string filename_out = std::string(argv[2]);
		float max = (argc == 4) ? strtol(argv[3], NULL, 10) : 200.0f;
		PEA_Timer tim = PEA_Timer();
		std::ofstream file;
		try {
			//open file to write
			file.open(filename_out, std::ios::app);
			if (!file.is_open()) {		// couldn't open file?
				throw pea_zp1::ERR_FILE_OPEN;
			}
			// generate data and solver
				TSP_Data data = TSP_Data(dim, max);
				//HeldKarp HK = HeldKarp(&data);
				BruteForce BF = BruteForce(&data);
				// solve problem
				tim.start_timer();
				//HK.HK_solve();
				BF.BF_solve();
				tim.stop_timer();
				file << std::setprecision(15);
				file << dim << ';' << tim.time_elapsed('u') << std::endl;
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
	else {					// user interface & interaction
		User_Menu um;
		bool running = true;
		while (running) {
			try {
				running = um.run();
			}
			catch (const pea_zp1::zp1_err &err) {
				switch (err) {
				case pea_zp1::ERR_FILE_OPEN:
					std::cout << "Couldn't open file." << std::endl;
					break;
				case pea_zp1::ERR_DATA:
				case pea_zp1::ERR_DIM:
					std::cout << "Data problem." << std::endl;
					break;
				case pea_zp1::ERR_BIG:
					std::cout << "Too many cities." << std::endl;
					break;
				default:
					break;
				}
				um.reset();
			}
			catch (const std::bad_alloc &err) {		// out of memory exception
				delete[] mem;
				std::cout << "Allocation problem: " << err.what() << std::endl << std::endl;;
				um.reset();
				mem = new (nothrow) int[1024];
			}
			catch (...) {
				delete[] mem;
				std::cout << "Other error" << std::endl << std::endl;;
				um.reset();
				mem = new (nothrow) int[1024];
			}
		} // while
	} // else

	delete[] mem;
	return 0;
}