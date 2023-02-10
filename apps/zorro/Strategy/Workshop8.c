// Workshop 8: Simple Option system //////////////////////////////////////////
#include <contract.c>

#define PREMIUM	2.00
#define DAYS		6*7 


void run() 
{
	StartDate = 20120101;
	EndDate = 20181231;
	BarPeriod = 1440;
	set(PLOTNOW,LOGFILE);

	History = ".t8"; // real options data
	assetList("AssetsIB");
	asset("SPY");
	Multiplier = 100;

// load today's contract chain
	if(!contractUpdate(Asset,0,CALL|PUT)) return;

// Enter new positions
	if(!NumOpenShort) { 
		if(combo(
			contractFind(CALL,DAYS,PREMIUM,2),1, 
			contractFind(PUT,DAYS,PREMIUM,2),1,
			0,0,0,0)) 
		{
			MarginCost = 0.15*priceClose()/2;
			enterShort(comboLeg(1));
			enterShort(comboLeg(2));
		}
	}
}