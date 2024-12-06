#include <iostream>
using namespace std;
#include "Game.h"

//add a data member that move changes that status can then call

Game::Game(const Board& b, Player* south, Player* north) : m_board(b), m_South(south), m_North(north){
    //Construct a Game to be played with the indicated players on a copy of the board b. The player on the south side always moves first.
    isOver = false;
}

void Game::display() const{
    //Display the game's board in a manner of your choosing, provided you show the names of the players and a reasonable representation of the state of the board.
    cout << "     " << m_North->name() << endl;
    for(int i = 1; i <= m_board.holes() ; i++){
        cout << "  " << m_board.beans(NORTH, i); 
    }
    cout << endl;
    cout << m_board.beans(NORTH, 0);
    for(int i = 1; i <= m_board.holes(); i++)
        cout << "   ";
    cout << m_board.beans(SOUTH, 0) << endl;
    for(int i = 1; i <= m_board.holes() ; i++){
        cout << "  " << m_board.beans(SOUTH, i);
    }
    cout << endl;
    cout << "     " << m_South->name() << endl;
}

void Game::status(bool& over, bool& hasWinner, Side& winner) const{
    //If the game is over (i.e., the move member function has been called and returned false), set over to true; otherwise, set over to false and do not change anything else. If the game is over, set hasWinner to true if the game has a winner, or false if it resulted in a tie. If hasWinner is set to false, leave winner unchanged; otherwise, set it to the winning side.
    if(isOver){
        over = true;      
        if(m_board.beans(NORTH,0)!=m_board.beans(SOUTH,0)){
            hasWinner = true;
            winner = m_board.beans(NORTH,0)>m_board.beans(SOUTH,0) ? NORTH : SOUTH;
        }else{hasWinner = false;}
    }else{
        over = false;
    }
}

bool Game::move(Side s){
    // Attempt to make a complete move for the player playing side s. "Complete" means that the player sows the seeds from a hole and takes any additional turns required or completes a capture. Whenever the player gets an additional turn, you should display the board so someone looking at the screen can follow what's happening. If the move can be completed, return true; if not, because the move is not yet completed but side s has no holes with beans to pick up and sow, sweep any beans in s's opponent's holes into that opponent's pot and return false.
    Side endSide = SOUTH;
    int endHole = 0;
    bool check = false;
    Player* player = (s==NORTH) ? m_North : m_South;
    Player* opp = (s==NORTH) ? m_South : m_North;
    isOver = false;
    while(endHole == 0){
        if(m_board.beansInPlay(s) == 0){
            cout << player->name() << " has no beans left to sow." << endl;
            cout << "Sweeping remaining beans into " << opp->name() << "'s pot" << endl;
            vector<int> oppBeans;
            for(int i = 1; i <= m_board.holes() ; i++){
                if(m_board.beans(opponent(s), i) > 0)
                    oppBeans.push_back(i);
            }
            for(size_t i = 0; i<oppBeans.size(); i++)
                m_board.moveToPot(opponent(s), oppBeans.at(i), opponent(s));
            isOver = true;
            return false;
        }
        
        if(!check)
            display();
        int move = player->chooseMove(m_board, s);
        if(!player->isInteractive())
            cout << player->name() << " chooses hole " << move << endl;
        m_board.sow(s, move, endSide, endHole);
        if(endHole == 0){
            display();
            cout << player->name() << " gets another turn." << endl;
            check = true;
        }
        if(endHole != 0 && endSide == s && m_board.beans(s, endHole) == 1 && m_board.beans(opponent(s), endHole) != 0){ //capture
            m_board.moveToPot(s, endHole, s);
            m_board.moveToPot(opponent(s), endHole, s);
        }
    }
    if(m_board.beansInPlay(s) == 0 && m_board.beansInPlay(opponent(s)) == 0){
        isOver = true;
        return false;
    }
    return true;
}

void Game::play(){
    //Play the game. Display the progress of the game in a manner of your choosing, provided that someone looking at the screen can follow what's happening. If neither player is interactive, then to keep the display from quickly scrolling through the whole game, it would be reasonable periodically to prompt the viewer to press ENTER to continue and not proceed until ENTER is pressed. (The ignore function for input streams is useful here.) Announce the winner at the end of the game. You can apportion to your liking the responsibility for displaying the board between this function and the move function.
    Side winner = NORTH; //this is not neccessary to initialize, just doing it to get rid of warning
    bool over = false;
    bool hasWinner = false;
    string Continue = "";
    while(!over){
        move(SOUTH);
        status(over, hasWinner, winner);
        if(isOver)
            break;
        move(NORTH);
        status(over, hasWinner, winner);
        if(!m_North->isInteractive() && !m_South->isInteractive()){
            cout << "Press enter to continue ";
            cin.ignore(100000, '\n');
        }
    }
    display();
        if(hasWinner){
            Player* Winner = winner == NORTH ? m_North : m_South;
            cout << "The winner is " << Winner->name() << "." << endl;
        }
        else{cout << "The game resulted in a tie." << endl;}
}

int Game::beans(Side s, int hole) const{
    return m_board.Board::beans(s, hole);
}
