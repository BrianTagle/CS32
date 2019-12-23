#include<iostream>
#include<string>
using namespace std;

////INVESTMENT DECLARATION////
class Investment {
public:
	Investment(string name, int price);
	virtual ~Investment(){}
	string name() const;
	int purchasePrice() const;
	virtual bool fungible() const = 0;
	virtual string description() const = 0;
private:
	string m_name;
	int m_price;
};
////STOCK DECLARATION////
class Stock :public Investment {
public:
	Stock(string name, int price, string stockName);
	virtual ~Stock();
	virtual bool fungible() const;
	virtual string description() const;
private:
	string m_stockName;
};
////PAINTING DECLARATION////
class Painting :public Investment {
public:
	Painting(string name, int price);
	virtual ~Painting();
	virtual bool fungible() const;
	virtual string description() const;
private:
};
////HOUSE DECLARATION////
class House :public Investment {
public:
	House(string name, int price);
	virtual ~House();
	virtual bool fungible() const;
	virtual string description() const;
private:
};
///////////////////////////////////////////////////////////////////////

////INVESTMENT IMPLEMENTATION////

Investment::Investment(string name, int price) {
	m_name = name;
	m_price = price;
}
string Investment::name() const {
	return m_name;
}
int Investment::purchasePrice() const{
	return m_price;
}

 
////STOCK IMPLEMENTATION////
Stock::Stock(string name, int price, string stockName):Investment(name,price) {
	m_stockName = stockName;
}
Stock::~Stock() {
	cout << "Destroying " << name() << ", a stock holding " << endl;
}
bool Stock::fungible() const {
	return true;
}
string Stock::description() const {
	return "stock trading as " + m_stockName;
}
////PAINTING DECLARATION////
Painting::Painting(string name, int price):Investment(name,price) {

}
Painting::~Painting() {
	cout << "Destroying " << name() << ", a painting " << endl;
}
bool Painting::fungible() const {
	return false;
}
string Painting::description() const {
	return "painting";
}
////HOUSE DECLARATION////
House::House(string name, int price) : Investment(name, price) {

}
House::~House() {
	cout << "Destroying the house " << name() << endl;
}
bool House::fungible() const{
	return false;
}
string House::description() const {
	return "house";
}

//DONT TURN IN ANYTHING PAST THIS POINT

