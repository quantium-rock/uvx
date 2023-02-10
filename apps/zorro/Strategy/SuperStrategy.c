// Strategy template ///////////////////////

#include <nexow.h>

int runs = 0;

void run() 
{
	LookBack = 200;
	set(PLOTNOW);

	asset("EURUSD");
	
    BarPeriod = 60;
	StartDate = 2000;

	
	
	double* Prices = series(price(0),100);
	double MA = SMA(Prices,30);
	plot("MA",MA,0,RED);

	if(!zInit(2,8)) return quit("Can't initialize process!"); 
	double* Info = (double*)zData(2);
	if(!zInit(3,8)) return quit("Can't initialize process!"); 
	double* b = (double*)zData(3);
	if(!zInit(4,4)) return quit("Can't initialize process!"); 
	int* r = (int*)zData(4);
	*Info = MA;
	*b = price(0);
	*r = runs;

	
	runs++;
 

}