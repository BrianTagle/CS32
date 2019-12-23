#include "Map.h"
#include <iostream>
using namespace std;

Map::Map() {
	m_size = 0;
	head = nullptr;
	tail = nullptr;
}

Map::~Map() {
	Node* p = head;
	while (p != nullptr) {
		Node * n = p->next;
		delete p;
		p = n;
	}
}

Map::Map(const Map &other) {
	m_size = 0;
	head = nullptr;
	tail = nullptr;
	Node *p = other.head;
	while (p != nullptr) {
		this->insert(p->key, p->value);
		p = p->next;
	}
}

Map& Map::operator=(const Map &other) {
	if (this == &other) {
		return *this;
	}
	Node* p = head;
	while (p != nullptr) {
		Node * n = p->next;
		delete p;
		p = n;
	}
	m_size = 0;
	head = nullptr;
	tail = nullptr;
	Node *k = other.head;
	while (k != nullptr) {
		this->insert(k->key, k->value);
		k = k->next;
	}
	return *this;


}

bool Map::empty() const {
	if (m_size > 0) {
		return false;
	}
	else {
		return true;
	}
}

int Map::size() const {
	return m_size;
}

bool Map::contains(const KeyType& key) const
{
	Node* p = head;
	while (p != nullptr){
		if (p->key == key) {
			return true;
		}
		p = p->next;
	}
	return false;
	
}

bool Map::insert(const KeyType& key, const ValueType& value) {

	if (this->contains(key)) {
		return false;
	}

	Node* p = new Node;
	if (head == nullptr) {
		head = p;
	}
	p->key = key;
	p->value = value;
	p->next = nullptr;
	p->prev = tail;
	if (tail != nullptr) {
		tail->next = p;
	}
	tail = p;
	m_size++;
	return true;
}


bool Map::update(const KeyType& key, const ValueType& value) {
	Node* p = head;
	while (p != nullptr) {
		if (p->key == key) {
			p->value = value;
			return true;
		}
		p = p->next;
	}
	return false;
}


bool Map::insertOrUpdate(const KeyType& key, const ValueType& value) {
	if (!this->update(key, value)) {
		this->insert(key, value);
	}
	return true;
}


bool Map::erase(const KeyType& key) {
	Node* p = head;
	while (p != nullptr) {
		if (p->key == key) {
			break;
		}
		p = p->next;
	}
	if (p == nullptr) { //Went through the list and did not find key
		return false;
	}
	if (p->next == nullptr && p->prev == nullptr) { //if the value to be erased is the only node in the list
		head = nullptr;
		tail = nullptr;
		delete p;
	}
	else if (p->prev == nullptr) { //if the value to be erased is the first node in the list
		head = p->next;
		head->prev = nullptr;
		delete p;
	}
	else if (p->next == nullptr) { //if the value to be erased is the last node in the list
		tail = p->prev;
		tail->next = nullptr;
		delete p;
	}
	else { //if the value to be erased is in the middle of the list
		p->prev->next = p->next;
		p->next->prev = p->prev;
		delete p;
	}
	m_size--;
	return true;
}


bool Map::get(const KeyType& key, ValueType& value) const {
	Node* p = head;
	while (p != nullptr) { //search for the key
		if (p->key == key) {
			break;
		}
		p = p->next;
	}
	if (p == nullptr) { // the key isnt in the map
		return false;
	}
	else {
		value = p->value;
	}
	return true;
}

bool Map::get(int i, KeyType& key, ValueType& value) const {
	if (i < 0 || i >= m_size) { //if the specified index is not in the map
		return false;
	}
	Node* p = head;
	
	for (int j = 0; j < i; j++) {
		p = p->next;
	}

	key = p->key;
	value = p->value;
	
	return true;
}


void Map::swap(Map& other) {
	Map temp;
	temp = *this;
	*this = other;
	other = temp;
	
	
}


void Map::dump() const {
	Node* p = head;
	while (p != nullptr) {
		cout << p->key << " " << p->value << endl;
		p = p->next;
	}
}

bool combine(const Map& m1, const Map& m2, Map& result) {
	KeyType k;
	ValueType v;
	bool duplicateStatus = true;
	for (int i = 0; i < result.size(); i++) {
		if (result.get(i, k, v)) {
			result.erase(k);
			i--;
		}
	}

	for (int i = 0; i < m1.size(); i++) {//adding items from m1 to result
		m1.get(i, k, v);
		if (!result.insert(k, v)) {
			ValueType vResult;
			result.get(k, vResult);
			if (v != vResult) {
				result.erase(k);
				duplicateStatus = false;
			}
		}
	}
	for (int i = 0; i < m2.size(); i++) {//adding items from m2 to result
		m2.get(i, k, v);
		if (!result.insert(k, v)) {
			ValueType vResult;
			result.get(k, vResult);
			if (v != vResult) {
				result.erase(k);
				duplicateStatus = false;
			}
		}
	}
	return duplicateStatus;

}

void subtract(const Map& m1, const Map& m2, Map& result) {
	KeyType k;
	ValueType v;
	
	for (int i = 0; i < result.size(); i++) {
		if (result.get(i, k, v)) {
			result.erase(k);
			i--;
		}
	}

	for (int i = 0; i < m1.size(); i++) {//adding items from m1 to result
		m1.get(i, k, v);
		result.insert(k, v);
	}
	for (int i = 0; i < m2.size(); i++) {//checking to see what values will be removed from result
		m2.get(i, k, v);
		ValueType vResult;
		if (result.get(k, vResult)) {
			result.erase(k);
		}
		
	}

}
