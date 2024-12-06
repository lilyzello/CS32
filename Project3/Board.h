#ifndef Board_h
#define Board_h

#include <iostream>
#include <vector>
#include "Side.h"

class Board{
public:
    Board(int nHoles, int nInitialBeansPerHole);
    int holes() const;
    int beans(Side s, int hole) const;
    int beansInPlay(Side s) const;
    int totalBeans() const;
    bool sow(Side s, int hole, Side& endSide, int& endHole);
    bool moveToPot(Side s, int hole, Side potOwner);
    bool setBeans(Side s, int hole, int beans);
    Board(const Board& b);
    Board& operator=(const Board& other);
private:
    int m_nHoles;
    int m_nInitialBeansPerHole;
    std::vector<int> m_Board[NSIDES]; //array of 2 vectors
    void lastMove(int pickup, Side currSide, int currPos, Side& endSide, int& endHole);
};

#endif /* Board_h */
