#pragma once
#include <iostream>
#include "TSP_Data.h"
#include "HeldKarp.h"
#include "BruteForce.h"
#include "PEA_Timer.h"

enum menu_mode {
	MAIN_MENU = 'm',
	GENERATE = '1',
	DATA_FILE = '2',
	PRINT_DATA = '3',
	SOLVE_HK = '4',
	SOLVE_BRUTE = '5',
	SOLVE_LITTLE = '6',
	PRINT_SOLUTION = '7',
	QUIT = 'q'
};

class User_Menu
{
	 menu_mode mode;
	 TSP_Data* data_ptr;
	 HeldKarp* HK_ptr;
	 BruteForce* BF_ptr;
	 PEA_Timer tim;

	 void clean_data();
	 void clean_solution();

	 void menu();
	 void generate_data();
	 void data_from_file();
	 void solve_HK();
	 void solve_brute();
	 void solve_little();
	 void print_data();
	 void print_solution(HeldKarp*);
	 void print_solution(BruteForce*);
	 void print_solution();

public:
	User_Menu();
	User_Menu(TSP_Data*, HeldKarp*);
	~User_Menu();

	bool run();
	void reset();
};

