#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
#include <cctype>
using namespace std;
#include "globals.h"

#ifndef History_h
#define History_h

class History
{
    public:
        History(int nRows, int nCols);
        bool record(int r, int c);
        void display() const;
    
    private:
        int m_rows;
        int m_cols;
        char m_history[MAXROWS][MAXCOLS];
    
};

#endif /* History_h */
