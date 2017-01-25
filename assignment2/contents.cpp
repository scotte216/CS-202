// Scott Ewing 
// CS 202
// Assignment 2
//
// filename: contents.cpp
//
//
//Changed the node from HAVING an attribute to BEING an attribute
//Able to remove several functions as a result.
#include "contents.h"

using namespace std;
//-----------
// NODE CLASS
// ----------

//default constructor
node_cont::node_cont():attributes(),next(NULL),previous(NULL)
{
}


//constructor given an item
node_cont::node_cont(attributes & item):attributes(item),previous(NULL),next(NULL)
{
}


//constructor given an item and the pointer to where the new node's 'previous'
//should be directed
node_cont::node_cont(attributes & item, node_cont * & previous):attributes(item),previous(previous),next(NULL)
{
}

//destructor
node_cont::~node_cont()
{
    next = NULL;
    previous = NULL;
}

/*
//display's item's attributes
void node_cont::display()
{
    item.display();
}

//display's name only
void node_cont::display_name()
{
    item.display_name();
}
*/

//returns the next pointer by reference, since the next data member is private.
node_cont * & node_cont::get_next()
{
    return next;
}

//returns the previous pointer by reference, since the previous data member is
//private.
node_cont * & node_cont::get_previous()
{
    return previous;
}

/*
//checks if to_find matches the item at this node.
bool node_cont::find_name(char * to_find)
{
    return item.find_name(to_find);
}
*/

//copies this node to destination attribute object
void node_cont::copy_item(attributes & dest)
{
    dest.set_name(name);
    dest.set_desc(desc);
}

//-----------------------
// CONTENTS CLASS
// ---------------------
//
//contents default constructor
contents::contents():head(NULL),tail(NULL)
{
}

//contents destructor
contents::~contents()
{
    remove_all(head);
    head = NULL;
    tail = NULL;
}

//recursive function to remove all items from the list. Used both by the
//destructor and a seperate wrapper function if needed.
void contents::remove_all(node_cont * & head)
{
    if (!head) return;

    node_cont * temp = head;
    head = head->get_next();
    delete temp;
    temp = NULL;
    remove_all(head);
}

//wrapper function to delete all of the items on the list.
void contents::delete_all()
{
    remove_all(head);
    head = NULL;
    tail = NULL;
}

//Wrapper function to display all items by name in the list.
void contents::inventory()
{
    if (!head) cout << "Nothing.\n";
    else inventory(head);
}

//Recursive function to display all items by name in the list.
void contents::inventory(node_cont * head)
{
    if (!head) return;

    head->display_name();
    head = head->get_next();
    inventory(head);
}

//Adds an item/attribute object to the list
void contents::add_item(attributes & to_add)
{
    //case 1: nothing in the list
    if (!head)
    {
        head = new node_cont(to_add);
        tail = head;
        tail->get_previous() = head;
    }
    //case 2: add at the tail
    else
    {
        //Note: this node constructor properly sets up the previous pointer to
        //point to where tail is currently pointing.
        tail->get_next() = new node_cont(to_add,tail);
        //moves the tail to the new last node, just added.
        tail = tail->get_next();
    }
}


//Wrapper function to delete an item by name.
void contents::delete_item(char * name)
{
    delete_item(name,head);
}


//recursive function to find the node with 'name'
void contents::delete_item(char * name,node_cont * & ptr)
{
    if (!ptr) return;

    //if we have a match...
    if (ptr->find_name(name))
    {
        //move our pointer alias to this node's next
        node_cont * temp = ptr;
        ptr = ptr->get_next();

        //if our pointer is now null, we removed last node
        if (!ptr)
            //so move the tail here
            tail = ptr;
        else
            //otherwise, we're not at the end and we can safely dereference ptr,
            //and properly set the previous pointer
            ptr->get_previous() = temp->get_previous();

        //delete the node
        delete temp;
    }
    //else recursively call the function again with the next node
    else
        delete_item(name,ptr->get_next());
}


//Copy a named item to a destination attribute/item object. Wrapper function
int contents::copy_item(char * name, attributes & dest)
{
    return copy_item(name,dest,head);
}

//recursive function to find item 'name' and copy it into the destination item.
int contents::copy_item(char * name, attributes & dest,node_cont * head)
{
    if (!head) return 0;

    if (head->find_name(name))
    {
        head->copy_item(dest);
        return 1;
    }
    else return copy_item(name,dest,head->get_next());
}


// Copy an entire contents list from a source to here. Wrapper function
void contents::copy_all(contents & source)
{
    copy_all(source.head);
}

//Recursive function to copy all of a source list to here. This adds the items
//to this list, if this list isn't empty to begin with. 
void contents::copy_all(node_cont * source)
{
    if (!source) return;

    attributes temp;
    source->copy_item(temp);
    add_item(temp);

    copy_all(source->get_next());
}


//Boolean function to find if object 'name' is in this list. Wrapper function.
bool contents::find_name(char * name)
{
    return find_name(name,head);
}


//recursive function to find if named object is in the list, returning true if
//so.
bool contents::find_name(char * name,node_cont * head)
{
    if (!head) return false;

    if (head->find_name(name))
        return true;
    else
        return find_name(name,head->get_next());
}
