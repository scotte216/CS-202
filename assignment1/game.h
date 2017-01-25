// Scott Ewing
// CS 202
// Assignment 1
//
// filename: game.h
//
// The Game object is the main work-horse of the assignment. It HAS A map and
// HAS A inventory.
#include "attributes.h"
#include "map.h"
#include "room.h"
#include "problem.h"
#include "contents.h"

class game
{
    public:
        game(); //default constructor
        ~game(); //default destructor
        void setup(); // sets up the game map and problems.
        int prompt(); // prompts the user for input
        void display_help(); //displays the text for the help
        void display_intro(); //displays the intro text.
        void display_goodbye(); // displays the farewell text.
        void run(); // runs the main loop for parsing user input

    protected:
        map my_map; // game map
        contents inventory; // user's inventory. Collect items by solving 
                            //problems in each room. 
        int score; // player's score
};


