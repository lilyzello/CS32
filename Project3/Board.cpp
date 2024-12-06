#include <iostream>
using namespace std;
#include "Board.h"
#include <vector>

Board::Board(int nHoles, int nInitialBeansPerHole){
    //Construct a Board with the indicated number of holes per side (not counting the pot) and initial number of beans per hole. If nHoles is not positive, act as if it were 1; if nInitialBeansPerHole is negative, act as if it were 0.
    vector<int> North_Holes;
    vector<int> South_Holes;
    North_Holes.push_back(POT); //first item in each vector will be pot amount (0)
    South_Holes.push_back(POT);
    if(nHoles<=0) //not positive includes 0
        m_nHoles = 1;
    else(m_nHoles = nHoles);
    if(nInitialBeansPerHole<0)
        m_nInitialBeansPerHole = 0;
    else(m_nInitialBeansPerHole = nInitialBeansPerHole);
    for(int i = 1; i <= nHoles; i++){
        North_Holes.push_back(m_nInitialBeansPerHole);
        South_Holes.push_back(m_nInitialBeansPerHole);
    }
    m_Board[NORTH] = North_Holes;
    m_Board[SOUTH] = South_Holes;
}

int Board::holes() const{
    //Return the number of holes on a side (not counting the pot).
    return m_nHoles;
}

int Board::beans(Side s, int hole) const{
    //Return the number of beans in the indicated hole or pot, or −1 if the hole number is invalid.
    if(hole>m_nHoles || hole<0)
        return -1;
    return m_Board[s][hole];
}

int Board::beansInPlay(Side s) const{
    //Return the total number of beans in all the holes on the indicated side, not counting the beans in the pot.
    int total = 0;
    for(int i = 1; i<=m_nHoles; i++){
        total += m_Board[s][i];
    }
    return total;
}

int Board::totalBeans() const{
    //Return the total number of beans in the game, including any in the pots.
    int total = 0;
    for(int i = 0; i<=m_nHoles; i++){
        total += m_Board[NORTH][i];
        total += m_Board[SOUTH][i];
    }
    return total;
}

bool Board::sow(Side s, int hole, Side& endSide, int& endHole){
    //If the hole indicated by (s,hole) is empty or invalid or a pot, this function returns false without changing anything. Otherwise, it will return true after sowing the beans: the beans are removed from hole (s,hole) and sown counterclockwise, including s's pot if encountered, but skipping s's opponent's pot. The function sets the parameters endSide and endHole to the side and hole where the last bean was placed. (This function does not make captures or multiple turns; different Kalah variants have different rules about these issues, so dealing with them should not be the responsibility of the Board class.)
    if(beans(s, hole) <= 0 || hole == 0) //if empty, invalid, or a pot
        return false;
    int pickup = beans(s, hole);
    m_Board[s][hole] -= pickup; //pickup the beans from the hole (set it = 0)
    Side currentSide = s;
    while(pickup > 0){ 
        if(currentSide == NORTH){
            for(int i = hole-1; i>0 && pickup > 0; i--){
                m_Board[NORTH][i] += 1;
                lastMove(pickup, currentSide, i, endSide, endHole); //if last move, set endSide and endHole
                pickup--;
            }
            if(s == NORTH && pickup > 0){ //will only deposit in north's pot when its north's turn
                m_Board[NORTH][POT] += 1;
                lastMove(pickup, currentSide, 0, endSide, endHole);
                pickup--;
            }
            currentSide = SOUTH;
            hole = 0;
        }
        if(currentSide == SOUTH && pickup > 0){
            for(int i = hole+1; i<=m_nHoles && pickup > 0; i++){
                m_Board[SOUTH][i] += 1;
                lastMove(pickup, currentSide, i, endSide, endHole);
                pickup--;
            }
            if(s == SOUTH && pickup > 0){
                m_Board[SOUTH][POT] += 1;
                lastMove(pickup, currentSide, 0, endSide, endHole);
                pickup--;
            }
            currentSide = NORTH;
            hole = m_nHoles+1;
        }
    }//lots of redundant code, need a way to simplify all this
    return true;
}

bool Board::moveToPot(Side s, int hole, Side potOwner){
    //If the indicated hole is invalid or a pot, return false without changing anything. Otherwise, move all the beans in hole (s,hole) into the pot belonging to potOwner and return true.
    if(hole < 1)
        return false;
    int num_beans = beans(s, hole);
    m_Board[s][hole] -= num_beans;
    m_Board[potOwner][POT] += num_beans;
    return true;
}

bool Board::setBeans(Side s, int hole, int beans){
    //If the indicated hole is invalid or beans is negative, this function returns false without changing anything. Otherwise, it will return true after setting the number of beans in the indicated hole or pot to the value of the third parameter. (This could change what beansInPlay and totalBeans return if they are called later.) This function exists solely so that we and you can more easily test your program: None of your code that implements the member functions of any class is allowed to call this function directly or indirectly. (We'll show an example of its use below.)
    if(Board::beans(s, hole) < 0 || beans < 0)
        return false;
    m_Board[s][hole] = beans;
    return true;
}

Board::Board(const Board& b){ //i think this is way extra work but idk how else to do it rn
    m_nHoles = b.m_nHoles;
    m_nInitialBeansPerHole = b.m_nInitialBeansPerHole;
    vector<int> North_Holes;
    vector<int> South_Holes;
    for(int i = 0; i < b.m_Board[NORTH].size(); i++){
        North_Holes.push_back(b.m_Board[NORTH][i]);
        South_Holes.push_back(b.m_Board[SOUTH][i]);
    }
    m_Board[NORTH] = North_Holes;
    m_Board[SOUTH] = South_Holes;
}

void Board::lastMove(int pickup, Side currSide, int currPos, Side& endSide, int& endHole){
    if(pickup == 1){
        endSide = currSide;
        endHole = currPos;
    }
    return;
}

Board& Board::operator=(const Board& other) {
    if (this == &other) {
        // Self-assignment check
        return *this;
    }

    m_nHoles = other.m_nHoles;
    m_nInitialBeansPerHole = other.m_nInitialBeansPerHole;

    for (int i = 0; i <= m_nHoles; i++) {
        m_Board[NORTH][i] = other.m_Board[NORTH][i];
        m_Board[SOUTH][i] = other.m_Board[SOUTH][i];
    }

    return *this;
}
