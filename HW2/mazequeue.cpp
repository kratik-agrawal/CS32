//
//  mazequeue.cpp
//  HW2
//
//  Created by Kratik Agrawal on 1/28/21.
//
#include <iostream>
#include <string>
#include <queue>
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
    queue<Coord> mazeQueue;
    
    Coord start(sr, sc);
    mazeQueue.push(start);
    maze[sr][sc] = '!';
    while(!mazeQueue.empty()){
        Coord curr = mazeQueue.front();
        mazeQueue.pop();
        cout << "current " << curr.r() << " " << curr.c() << endl;
        if(curr.r() == er && curr.c() == ec)
            return true;
        
        if(maze[curr.r()-1][curr.c()] == '.'){
            mazeQueue.push(Coord(curr.r()-1, curr.c()));
            //cout << "north " << curr.r()-1 << " " << curr.c() << endl;
            maze[curr.r()-1][curr.c()] = '!';
        }
        
        if(maze[curr.r()][curr.c()+1] == '.'){
            mazeQueue.push(Coord(curr.r(), curr.c()+1));
            //cout << "east " << curr.r() << " " << curr.c()+1 << endl;
            maze[curr.r()][curr.c()+1] = '!';
        }
        
        if(maze[curr.r()+1][curr.c()] == '.'){
            mazeQueue.push(Coord(curr.r()+1, curr.c()));
            //cout << "south " << curr.r()+1 << " " << curr.c() << endl;
            maze[curr.r()+1][curr.c()] = '!';
        }
        
        if(maze[curr.r()][curr.c()-1] == '.'){
            mazeQueue.push(Coord(curr.r(), curr.c()-1));
            //cout << "west " << curr.r() << " " << curr.c()-1 << endl;
            maze[curr.r()][curr.c()-1] = '!';
        }
        
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
        "X........X",
        "XXXXXXXXXX",
    };
    //if (pathExists(maze2, 3,10, 1,1, 1,7))
    if (pathExists(maze, 10,10, 6,4, 1,1))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}
