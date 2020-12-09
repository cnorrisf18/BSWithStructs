#include <iostream>
#include "NormalCDF.h"
#include "Structs.h"
using namespace std;


double CalculateDelta(MarketData GMarket, TradeData GTrade, double nd)
{
	double delta = exp(-GMarket.DividendYield * GTrade.YearsToExpiry) * nd * GTrade.NumberOfShares;
	return delta;
}


double CalculateGamma(MarketData GMarket, TradeData GTrade, double nd)
{
	double partone = exp(-GMarket.DividendYield * GTrade.YearsToExpiry);
	double parttwo = nd / (GMarket.SharePrice * GMarket.Volatility * sqrt(GTrade.YearsToExpiry));
	double gamma = partone * parttwo;
	return gamma;
}

double CalculateVega(MarketData GMarket, TradeData GTrade, double nd)
{
	double vega = GMarket.SharePrice * exp(-GMarket.DividendYield * GTrade.YearsToExpiry) * nd * sqrt(GTrade.YearsToExpiry);
	return vega;
}


void GetTradeInputs(TradeData* SomeTradeData)
{

	cout << "	" << "Number of shares: ";
	cin >> (*SomeTradeData).NumberOfShares;
	cout << "	" << "Strike Price: ";
	cin >> (*SomeTradeData).Strike;
	cout << "	" << "Time to Expiry (in years): ";
	cin >> (*SomeTradeData).YearsToExpiry;
}


void GetMarketInputs(MarketData* SomeMarketData)
{
	cout << "	" << "Share Price: ";
	cin >> (*SomeMarketData).SharePrice;
	cout << "	" << "Interest Rate (%): ";
	cin >> (*SomeMarketData).InterestRate;
	(*SomeMarketData).InterestRate /= 100;
	cout << "	" << "Dividend Yield (%): ";
	cin >> (*SomeMarketData).DividendYield;
	(*SomeMarketData).DividendYield /= 100;
	cout << "	" << "Volatility (%): ";
	cin >> (*SomeMarketData).Volatility;
	(*SomeMarketData).Volatility /= 100;
}

//double CalculateOptionPrice(double S, double r, double q, double σ, double N, double K, double T, double* delta, double* gamma, double* vega)
double CalculateOptionPrice(MarketData SomeMarketData, TradeData SomeTradeData, Greeks* SomeGreeks)
{
	double DiscountFactor = exp(-SomeMarketData.InterestRate * SomeTradeData.YearsToExpiry);
	double Forward = SomeMarketData.SharePrice * exp((SomeMarketData.InterestRate - SomeMarketData.DividendYield) * SomeTradeData.YearsToExpiry);
	double VolTimesSqrt = SomeMarketData.Volatility * sqrt(SomeTradeData.YearsToExpiry);
	double d1 = (log(Forward / SomeTradeData.Strike) / VolTimesSqrt) + .5 * VolTimesSqrt;
	double d2 = (log(Forward / SomeTradeData.Strike) / VolTimesSqrt) - .5 * VolTimesSqrt;
	double nd1 = exp(-(pow(d1, 2))) / sqrt(2 * 3.14159265);
	double nd2 = exp(-(pow(d2, 2))) / sqrt(2 * 3.14159265);
	double cdf1 = CumulativeNormalDistribution(d1);
	double cdf2 = CumulativeNormalDistribution(d2);
	double OptionPrice = DiscountFactor * ((Forward * cdf1) - (SomeTradeData.Strike * cdf2)) * SomeTradeData.NumberOfShares;
	(*SomeGreeks).Delta = CalculateDelta(SomeMarketData, SomeTradeData, nd1);
	(*SomeGreeks).Gamma = CalculateGamma(SomeMarketData, SomeTradeData, nd1);
	(*SomeGreeks).Vega = CalculateVega(SomeMarketData,SomeTradeData, nd1);
	return OptionPrice;
}

