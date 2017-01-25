// Scott Ewing
// CS 202
// Assignment 3
//
// Filename: simple_string.h
//
// A simple string class for CS 202
//
// This class was made primarily so the assingment operations would function as
// desired when working with text arrays.
//
#include <iostream>
#include <cstring> //used for strcpy, strlen, strcat, and strcmp

using namespace std;

#ifndef SIMPLE_STRING
#define SIMPLE_STRING

class simple_string
{
    public:
        simple_string();
        //Create a new simple_string based on char *
        simple_string(const char *);
        //create a simple string based on an existing simple_string
        simple_string(const simple_string &);
        //destructor
        ~simple_string();

        //Copy functions using a char * and simple_string
        void copy(const char *);
        void copy(const simple_string &);

        //Assigment operators for assigning charactr arrays to the simple string
        //Both simple strings and char *s work.
        simple_string & operator = (const simple_string &);
        simple_string & operator = (const char *);

        //concatination operatoin with the +. Works with string+string,
        //string+char * and char *+string.
        simple_string operator + (const char * )const;
        simple_string operator + (const simple_string &)const;
        friend simple_string operator + (const char *, const simple_string &);

        //Concatination using the += operator, taking both char *s and
        //simple-strings
        simple_string & operator += (const char *);
        simple_string & operator += (const simple_string &);

        //comparison operators for determining equality. Works with string ==
        //string, string == char *, and char * == string. Compares with strcmp
        //function.
        bool operator == (const char *) const;
        bool operator == (const simple_string &)const;
        friend bool operator == (const char *, const simple_string &);

        //Same as above but for the != sign.
        bool operator != (const char *) const;
        bool operator != (const simple_string &)const;
        friend bool operator != (const char *, const simple_string &);


        //Ostream insertion operator for easy displaying of the simple_string
        friend ostream & operator << (ostream &, const simple_string &);

        //I could not figure out how to do the extraction operator. I would find
        //this very handy for my future work! 
        
    protected:
        //the actual text hidden inside.
        char * text;
};
#endif
