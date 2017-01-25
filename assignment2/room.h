// Scott Ewing
// CS 202
// Assignment 2
//
// filename: room.h
//
//The Room class makes use the attributes class. Room class also HAS A Problem
//class and a Contents class.
//The room class is used by the Map class
//
#include "attributes.h"
#include "contents.h"
#include "problem.h"

#ifndef ROOM
#define ROOM

class room:public attributes
{
    public:
        //constructors
        room();
        room(const char * new_name,const char * new_desc);
        room(const room & to_copy);
        //destructor
        ~room();
        void contents(); // list contents of it's Contents object
        void add_item(attributes & item); //Adds 'item' to its contents
        void remove_item(char * name); // removes item from contents via name.
        int copy_item(char * name,attributes & copy); // copies item 'name' 
                                                     //to 'copy'
        void copy(room & source);//copies a room object to here.
        void remove_all_items(); //removes all items from contents
        void add_problem(const problem & to_add); //adds a problem to this problem
        int display_problem(); // display the problem
        int solve_problem(int answer); // solve the problem with answer
        bool is_hidden(); // is the room hidden?
        void set_hidden(bool); // set the room hidden or not
        bool is_locked(); // is the door locked?
        void set_locked(bool); // set the room locked or not
        void collect(class contents & dest); // collec the contents from this room
    protected:
        class contents my_contents;//contents of room (items to be collected)
        class problem my_problem; // problem in the room to be solved
        bool hidden; // flag for hidden room
        bool locked; // flag for locked room
        bool solved; // flag for solved problem

};

#endif
