// Scott Ewing
// CS 202
// Assignment 1
//
// filename: attributes.h
//
// The attributes class is the base class, containing just a name and a
// description. The attributes are used by both the Rooms class and the Contents
// class.
//  
#include <iostream>
#include <cctype>
#include <cstring>
#include <cstdlib>

#ifndef ATTRIBUTES
#define ATTRIBUTES

class attributes
{
    public:
        //constructors
        attributes();
        attributes(const char * new_name, const char * new_desc);
        attributes(const attributes & to_copy);
        //destructor
        ~attributes();
        
        void copy(const attributes & to_copy); //copy function
        void set_desc(const char * new_desc); // setting new description
        void set_name(const char * new_name); // setting a new name
        void display(); // Displaying these attributes
        bool find_name(const char * to_match); // match a name to this attribute
        void display_name(); // display just the name
        bool has_name(); // determine if attribute has a name.

    protected:
        char * desc; // description
        char * name; // name
};

#endif
