#include "Map.h"
#include "CarMap.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
	CarMap m;
	assert(m.addCar("ABC123"));
	assert(!m.addCar("ABC123"));
	m.addCar("DEF456");
	m.addCar("GHI789");
	assert(m.fleetSize() == 3);
	assert(m.gas("ABC123") == 0);
	assert(!m.addGas("DEF456", -30));
	assert(m.addGas("DEF456", 30));
	assert(m.gas("DEF456") == 30);
	assert(m.useGas("DEF456", 20) && m.gas("DEF456") == 10);
	assert(!m.useGas("ABC123", 40) && m.gas("ABC123") == 0);
	//m.print();
	cerr << "Passed all tests" << endl;
}