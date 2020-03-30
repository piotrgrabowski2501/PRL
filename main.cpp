#include <iostream>
#include "City.h"
using namespace std;

double limit_child[2] = {0.75, 0.3};
double limit_worker[2] = {2.1, 0.15};
double limit_pregnant_women[2] = {3.0, 0.7};

int main(){
	cout << people << endl;
	City Krakow(1,1);
	Krakow.ShopsWithChocolate[0].symbol = 'C';
	Krakow.ShopsWithChocolate[0].commodity = 10;
	Krakow.ShopsWithChocolate[0].setClientInTheQueue(0);
	cout << Krakow.ShopsWithChocolate[0].checkPresence() << endl;
	cout << people << endl;
	Krakow.MeatMarkets[0].symbol = 'M';
	Krakow.MeatMarkets[0].commodity = 2;
	Krakow.MeatMarkets[0].setClientInTheQueue(0);
	Krakow.MeatMarkets[0].setClientInTheQueue(1);
	Krakow.MeatMarkets[0].setClientToTheFrontOfQueue(2);
	cout << Krakow.MeatMarkets[0].checkPresence() << endl;
	Krakow.MeatMarkets[0].sale(2);
	cout << Krakow.MeatMarkets[0].commodity << endl;
	cout << Krakow.MeatMarkets[0].checkPresence() << endl;

	Krakow.MeatMarkets[0].delivery(2.3);
	Krakow.MeatMarkets[0].setClientInTheQueue(0);
	Krakow.MeatMarkets[0].setClientToTheFrontOfQueue(1);
	Krakow.MeatMarkets[0].setBehindClientRight(3,1);
	Krakow.MeatMarkets[0].setClientToTheFrontOfQueue(2);
	cout << Krakow.MeatMarkets[0].checkPresence() << endl;
	Krakow.MeatMarkets[0].turnSequenceAround();
	cout << Krakow.MeatMarkets[0].checkPresence() << endl;
	Krakow.MeatMarkets[0].sort_();
	Krakow.MeatMarkets[0].deleteClient(2);
	cout << Krakow.MeatMarkets[0].checkPresence() << endl;

	Krakow.MeatMarkets[0].sale(2);
	cout << Krakow.MeatMarkets[0].checkPresence() << endl;
	cout << people << endl;
	return 0;
}
