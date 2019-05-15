#pragma once
#include <windows.h>
#include <random>

namespace pea_zp1 {

	enum zp1_err {
		NO_ERR = 0,
		ERR_FILE_OPEN = 101,
		ERR_DATA = 102,
		ERR_DIM = 103,
		ERR_BIG = 104
	};


	int zp1_rand(int, int);

	
	


};