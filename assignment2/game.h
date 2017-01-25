// Scott Ewing
// CS 202
// Assignment 2
//
// filename: game.h
//
// The Game object is the main work-horse of the assignment. It HAS A map and
// HAS A inventory. 
//
// The Base-Game class is a abstract base class. 
// It's two
// children are single_game and multi_game, the behavior of each differing,
// though using many of the same functions.
// By using pointers to the base_game, we can use dynamic binding. Specifically,
// the session class (in multiplayer.h/.cpp) determines if the game should run
// single player or multiplayer.
//
#include "attributes.h"
#include "map.h"
#include "room.h"
#include "problem.h"
#include "contents.h"
#include <fstream>


//This is the base-class for the game. It is not expected that there should be
//any base_game objects. It's pure virtual with many null-bodied functions.
//The virtual functions are ones that are different for single- or multi-player
//games. The non-virtual are used by both.
class base_game
{
    public:
        base_game(); //default constructor
        virtual ~base_game(); //default destructor
        
        virtual void display_help()=0; //displays the text for the help
        virtual int run(){}; // runs the main functions of the program
        virtual int resume(){};//resumes the game, used for multiplayer games.
        virtual int input(){};//parses the input from the user.
        virtual void display_score(){};//displays score
        virtual void display_inventory(){};//displays inventory
        
        void setup(); // sets up the game map and problems.
        void setup_adjacencies();// connects the adjacent rooms
        void display_intro(); //displays the intro text.
        int prompt(); // prompts the user for input

    protected:
        map my_map; // game map
        contents inventory; // user's inventory. Collect items by solving 
                            //problems in each room. 
        int score; // player's score
};

//this is the single-player subclass of the base_game. It is run directly for
//single player games. 
class single_game:public base_game
{
    public:
        single_game(); //default constructor
        ~single_game(); //default destructor
        
        void display_help(); //displays the text for the help
        int run(); // runs the main loop for parsing user input
        int resume();
        int input();
        
        //the following function is unique to the single-player game.
        void display_goodbye(); // displays the farewell text.

};


//This is the multiplayer subclass of the base_game. It is run through the
//multiplayer object (multiplayer.h). 
class multi_game:public base_game
{
    public:
        multi_game(); //default constructor
        ~multi_game(); //default destructor
        void display_help(); //displays the text for the help
        int run(); // runs the main loop for parsing user input
        int resume();
        int input();

        //the following functions are unique to multiplayer games.
        bool are_you_sure();
        void display_score();
        void display_inventory();

    protected:
        int num_actions;
};

