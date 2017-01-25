// Scott Ewing
// CS202
// Assignment 3
//
// Filename: avl.h
//
// This is the header file for the avl class
//
//
#include <iostream>
#include "message.h"

// The AVL Tree HAS nodes/leaves. Typically a new node is created by first
// creating a message, packaging it into a node, then handing off to the AVL
// tree which will copy and add the node to the tree. 
class node
{
    public:
        //constructors
        node();
        node(const message & to_copy);
        node(const node &);
        //destructor
        ~node();
        
        //Copy function, used by copy constructor and assignment operator
        void copy(const message & to_add);

        //Unfortunate setters and getters necessary for this node structure
        //We were instructed by Karla to construct our nodes in this way, even
        //though it's not OOD. 
        void set_left(node *&);
        void set_right(node *&);
        void set_height(int);
        node *& get_left();
        node *& get_right();
        int get_height();

        //displays a leaf's data
        void display();


        //Overloaded comparison operators. 2 version, one that compares to a
        //node and one that compares to a node *. This helps the overloaded
        //operators to perform in an expected way, regardless of the comparison
        //type/
        bool operator < (const node *) const;
        bool operator > (const node *) const;
        bool operator == (const node *) const;
        bool operator <= (const node *) const;
        bool operator >= (const node *) const;
        bool operator != (const node *) const;
        
        bool operator < (const node &) const;
        bool operator > (const node &) const;
        bool operator == (const node &) const;
        bool operator <= (const node &) const;
        bool operator >= (const node &) const;
        bool operator != (const node &) const;

        //Assignment operator, makes use of the copy function to make a deep
        //copy of a node.
        node & operator = (const node &);
        
        friend ostream & operator << (ostream & out, const node &);

    protected:
        message * data;
        //a pointer to our data. Note: all the references to data are generic 
        //enough that if you used the same interface, our data could be
        //anything. This AVL node could be used for any data type.

        int height;
        node * left;
        node * right;

};

//The AVL Class, to actually construct the tree, add and delete items, find
//items, etc. 
class avl
{
    public:
        //constructors
        avl();
        avl(const avl &);
        //destructor
        virtual ~avl();

        //Functions
        void display_all();//wrapper function to display all items in a tree
        bool insert(const node &);//Function to insert a node into the tree. 
                                 //Returns true if successful
        void copy_all(node * & destination)const;//wrapper function to copy all
        bool find_entry(const node & key);//wrapper function to find a specific 
                                         //entry in the tree based on a key 
                                         // encapsulated in a node. Return true
                                         // if successful
        bool delete_entry(const node & key);//wrapper function to delete a 
                                            //specific key item wrapped in a
                                            //node. Returns true if successful

        //Overloaded assignment operators. += will add a node, = will copy an
        //entire tree, + will add a node to a tree either with a tree first or a
        //node first. 
        avl & operator += (const node &);
        avl & operator = (const avl &);
        avl operator + (const node &)const;
        friend avl operator + (const node &, const avl &);

    protected: 
        //head pointer, sometimes called 'root' but not here
        node * head;
        void destroy_all(node *&);//destroys all from node down.
        void display_all(node *);//displays all from node down.
        bool insert(const node &to_add, node *&);//recursive function to insert 
        //Rotation functions for the AVL tree
        //These will return to pointers to the proper node after a rotation is
        //executed.
        node * single_rot_right(node *&);
        node * single_rot_left(node *&);
        node * double_rot_right(node *&);
        node * double_rot_left(node *&);

        //Gets the height of a node *, including null pointers.
        int height(node *);
        int max(int,int);//returns larger of 2 integers
        void copy_all(node * & dest,node * source)const;//recursive copy function
        bool find_entry(const node & to_find, node *&);//recursive find function
        bool delete_entry(const node &to_delete, node *&);//recursive to locate 
                                                          // the node to_delete
        void delete_entry(node *& to_delete);//actually deletes the node, finding 
                                         //the in-order successor in the process
        node *& find_min(node *&);//finds the smallest node in a subtree. used to 
                                  //help find the in-order successor;
};

//The Tree class was made to help with the user-interface of the AVL class. This
//is what the client will interact with.
class tree:public avl
{
    public:
        //constructors
        tree();
        tree(const simple_string & name);
        tree(const char * name);
        //destructor
        ~tree();

        //The overloaded AVL functions are used to personalize the output based on
        //the tree_name as well as update the counter. The return values are the
        //same as described above.
        void display_all();
        void insert (const node &);
        bool delete_entry(const node & key);

        //A menu function added to facilitate reading of messages.
        void read_menu();

        //overloaded assignment operators to kick-start the AVL operators while
        //updating the counter
        tree & operator += (const node &);
        tree & operator = (const tree &);
        tree operator + (const node &)const;
        friend tree operator + (const node &, const tree &);

        //A friend used to output the number of messages if the object is
        //included in a cout << line. 
        friend ostream & operator << (ostream &, const tree &);

    private:
        int counter;//counter of number of messages in the tree.
        simple_string tree_name;//name of the tree: ex. facebook messages
        void destroy_all(node *&);//wrapper used to kickstart deleting all nodes 
                                 // used to update the counter. 
};
