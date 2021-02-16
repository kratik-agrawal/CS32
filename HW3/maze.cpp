//
//  maze.cpp
//  HW3
//
//  Created by Kratik Agrawal on 2/4/21.
//

#include <iostream>
#include <string>

using namespace std;


class Coord
{
    public:
        Coord(int rr, int cc) : m_row(rr), m_col(cc) {}
        int r() const { return m_row; }
        int c() const { return m_col; }
    private:
        int m_row;
        int m_col;
};

// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec){
    
    Coord curr(sr, sc);
    maze[sr][sc] = '!';
    cout << sr << " " << sc << endl;
    if(sr == er && sc == ec)
        return true;
    
    bool solvable = false;
    if(maze[curr.r()-1][curr.c()] == '.'){
        maze[curr.r()-1][curr.c()] = '!';
        solvable = pathExists(maze, nRows, nCols, curr.r()-1, curr.c(), er, ec);
        if(solvable) return true;
    }
    if(maze[curr.r()][curr.c()+1] == '.'){
        maze[curr.r()][curr.c()+1] = '!';
        solvable = pathExists(maze, nRows, nCols, curr.r(), curr.c()+1, er, ec);
        if(solvable) return true;
    }
    if(maze[curr.r()+1][curr.c()] == '.'){
        maze[curr.r()+1][curr.c()] = '!';
        solvable = pathExists(maze, nRows, nCols, curr.r()+1, curr.c(), er, ec);
        if(solvable) return true;
    }
    if(maze[curr.r()][curr.c()-1] == '.'){
        maze[curr.r()][curr.c()-1] = '!';
        solvable = pathExists(maze, nRows, nCols, curr.r(), curr.c()-1, er, ec);
        if(solvable) return true;
    }
    
    return false;
    
}





int main()
{
    string maze[10] = {
        "XXXXXXXXXX",
        "X........X",
        "XX.X.XXXXX",
        "X..X.X...X",
        "X..X...X.X",
        "XXXX.XXX.X",
        "X.X....XXX",
        "X..XX.XX.X",
        "X...X....X",
        "XXXXXXXXXX"
    };
    string maze2[3] = {
        "XXXXXXXXXX",
        "X..X.....X",
        "XXXXXXXXXX",
    };
    //if (pathExists(maze2, 3,10, 1,1, 1,7))
    if (pathExists(maze, 10,10, 6,4, 1,1))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}
