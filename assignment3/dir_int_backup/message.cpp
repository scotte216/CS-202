#include "message.h"

message::message():data(0)
{
}

message::message(int x):data(x)
{
}

message::message(const message & msg)
{
    copy(msg);
}

message::~message()
{
    data = 0;
}

void message::copy(const message & source)
{
    data = source.data;
}

bool message::operator < (const message & msg) const
{
    return this->data < msg.data;
}

bool message::operator < (const message * msg) const
{
    return this->data < msg->data;
}

bool message::operator > (const message & msg) const
{
    return this->data > msg.data;
}

bool message::operator > (const message * msg) const
{
    return this->data > msg->data;
}

bool message::operator == (const message & msg)const
{
    return this->data == msg.data;
}

bool message::operator == (const message * msg)const
{
    return this->data == msg->data;
}

bool message::operator != (const message & msg)const
{
    return this->data != msg.data;
}

bool message::operator != (const message * msg)const
{
    return this->data != msg->data;
}

bool message::operator >= (const message & msg)const
{
    return this->data >= msg.data; 
}

bool message::operator >= (const message * msg)const
{
    return this->data >= msg->data; 
}

bool message::operator <= (const message & msg)const
{
    return this->data <= msg.data;
}

bool message::operator <= (const message * msg)const
{
    return this->data <= msg->data;
}

message & message::operator = (const message & msg)
{
    if (&msg == this) return *this;

    //if there's any data, delete it first.
    if (data) data = 0;

    data = msg.data;

    return *this;
}

ostream & operator << (ostream & out, const message & msg)
{
    out << msg.data;
}
 
