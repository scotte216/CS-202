// Scott Ewing
// CS 202
// Assignment 3
//
// Filename: simple_string.h
//
// A simple string class for CS 202
//
#include <iostream>
#include <cstring> //used for strcpy, strlen, and strcmp

using namespace std;

#ifndef SIMPLE_STRING
#define SIMPLE_STRING

class simple_string
{
    public:
        simple_string();
        simple_string(const char *);
        simple_string(const simple_string &);
        ~simple_string();
        void copy(const char *);
        void copy(const simple_string &);

        simple_string & operator = (const simple_string &);
        simple_string & operator = (const char *);

        simple_string operator + (const char * )const;
        simple_string operator + (const simple_string &)const;
        friend simple_string operator + (const char *, const simple_string &);

        simple_string & operator += (const char *);
        simple_string & operator += (const simple_string &);

        bool operator == (const char *) const;
        bool operator == (const simple_string &)const;
        friend bool operator == (const char *, const simple_string &);

        bool operator != (const char *) const;
        bool operator != (const simple_string &)const;
        friend bool operator != (const char *, const simple_string &);

        friend ostream & operator << (ostream &, const simple_string &);

        
    protected:
        char * text;
};
#endif
