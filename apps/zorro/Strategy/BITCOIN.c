// Strategy template ///////////////////////

#include <nexow.h>

// INIT //


void run() 
{
	
    //init();
    //setplt();

    set(PLOTNOW|PRELOAD);

    asset("BTCUSD");

    BarPeriod = 60;
    LookBack = 200;
    
    /*
    int len = 120;

	double *ps = series(price(0),len);
	double *zma = series(ZMA(ps,len),len);
    double *lpf = series(LowPass(ps,len),len);
    
    plot("ZMA",zma,0,PURPLE);
    plot("LPF",lpf,0,ORANGE);
    */
    /*

    double *ret = series(ps[0]/ps[1]-1,len);
    double *vol = series(priceHigh(0)/priceLow(0)-1,len);
    double *ema = series(EMA(ret,len),len);
    double *std = series(StdDev(ret,len),len);
    double *zsc = series((ps[0]-ema[0])/std[0],len); 

    plot("line",0,1,BLACK);
    plot("Ret",ret,0,BLUE);
    plot("Vol+",vol,0,RED);
    plot("Vol-",-vol[0],0,RED);
    */                                                                                                                          
    /*
    if( zma[0] > lpf[0] && zma[0] > zma[2] && priceOpen(0) > priceClose(0) )
        enterLong();
    else if( zma[0] < lpf[0] && zma[0] < zma[2] && priceOpen(0) < priceClose(0) )
        enterShort();
    */

    /*
    if( LP[2] < LP[1] && LP[1] > LP[0] )
        exitLong();
    if( LP[2] > LP[1] && LP[1] < LP[0] )
        exitShort();

    */





    //plot("Equity",Equity,1,RED);
}