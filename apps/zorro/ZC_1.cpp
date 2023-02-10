// ZorroTest.cpp : Defines the entry point for the console application.
//

#include "Source/ZorroControl/stdafx.h"
#include "Source/ZorroControl/ZorroControl.h"

int _tmain(int argc, _TCHAR* argv[])
{
// open ZorroControl.dll and get its function pointers
	
	HINSTANCE H = LoadLibrary("ZorroControl.dll");
	if(!H) {
		printf("Can't mount ZorroControl.dll!"); return EXIT_FAILURE;
	}
	_zInit zInit = (_zInit)GetProcAddress(H,"zInit");
	_zOpen zOpen = (_zOpen)GetProcAddress(H,"zOpen");
	_zClose zClose = (_zClose)GetProcAddress(H,"zClose");
	_zStatus zStatus = (_zStatus)GetProcAddress(H,"zStatus");
	_zData zData = (_zData)GetProcAddress(H,"zData");

	
// initialize process communication

	if(!zInit(2,8)) {
		printf("Can't initialize communication!"); return EXIT_FAILURE;
	}

	if(!zInit(3,8)) {
		printf("Can't initialize communication!"); return EXIT_FAILURE;
	}

	if(!zInit(4,4)) {
		printf("Can't initialize communication!"); return EXIT_FAILURE;
	}

	double* Info = (double*)zData(2);
	double* b = (double*)zData(3);
	int* r = (int*)zData(4);

// start minimized Zorro process
	if(!zOpen(2,"SuperStrategy.c -run -h")) {	
		printf("Can't initialize Zorro process!"); return EXIT_FAILURE;
	}

	while( zStatus(2) ) printf("MA %f  Price %f  Runs %i\n",*Info, *b, *r);


	zClose(0);

	return EXIT_SUCCESS;
}


