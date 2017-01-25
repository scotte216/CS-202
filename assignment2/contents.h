// Scott Ewing
// CS 202
// Assignment 2
//
// filename: contents.h
//
// The contents class makes use of attributes. Rooms and the Game class both
// HAVE contents.
//
//Changed the node from HAVING an attribute to BEING an attribute
//Able to remove several functions as a result.
//
#include "attributes.h"

#ifndef CONTENTS
#define CONTENTS


//The contents class has a doubly-linked list with this node class
class node_cont:public attributes
{
    public:
        //constructors
        node_cont();
        node_cont(attributes & item);
        node_cont(attributes & item,node_cont * & previous);
        //destructor
        ~node_cont();
//        void display();//displays the node
//        void display_name(); // displays just the name from the node
        node_cont * & get_next(); // returns the next pointer
        node_cont * & get_previous(); // returns the previous pointer
//        bool find_name(char * to_find); // matches a name to this node
        void copy_item(attributes & dest); // copies this node to the 
                                           //destination object.
    private:
//        attributes item;// Each node HAS an item which is an attribute object
        node_cont * next;//next pointer
        node_cont * previous;//previous pointer
};

// The contents class manages a doubly-linked list of node-items. Like an
// inventory.
class contents
{
    public:
        contents();//constructor
        ~contents();//destructor
        void inventory(); // displays all items in the list
        void add_item(attributes & item); // adds an attribute object to the list
        void delete_item(char * name); // finds 'name' and deletes it
        int copy_item(char * name,attributes & destination); // copies object with 
                                        //name to the destination attribute object.
        void copy_all(contents & source); //copies entire contents/inventory from 
                                          //source to here.
        void delete_all(); // delete entire list
        bool find_name(char * name); // determines if 'name' is in the list.
    protected:
        node_cont * head;//head pointer
        node_cont * tail;//tail pointer 
        void remove_all(node_cont * & head);//recursive function to remove list
        void inventory(node_cont * head); // recurisve function to display all
        void delete_item(char * name, node_cont * & head); // recursive function 
                                        // to delete a specific item with 'name'
        int copy_item(char * name, attributes & dest, node_cont *head); 
                // recursive copy of item 'name' to the destination
        void copy_all(node_cont * source);// recursive function to copy source list
        bool find_name(char * name, node_cont * head); // recursive find of 'name' 
                                                        //in the list
};

#endif
