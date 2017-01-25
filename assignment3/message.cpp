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

//Constructor which copies a message to here.
message::message(const message & to_add)
{
    copy(to_add);
}

//Constructor which takes simple_strings as arguments to construct the message.
message::message(const simple_string & a_body, const simple_string & an_address, const simple_string & a_contact,int ID)
{
    body = a_body;
    address = an_address;
    contact = a_contact;
    message_ID = ID;
}

//Constructor taking char *s to create the message. Takes advantage of the
//simple_string copy constructors.
message::message(const char * a_body, const char * an_address, const char * a_contact, int ID):body(a_body),address(an_address),contact(a_contact),message_ID(ID)
{
}

//Creates an empty message save for the ID number. Used to search for a specific
//message.
message::message(int ID)
{
    body = "";
    address = "";
    contact = "";
    message_ID = ID;
}

//Destructor to set zero-cases on variables.
message::~message()
{
    body = "";
    address = "";
    contact = "";
    message_ID = -1;
}

//copy function used by the copy constructor and the assignment operators.
//Copies a message to_add to this object
void message::copy(const message & to_add)
{
    body = to_add.body;
    address = to_add.address;
    contact = to_add.contact;
    message_ID = to_add.message_ID;
    
}


//Operator Overloading
//
//Assignment operator.
//Included are also all the comparison operators taking both message objects and
//pointers
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

//Equivalency operators for checking the name. I added these thinking of
//searching name, but never added it. Allows for the client to search if they
//want to in the future.
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
//To check via  an integer directly rather than comparing vs another object.
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

//Ostream overloaded operator so the message can be displayed in the ostream.
//NOTE this isn't ever executed directly, but I couldnt' make a virtual friend
//operator overloading. It seems to need this function even though it's never
//directly executed. The subclasses have their own versions.
ostream & operator << (ostream & out, const message & to_display)
{
    out  << "ID#: " << to_display.message_ID 
         << "\nUnidentified Message:"
         << "\nName: " << to_display.contact
         << "\nSource: " << to_display.address
         << "\nMessage:"
         << "\n--------\n"
         << to_display.body  
         << "\n-------------------------\n"
         << endl;
}

//------------------------------------------------
//   FACEBOOK
//

//These constructors create a message based on an existing facebook object 
//or message
facebook::facebook():message()
{
}

facebook::facebook(const facebook & to_add):message(to_add)
{
}

facebook::facebook(const message & to_add):message(to_add)
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

//Display function to show the message formatted for Facebook, used with dynamic
//binding.
void facebook::display()
{
    cout << "ID#: " <<message_ID 
         << "\nFacebook Message:"
         << "\nName: " << contact
         << "\nFacebook name: " << address
         << "\nMessage:"
         << "\n--------\n"
         << body  
         << "\n-------------------------\n"
         << endl;
}


//Compose function formatted for Facebook, used with dynamic binding.
void facebook::compose()
{
    char temp_name[200];
    char temp_id[200];
    char temp_text[200];

    // Each message has a unique identifier, such as a timestamp. In our simple
    // simulation, I'm randomly generating a number instead
    int msg_id_num;
    msg_id_num = rand() % 100 + 20;

    cout << "\nWho are you sending it to? ";
    cin.get(temp_name,200,'\n');
    cin.ignore(200,'\n');
    
    cout << "\nWhat is their Facebook name? ";
    cin.get(temp_id,200,'\n');
    cin.ignore(200,'\n');

    cout << "\nCompose message here: ";
    cin.get(temp_text,200,'\n');
    cin.ignore(200,'\n');

    body = temp_text;
    address = temp_id;
    contact = temp_name;
    message_ID = msg_id_num;

}

//Overloaded ostream so the client has the option of using the ostream rather
//than the display() function. 
ostream & operator << (ostream & out, const facebook & to_display)
{
    out  << "ID#: " << to_display.message_ID 
         << "\nFacebook Message:"
         << "\nName: " << to_display.contact
         << "\nFacebook name: " << to_display.address
         << "\nMessage:"
         << "\n--------\n"
         << to_display.body  
         << "\n-------------------------\n"
         << endl;
}

