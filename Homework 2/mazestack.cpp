#include <string>
#include <iostream>
#include <stack>
using namespace std;

class Coord
{
public:
	Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
	int r() const { return m_r; }
	int c() const { return m_c; }
private:
	int m_r;
	int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
	stack<Coord> pathStack;
	Coord endCoord(er, ec);
	pathStack.push(Coord(sr, sc));
	maze[sr][sc] = '#';
	
	while (!pathStack.empty()) {
		Coord current = pathStack.top();
		pathStack.pop();
		if (current.r()  == er && current.c() == ec) {
			return true;
		}
		if (maze[current.r()][current.c() + 1] == '.') { //east direction, (r, c+1)
			pathStack.push(Coord(current.r(), current.c() + 1));
			maze[current.r()][current.c()+1] = '#';
		}
		if (maze[current.r()+1][current.c()] == '.') { //south direction, (r+1, c)
			pathStack.push(Coord(current.r()+1, current.c()));
			maze[current.r()+1][current.c()] = '#';
		}
		if (maze[current.r()][current.c() - 1] == '.') { //west direction, (r, c-1)
			pathStack.push(Coord(current.r(), current.c() - 1));
			maze[current.r()][current.c() - 1] = '#';
		}
		if (maze[current.r()-1][current.c()] == '.') { //north direction, (r-1, c)
			pathStack.push(Coord(current.r()-1, current.c()));
			maze[current.r() - 1][current.c()] = '#';
		}
		
	}
	return false;
}

// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise\\int main()
int main(){
	string maze[10] = {
		"XXXXXXXXXX",
		"X...X..X.X",
		"X..XX....X",
		"X.X.XXXX.X",
		"XXX......X",
		"X...X.XX.X",
		"X.X.X..X.X",
		"X.XXXX.X.X",
		"X..X...X.X",
		"XXXXXXXXXX"
	};

	if (pathExists(maze, 10, 10, 4, 3, 1, 8))
		cout << "Solvable!" << endl;
	else
		cout << "Out of luck!" << endl;
}