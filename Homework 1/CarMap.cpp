#include "CarMap.h"
#include <iostream>
using namespace std;
CarMap::CarMap() {

}
bool CarMap::addCar(KeyType license) {
	if (m_carMap.insert(license, 0)) {
		return true; //if license isn't in the map, add it
	}
	else {
		return false; //map full or license alreadt in map
	}
}
ValueType CarMap::gas(KeyType license) const {
	ValueType Value = -1;
	if (m_carMap.get(license, Value)) {
		return Value;
	}
	else {
		return -1;
	}
}
bool CarMap::addGas(KeyType license, ValueType gallons) {
	ValueType currentGallons = gas(license);
	if (currentGallons >= 0 && gallons >= 0) {
		m_carMap.update(license, currentGallons + gallons);
		return true;
	}
	else {
		return false;
	}
}


bool CarMap::useGas(KeyType license, ValueType gallons) {
	ValueType currentGallons = gas(license);
	if (currentGallons >= 0 && gallons >= 0 && (currentGallons - gallons >= 0) ) { // checks that the car is in the map, gallons to be used is not negative, and that gallons to be used is not greater than current gallons
		m_carMap.update(license, currentGallons - gallons); //updates map so that the car now has its currentgallons decreased by the amount of gallons spent
		return true;
	}
	else {
		return false;
	}
}

int CarMap::fleetSize() const {
	return m_carMap.size();
}

void CarMap::print() const {
	KeyType carKey;
	ValueType carValue;
	for (int i = 0; i < m_carMap.size(); i++) {
		m_carMap.get(i, carKey, carValue);
		cout << carKey << " " << carValue << endl;
	}
	
}
// Write to cout one line for every car in the map.  Each line
// consists of the car's license plate, followed by one space,
// followed by the number of gallons in that car's tank.  Write
// no other text.