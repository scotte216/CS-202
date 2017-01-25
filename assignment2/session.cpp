// Scott Ewing
// CS 202
// Assignment 2
//
// Filename: session.cpp
//
////////////////
// Session Class
////////////////

#include "session.h"

using namespace std;


//default constructor. simple, but not effective to for setting # of players
//Expected to use session(int)
session::session()
{
    cout << "How many players playing? ";
    cin >> players;
    cin.ignore(100,'\n');   
}

//Constructor that takes 'num' to set the number of players. Expected
//constructor to be used. 
session::session(int num):players(num)
{
}

void session::run()
{

    //The dynamic binding is happening here: base_game is the base class for
    //single or multiplayer games with single_game and multi_game as subclasses.
    //
    // If there is 1 player, my_game is just a pointer to base-class type
    // base_game. If there are more than 1 player, then the multiplayer class
    // creates an array of base_game pointers, but when allocating it creates
    // new multi_game objects.
    //
    if (players == 1)
    {
        base_game * my_game = new single_game;
        my_game->run();
        delete my_game;
    }
    else
    {
        multiplayer * my_game = new multiplayer(players);
        my_game->run();
        delete my_game;
    }
}