//-----------------------
//  Texting
//

//Same as Facebook but for texts.
text::text():message()
{
}

text::text(const text & to_add):message(to_add)
{
}

text::text(const message& to_add):message(to_add)
{
}
text::~text()
{
    body = "";
    address = "";
    contact = "";
    message_ID = -1;
}

//Display formatted for Text messages
void text::display()
{
    cout << "ID#: " << message_ID 
         << "\nText Message:"
         << "\nName: " << contact
         << "\nText number: " << address
         << "\nMessage:"
         << "\n--------\n"
         << body  
         << "\n-------------------------\n"
         << endl;
}


//New text message composition. Formatted for text messages.
void text::compose()
{
    char temp_name[200];
    char temp_id[200];
    char temp_text[200];

    // Each message has a unique identifier, such as a timestamp. In our simple
    // simulation, I'm randomly generating a number instead
    int msg_id_num;
    msg_id_num = rand() % 100 + 20;

    cout << "\nWho are you sending it to? ";
    cin.get(temp_name,200,'\n');
    cin.ignore(200,'\n');
    
    cout << "\nWhat is their phone number? ";
    cin.get(temp_id,200,'\n');
    cin.ignore(200,'\n');

    cout << "\nCompose text here: ";
    cin.get(temp_text,200,'\n');
    cin.ignore(200,'\n');

    body = temp_text;
    address = temp_id;
    contact = temp_name;
    message_ID = msg_id_num;

}

//Ostream insertion operator formatted for text messages. 
ostream & operator << (ostream & out, const text & to_display)
{
    out  << "ID#: " << to_display.message_ID 
         << "\nText Message:"
         << "\nName: " << to_display.contact
         << "\nText number: " << to_display.address
         << "\nMessage:"
         << "\n--------\n"
         << to_display.body  
         << "\n-------------------------\n"
         << endl;
}


///---------------------------
//  email
//
//See Facebook for more details.
//Similar but formatted for email
email::email():message()
{
}

email::email(const email & to_add):message(to_add)
{
}

email::email(const message & to_add):message(to_add)
{
}


email::~email()
{
    body = "";
    address = "";
    contact = "";
    message_ID = -1;
}

//Display function formatted for emails.
void email::display()
{
    cout << "ID#: " << message_ID 
         << "\nEmail Message:"
         << "\nName: " << contact
         << "\nEmail address: " << address
         << "\nMessage:"
         << "\n--------\n"
         << body  
         << "\n-------------------------\n"
         << endl;
}


//Compose function formated for emails
void email::compose()
{
    char temp_name[200];
    char temp_id[200];
    char temp_text[200];

    // Each message has a unique identifier, such as a timestamp. In our simple
    // simulation, I'm randomly generating a number instead
    int msg_id_num;
    msg_id_num = rand() % 100 + 20;

    cout << "\nWho are you sending it to? ";
    cin.get(temp_name,200,'\n');
    cin.ignore(200,'\n');
    
    cout << "\nWhat is their email address? ";
    cin.get(temp_id,200,'\n');
    cin.ignore(200,'\n');

    cout << "\nCompose message here: ";
    cin.get(temp_text,200,'\n');
    cin.ignore(200,'\n');

    body = temp_text;
    address = temp_id;
    contact = temp_name;
    message_ID = msg_id_num;

}

//OStream insertion operator formatted for emails.
ostream & operator << (ostream & out, const email & to_display)
{
    out  << "ID#: " << to_display.message_ID 
         << "\nEmail Message:"
         << "\nName: " << to_display.contact
         << "\nEmail address: " << to_display.address
         << "\nMessage:"
         << "\n--------\n"
         << to_display.body  
         << "\n-------------------------\n"
         << endl;
}


