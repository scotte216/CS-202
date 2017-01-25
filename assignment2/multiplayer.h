// Scott Ewing
// CS 202
// Assignment 2
//
// Filename: multiplayer.h
//
// The multiplayer object HAS a game (a flexible array of pointers to games, to
// be specific). Each index in the flexible array HAS A pointer to a game.
//
#include "game.h"


//Each node of the flexible array has the information for each node's array
//(size, current game pointer, top game pointer, etc). Each node has an array of
//game pointers of a fixed size. 
class node_game
{

    public:
        node_game();
        node_game(int array_size);
        node_game(int array_size,node_game * next_node);//constructor to properly
                                                      //set up the next pointer.
        ~node_game();
        node_game * & get_next();//returns a next pointer
        base_game * & resume(int index);//returns a game pointer for 
                                        // resuming a player's turn.
        int add_game();
        int remove_game();
        void score(int index);//score of a game at Index
        void display_inventory(int index);//Inventory of a game at Index.

    protected:
        base_game ** player; // Array of pointers to games
        node_game * next; // pointer to next node of the flexible array
        int size;//size of the array
        int top;//top pointer to the array
};

//This class handles navigating between nodes in the LLL of arrays as well as
// adding, removing players and tracking who's turn it is. 
class multiplayer
{
    public:
        multiplayer();
        multiplayer(int players);
        ~multiplayer();
        void add_player();//push a player to list
        int remove_player();//pop a player from list
        void run();//executes multiplayer game

    protected:
        int array_size;//size of each array
        int num_players;//(Integer 1 or greater)
        node_game * head;//head to the start of the flexible array
        int current_player;//index of current player, 0 - (num_players - 1)
        void delete_all(node_game * head);//recursive function to remove all
        int num_nodes; // number of nodes in the LLL
        void advance();// advances the current player by 1
        base_game * & current();// Returns a pointer to the current player's game.
        void header(int num);//display header for current player
        void display_scores();//displays scores of all players
        void display_goodbye();//display a goodbye message
};
