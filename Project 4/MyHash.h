// MyHash.h

// Skeleton for the MyHash class template.  You must implement the first seven
// member functions; we have implemented the eighth.
#ifndef MYHASH_H
#define MYHASH_H
#include<iostream>

template<typename KeyType, typename ValueType>
class MyHash
{
public:
	MyHash(double maxLoadFactor = 0.5);
	~MyHash();
	void reset();
	void associate(const KeyType& key, const ValueType& value);
	int getNumItems() const;
	double getLoadFactor() const;


	// for a map that can't be modified, return a pointer to const ValueType
	const ValueType* find(const KeyType& key) const;

	// for a modifiable map, return a pointer to modifiable ValueType
	ValueType* find(const KeyType& key)
	{
		return const_cast<ValueType*>(const_cast<const MyHash*>(this)->find(key));
	}

	// C++11 syntax for preventing copying and assignment
	MyHash(const MyHash&) = delete;
	MyHash& operator=(const MyHash&) = delete;

private:
	struct Node {
		Node(KeyType key, ValueType value) {
			m_key = key;
			m_value = value;
			next = nullptr;
		}
		KeyType   m_key;
		ValueType m_value;
		Node* next;
	};
	int NUM_BUCKETS = 100;
	double m_loadFactor = 0.5;
	Node** m_arr;

	int NUM_ITEMS = 0;

	void destructHashArray();
	void insert(const KeyType& key, const ValueType& value);
	unsigned int getBucketNumber(const	KeyType&	key)	const
	{
		unsigned	int	hasher(const	KeyType&	k);		//	prototype
		unsigned	int	h = hasher(key);
		h = h % NUM_BUCKETS;
		return h;
	}
};

template<typename KeyType, typename ValueType>
MyHash<KeyType, ValueType>::MyHash(double maxLoadFactor)

{
	m_loadFactor = maxLoadFactor;
	if (m_loadFactor <= 0) {
		m_loadFactor = .5;
	}
	else if (m_loadFactor > 2) {
		m_loadFactor = 2;
	}
	m_arr = new Node*[NUM_BUCKETS];
	for (int i = 0; i < NUM_BUCKETS; i++) {
		m_arr[i] = nullptr;
	}
}
template <typename KeyType, typename ValueType>
void MyHash<KeyType, ValueType>::destructHashArray() {
	for (int i = 0; i < NUM_BUCKETS; i++) {
		if (m_arr[i] != nullptr) {
			Node* N = m_arr[i];
			while (N != nullptr) {
				Node* killme = N;
				N = N->next;
				delete killme;
			}
		}

	}
	delete[]m_arr;
}

template <typename KeyType, typename ValueType>
MyHash<KeyType, ValueType>::~MyHash() {
	destructHashArray();
}

template <typename KeyType, typename ValueType>
void MyHash<KeyType, ValueType>::reset() {
	destructHashArray();
	NUM_BUCKETS = 100;
	NUM_ITEMS = 0;
	m_arr = new Node*[NUM_BUCKETS];
	for (int i = 0; i < NUM_BUCKETS; i++) {
		m_arr[i] = nullptr;
	}
}

template <typename KeyType, typename ValueType>
int MyHash<KeyType, ValueType>::getNumItems() const {
	return NUM_ITEMS;
}

template <typename KeyType, typename ValueType>
double MyHash<KeyType, ValueType>::getLoadFactor()const {
	return (NUM_ITEMS / double(NUM_BUCKETS)); //cast one of the items as a double to make sure the answer isn't floored when it is still an integer
}

template <typename KeyType, typename ValueType>
void MyHash <KeyType, ValueType>::associate(const KeyType& key, const ValueType& value) {

	insert(key, value);

	if (getLoadFactor() > m_loadFactor) { //if the real load factor is given than the desired load factor, we must allocate a new hash array of double the size and delete the old one
		int OLD_NUM_BUCKETS = NUM_BUCKETS;
		NUM_BUCKETS *= 2;
		Node** oldarr = m_arr;
		m_arr = new Node*[NUM_BUCKETS]; //creates a new array of double the size and sets m_arr equal to it so the insert function can put it into the right place.
		for (int i = 0; i < NUM_BUCKETS; i++) {
			m_arr[i] = nullptr;
		}
		for (int i = 0; i < OLD_NUM_BUCKETS; i++) {
			Node* N = oldarr[i];
			while (N != nullptr) {
				insert(N->m_key, N->m_value);
				NUM_ITEMS--; //because every new value inserted into our new array will be a "new item" the insert function will increment num_items, but
							 //in reality these items aren't "new" they are just being put into a new array and we don't want num_items to change.
				N = N->next;
			}

		}
		for (int i = 0; i < OLD_NUM_BUCKETS; i++) {
			if (oldarr[i] != nullptr) { //if there is a nullptr in the slot then there are no items in the bucket
				Node* N = oldarr[i];
				while (N != nullptr) { //go down the items in the bucket and delete all of them
					Node* killme = N;
					N = N->next;
					delete killme;
				}
			}

		}
		delete[]oldarr;
	}
}

template <typename KeyType, typename ValueType>
void MyHash <KeyType, ValueType>::insert(const KeyType& key, const ValueType& value) {
	unsigned int numBucket = getBucketNumber(key);
	if (m_arr[numBucket] == nullptr) {
		m_arr[numBucket] = new Node(key, value);
		NUM_ITEMS++;
		return;
	}
	Node* currentItem = m_arr[numBucket]; //initialize the currentItem to the first item in the bucket linked list.
	while (currentItem->next != nullptr) { //ends once the next item is a nullptr
		if (currentItem->m_key == key) { //when the key is already in the map, simply change that item's value to the value paramater
			currentItem->m_value = value; //changing value
			return;
		}
		currentItem = currentItem->next;
	}
	if (currentItem->m_key == key) { //checker for the very last node in the list since we don't want to go past the end or else we wont be able to link our new node to the linked list
		currentItem->m_value = value; //changing value
		return;
	}
	currentItem->next = new Node(key, value); //add a new item and increase the item counter;
	NUM_ITEMS++;
}




template <typename KeyType, typename ValueType>
const ValueType* MyHash <KeyType, ValueType>::find(const KeyType& key) const {
	unsigned int numBucket = getBucketNumber(key);
	Node* N = m_arr[numBucket];
	while (N != nullptr) {
		if (N->m_key == key) {
			return &(N->m_value);
		}
		N = N->next;
	}
	return nullptr;
}
#endif