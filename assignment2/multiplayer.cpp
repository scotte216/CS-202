// Scott Ewing
// CS 202
// Assignment 2
//
// Filename: multiplayer.cpp
//
// The multiplayer object HAS a game (a flexible array of pointers to games, to
// be specific). Each index in the flexible array HAS A pointer to a game.
//
#include "multiplayer.h"
using namespace std;

//default constructor
node_game::node_game()
{
    //Default array size of 5
    size = 5;
    top = 0;
    player = new base_game*[size];
    for (int i = 0; i < size; ++i) player[i] = NULL;

    next = NULL;
}

//constructor that takes a variable array size. This is the number of
//elements in an array in a given node. 
node_game::node_game(int array_size)
{
    size = array_size;
    top = 0;

    player = new base_game*[size];

    for (int i = 0; i < size; ++i) player[i] = NULL;

    next = NULL;
}

//pushes a new node to the front of the stack with the given next pointer
node_game::node_game(int array_size,node_game * next_node)
{
    size = array_size;
    top = 0;

    player = new base_game*[size];

    for (int i = 0; i < size; ++i) player[i] = NULL;

    next = next_node;
}

//node destructor
node_game::~node_game()
{
    for (int i = 0; i < size; ++i)
        if (player[i]) 
        {
            delete player[i];
            player[i] = NULL;
        }

    delete [] player;
    player = NULL;
    top = 0;
    size = 0;
    next = NULL;
}


//next pointer.
node_game * & node_game::get_next()
{
    return next;
}


//push a game to the array in this node.
int node_game::add_game()
{
    //if this node's array is full, return -1.
    if (top == size)
        return -1;

    player[top++] = new multi_game;
    return top;

}

//remove the top game from this node. 
int node_game::remove_game()
{
    //if our array is unpopulated in this node, return -1
    if (top == 0) return -1;

    delete player[--top];
    player[top] = NULL;

    return top;
}

//returns the game pointer for resuming Index player's game.
base_game * & node_game::resume(int index)
{
    return player[index];
}

//score of this node's player at index.
void node_game::score(int index)
{
    player[index]->display_score();
}

//inventory of this node's player at index. 
void node_game::display_inventory(int index)
{
    player[index]->display_inventory();
}

////////////////////
// Multiplayer class
///////////////////
//


//Constructor
multiplayer::multiplayer()
{
    array_size = 5;//default array size for each node
    num_players = 0;//Total number of players in the flexible array
    head = NULL;
    current_player = 0;//Index of the current player. This will range 
                       //from 0 to num_players-1
    num_nodes = 0;
}

//Constructor with variable number of players.
//Expected to use this one. 
multiplayer::multiplayer(int players)
{
    array_size = 5;//default array size for each node
    num_players = 0;//the adding players will properly set this
    current_player = 0;
    num_nodes = 0;
    head = NULL;//adding players properly sets this up

    //pushes num_players into the flexible array
    for (int i = 0; i < players; ++i)
        add_player();

}

//Destructor
multiplayer::~multiplayer()
{
    delete_all(head);
    array_size = 0;
    num_players = 0;
    current_player = 0;
    num_nodes = 0;
    head = NULL;
}


//deletes all nodes in the LLL
void multiplayer::delete_all(node_game * head)
{
    if (!head) return;

    node_game * temp = head;
    head = head->get_next();
    delete temp;
    delete_all(head);
}

//Pushes a new player to the stack. 
//adds a new node if necessary.
void multiplayer::add_player()
{
    if (num_players++ % 5 == 0) // we need a new node
    {
        head = new node_game(array_size,head);
        ++num_nodes;
    }

    head->add_game();
}


//Removes the top player from the stack and deletes the node if necessary
int multiplayer::remove_player()
{
    if (num_players == 0) return 0;

    --num_players;
    int result = head->remove_game();

    if (result == 0)//the first node is now empty. delete it
    {
        node_game * temp = head;
        head = head->get_next();
        delete temp;
        --num_nodes;
    }

    //if the current player was deleted, sets current back to the first;
    if (current_player >= num_players) current_player = 0;

    return 1;
}


//Returns a pointer to the current player's game. 
base_game * & multiplayer::current()
{
    // determine which node and index the current player exists in
    int current_node = current_player / array_size;
    current_node = num_nodes - current_node;

    int current_index = current_player % array_size;
    
    //traverse to the right node
    node_game * current = head;
    for (int i = 1; i < current_node; ++i)
        current = current->get_next();

    //return current node's game pointer for index 'current_index'
    return current->resume(current_index);
}

//Advance to the next player, circling back to the first if necessary.
void multiplayer::advance()
{
    //determine if we need to roll back to the first player or not
    //depending on the current index and total number of players.
    //remember index starts at 0
    if (current_player + 1 >= num_players)
        current_player = 0;
    else
        ++current_player;
}

//Header for the current player
void multiplayer::header(int num)
{
    cout << "-------------------\n"
         << "Current Player: " << num << "\n"
         << "-------------------\n\n";

}

//Execution of the a multiplayer game. 
void multiplayer::run()
{
    if (num_players > 1)
        header(current_player + 1);
    
    //result will be 1 for normal end of turn, 0 for player quitting
    //and 2 for a player winning.
    int result = current()->run();


    while ( result == 1)
    {
        if (num_players > 1)
        {   
            advance(); 
            header(current_player + 1);
        }
        result = current()->resume();
    }

    //We have a winner!
    if (result = 2)
    {
        cout << "\n\n----------------------------------------------\n"
             << "Congratulations! Player " << current_player + 1
             << " has won the game! Here are the final scores.\n\n";
    }

    display_scores();
    display_goodbye();
}


//Displays the scores for all players. 
void multiplayer::display_scores()
{
    int current_node;
    int current_index;
    for (int i = 0; i < num_players; ++i)
    {
        current_node = i / array_size;
        current_node = num_nodes - current_node;

        current_index = i % array_size;

        //traverse to the right node
        node_game * current = head;
        for (int j = 1; j < current_node; ++j)
           current = current->get_next();

        cout << "Player " << i+1 << " final score: ";
        current->score(current_index);
        cout << " out of 400. Items collected: ";
        current->display_inventory(current_index);
    }
}

//Displays the farewell message
void multiplayer::display_goodbye()
{
    cout <<"\nThanks for playing!\n";
}

