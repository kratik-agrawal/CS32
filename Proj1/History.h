//
//  History.h
//  Proj1
//
//  Created by Kratik Agrawal on 1/10/21.
//

#ifndef History_h
#define History_h

#include "globals.h"

class History
{
    public:
        History(int nRows, int nCols);
        bool record(int r, int c);
        void display() const;
    private:
        int m_rows;
        int m_cols;
        int  m_grid[MAXROWS][MAXCOLS];
        
};


#endif /* History_h */
