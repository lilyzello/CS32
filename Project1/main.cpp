#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
#include <cctype>
using namespace std;
#include "Game.h"
//#include "History.h"

int main()
{
      // Create a game
      // Use this instead to create a mini-game:   Game g(3, 5, 2);
    //Game g(10, 12, 40);
    Game g(3, 5, 2);
      // Play the game
    g.play();
}

