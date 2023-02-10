// Trend Trading ///////////////////
#include <profile.c>

function run()
{
	EndDate = 20171231; // fixed simulation period 
	Verbose = 2;
	LookBack = 300;	// needed for MMI
	asset("EUR/USD");
	set(LOGFILE,PLOTNOW); // log all trades

	vars Prices = series(priceClose());
	vars Trends = series(LowPass(Prices,300));
	
	Stop = 30*ATR(100);
	
	vars MMI_Raws = series(MMI(Prices,300));
	vars MMI_Smooths = series(LowPass(MMI_Raws,300));
	
	if(falling(MMI_Smooths)) 
	{
		if(valley(Trends))
			enterLong();
		else if(peak(Trends))
			enterShort();
	}
	
	plot("MMI_Raw",MMI_Raws,NEW,GREY);
	plot("MMI_Smooth",MMI_Smooths,0,BLACK);
	//plotTradeProfile(-50); 
}