#include<string>
#include<iostream>
using namespace std;



// Return false if the somePredicate function returns false for at
// least one of the array elements; return true otherwise.
bool allTrue(const double a[], int n)
{
	if (n>0 && !somePredicate(a[n-1]) ){
		return false;
	}
	n--;
	if (n > 0) {
		return allTrue(a, n);
	}
	else {
		return true;
	}
	//return false;  // This is not always correct.
}

// Return the number of elements in the array for which the
// somePredicate function returns false.
int countFalse(const double a[], int n)
{

	int i = 0;
	int x = 0;
	if (n > 0 && !somePredicate(a[n - 1])) {
		i++;
	}
	n--;
	if (n > 0) {
		x = countFalse(a, n);
	}
	return i + x;
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns false.  If there is no such
// element, return -1.
int firstFalse(const double a[], int n)
{
	if (n <= 0) {
		return -1;
	}
	if (!somePredicate(a[0])) {
		return 0;
	}
	else if (firstFalse(a + 1, n - 1 == -1)) { //increase the array by one and the number of items able to be inspected by one
		return -1;
	}
	return 1 + firstFalse(a + 1, n - 1);
}

	/*if (n != 0 && !somePredicate(a[n-1])) {
		return (n - 1);
	}
	n--;
	if (n > 0) {
		return firstFalse(a, n);
	}
	else {
		return -1;
	}*/
	


// Return the subscript of the smallest double in the array (i.e.,
// the one whose value is <= the value of all elements).  If more
// than one element has the same smallest value, return the smallest
// subscript of such an element.  If the array has no elements to
// examine, return -1.
int indexOfMin(const double a[], int n) 
{
	if (n <= 0) {
		return -1;
	}
	int i = indexOfMin(a, n - 1);
	if (i == -1) {
		i = 0;
	}
	if (a[i] > a[n - 1]) {
		return n - 1;
	}
	else {
		return i;
	}
	/*
	if (n <= 0) {
		return -1;
	}
	int i = 1+ indexOfMin(a+1, n - 1); //makes the array smaller by going up the array
	if (a[i] > a[0]) {
		return 0;
	}
	else {
		return i;
	}
	*/
}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    10 50 40 20 50 40 30
// then the function should return true if a2 is
//    50 20 30
// or
//    50 40 40
// and it should return false if a2 is
//    50 30 20
// or
//    10 20 20
bool includes(const double a1[], int n1, const double a2[], int n2)
{
	if (n2 <= 0) {
		return true;
	}
	if (n1 <= 0) {
		return false;
	}
	if (a1[n1-1] == a2[n2-1]) { //when they are both equal increment them both down
		n2--;
		n1--;
	}
	else if (a1[n1 - 1] != a2[n2 - 1]) {
		n1--;
	}
	return includes(a1, n1, a2, n2);
}

