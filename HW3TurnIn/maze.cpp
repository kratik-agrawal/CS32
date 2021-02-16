//
//  maze.cpp
//  HW3
//
//  Created by Kratik Agrawal on 2/4/21.
//



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
    //cout << sr << " " << sc << endl;
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

