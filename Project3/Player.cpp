#include <iostream>
using namespace std;
#include "Player.h"

//-------------Player's Functions-------------
Player::Player(std::string name){
    m_name = name;
}
std::string Player::name() const{
    return m_name;
}
bool Player::isInteractive() const{
    //Return false if the player is a computer player. Return true if the player is human. Most kinds of players will be computer players.
    return false;
}

Player::~Player(){
    //Since this class is designed as a base class, it should have a virtual destructor.
}


//--------------Human Player's Functions---------------
HumanPlayer::HumanPlayer(std::string name) : Player(name) {}
bool HumanPlayer::isInteractive() const{
    return true;
}
//Every concrete class derived from this class must implement this function so that if the player were to be playing side s and had to make a move given board b, the function returns the move the player would choose. If no move is possible, return −1.
// A HumanPlayer chooses its move by prompting a person running the program for a move (reprompting if necessary until the person enters a valid hole number), and returning that choice. We will never test for a situation where the user doesn't enter an integer when prompted for a hole number. (The techniques for dealing with the issue completely correctly are a distraction to this project, and involve either a function like stoi or strtol, or the type istringstream.)
int HumanPlayer::chooseMove(const Board& b, Side s) const{
    if(b.beansInPlay(s) == 0) //if no move is possible
        return -1;
    int hole_num = -1;
    while(hole_num <= 0 || hole_num > b.holes()){
        cout << "Select a hole, " << Player::name() << ": ";
        cin >> hole_num;
        if(hole_num <=0 || hole_num > b.holes())
            cout << "The hole number must be from 1 to " << b.holes() <<"." << endl;
        if(b.beans(s, hole_num) <= 0){
            cout << "There are no beans in that hole." << endl;
            hole_num = -1; //so player is prompted to select a hole again
        }
    }
    return hole_num;
}

HumanPlayer::~HumanPlayer(){
    
}


//-------------Bad Player's Functions-------------------
// A BadPlayer is a computer player that chooses an arbitrary valid move and returns that choice. "Arbitrary" can be what you like: leftmost, nearest to pot, fewest beans, random, etc.. The point of this class is to have an easy-to-implement class that at least plays legally.
BadPlayer::BadPlayer(std::string name) : Player(name) {}
int BadPlayer::chooseMove(const Board& b, Side s) const{
    int hole_num = 1;
    while(b.beans(s, hole_num) == 0 && hole_num <= b.holes()){
        hole_num++;
    }
    return hole_num;
}
BadPlayer::~BadPlayer(){
    
}


//-------------Smart Player's Functions-----------------
//Here's your chance to shine. A SmartPlayer chooses a valid move and returns it. For any game played on a board of up to six holes per side, with up to four initial beans per hole, SmartPlayer::chooseMove must return its choice in no more than five seconds on the SEASnet Linux server lnxsrv07.seas.ucla.edu or lnxsrv09.seas.ucla.edu: (We'll give you a way of determining the time soon; until then, you can meet this requirement by limiting the depth of your game tree search or the number of game tree positions you explore to a limit you determine experimentally.) SmartPlayer::chooseMove will be worth about 15-20% of the points for this project.
SmartPlayer::SmartPlayer(std::string name) : Player(name) {}

int SmartPlayer::evaluate(Board b, Side s) const{
    int scorediff = b.beans(s, POT) - b.beans(opponent(s), POT);
        //score diff is positive if winning, negative if losing
    int value = 0;
    //if side has more than half the total beans (a majority of the beans), they've won the game
    if(b.beans(s, POT) > b.totalBeans()/2){ //change to if game is over?
        value = s == NORTH ? INT_MAX : INT_MIN;
        return value;
    }
    //if opponent has majority of the total beans, side has lost the game
    if(b.beans(opponent(s), POT) > b.totalBeans()/2){
        value = s == NORTH ? INT_MIN : INT_MAX;
        return value;
    }
    if(s==NORTH)
        value = scorediff;
        //NORTH wants as positive as possible, so +points if winning, -points if losing
    if(s==SOUTH)
        value = -scorediff;
        //SOUTH wants as negative is possible, so -points if wining, +points if losing
    
    return value; //returns 0 if no difference in beans
}


int SmartPlayer::minimax(Board b, Side s, int depth) const{
    Timer timer;
    const double timeLimit = 4.99;
    
    int score = evaluate(b, s);
    int endHole = -1;
    Side endSide;
    
    //if depth is reached or game is over
    if(depth>4 || ((b.beansInPlay(NORTH) == 0) && (b.beansInPlay(SOUTH) == 0)))
        return score;
    
    int bestVal = s == NORTH ? INT_MIN : INT_MAX;
    for (int i = 1; i <= b.holes(); i++){
        if (b.beans(s, i) > 0){
            Board temp(b);
            temp.sow(s, i, endSide, endHole);
            if(endHole == 0){
                bestVal = minimax(temp, s, depth+1); //side gets another turn
            }
            int value = minimax(temp, opponent(s), depth+1);
            
            if(endSide == s && temp.beans(s, endHole) == 1 && temp.beans(opponent(s), endHole) != 0 && endHole != 0){ //capture
                temp.moveToPot(s, endHole, s);
                temp.moveToPot(opponent(s), endHole, s);
                int added = s == NORTH ? 10 : -10;
                if(value != INT_MIN && value != INT_MAX)
                    value += added; //add extra points for a capture
            }
            if(s==NORTH)
                bestVal = max(bestVal, value);
            else{bestVal = min(bestVal, value);}
        }
        if (timer.elapsed() >= timeLimit)
            break;
    }
    return bestVal;
}


int SmartPlayer::chooseMove(const Board& b, Side s) const{
    int bestVal = s == NORTH ? -1000 : 1000;
    int bestMove = 1;
    Side endSide;
    int endHole;
    for(int i = 1; i<=b.holes(); i++){
        if(b.beans(s, i) > 0){
            Board temp(b);
            temp.sow(s, i, endSide, endHole);
            int moveVal = minimax(temp, s, 0);
            if(endHole == 0 && endSide == s){
                int added = s==NORTH ? 10 : -10;
                if(moveVal != INT_MIN && moveVal != INT_MAX)
                    moveVal += added;
            }
            if(s==NORTH){
                if(moveVal > bestVal){ //NORTH wants more positive values
                    bestMove = i;
                    bestVal = moveVal;
                }
            }
            if(s==SOUTH){
                if(moveVal < bestVal){ //SOUTH wants more negative values
                    bestMove = i;
                    bestVal = moveVal;
                }
            }
        }
    }

    while(b.beans(s, bestMove) == 0){ //if bestMove is empty hole, picks next move
        bestMove++;                   //error caused by endHole == 0
    }
    
    return bestMove;
}
