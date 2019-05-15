#include "PEA_Timer.h"

/* CONSTRUCTOR AND DESTRUCTOR */

PEA_Timer::PEA_Timer() : start(0), end(0)
{
}

PEA_Timer::~PEA_Timer()
{
}


/* METHODS */

/* Read QueryPerformanceCounter value */
/* by A.S.*/
long long int PEA_Timer::read_QPC()
{
	LARGE_INTEGER count;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&count);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return((long long int)count.QuadPart);
}

/* Calculate time elapsed (seconds, miliseconds, microseconds) */
double PEA_Timer::time_elapsed(char unit) {
	long long int freq;
	float mt;
	 
	QueryPerformanceFrequency((LARGE_INTEGER *)&freq);
	switch (unit) {
	case 'm':			// miliseconds
		mt = 1e3f;
		break;
	case 'u':			// microseconds
		mt = 1e6f;
		break;
	case 's':			// seconds
	default:
		mt = 1.0f;
		break;
	}
	return (mt * (float)(end - start)) / (float)freq;
}

/* Note start time */
void PEA_Timer::start_timer() {
	start = read_QPC();
}

/* Note stop time */
void PEA_Timer::stop_timer() {
	end = read_QPC();
}