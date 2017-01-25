// Scott Ewing
// CS 202
// Assignment 3
//
// Filename: simple_string.cpp
//
// The implimentation file for the simple_string class. This lets our text
// arrays in a simple string behave more seamlessly with many common operators,
// performing deep copies where needed. 
//
#include "simple_string.h"

using namespace std;

//Default constructor.
simple_string::simple_string():text(NULL)
{
}

//Constructor which copies a char * to this simple-string
simple_string::simple_string(const char * to_copy):text(NULL)
{
    copy(to_copy);
}

//Constructor which copies another simple string here.
simple_string::simple_string(const simple_string & to_copy):text(NULL)
{
    copy(to_copy);
}


//The destructor which deallocates the memory if it exists.
simple_string::~simple_string()
{
    if (text) delete [] text;
    text = NULL;
}

//The copy function taking a char *. Performs a deep copy.
void simple_string::copy(const char * to_copy)
{
    if (text) delete [] text;
    text = new char[strlen(to_copy) + 1];
    strcpy(text,to_copy);
}

//Copy funtion taking a simple_string and deep copying.
void simple_string::copy(const simple_string & to_copy)
{
    copy(to_copy.text);
}

//Assignment operators
//These operators can be used to make the simple string behave more simply.
//It deep copies a char * or another simple string with an = sign. 
simple_string & simple_string::operator = (const simple_string & to_copy)
{
    copy(to_copy.text);
}


simple_string & simple_string::operator = (const char * to_copy)
{
    copy(to_copy);
}
//End assignent operators


//The + and += operators overloaded to concatenate text to our simple string.
simple_string simple_string::operator + (const char * to_append)const
{
    char * temp = new char[strlen(this->text) + strlen(to_append) + 1];
    strcpy(temp,this->text);
    strcat(temp,to_append);
    simple_string result(temp);

    delete [] temp;

    return result;
}

simple_string simple_string::operator + (const simple_string & to_add)const
{
    return (*this + to_add.text);
}

simple_string operator + (const char * to_append,const simple_string & a_string)
{
    simple_string temp(to_append);
    return temp + a_string;
}

simple_string & simple_string::operator += (const char * to_append)
{
    simple_string temp(*this);
    if (text) delete [] text;

    text = new char[strlen(temp.text) + strlen(to_append) + 1];
    strcpy(text,temp.text);
    strcat(text,to_append);
    
    return *this;
}

simple_string & simple_string::operator += (const simple_string & to_append)
{
    simple_string temp(*this);
    if (text) delete[] text;

    text = new char[strlen(temp.text) + strlen(to_append.text) + 1];
    strcpy(text,temp.text);
    strcat(text,to_append.text);

    return *this;
}
//////end of concatination operators


//Comparison operators
//These allow for easy comparison of strings to strings and strings to chars and
//chars to strings.

bool simple_string::operator == (const char * to_check)const
{
    return !strcmp(this->text,to_check);
}

bool simple_string::operator == (const simple_string & to_check)const
{
    return !strcmp(this->text,to_check.text);
}

bool operator == (const char * to_check,const simple_string & string_to_check)
{
    return string_to_check == to_check;
}

bool simple_string::operator != (const char * to_check)const
{
    return strcmp(this->text,to_check);
}

bool simple_string::operator != (const simple_string & to_check)const
{
    return strcmp(this->text,to_check.text);
}

bool operator != (const char * to_check,const simple_string & string_to_check)
{
    return string_to_check != to_check;
}
/// END Comparison operators

//Overloaded insertion operator for the ostream. Allows for easy displaying of
//the text in the ostream.
ostream & operator << (ostream & out, const simple_string & to_display)
{
    out << to_display.text;
}
