// Scott Ewing
// CS 202
// Assignment 3
//
// Filename: message.h
//
// Interface for the base-class for the messages.
// The message is the basis for our project. The Message is an abastract base
// class used by it's children Facebook, Text, and Email. Here, the primary
// differences are how the data is displayed and how new messages are composed.
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
        //constructors
        message();
        //Taking a message object
        message(const message & );
        //taking the parts of a message object: body, adddress, contact, and ID
        //using the simple_class
        message(const simple_string & body,const simple_string & address,
                const simple_string & contact,int ID);
        //Using char *s instead of the simple_string class
        message(const char * body,const char * address,
                const char * contact,int ID);
        //Creating a message that's otherwise empty besides the unique ID
        //number. 
        message(int ID);

        //Since we're using dynamic binding, the destructor is virtual
        virtual ~message();
        //Virtual display class, bodiless
        virtual void display(){};
        //copy constructor taking a message object
        void copy(const message &);
        //virtual compose function for composing a new message. 
        virtual void compose(){};
        

        //overloaded assignment operator to deep copy a message.
        message & operator = (const message &);
        
        //Overloaded comparison operators, taking both objects and pointers, for
        //consistency and ease-of-use
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
        
        //Additional overloading for checking the name rather than unique ID
        //number. Not actually used in this assignment.
        bool operator == (const char *)const;
        bool operator != (const char *)const;
        friend bool operator == (const char *, const message & );
        friend bool operator != (const char *, const message & );

        //Since the primary comparison for this class is the ID Number, I've
        //overloaded the operators to check with integers rather than
        //exclusively needing another message. Though I actually didn't end up
        //using these... BUT THERE THERE! Works both ways message (comp) int and
        //int (comp) message
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
        
        //Overloaded friend function for outputting the message in the ostream.
        friend ostream & operator << (ostream & , const message &);
        

    protected:
        //The basics of a message: A body (the text), an address (email, phone
        //number etc), and the contact (who is it). And a unique ID number,
        //which is used for comparisons (finding exact matches). In a real
        //application this might be a timestamp.
        simple_string body;
        simple_string address;
        simple_string contact;
        int message_ID;
};


//The facebook class which will use dynamic binding for several function
class facebook: public message
{
    public:
        facebook();
        //constructor taking a facebook object
        facebook(const facebook & to_copy);
        //constructor taking a message object -- I feel like this shouldn't be
        //necessary, but for some reason I think it fixed an issue for me. I
        //can't remember any more.
        facebook(const message & to_copy);
        ~facebook();

        //Display and compose functions for the dynamic binding.
        void display();
        void compose();

        //Similar to the display function for dynamic binding.
        friend ostream & operator << (ostream & , const facebook &);

    protected:
};

//See Facebook. This is the text class to handle text messages. 
class text: public message
{
    public:
        text();
        text(const text &);
        text(const message&);
        ~text();
        void display();
        void compose();

        friend ostream & operator << (ostream & , const text &);
    protected:

};

//See Facebook class for details. It's the same but for email messages. 
class email: public message
{
    public:
        email();
        email(const email&);
        email(const message &);
        ~email();
        void display();
        void compose();

        friend ostream & operator << (ostream & , const email &);
    protected:
};

#endif
