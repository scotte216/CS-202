#include "simple_string.h"

using namespace std;


simple_string::simple_string():text(NULL)
{
}

simple_string::simple_string(const char * to_copy):text(NULL)
{
    copy(to_copy);
}

simple_string::simple_string(const simple_string & to_copy):text(NULL)
{
    copy(to_copy);
}

simple_string::~simple_string()
{
    if (text) delete [] text;
    text = NULL;
}

void simple_string::copy(const char * to_copy)
{
    if (text) delete [] text;
    text = new char[strlen(to_copy) + 1];
    strcpy(text,to_copy);
}

void simple_string::copy(const simple_string & to_copy)
{
    copy(to_copy.text);
}

simple_string & simple_string::operator = (const simple_string & to_copy)
{
    copy(to_copy.text);
}


simple_string & simple_string::operator = (const char * to_copy)
{
    copy(to_copy);
}

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

ostream & operator << (ostream & out, const simple_string & to_display)
{
    out << to_display.text;
}

