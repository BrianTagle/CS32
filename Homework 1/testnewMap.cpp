#include "newMap.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
	Map m;  // maps strings to doubles
	assert(m.empty());
	ValueType v = -1234.5;
	assert(!m.get("abc", v) && v == -1234.5); // v unchanged by get failure
	m.insert("xyz", 9876.5);
	assert(m.size() == 1);
	KeyType k = "hello";
	assert(m.get(0, k, v) && k == "xyz"  &&  v == 9876.5);
	m.insert("abc", 123);
	m.insert("def", 45.6);
	m.insert("ghi", 7.89);
	assert(m.get("def", v) && k == "xyz"  &&  v == 45.6); //k is still xyz because the other get doesn't copy the key into the key parameter
	assert(m.insertOrUpdate("abc", 321) && m.get("abc", v) && v == 321); //testing update part of insertOrUpdate
	assert(m.insertOrUpdate("jkl", 1.23) && m.get(4, k, v) && k == "jkl" && v == 1.23); //testing insert part of insertOrUpdate

	assert(!m.update("fhk", 30));
	assert(m.update("abc", 123));
	assert(m.erase("abc")); //testing erase
	assert(m.get(1, k, v) && k == "def" && v == 45.6); //since "abc" was erased, everything was moved down by one

	Map m1;
	m1.insert("alpha", 1);
	m1.insert("beta", 2);
	m.swap(m1); //testing swap
	assert(m.get(0, k, v) && k == "alpha" && v == 1); //making sure everything swapped correctly
	assert(m.get(1, k, v) && k == "beta" && v == 2);
	assert(m1.get(0, k, v) && k == "xyz" && v == 9876.5);
	assert(m1.get(3, k, v) && k == "jkl" && v == 1.23);

	Map m2(3);
	m2.insert("alpha", 1);
	m2.insert("beta", 2);
	m2.insert("charlie", 3);
	assert(!m2.insert("delta", 4));
	assert(!m2.get(3, k, v) && k == "jkl" && v == 1.23);

	cerr << "Passed all tests" << endl;
}