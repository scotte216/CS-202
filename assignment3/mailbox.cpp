// Scott Ewing
// CS 202
// Assignment 3
//
// filename: mailbox.cpp
//
// This is simple client program to run assignment 3.
#include "mailbox.h"

using namespace std;

//Our default constructor creates three trees with the given names for this
//assignment.
mailbox::mailbox():fb_tree("Facebook messages"),text_tree("Text messages"),email_tree("Email meessages")
{
}

//Destructor doesn't need to deallocate any dynamic memory.
mailbox::~mailbox()
{
}


//The main run function of our client. 
void mailbox::run()
{
    cout << "\nYou have new messages!\n";
    int menu;

    //Load messages from text files.
    if (!load_items(fb_tree, "msg_file_facebook.txt",0))
        cout << "Error loading file.\n";

    if (!load_items(text_tree, "msg_file_text.txt",1))
        cout << "Error loading file.\n";

    if (!load_items(email_tree, "msg_file_email.txt",2))
        cout << "Error loading file.\n";
 
    
    //Display main menu and determine responses.
    menu = display_main_menu();

    while ( menu != 5)
    {
        //read facebook messages
        if ( menu == 1)
        {
            cout << "Menu 1 selected.";
            fb_tree.read_menu();
        }
        //read text messages
        else if ( menu == 2)
        {
            cout << "Menu 2 selected.";
            text_tree.read_menu();
        }
        //read emails
        else if ( menu == 3)
        {
            cout << "Menu 3 selected.";
            email_tree.read_menu();
        }
        //send a message
        else if (menu == 4)
        {
            cout << "Menu 4 selected.";
            int send = send_menu();

            //Send a Facebook message
            //Uses the dynamic binding of to_sent to properly compose the new
            //message for each type (facebook, text, email)
            if (send == 1)
            {
                message * to_send = new facebook;
                to_send->compose();
                
                node temp_node(*to_send);
                
                fb_tree += temp_node;

                delete to_send;                
            }
            //send a text message
            else if (send == 2)
            {
                message * to_send = new text;
                to_send->compose();
                
                node temp_node(*to_send);
                
                text_tree += temp_node;

                delete to_send;                
            }
            //send an email
            else if (send == 3)
            {
                message * to_send = new email;
                to_send->compose();
                
                node temp_node(*to_send);
                
                email_tree += temp_node;

                delete to_send;                
            }
            //else cancel
        }

        menu = display_main_menu();
    }

    cout << "\nThanks for using the system!\n";
    
}

//Again function to return 'true' with 'Y' and false with any other input. 
bool mailbox::again()
{
    char response;

    cout << "\nAnother? ";
    cin >> response;
    cin.ignore(100,'\n');
    
    response = toupper(response);

    if (response == 'Y' )
        return true;
    return false; 
}



// Loads the messages from filename. Type of message is determind by type:
// 0 - facebook message
// 1 - texts
// 2 - emails
bool mailbox::load_items(tree & my_tree, const char * filename,int type)
{
    if (type > 2 || type < 0 ) return false;

    ////////////////
    //Load messages/
    ////////////////
    char temp_name[MAX];
    char temp_address[MAX];
    char temp_text[MAX];

    //Each message has a unique ID number. Likely a time-stamp. In our
    //simplified simulation I will just use a integer counter.
    int counter = 0;

    message * msg_ptr;

    ifstream file_in;

    file_in.open(filename);


    // Files are expected to have the format:
    // Name|address|Body of message \n
    //
    if (file_in)
    {
        //Grabs name.
        file_in.get(temp_name,MAX,'|');
        file_in.ignore(MAX,'|');
        
        while(!file_in.eof())
        {
            //Grabs the address (or phone number)
            file_in.get(temp_address,MAX,'|');
            file_in.ignore(MAX,'|');

            //Grabs the text body of the message
            file_in.get(temp_text,MAX,'\n');
            file_in.ignore(MAX,'\n');

            //Puts the temporary character arrays into our simple_string using
            //the assignment operators.
            simple_string s_name = temp_name;
            simple_string s_address = temp_address;
            simple_string s_text = temp_text;

            //Encapsulates the message into an object. Here the unique message
            //ID number is set.
            message temp(s_text,s_address,s_name,++counter);

            //Depending on the type of file being loaded, the proper message
            //pointer is allocated.
            if (type == 0)
            {
                msg_ptr = new facebook(temp);
            }
            else if (type == 1)
            {
                msg_ptr = new text(temp);
            }
            else if (type == 2)
            {
                msg_ptr = new email(temp);
            }

            //The message pointer is given to a node which uses RTTI to
            //determine the proper memory allocation.
            node temp_node(*msg_ptr);

            //The node is added to the tree with the overloaded += operator.
            my_tree += temp_node;

            //freeing up the dynamic memory used in this scope.
            delete msg_ptr;

            //prepping for the next item on the list.
            file_in.get(temp_name,MAX,'|');
            file_in.ignore(MAX,'|');
        }
        file_in.close();
        file_in.clear();
    }
    else
    {
        cout << "Error: " << filename << " not found.\n";
    }

    return true;
}


//Main menu display and gathers user response. 
int mailbox::display_main_menu()
{
    int response;

    //Notice the << overloaded to take the Tree object and display the item
    //count.
    cout << "\nPlease select from the following options:"
         << "\n1) Read your Facebook messages (" << fb_tree << ')'
         << "\n2) Read your text messages (" << text_tree << ')'
         << "\n3) Read email messages (" << email_tree << ')'
         << "\n4) Send a message"
         << "\n5) Quit\n";

    cin >> response;
    cin.ignore(MAX,'\n');

    while (response < 1 || response > 5)
    {
        cout << "Please select from one of the numbers above: ";
        cin >> response;
        cin.ignore(MAX,'\n');
    }

    return response;
    
}


//Menu to handle selection of type of message to write.
int mailbox::send_menu()
{
    int response;

    cout << "\nSince this is just a simulation, the SEND function"
         << "\nwill guide you through creating a new message."
         << "\nWhen 'sent' it will use that message as if you have"
         << "\njust received a new message."
         << "\nSo the new message will show up in your inbox in the"
         << "\nappropriate type (facebook, text, or email)."
         << "\n"
         << "\nWhat kind of message would you like to send:"
         << "\n1) Facebook"
         << "\n2) Text message"
         << "\n3) Email"
         << "\n4) Get me out of here!\n";
    
    cin >> response;
    cin.ignore(MAX,'\n');

    while (response < 1 || response > 4)
    {
        cout << "Please select from one of the numbers above: ";
        cin >> response;
        cin.ignore(MAX,'\n');
    }

    return response;
}
