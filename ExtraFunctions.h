#pragma once
#include "Structs.h"
void GetTradeInputs(TradeData* SomeTradeData);
void GetMarketInputs(MarketData* SomeMarketData);
double CalculateOptionPrice(MarketData SomeMarketData, TradeData SomeTradeData, Greeks* SomeGreeks);
double CalculateDelta(MarketData GMarket, TradeData GTrade, double nd);
double CalculateGamma(MarketData GMarket, TradeData GTrade, double nd);
double CalculateVega(MarketData GMarket, TradeData GTrade, double nd);