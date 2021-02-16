//
//  History.cpp
//  Proj1
//
//  Created by Kratik Agrawal on 1/10/21.
//



#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
#include <stdio.h>

#include "History.h"
#include "globals.h"


using namespace std;


///////////////////////////////////////////////////////////////////////////
//  History implementations
///////////////////////////////////////////////////////////////////////////


History::History(int nRows, int nCols): m_rows(nRows), m_cols(nCols)
{
    for (int r = 0; r < nRows; r++)
        for (int c = 0; c < nCols; c++)
            m_grid[r][c] = 0;
}


bool History::record(int r, int c){
    if(r < 1 || r > m_rows || c < 1 || c > m_cols){
        return false;
    }
    m_grid[r-1][c-1]++;
    return true;
}




void History::display() const{
    clearScreen();
    char dis[MAXROWS][MAXCOLS];
    int r, c;
    
        // Fill the grid with dots
    for (r = 0; r < m_rows; r++){
        for (c = 0; c < m_cols; c++){
            if(m_grid[r][c] == 0){
                dis[r][c] = '.';
            } else if(m_grid[r][c] < 26){
                dis[r][c] = 'A' + m_grid[r][c]-1;
            } else{
                dis[r][c] = 'Z';
            }
        }
    }

    
    
    
    for (r = 0; r < m_rows; r++)
    {
        for (c = 0; c < m_cols; c++)
            cout << dis[r][c];
        cout << endl;
    }
    cout << endl;
    
}
