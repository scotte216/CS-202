// Scott Ewing
// CS 202
// Assignment 2
//
// Filename: main.cpp
//
// This is the main of assignment 2. It determines the number of players, and
// then sends that information to the session, which decides how to proceed
// (Single- or multi-player game).
//  
#include "session.h"

using namespace std;

//Prototypes
int num_players();

int num_players()
{
    int num_players;
    cout << "Welcome to Math-Venture, a multiplayer game about math..."
         << "\nHow many mathventurers are playing today?"
         << "\n> ";
    cin >> num_players;
    cin.ignore(100,'\n');

    while (num_players < 1)
    {
        cout << "\nPlease enter a number of 1 or more."
             << "\n> ";
        cin >> num_players;
        cin.ignore(100,'\n');
    }

   return num_players;
}

int main()
{
    int players = num_players();    
    
    session my_game(players);
    my_game.run();
    return 0;
}

