#include <iostream>
#include "History.h"
#include "globals.h"

using namespace std;

History::History(int nRows, int nCols) {
	m_rows = nRows;
	m_cols = nCols;
	for (int i = 0; i < nRows; i++) {
		for (int j = 0; j < nCols; j++) {
			failedPreach[i][j] = 0;	
		}
	}
}

bool History::record(int r, int c) {
	if (r > m_rows || c > m_cols || r < 1 || c < 1) {
		return false;
	}
	failedPreach[r - 1][c - 1] ++;
	return true;
}

void History::display() const {
	char historyGrid[MAXROWS][MAXCOLS]; // wanted to use m_rows and m_cols but cant since these values aren't known at compile time
	for (int i = 0; i < m_rows; i++) {
		for (int j = 0; j < m_cols; j++) {
			if (failedPreach[i][j] == 0) {
				historyGrid[i][j] = '.';
			}
			else {
				historyGrid[i][j] = 64; //ASCII character before A-Z
				for (int x = failedPreach[i][j]; x > 0; x--) { //TODO: make sure this doesnt put a character that is greater than z which is ascii value 90
					historyGrid[i][j]++;
					if (historyGrid[i][j] > 90) {
						historyGrid[i][j] = 90;
						break;
					}
				}
			}
		}
	}

	clearScreen(); //following code copied from the code given in City.cpp for displaying the screen
	for (int r = 0; r < m_rows; r++)
	{
		for (int c = 0; c < m_cols; c++)
			cout << historyGrid[r][c];
		cout << endl;
	}
	cout << endl;

}
