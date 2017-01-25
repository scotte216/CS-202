// Scott Ewing
// CS 202
// Assignment 1
//
// filename: room.cpp
// 
// Room class, used by Map class. Contains (or HAS A) Problem object and Contents
// object

#include "room.h"

//default constructor
room::room():hidden(false),locked(false),solved(false)
{
}

//constructor with a name and description passed in.
room::room(const char * new_name, const char * new_desc):attributes(new_name,new_desc),hidden(false),locked(false),solved(false)
{
}

//constructor with a room passed in.
room::room(const room & to_copy):attributes(to_copy),hidden(false),locked(false),solved(false)
{
}

//default destructor. No dynamically allocated memory, so nothing to do here.
room::~room()
{
}

//wrapper function for content object to display it's inventory.
void room::contents()
{
    my_contents.inventory();
}


//wrapper function for contents to add an item.
void room::add_item(attributes & item)
{
    my_contents.add_item(item);
}

//wrapper for contents to remove item by name.
void room::remove_item(char * name)
{
    my_contents.delete_item(name);
}

//wrapper for contents to copy name into copy.
int room::copy_item(char * name,attributes & copy)
{
    return my_contents.copy_item(name,copy);
}

//Copy function to copy a room's details here, including copying contents and
//problems via those objects functions.
void room::copy(room & source)
{
    attributes::copy(source);
    my_contents.copy_all(source.my_contents);
    add_problem(source.my_problem);
    hidden = source.hidden;
    locked = source.locked;
    solved = false;
}

// Wrapper function for contents to remove all items.
void room::remove_all_items()
{
    my_contents.delete_all();
}

//Wrapper function for the problem object to add a problem here.
void room::add_problem(const problem & to_add)
{
    my_problem.copy_problem(to_add);
}

//Wrapper for problem object to display the math problem, if it hasn't been
//solved.
int room::display_problem()
{
    if (solved)
        return 0;
    return my_problem.display_problem();
}


//Wrapper function for the problem object to solve the problem. Sets the solved
//flag if it does. Expects a 1 for properl sovled.
int room::solve_problem(int answer)
{
    int result = my_problem.solve(answer);
    if (result == 1)
        solved = true;

    return result;
}


//Returns the hidden flag
bool room::is_hidden()
{
    return hidden;
}

//sets the hidden flag.
void room::set_hidden(bool answer)
{
    hidden = answer;
}

//Returns the locked flag.
bool room::is_locked()
{
    return locked;
}

//returns the locked flag.
void room::set_locked(bool answer)
{
    locked = answer;
}

// Collects the contents of this room into destination contents list.
void room::collect(class contents & dest)
{
   dest.copy_all(my_contents);
}
