// Scott Ewing
// CS 202
// Assignment 3
//
// Filename: mailbox.h
//
// This mailbox class is used to run the assignment, demonstrating multiple
// mailboxes.
//
// create an instance of this class and use the run() function. It will handle
// loading of messages and setting up multiple inboxes.
//
#include "avl.h"
#include "simple_string.h"
#include "message.h"
#include <fstream>


const int MAX = 200;//only used for setting up temporary char arrays before
                    //being deep copied in to dynamicly allocated char *s
class mailbox
{
    public:
        //Default constructor and destructor. No derived classes so non-virtual
        //destructor.
        mailbox();
        ~mailbox();

        //Run() is the main and only function to be used. This is the client
        //executable for this assignment.
        void run();

    protected:
        //Three trees, for facebook, texting, and email
        tree fb_tree;
        tree text_tree;
        tree email_tree;

        //simple again function. Prompts for input. Returns true if 'Y'
        bool again();

        //The loading routine to load messages from "filename" (a raw text file) 
        //into tree of type.
        //Type 0 = facebook, 1 = text, and 2 = email.
        //Return true if successful.
        bool load_items(tree & tree, const char * filename,int type);
        
        int display_main_menu();//main menu function, returns integer menu 
                                //selection
        int send_menu();//the menu for sending a message. Returns an integer
                        // menu selection.
};
