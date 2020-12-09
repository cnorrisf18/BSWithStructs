#pragma once
struct TradeData
{
	double Strike =0;
	long NumberOfShares=0;
	double YearsToExpiry=0;
};

struct MarketData
{
	double SharePrice=0;
	double InterestRate=0;
	double DividendYield=0;
	double Volatility=0;
};

struct Greeks
{
	double Delta=0;
	double Gamma=0;
	double Vega=0;
};