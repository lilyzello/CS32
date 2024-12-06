#include <iostream>
#include "Game.h"
#include <cassert>
#include <vector>
using namespace std;

int main(){
//    //TESTING Board Member Functions
//    Board b(6, 4);
//    Board b2(-2, -1); //negative wholes, negative beans
//    HumanPlayer P1("P1");
//    HumanPlayer P2("P2");
//    Side endside = NORTH;
//    int endhole = 5;
//    assert(b.holes() == 6);
//    assert(b2.holes() == 1); //not positive holes should -> one hole
//    assert(b.beans(NORTH, 1) == 4);
//    assert(b.beans(SOUTH, 1) == 4);
//    assert(b2.beans(NORTH, 1) == 0); //negative beans should -> zero beans per hole
//    assert(b.beans(NORTH, 0) == 0); //checking pot values
//    assert(b.beans(SOUTH, 0) == 0);
//    assert(b.beans(SOUTH, -2) == -1); //invalid hole number
//    assert(b.beans(SOUTH, 10) == -1); //invalid hole number
//    assert(b.beansInPlay(NORTH) == 24);
//    assert(b.beansInPlay(SOUTH) == 24);
//    assert(b.totalBeans() == 48);
//    assert(b.sow(NORTH, 0, endside, endhole) == false); //cannot pickup from pot
//    assert(endside == NORTH && endhole == 5); //if sow returns false, enside and endhole should not change
//    assert(b.sow(SOUTH, 1, endside, endhole) == true);
//    assert(b.beans(SOUTH, 1) == 0); //should be empty after pickup
//    assert(b.beans(SOUTH, 2) == 5 && b.beans(SOUTH, 3) == 5 && b.beans(SOUTH, 4) == 5 && b.beans(SOUTH, 5) == 5 && b.beans(SOUTH, 6) == 4); //ensure beans are distributed correctly
//    assert(endside == SOUTH && endhole == 5);
//    assert(b.sow(SOUTH, 1, endside, endhole) == false); //can't pickup from empty hole
//    assert(b.sow(SOUTH, 6, endside, endhole) == true);
//    assert(b.beans(SOUTH, POT) == 1);
//    assert(b.beans(NORTH, 6) == 5 && b.beans(NORTH, 5) == 5 && b.beans(NORTH, 4) == 5 && b.beans(NORTH, 3) == 4); //ensure sow moves correctly from one side to another
//    Board b3(4, 6);
//    assert(b3.sow(SOUTH, 4, endside, endhole) == true);
//    assert(endside == SOUTH && endhole == 1); //ensure sow works correctly when passing around board more than once (like from SOUTH->NORTH->SOUTH in one turn
//    assert(b3.beans(NORTH, POT) == 0); //ensure no beans in NORTH's pot when SOUTH's turn
//    assert(b3.beansInPlay(SOUTH) == 7+6+6+0); //ensure pot beans are not included in count
//    assert(b3.totalBeans() == 48); //ensure beans in pot included in total count
//    assert(b3.moveToPot(SOUTH, 0, NORTH) == false);
//    assert(b3.moveToPot(SOUTH, -4, NORTH) == false);
//    assert(b3.moveToPot(NORTH, 1, SOUTH) == true);
//    assert(b3.beans(NORTH, 1) == 0); //ensure beans are removed
//    assert(b3.beans(SOUTH, POT) == 1+7); //ensure pot bean number is updated correctly
//    assert(b3.totalBeans() == 48);
//    assert(b3.setBeans(NORTH, -2, 3) == false); //invalid hole number
//    assert(b3.setBeans(NORTH, 1, -2) == false); //invalid bean number
//    assert(b3.setBeans(NORTH, 1, 4) == true);
//    assert(b3.beans(NORTH, 1) == 4);
//    assert(b3.totalBeans() == 48+4); //makes sure bean count is updated
//
//    //TESTING HumanPlayer and BadPlayer
//    Board b(6, 4);
//    Board b2(3, 0);
//    //Player p1("Jenny"); //Player is ABC, should not build
//    HumanPlayer P1("P1");
//    BadPlayer P2("P2");
//    assert(P1.name() == "P1"); //testing name function
//    assert(P2.name() == "P2");
//    assert(P1.isInteractive());
//    assert(P1.chooseMove(b, NORTH) == 5); //enter 10 first, make sure user is reprompted
//                                          //then enter 5. function should return 5
//    assert(P1.chooseMove(b2, NORTH) == -1); //ensure function returns -1 if no moves possible
//    b.setBeans(NORTH, 5, 0);
//    P1.chooseMove(b, NORTH); //ensure user is reprompted if user enters hole num w no beans
//    assert(!P2.isInteractive()); //BadPlayer is not interactive
//    assert(P2.chooseMove(b, NORTH) == 1); //BadPlayer always chooses hole #1 unless empty
//    b.setBeans(NORTH, 1, 0);
//    assert(P2.chooseMove(b, NORTH) == 2); //if hole #1 is empty, chooses hole 2
//
//    //TESTING Game member functions
//    Board b(6, 4);
//    BadPlayer P1("NORTH");
//    BadPlayer P2("SOUTH");
//    Game test(b, &P2, &P1);
//    test.display(); //ensure board is displayed correct visually
//                    //should have NORTH name at top, SOUTH name at bottom, pot numbers on each side
//                    //should have six holes, each with 4 beans
//    test.move(NORTH);
//    assert(test.beans(NORTH, 1) == 0); //Bad Player chooses hole 1, beans should be empty after
//    test.display(); //board should display
//                    //should output "NORTH chooses hole 1"
//                    //should display updated board
//    //test.play();
//    //check that user is prompted to press enter to continue every SOUTH then NORTH turn
//    Board b2(6, 0);
//    Game test2(b2, &P2, &P1);
//    test2.play();
//    //Should output:
//    //SOUTH has no beans left to sow.
//    //Sweeping remaining beans into NORTH's pot
//    //     NORTH
//    //  0  0  0  0  0  0
//    //0                  0
//    //  0  0  0  0  0  0
//    //     SOUTH
//    //The game resulted in a tie.
//    b2.setBeans(NORTH, 1, 4);
//    Game test3(b2, &P2, &P1);
//    test3.play();
//    //Should output:
//    //SOUTH has no beans left to sow.
//    //Sweeping remaining beans into NORTH's pot
//    //     NORTH
//    //  0  0  0  0  0  0
//    //4                  0
//    //  0  0  0  0  0  0
//    //     SOUTH
//    //The winner is NORTH.
//    //this ensures that sweep function works correctly when South's turn begins w no beans
//    Game test4(b2, &P2, &P1);
//    test4.display();
//    assert(test4.move(SOUTH) == false); //testing move function
//                                        //should return false when player cannot complete turn (i.e has no beans)
//    assert(test4.beans(NORTH, 0) == 4); //ensure sweep works correctly
//    bool over;
//    bool hasWinner;
//    Side winner;
//    test4.status(over, hasWinner, winner);
//    assert(over); //ensure status correctly sets over when game is over
//    assert(hasWinner); //ensure hasWinner is true if game has winner
//    assert(winner == NORTH); //ensure status sets winner to side w more beans
//    Board b3(6,0);
//    b3.setBeans(NORTH, 1, 1);
//    b3.setBeans(SOUTH, 0, 1);
//    Game test5(b3, &P2, &P1); //setting up tie game
//    test5.move(NORTH);
//    //     NORTH
//    //  0  0  0  0  0  0
//    //1                  1
//    //  0  0  0  0  0  0
//    //     SOUTH
//    test5.status(over, hasWinner, winner);
//    assert(over);
//    assert(!hasWinner); //ensure hasWinner is false if game is a tie
//    assert(winner == NORTH); //ensure winner is unchanged if tie
//    b3.setBeans(NORTH, 2, 1);
//    Game test6(b3, &P2, &P1);
//    test6.move(NORTH);
//    test6.status(over, hasWinner, winner);
//    assert(!over); //ensure over is false if game is not over
//
//
//    //Testing copy constructors and assignment operators for Board and Game
//    BadPlayer P3("Player 1");
//    BadPlayer P4("Player 2");
//    Board b(6, 5);
//    Board b2(6, 4);
//    Game test4(b2, &P3, &P4);
//    b2=b;
//    assert(b.totalBeans()==b2.totalBeans());
//    Game test5(b2, &P3, &P4);
//    assert(test5.beans(NORTH,1) == 5);
//    Board b3(b2);
//    assert(b3.totalBeans()==b2.totalBeans());
//    Game test6(b3, &P3, &P4);
//    test6=test4;
//    assert(test6.beans(NORTH, 1) == test4.beans(NORTH, 1));
//    Game test7(test6);
//    assert(test7.beans(NORTH, 1) == test6.beans(NORTH, 1));
//
//    Board b(3,1);
//    Side s = NORTH;
//    vector<int> legalMoves;
//    for(int hole = 1; hole<=b.holes(); hole++){
//        if(b.beans(s, hole) > 0)
//            legalMoves.push_back(hole);
//    }
//
//    Board temp = b;
//    Side endSide = NORTH;
//    int endHole = -1;
//    Node curr(b);
//    BadPlayer P1("NORTH");
//                  BadPlayer P2("SOUTH");
//    Game test(b, &P2, &P1);
//    test.display();
//    for(int i = 0; i<legalMoves.size(); i++){
//        Board temp2 = b;
//        temp2.sow(s, legalMoves[i], endSide, endHole);
//        curr.moves.push_back(new Node(temp2));
//    }
//    legalMoves.clear();
//    for(int i = 0; i<curr.moves.size(); i++){
//        cout << "Board #" << i+1 << endl;
//        Board b2 = (curr.moves[i])->board;
//        Game test2(b2, &P2, &P1);
//        test2.display();
//        //delete curr.moves[i];
//    } //first move
//    //second move
//    Board currB = (curr.moves[0])->board;
//    for(int hole = 1; hole<=b.holes(); hole++){
//        if(b.beans(opponent(s), hole) > 0)
//            legalMoves.push_back(hole);
//    }
//    cout << legalMoves.size() << endl;
//    for(int i = 0; i<legalMoves.size(); i++){
//        Board temp2 = currB;
//        temp2.sow(opponent(s), legalMoves[i], endSide, endHole);
//        Game test2(temp2, &P2, &P1);
//        cout << "move #" << i+1 << endl;
//        test2.display();
////        (curr.moves[i])->moves.push_back(new Node(temp2));
//    }
////    legalMoves.clear();
////    for(int i = 0; i<(curr.moves[0])->moves.size(); i++){
////        cout << "Board #" << i+1 << endl;
////        Board b2 = (curr.moves[0])->moves[i]->board;
////        Game test2(b2, &P2, &P1);
////        test2.display();
////        //delete curr.moves[i];
////    }
////
//    for(int i = 0; i<curr.moves.size(); i++)
//        delete curr.moves[i];
////    for(int i = 0; i<(curr.moves[0])->moves.size(); i++)
////        delete (curr.moves[0])->moves[i];

//To test the SmartPlayer, I created various games and evaluated the choices that the smart player made. If the move resulted in a win, I considered that to be a Smart move. If the move put more beans in the SmartPlayer's pot, I considered that a smart move. Here are some of the boards I created:
    Board b(6,4);
    Board b2(5,4);
    Board b3(4,3);
    Board b4(3,4);
    Board b5(3,2);
    Board b6(3,0);
    b6.setBeans(SOUTH, 3, 1);
    b6.setBeans(SOUTH, 2, 1);
    b6.setBeans(NORTH, 3, 1);
    SmartPlayer Smart("smart");
    BadPlayer Bad("bad");
    Game testA(b, &Bad, &Smart);
    Game testB(b, &Smart, &Bad);
    Game test2A(b, &Bad, &Smart);
    Game test2B(b, &Smart, &Bad);
    Game test3A(b, &Bad, &Smart);
    Game test3B(b, &Smart, &Bad);
    Game test4A(b, &Bad, &Smart);
    Game test4B(b, &Smart, &Bad);
    Game test5A(b, &Bad, &Smart);
    Game test5B(b, &Smart, &Bad);
    Game test6A(b, &Bad, &Smart);
    Game test6B(b, &Smart, &Bad);
    testA.play();
}
