#include "Map.h"

Map::Map() :m_size(0) {
	
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

bool Map::insert(const KeyType& key, const ValueType& value) {
	if (m_size >= DEFAULT_MAX_ITEMS || this->contains(key)) {
		return false;
	}
	
	m_map[m_size].key = key;
	m_map[m_size].value = value;
	m_size++;
	return true;
}
bool Map::update(const KeyType& key, const ValueType& value) {
	for (int i = 0; i < m_size; i++) {
		if (m_map[i].key == key) {
			m_map[i].value = value;
			return true;
		}
	}
	return false;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value) {
	for (int i = 0; i < m_size; i++) {
		if (m_map[i].key == key) {
			m_map[i].value = value;
			return true;
		}
	}
	if (m_size >= DEFAULT_MAX_ITEMS) {
		return false;
	}
	m_map[m_size].key = key;
	m_map[m_size].value = value;
	m_size++;
	return true;
}
bool Map::erase(const KeyType& key) {
	for (int i = 0; i < m_size; i++) {
		if (m_map[i].key == key) {
			for (i; i < m_size-1; i++) {
				m_map[i].key = m_map[i + 1].key;
				m_map[i].value = m_map[i + 1].value;
			}
			m_size--;
			return true;
		}
	}
	return false;
}
bool Map::contains(const KeyType& key) const
{

	for (int i = 0; i<m_size; i++)
	{
		if (m_map[i].key == key) {
			return true;
		}
	}
	return false;
}

bool Map::get(const KeyType& key, ValueType& value) const {
	for (int i = 0; i < m_size; i++) {
		if (m_map[i].key == key) {
			value = m_map[i].value;
			return true;
		}
	}
	return false;
}


bool Map::get(int i, KeyType& key, ValueType& value) const {
	if(i>= 0 && i < m_size){
		key = m_map[i].key;
		value = m_map[i].value;
		return true;	
	}
	else {
		return false;
	}
}


void Map::swap(Map& other) {
	Map temp;
	temp = *this;
	*this = other;
	other = temp;
	/*
	Map temp;
	for (int i = 0; i < this->size(); i++) {
		(temp.m_map[i]) = (this->m_map[i]);
	}
	temp.m_size = this->size();

	for (int i = 0; i < other.size(); i++) {
		this->m_map[i] = other.m_map[i];
	}
	this->m_size= other.size();
	for (int i = 0; i < temp.size(); i++) {
		other.m_map[i] = temp.m_map[i];
	}
	other.m_size = temp.m_size;
	*/
}

// Exchange the contents of this map with the other one.
