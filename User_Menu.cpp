#include "User_Menu.h"



User_Menu::User_Menu() : mode(MAIN_MENU), data_ptr(nullptr), HK_ptr(nullptr), 
						 BF_ptr(nullptr)
{
}

User_Menu::User_Menu(TSP_Data* dt, HeldKarp* hk) : mode(MAIN_MENU), tim(PEA_Timer())
{
	data_ptr = dt;
	HK_ptr = hk;
}

User_Menu::~User_Menu()
{
	clean_data();
	clean_solution();
}

void User_Menu::clean_data() {
	if (data_ptr != nullptr) {
		delete data_ptr;
	}
}

void User_Menu::clean_solution() {
	if (HK_ptr != nullptr) {
		delete HK_ptr;
		HK_ptr = nullptr;
	}
	if (BF_ptr != nullptr) {
		delete BF_ptr;
		BF_ptr = nullptr;
	}
}

void User_Menu::menu() {
	char choice;
	std::cout << "Choose program mode:\n" << (char)GENERATE << " - generate random data,\n"
		<< (char)DATA_FILE << " - import data from file,\n" << (char)PRINT_DATA << " - print data,\n"
		<< (char)SOLVE_HK << " - solve using Held-Karp algorithm,\n"
		<< (char)SOLVE_BRUTE << " - solve using brute force method,\n"
		<< (char)SOLVE_LITTLE << " - solve using branch and bound method - Little algorithm,\n"
		<< (char)PRINT_SOLUTION << " - print solution,\n" << (char)QUIT << " - quit." << std::endl;
	std::cin >> choice;
	mode = (menu_mode)choice;
}

void User_Menu::generate_data() {
	int i = 0;
	std::cout << "Number of cities (more than 2):" << std::endl;
	std::cin >> i;
	if (i < 3) {
		std::cout << "Wrong number of cities." << std::endl;
	}
	else {
		data_ptr = new TSP_Data(i);	// generate random data
	}
	mode = MAIN_MENU;
}

void User_Menu::data_from_file() {
	std::string filename;
	std::cout << "Name of data file:" << std::endl;
	std::cin.ignore(INT_MAX, '\n');
	getline(std::cin, filename);
	data_ptr = new TSP_Data(filename);
	mode = MAIN_MENU;
}

void User_Menu::print_data() {
	if (data_ptr != nullptr) {
		data_ptr->print();
	}
	else {
		std::cout << "No data to print." << std::endl;
	}
	mode = MAIN_MENU;
}

void User_Menu::solve_HK() {
	if (data_ptr != nullptr) {
		clean_solution();
		HK_ptr = new HeldKarp(data_ptr);
		tim.start_timer();
		HK_ptr->HK_solve();
		tim.stop_timer();
		print_solution(HK_ptr);
	}
	else {
		std::cout << "No data to solve problem." << std::endl;
	}
	mode = MAIN_MENU;
}

void User_Menu::solve_brute() {
	if (data_ptr != nullptr) {
		clean_solution();
		BF_ptr = new BruteForce(data_ptr);
		tim.start_timer();
		BF_ptr->BF_solve();
		tim.stop_timer();
		print_solution(BF_ptr);
	}
	else {
		std::cout << "No data to solve problem." << std::endl;
	}
	mode = MAIN_MENU;
}

void User_Menu::solve_little() {
	std::cout << "Not implemented." << std::endl;
	mode = MAIN_MENU;
}

void User_Menu::print_solution(HeldKarp* HK_ptr) {
	if (HK_ptr != nullptr) {
		std::cout << "Best route:" << std::endl;
		HK_ptr->route_print();
		std::cout << "Cost:" << HK_ptr->get_best_cost() << std::endl;
		std::cout << "Time: ";
		float time = tim.time_elapsed('u');
		if (time < 1e4) {
			std::cout << time << " us" << std::endl;
		}
		else if (time >= 1e4 && time < 1e7) {
			std::cout << time / 1e3 << " ms" << std::endl;
		}
		else {
			std::cout << time / 1e6 << " s" << std::endl;
		}
	}
	else {
		std::cout << "No solution to print." << std::endl;
	}
	mode = MAIN_MENU;
}

void User_Menu::print_solution(BruteForce* BF_ptr) {
	if (BF_ptr != nullptr) {
		std::cout << "Best route:" << std::endl;
		BF_ptr->route_print(BF_ptr->get_best_route());
		std::cout << "Cost:" << BF_ptr->get_best_cost() << std::endl;
		std::cout << "Time: ";
		float time = tim.time_elapsed('u');
		if (time < 1e4) {
			std::cout << time << " us" << std::endl;
		}
		else if (time >= 1e4 && time < 1e7) {
			std::cout << time / 1e3 << " ms" << std::endl;
		}
		else {
			std::cout << time / 1e6 << " s" << std::endl;
		}
	}
	else {
		std::cout << "No solution to print." << std::endl;
	}
	mode = MAIN_MENU;
}


void User_Menu::print_solution() {
	if (HK_ptr != nullptr) {
		print_solution(HK_ptr);
	}
	else if (BF_ptr != nullptr) {
		print_solution(BF_ptr);
	}
	else {
		std::cout << "No solution to print." << std::endl;
	}

}

bool User_Menu::run() {
	switch (mode) {
		case MAIN_MENU:
			menu();
			break;
		case GENERATE:
			generate_data();
			break;
		case DATA_FILE:
			data_from_file();
			break;
		case PRINT_DATA:
			print_data();
			break;
		case SOLVE_HK:
			solve_HK();
			break;
		case SOLVE_BRUTE:
			solve_brute();
			break;
		case SOLVE_LITTLE:
			solve_little();
			break;
		case PRINT_SOLUTION:
			print_solution();
			break;
		case QUIT:
			std::cout << "Quit the program." << std::endl;
			return false;
			break;
		default:
			std::cout << "Wrong option." << std::endl;
			mode = MAIN_MENU;
			break;
		}
		std::cout << std::endl;
	return true;
}

void User_Menu::reset() {
	mode = MAIN_MENU;
}