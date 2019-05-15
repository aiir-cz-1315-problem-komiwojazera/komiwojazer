#pragma once
#include <windows.h>

class PEA_Timer
{
	long long int start;
	long long int end;
	
	long long int read_QPC();
	

public:
	PEA_Timer();
	~PEA_Timer();

	void start_timer();
	void stop_timer();
	double time_elapsed(char);
};

