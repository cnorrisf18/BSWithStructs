#include "NormalCDF.h"
#include "ExtraFunctions.h"
#include "Structs.h"
#include <iostream>
using namespace std;


int main()
{
	MarketData BSMarketData;
	TradeData BSTradeData;
	Greeks BSGreeks;
	//double SharePrice = 0, InterestRate = 0, DividendYield = 0, Volatility = 0, NumberOfShares = 0, Strike = 0, YearsToExpiry = 0;
	//double Delta = 0, Gamma = 0, Vega = 0;
	cout << "This is a program to determine the price of a share via the Black Scholes formula." << endl;
	cout << "Please input market data." << endl;
	GetMarketInputs(&BSMarketData);
	cout << "Please input trade data." << endl;
	GetTradeInputs(&BSTradeData);
	
	/*
	double InputArray[] = { BSMarketData.SharePrice, BSMarketData.InterestRate, BSMarketData.DividendYield, BSMarketData.Volatility, BSTradeData.NumberOfShares, BSTradeData.Strike, BSTradeData.YearsToExpiry };
	double size_array = sizeof(InputArray) / sizeof(InputArray[0]);
	for (int i = 0; i < size_array; i++)
	{
		cout << InputArray[i] << " ";
	}
	*/
	double FinalPrice = CalculateOptionPrice(BSMarketData, BSTradeData, &BSGreeks);
	cout << "The price of the option is: " << FinalPrice << endl;
	cout << "Delta is " << BSGreeks.Delta << ", Gamma is " << BSGreeks.Gamma << ", and Vega is " << BSGreeks.Vega << "." << endl;
	return 0;
}