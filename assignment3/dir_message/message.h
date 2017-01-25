// Scott Ewing
// CS 202
// Assignment 3
//
// Filename: message.h
//
// Interface for the base-class for the messages.
// 
#include <cstdlib>
#include <iostream>
#include <cctype>
#include <cstring>
#include "simple_string.h"

#ifndef MESSAGE
#define MESSAGE
using namespace std;
class message
{
    public:
        message();
        message(const message & );
        message(const simple_string & body,const simple_string & address,const simple_string & contact);
        virtual ~message();
        virtual void display(){};
        void copy(const message &);
        
        message & operator = (const message &);
        
        bool operator < (const message &)const;
        bool operator > (const message &)const;
        bool operator == (const message &)const;
        bool operator != (const message &)const;
        bool operator >= (const message &)const;
        bool operator <= (const message &)const;

        bool operator < (const message *)const;
        bool operator > (const message *)const;
        bool operator == (const message *)const;
        bool operator != (const message *)const;
        bool operator >= (const message *)const;
        bool operator <= (const message *)const;
        
        bool operator == (const char *)const;
        bool operator != (const char *)const;
        friend bool operator == (const char *, const message & );
        friend bool operator != (const char *, const message & );

        bool operator < (const int)const;
        bool operator > (const int)const;
        bool operator == (const int)const;
        bool operator != (const int)const;
        bool operator >= (const int)const;
        bool operator <= (const int)const;
        friend bool operator < (const int, const message&);
        friend bool operator > (const int, const message &);
        friend bool operator == (const int, const message &);
        friend bool operator != (const int, const message &);
        friend bool operator >= (const int, const message &);
        friend bool operator <= (const int, const message &);
        
        


    protected:
        simple_string body;
        simple_string address;
        simple_string contact;
        int message_ID;
};


class facebook: public message
{
    public:
        facebook();
        facebook(const facebook &);
        facebook(const simple_string &body,const simple_string &address,const simple_string &contact);
        ~facebook();
        void display();

    protected:
};

class text: public message
{
    public:
        text();
        text(const text &);
        ~text();
        void display();

    protected:

};

class email: public message
{
    public:
        email();
        email(const email&);
        ~email();
        void display();

    protected:
};

#endif
