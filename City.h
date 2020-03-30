//Piotr Grabowski
#ifndef __CITY_H__
#define __CITY_H__
#include "PRL.cpp"

struct City{
	int number_of_meat_markets;
	int number_of_shops_with_chocolate;
	Shop* MeatMarkets;
	Shop* ShopsWithChocolate;

	City(int meat, int chocolate){
		number_of_meat_markets = meat;
		number_of_shops_with_chocolate = chocolate;
		MeatMarkets = new Shop[number_of_meat_markets];
		ShopsWithChocolate = new Shop[number_of_shops_with_chocolate];
	}
};

#endif
