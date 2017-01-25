// Scott Ewing
// CS 202
// Assignment 3
//
// Filename: message.cpp
//
// The implimentation of the message base class

#include "message.h"

using namespace std;

message::message():body(""),address(""),contact(""),message_ID(-1)
{
}

message::message(const message & to_add):message_ID(-1)
{
    copy(to_add);
}

message::message(const simple_string & a_body, const simple_string & an_address, const simple_string & a_contact)
{
    body = a_body;
    address = an_address;
    contact = a_contact;
}

message::~message()
{
    body = "";
    address = "";
    contact = "";
    message_ID = -1;
}

void message::copy(const message & to_add)
{
    body = to_add.body;
    address = to_add.address;
    contact = to_add.contact;
    message_ID = to_add.message_ID;
    
}

message & message::operator = (const message & to_add)
{
    if (&to_add == this) return *this;

    copy(to_add);

    return *this;
}

bool message::operator < (const message & msg) const
{
    return this->message_ID < msg.message_ID;
}

bool message::operator < (const message * msg) const
{
    return this->message_ID < msg->message_ID;
}

bool message::operator > (const message & msg) const
{
    return this->message_ID > msg.message_ID;
}

bool message::operator > (const message * msg) const
{
    return this->message_ID > msg->message_ID;
}

bool message::operator == (const message & msg)const
{
    return this->message_ID == msg.message_ID;
}

bool message::operator == (const message * msg)const
{
    return this->message_ID == msg->message_ID;
}

bool message::operator != (const message & msg)const
{
    return this->message_ID != msg.message_ID;
}

bool message::operator != (const message * msg)const
{
    return this->message_ID != msg->message_ID;
}

bool message::operator >= (const message & msg)const
{
    return this->message_ID >= msg.message_ID; 
}

bool message::operator >= (const message * msg)const
{
    return this->message_ID >= msg->message_ID; 
}

bool message::operator <= (const message & msg)const
{
    return this->message_ID <= msg.message_ID;
}

bool message::operator <= (const message * msg)const
{
    return this->message_ID <= msg->message_ID;
}

//Equivalency operators for checking the name
bool message::operator == (const char * name)const
{
    return this->contact == name;
}

bool message::operator != (const char * name)const
{
    return this->contact != name;
}

bool operator == (const char * name,const message & to_check)
{
    return to_check == name;
}

bool operator != (const char * name,const message & to_check)
{
    return to_check != name;
}

//Equivalency operators for checking the message_ID

bool message::operator < (const int num)const
{
    return this->message_ID < num; 
}

bool message::operator > (const int num)const
{
    return this->message_ID > num;
}

bool message::operator == (const int num)const
{
    return this->message_ID == num;
}

bool message::operator != (const int num)const
{
    return this->message_ID != num;
}

bool message::operator >= (const int num)const
{
    return this->message_ID >= num;
}

bool message::operator <= (const int num)const
{
    return this->message_ID <= num;
}

bool operator < (const int num, const message& to_check)
{
    return to_check > num;
}

bool operator > (const int num, const message & to_check)
{
    return to_check < num;
}

bool operator == (const int num, const message & to_check)
{
    return to_check == num;
}

bool operator != (const int num, const message & to_check)
{
    return to_check != num;
}

bool operator >= (const int num, const message & to_check)
{
    return to_check <= num;
}

bool operator <= (const int num, const message & to_check)
{
    return to_check >= num;
}

//------------------------------------------------
//   FACEBOOK
//


facebook::facebook():message()
{
}

facebook::facebook(const facebook & to_add):message(to_add)
{
}

facebook::facebook(const simple_string & body, const simple_string & address, const simple_string & name):message(body,address,name)
{
}

//With abstract base-classes we have to have the base-class destructor virtual
//(which it is). In this case, the derived classes have no additional dynamic
//memory, so I'm not sure if I need to implement derived-class destructors, but
//I'm doing so to be safe. 
facebook::~facebook()
{
    body = "";
    address = "";
    contact = "";
    message_ID = -1;
    
}

void facebook::display()
{
    cout << "Facebook Message:"
         << "\n-----------------"
         << "\nName: " << contact
         << "\nFacebook name: " << address
         << "\nMessage:"
         << "\n--------\n"
         << body  
         << "\n-------------------------"
         << endl;
}


