#include "newMap.h"

Map::Map() :m_size(0) {
	m_map = new mapValues[DEFAULT_MAX_ITEMS];
	m_maxSize = DEFAULT_MAX_ITEMS;
}
Map::Map(int size): m_size(0) {
	if (size < 0) {
		exit(0);
	}
	m_map = new mapValues[size];
	m_maxSize = size;
}
Map::~Map()
{
	delete[] m_map;
}

Map& Map::operator=(const Map &other) {
	if (&other == this) {
		return *this;
	}
	
	delete [] m_map;
	m_size = other.m_size;
	m_maxSize = other.m_maxSize;
	m_map = new mapValues[m_maxSize];
	for (int i = 0; i < m_size; i++) {
		m_map[i] = other.m_map[i];
	}
	return(*this);
}

Map::Map(const Map &other) {
	m_size = other.m_size;
	m_maxSize = other.m_maxSize;
	m_map = new mapValues[m_maxSize];
	for (int i = 0; i < m_size; i++) {
		m_map[i] = other.m_map[i];
	}
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
	if (m_size >= m_maxSize || this->contains(key)) {
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
	if (m_size >= m_maxSize) {
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
			for (i; i < m_size - 1; i++) {
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
	if (i >= 0 && i < m_size) {
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

	//int tempMaxSize = this->m_maxSize; // changes the max sizes for both of the maps
	//this->m_maxSize = other.m_maxSize;
	//other.m_maxSize = tempMaxSize;
}

// Exchange the contents of this map with the other one.
