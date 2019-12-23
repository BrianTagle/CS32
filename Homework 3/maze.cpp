#include<string>
#include<iostream>
using namespace std;
/*
If the start location is equal to the ending location, then we've
solved the maze, so return true.
Mark the start location as visted.
For each of the four directions,
If the location one step in that direction(from the start
	location) is unvisited,
	then call pathExists starting from that location(and
		ending at the same ending location as in the
		current call).
	If that returned true,
	then return true.
	Return false.
	*/
bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
	if (sr == er && sc == ec) {
		return true;
	}
	maze[sr][sc] = '#';
	if (maze[sr][sc + 1] == '.') { //east direction, (r, c+1)
		if (pathExists(maze, nRows, nCols, sr, sc + 1, er, ec)) {
			return true;
		}
	}
	if (maze[sr+1][sc] == '.') { //south direction, (r+1, c)
		if (pathExists(maze, nRows, nCols, sr+1, sc , er, ec)) {
			return true;
		}
	}
	if (maze[sr][sc- 1] == '.') { //west direction, (r, c-1)
		if (pathExists(maze, nRows, nCols, sr, sc - 1, er, ec)) {
			return true;
		}
	}
	if (maze[sr - 1][sc] == '.') { //north direction, (r-1, c)
		if (pathExists(maze, nRows, nCols, sr-1, sc, er, ec)) {
			return true;
		}
	}
	return false;
}
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise
