// Scott Ewing
// CS 202
// Assignment 1
//
// filename:
// attributes.cpp
// This class is used by the Rooms and Contents classes.

#include "attributes.h"
using namespace std;

// default constructor
attributes::attributes()
{
    desc = NULL;
    name = NULL;
}

//Constructor where name and desc are passed in.
attributes::attributes(const char * new_name, const char * new_desc):desc(NULL),name(NULL)
{
    set_name(new_name);
    set_desc(new_desc);
}


//constructor where an attributes object is passed in.
attributes::attributes(const attributes & to_copy):desc(NULL),name(NULL)
{
    copy(to_copy);
}


//destructor
attributes::~attributes()
{
    if (desc) delete [] desc;
    desc = NULL;

    if (name) delete [] name;
    name = NULL;
}


//Takes a given attribute 'to_copy' and copies the data contained within to
//here.
void attributes::copy(const attributes & to_copy)
{
    set_name(to_copy.name);
    set_desc(to_copy.desc);
}

//deep copies a new desc here, replacing if one exists.
void attributes::set_desc(const char * new_desc)
{
    //if there is already a desc, delete it to prevent memory leaks.
    if (desc) delete [] desc;

    //deep copy new description
    desc = new char[strlen(new_desc) + 1];
    strcpy(desc,new_desc);
}


//deep copies a new name here, replaces if one exists.
void attributes::set_name(const char * new_name)
{
    //if there is already a name, delete it 
    if (name) delete [] name;

    //deep copy the new name.
    name = new char[strlen(new_name) + 1];
    strcpy(name,new_name);

    name[0] = toupper(name[0]);
}


//display name and description
void attributes::display()
{
    cout << name << endl;
    cout << desc << endl;
}


//find if to_match matches the name in this attribute object
bool attributes::find_name(const char * to_match)
{
    bool result;

    //creates a tempory char * and deep copies so we can capitalize the first
    //letter
    char * temp = new char[strlen(to_match)+1];
    strcpy(temp,to_match);

    //capitalize first letter
    temp[0] = toupper(to_match[0]);
    result = !strcmp(temp,name);

    //deallocates the temporary memory
    delete [] temp;
    return result;
}


//display just the name. Useful for the room exits and items in inventory
void attributes::display_name()
{
    cout << name << endl;
}


//determines if a name has been set
bool attributes::has_name()
{
    if (!name)
        return false;
    return true;
}

