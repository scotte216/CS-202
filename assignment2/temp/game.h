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

class base_game
{
    public:
        base_game(); //default constructor
        virtual ~base_game(); //default destructor
        
        virtual void display_help(){}; //displays the text for the help
        virtual int run(){}; // runs the main loop for parsing user input
        virtual int resume(){};
        virtual int input(){};
        
        void setup(); // sets up the game map and problems.
        void setup_adjacencies();
        void display_intro(); //displays the intro text.
        int prompt(); // prompts the user for input

    protected:
        map my_map; // game map
        contents inventory; // user's inventory. Collect items by solving 
                            //problems in each room. 
        int score; // player's score
};


class single_game:public base_game
{
    public:
        single_game(); //default constructor
        ~single_game(); //default destructor
        
        void display_help(); //displays the text for the help
        int run(); // runs the main loop for parsing user input
        int resume();
        int input();
        
        void display_goodbye(); // displays the farewell text.

};

class multi_game:public base_game
{
    public:
        multi_game(); //default constructor
        ~multi_game(); //default destructor
        void display_help(); //displays the text for the help
        int run(); // runs the main loop for parsing user input
        int resume();
        int input();

        bool are_you_sure();
        void display_score();
        void display_inventory();

    protected:
        int num_actions;
};

