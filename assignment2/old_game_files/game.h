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
#include <fstream>

class game
{
    public:
        game(); //default constructor
        ~game(); //default destructor
        void setup(); // sets up the game map and problems.
        void setup_adjacencies();
        int prompt(); // prompts the user for input
        void display_help(); //displays the text for the help
        void display_intro(); //displays the intro text.
        int run(); // runs the main loop for parsing user input
        int resume();
        int input();
        bool are_you_sure();
        void display_score();
        void display_inventory();

    protected:
        map my_map; // game map
        contents inventory; // user's inventory. Collect items by solving 
                            //problems in each room. 
        int score; // player's score
        int num_actions;
};


