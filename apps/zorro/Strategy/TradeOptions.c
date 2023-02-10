// Trade Options or Combos ///////////////////

#include <contract.c>

//#define LIST	"AssetsSP30"
//#define TICKER	"MO" // select specific list with symbol
#define WAIT_TIME	60	// seconds
#define PRINT_GREEKS

int Chain = 0;
int Type = 1; // 1 Call, 2 Put, 3 Strangle, 4 Butterfly, 5 Condor 
var Strike;
int Expiry;

void trade(int Dir)
{
	Strike = slider(1);
	Expiry = slider(2);
	//var Limit = slider(3);
	var CenterPrice = priceClose();
	int Legs = 0;
	if(Type == 1)
		Legs = combo(
			contract(CALL,Expiry,CenterPrice+Strike),1,
			0,0,0,0,0,0);
	else if(Type == 2)
		Legs = combo(
			contract(PUT,Expiry,CenterPrice+Strike),1,
			0,0,0,0,0,0);
	else if(Type == 3)
		Legs = combo(
			contract(CALL,Expiry,CenterPrice-Strike),1, 
			contract(PUT,Expiry,CenterPrice+Strike),1,
			0,0,0,0);
	else if(Type == 4) // butterfly
		Legs = combo(
			contract(PUT,Expiry,CenterPrice-abs(Strike)),-1, 
			contract(PUT,Expiry,CenterPrice+abs(Strike)),-1,
			contract(PUT,Expiry,CenterPrice),2, 
			0,0);
	else if(Type == 5)
		Legs = combo(
			contract(CALL,Expiry,CenterPrice+abs(Strike)),1, 
			contract(PUT,Expiry,CenterPrice-abs(Strike)),1,
			contract(CALL,Expiry,(CenterPrice+2*abs(Strike))),-1, 
			contract(PUT,Expiry,(CenterPrice-2*abs(Strike))),-1);
	if(!Legs) return;
	printf("\nSend order...");
	setf(TradeMode,TR_GTC);
	/*if(Limit >= 1.) {
		var AskBidSpread = abs(comboPremium(Dir)+comboPremium(-Dir));
		OrderLimit = comboPremium(Dir) - Dir*0.01*Limit*AskBidSpread;
		printf(" at Limit %.2f Spread %.2f",OrderLimit,AskBidSpread);
	}*/
	if(comboLeg(1)) enterLong(Dir*comboLeg(1));
	if(comboLeg(2)) enterLong(Dir*comboLeg(2));
	if(comboLeg(3)) enterLong(Dir*comboLeg(3));
	if(comboLeg(4)) enterLong(Dir*comboLeg(4));
}


void click(int row,int col)
{
	if(!is(RUNNING)) return; // only clickable when session is active
	sound("click.wav");	
	string Text = panelGet(row,col);
	
	if(Text == "Call") {
		panelSet(row,col,"Put",0,0,0); 
		Type = 2;
	} else if(Text == "Put") {
		panelSet(row,col,"Strangle",0,0,0); 
		Type = 3;
	} else if(Text == "Strangle") {
		panelSet(row,col,"Butterfly",0,0,0); 
		Type = 4;
	} else if(Text == "Butterfly") {
		panelSet(row,col,"Condor",0,0,0); 
		Type = 5;
	} else if(Text == "Condor") {
		panelSet(row,col,"Call",0,0,0); 
		Type = 1;
	}
	else if(Chain) {
		if(Text == "Buy")
			trade(1);
		else if(Text == "Sell")
			trade(-1);
	}
}

void run()
{
	if(Test) { quit("Click [Trade]!"); return; }
#ifdef LIST
	assetList(LIST,TICKER);
#endif
	BarPeriod = 1;
	NumYears = 1;
	LookBack = 0;
	Verbose = 3;
	set(LOGFILE);
	SaveMode = 0;

	Lots = 1;
	Strike = slider(1,5,-30,30,"Strike","Strike offset in $");
	Expiry = slider(2,30,1,100,"Expiry","Expiration in days");
	//slider(3,0,0,200,"Limit","Order limit in ask-bid percent");

	if(!Live) {
		quit("Click [Trade]!");
		return;
	} 

	static int UpdateTime;

	if(Init) {
		panel(4,1,GREY,80);
		int row = 0;
		panelSet(row++,0,Asset,ColorPanel[0],1,1);
		panelSet(row++,0,"Call",ColorPanel[3],1,4);
		panelSet(row++,0,"Buy",ColorPanel[3],3,4);
		panelSet(row++,0,"Sell",ColorPanel[3],3,4);
	}

	if(Init)	{
		printf("\nNY Time: %02d:%02d",lhour(ET,NOW),minute(NOW));
		UpdateTime = 60;
		printf("\nRetrieving %s data.. ",Asset);
	}
	asset(Asset);
	Multiplier = 100;
	if(Init) printf("ok");
	
	if(UpdateTime++ >= 60) { // every 60 bars
		UpdateTime = 0;
		printf("\nDownloading %s chain.. ",Asset);
		Chain = contractUpdate(Asset,0,PUT|CALL); 
		printf("\n%d contracts",Chain);
		if(!Chain) { quit("No Options Chain"); return; }
		panelSet(2,0,0,0,1,0);
		panelSet(3,0,0,0,1,0);
	}	
	
#ifdef PRINT_GREEKS
	if(contract(CALL,Expiry,priceClose()+Strike)) {
		//brokerCommand(SET_PRICETYPE,8); // fast mode, no greeks
		contractPrice(ThisContract);
		printf("\nCall %i %.2f: Ask %.2f Bid %.2f",
			ContractExpiry,ContractStrike,ContractAsk,ContractBid);
		var Greeks[5];
		brokerCommand(GET_GREEKS,Greeks);
		printf("\nIV %.2f Delta %.2f Gamma %.2f Vega %.2f Theta %.2f",
			Greeks[0],Greeks[1],Greeks[2],Greeks[3],Greeks[4]);
	}
#endif	

	for(open_trades) {
		printf("\n%s Strike %2f Unl %.2f Prem %.0f",
			ifelse(TradeIsCall,"Call","Put"),
			TradeStrike,TradeUnderlying,TradePriceOpen);
		//contractCheck(ThisTrade,3);
	}	
}