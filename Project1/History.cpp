#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
#include <cctype>
using namespace std;

#include "History.h"
#include "Arena.h"              //ADD COMMENTS TO THIS FILE AND .H FILE


History::History(int nRows, int nCols)
{
    m_cols = nCols;
    m_rows = nRows;
    
    for(int i = 0; i < m_rows; i++) //intialize history grid to be all 0s
    {
        for(int j = 0; j < m_cols; j++)
        {
            m_history[i][j] = 0;
        }
    }
}

bool History::record(int r, int c)
{
    if (r <= 0  ||  c <= 0  ||  r > m_rows  ||  c > m_cols) //if rows and columns are invalid
        return false;
    m_history[r-1][c-1] ++;
    return true;
}


//displays the history grid, replacing the numbers with the corresponding . or A-Z letters
void History::display() const
{
    clearScreen();

    for(int i = 0; i < m_rows; i++)
    {
        for(int j = 0; j < m_cols; j++)
        {
            switch(m_history[i][j])
            {
                default: cout << 'Z'; break;
                case 0: cout << '.'; break;
                case 1: cout << 'A'; break;
                case 2: cout << 'B'; break;
                case 3: cout << 'C'; break;
                case 4: cout << 'D'; break;
                case 5: cout << 'E'; break;
                case 6: cout << 'F'; break;
                case 7: cout << 'G'; break;
                case 8: cout << 'H'; break;
                case 9: cout << 'I'; break;
                case 10: cout << 'J'; break;
                case 11: cout << 'K'; break;
                case 12: cout << 'L'; break;
                case 13: cout << 'M'; break;
                case 14: cout << 'N'; break;
                case 15: cout << 'O'; break;
                case 16: cout << 'P'; break;
                case 17: cout << 'Q'; break;
                case 18: cout << 'R'; break;
                case 19: cout << 'S'; break;
                case 20: cout << 'T'; break;
                case 21: cout << 'U'; break;
                case 22: cout << 'V'; break;
                case 23: cout << 'W'; break;
                case 24: cout << 'X'; break;
                case 25: cout << 'Y'; break;
            }
        }
        cout << endl;
    }
    cout << endl;
}


