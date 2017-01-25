#include "avl.h"

using namespace std;

//Constructors
node::node():data(NULL),height(0),left(NULL),right(NULL)
{
}

//Constructor taking a message.
node::node(const message & to_add):height(0),left(NULL),right(NULL)
{
    copy(to_add);
}

//constructor taking a node instead of a message
node::node(const node & to_add):height(0),left(NULL),right(NULL)
{
    copy(*to_add.data);
}

//destructor to release dynamic memory and set zero-state on variables
node::~node()
{
    if (data) delete data;
    data = NULL;
    height = 0;
    left = NULL;
    right = NULL;
}


//Copy function that uses RTTI to determine what the message pointer should
//point. This Dynamic Binding helps us get different behavior from our node data
//(which is a message pointer). See message.h for details.
void node::copy(const message & to_add)
{
    const facebook * facebook_ptr = dynamic_cast<const facebook *> (&to_add);
    const text * text_ptr = dynamic_cast<const text *> (&to_add);
    const email * email_ptr = dynamic_cast<const email *> (&to_add);

    if (facebook_ptr)
        data = new facebook(*facebook_ptr);
    else if (text_ptr) 
        data = new text(*text_ptr);
    else if (email_ptr)
        data = new email(*email_ptr);
    else data = new message(to_add);
}

//Sets the left node pointer
void node::set_left(node *& next)
{
    left = next;
}

//sets right node node pointer
void node::set_right(node *& next)
{
    right = next;
}

//sets the height of the node
void node::set_height(int num)
{
    height = num;
}

//Gets left node, used for navigating tree
//This is how we've been instructed to create our nodes
node *& node::get_left()
{
    return left;
}

//Gets right node, used for navigating tree. 
node *& node::get_right()
{
    return right;
}

//Operator Overloading
//I've included the comparison operators for completeness, even though I don't
//use them all in my program. There are two versions for each. 
//1) takes Node object and compares to a Node Pointer
//2) Takes a Node object and compares to a Node object
//Covered are:
// <, >, ==, !=, >=, and <=
// NOTE: these are expecting 'data' to have comparison operators.
// In this case, they are overloaded in the message class.
bool node::operator < (const node * to_comp) const
{
    return *this->data < to_comp->data;
}

bool node::operator < (const node & to_comp) const
{
    return *this->data < to_comp.data;
}

bool node::operator > (const node * to_comp) const
{
    return *this->data > to_comp->data;
}

bool node::operator > (const node & to_comp) const
{
    return *this->data > to_comp.data;
}

bool node::operator == (const node * to_comp) const
{
    return *this->data == to_comp->data;
}

bool node::operator == (const node & to_comp) const
{
    return *this->data == to_comp.data;
}

bool node::operator <= (const node * to_comp) const
{
    return *this->data <= to_comp->data;
}

bool node::operator <= (const node & to_comp) const
{
    return *this->data <= to_comp.data;
}

bool node::operator >= (const node * to_comp) const
{
    return *this->data >= to_comp->data;
}

bool node::operator >= (const node & to_comp) const
{
    return *this->data >= to_comp.data;
}

bool node::operator != (const node * to_comp) const
{
    return *this->data != to_comp->data;
}

bool node::operator != (const node & to_comp) const
{
    return *this->data != to_comp.data;
}
/////END Comparison Overloading


//Assignment Operator
//This makes a deep copy of the given node to_copy
node & node::operator = (const node & to_copy)
{
    if ( & to_copy == this) return *this;

    copy(*to_copy.data);

    return *this;
}

// Ostream insertion operator overloaded to allow easy displaying of the node's
// data into the ostream
ostream & operator << (ostream & out, const node & to_display)
{
    out << *to_display.data;
}

//Height getter
int node::get_height()
{
    return height;
}


//Node display fucntion.
//Note: Both data->display() and cout << *data work since data has overloaded
//the << operator. See message class for more.
void node::display()
{
//    data->display();
    cout << *data;
}



//////////////////////////////
//  AVL Class
//

//constructor
avl::avl():head(NULL)
{
}

//constructor to copy an entire tree. Uses recursive copy_all
avl::avl(const avl & source)
{
    head = NULL;
    copy_all(head,source.head);
}

//Destructor, using recursive destroy_all
avl::~avl()
{
    if (head) destroy_all(head);
}

//recursive function to destroy all nodes in a tree.
void avl::destroy_all(node *& head)
{
    if (!head) return;

    destroy_all(head->get_left());
    destroy_all(head->get_right());

    delete head;
    head = NULL;

}


//Wrapper display function
void avl::display_all()
{
    display_all(head);
}

//Resursive display function.
void avl::display_all(node * head)
{
    if (!head) return;
    
    display_all(head->get_left());

    head->display();
    
    display_all(head->get_right());
}

//Wrapper function to insert a node onto the tree. Returns true if successful
bool avl::insert(const node & to_add)
{
    return insert(to_add, head);
}

//The resurive insert function that checks for and handles tree rotations.
//Returns true if successfully added. Will not add data duplicates. 
//NOTE that the comparison overloaded functions are used here. 
//Data duplicates are determined by the comparison operators. See the Message
//class for details.
bool avl::insert(const node & to_add, node *& ptr)
{
    bool result = true;

    if (!ptr)
    {
        //copy the node here.
        ptr = new node(to_add);
    }
    else
    {
        //if current node is greater than the item to add, go left
        if(to_add < ptr)
        {
            insert(to_add, ptr->get_left());
            //check if the height is unbalanced, sinec we added to the left,
            //if it's unablanced, the left leg will be too big.
            if ((height(ptr->get_left()) - height(ptr->get_right())) == 2 )
            {
                if ( to_add < ptr->get_left() )
                {
                    ptr = single_rot_left(ptr);
                }
                else
                {
                    ptr = double_rot_left(ptr);
                }
            }
        }
        //else, go right
        else if (to_add > ptr)
        {
            insert(to_add, ptr->get_right());
            //check if it's unbalanced. Since we added to the right, the right
            //leg will be unbalanced.
            if ((height(ptr->get_right()) - height(ptr->get_left())) == 2 )
            {
                if (to_add > ptr->get_right())
                {
                    ptr = single_rot_right(ptr);
                }
                else
                {
                    ptr = double_rot_right(ptr);
                }
            }
        }
        else 
        {
            cout << "Data already exists.\n";
            result = false;
        }
    }
    
    //adjust the height of each node upon return.
    int temp_height = 1 + max(height(ptr->get_left()),height(ptr->get_right())); 
    ptr->set_height(temp_height); 
    return result;
}


//Wrapper function to find data and display (wrapped in a node for encapsuation)
//returns true if found.
bool avl::find_entry(const node & key)
{
    return find_entry(key,head);
}

//Recursive function to find and display data wrapped in node key.
bool avl::find_entry(const node & key, node *& ptr)
{
    if (!ptr) return false;

    //notice the overloaded comparison operator is being used.
    if (key == ptr)
    {
        //Note: both display() and cout << work
        ptr->display();
//        cout << *ptr;
        return true;
    }
    else if (key < ptr)
        return find_entry(key,ptr->get_left());
    else
        return find_entry(key,ptr->get_right());
}

//Wrapper function to delete a single node based on a key (wrapped in a node)
//Returns true on success
bool avl::delete_entry(const node & key)
{
    return delete_entry(key,head);
}

//Recursive function to delete a node based on a key. 
//return strue on success
bool avl::delete_entry(const node & key, node *& ptr)
{
    if (!ptr) return false;

    if (key == ptr)
    {
        delete_entry(ptr);
        return true;
    }
    else if (key < ptr)
        return delete_entry(key,ptr->get_left());
    else
        return delete_entry(key,ptr->get_right());
}

//This function does the actual removeal of the node and setting the in-order
//successor. 
void avl::delete_entry(node *& ptr)
{
    if (!ptr) return;

    //case 1, no leaves, delete it and set to null
    if (!ptr->get_left() && !ptr->get_right())
    {
        delete ptr;
        ptr = NULL;
    }
    //case 2a if there is just one leaf, delete node and attach ptr to the
    //subtree. 2a, left is null, attach right.
    else if (!ptr->get_left())
    {
        node * temp = ptr;
        ptr = ptr->get_right();
        delete temp;
        temp = NULL;
    }
    //case 2b: right is null, attached left.
    else if (!ptr->get_right())
    {
        node * temp = ptr;
        ptr = ptr->get_left();
        delete temp;
        temp = NULL;
    }
    //case 2: there are two leaves. Find the in-order successor
    else
    {
        //temp now points to the in-order successor
        node * temp = find_min(ptr->get_right());

        //copy that data to here with the overloaded assignment operator
        *ptr = *temp;

        //now delete that in-order successor with the delete_entry(key,pointer) 
        //function. It will only have 1 leaf at most.
        delete_entry(*temp,ptr->get_right());
    }
}


//This function returns a node pointer to the smallest node in a sub-tree. Used
//by delete_entry() to properly set up the tree with the in-order successor.
node *& avl::find_min(node *& ptr)
{
    //If a null pointer has been passed here, this is unexpected behavior, just
    //return it.
    if (!ptr) return ptr;

    //if there is no left node, no nodes are smaller
    if (!ptr->get_left())
    {
        return ptr;
    }
    else
        return find_min(ptr->get_left());
}

//Assignment Operator Overloading:
//These 4 operators can be used for adding a node (+=), deep-copying an entire
//tree (=), and + operator for adding a node to a tree or vice-versa. 
avl & avl::operator += (const node & to_add)
{
    insert(to_add);

    return *this;
}

avl & avl::operator = (const avl & to_copy)
{
    if ( &to_copy == this) return *this;

    if (this->head) destroy_all(this->head);

    to_copy.copy_all(this->head);

    return *this;
}

avl avl::operator + (const node & to_add)const
{
    avl temp(*this);

    temp += to_add;

    return temp;
}

avl operator + (const node & to_add, const avl & tree)
{
    return tree + to_add;
}
//////END Assignment Overloading



// Height returns the height of a node a pointer is directed towards. Returns -1
// if null. 
int avl::height(node * ptr)
{
    int result;

    if (!ptr)
        result = -1;
    else
        result = ptr->get_height();

    return result;
}

//Returns the larger of two integers, used when comparing sub-tree heights for
//executing rotations when adding to the AVL tree. 
int avl::max(int x,int y)
{
    if (y > x)
        return y;
    
    return x;
}


//Rotation functions. These execute the four different rotations used to keep an
//AVL balanced.
node * avl::single_rot_right(node *& ptr)
{
    node * temp;
    temp = ptr->get_right();
    ptr->set_right(temp->get_left());
    temp->set_left(ptr);

    int temp_height = 1 + max(height(ptr->get_left()),height(ptr->get_right()));
    ptr->set_height(temp_height);

    temp_height = 1 + max(height(ptr),height(temp->get_right()));
    temp->set_height(temp_height);

    return temp;
}

node * avl::single_rot_left(node *& ptr)
{
    node * temp;
    temp = ptr->get_left();
    ptr->set_left(temp->get_right());
    temp->set_right(ptr);

    int temp_height = 1 + max(height(ptr->get_left()),height(ptr->get_right()));
    ptr->set_height(temp_height);

    temp_height = 1 + max(height(ptr),height(temp->get_left()));
    temp->set_height(temp_height);

    return temp;
}

node * avl::double_rot_right(node *& ptr)
{
    node * temp = single_rot_left(ptr->get_right());

    ptr->set_right(temp);
    
    return single_rot_right(ptr);
}

node * avl::double_rot_left(node *& ptr)
{
    node * temp = single_rot_right(ptr->get_left());
    ptr->set_left(temp);
    
    return single_rot_left(ptr);
}


//Wrapper function to copy an entire tree;
void avl::copy_all(node * & dest) const
{
    copy_all(dest,head);
}


//Since this is copying a previously generated AVL tree, it is assumed to be
//balanced, and thus the balance isn't checked. If any new nodes are added, they
//will be appropriately checked with the insert() function. 
void avl::copy_all(node *& dest, node * source)const
{
    if (!source) 
    {
        dest = NULL;
        return;
    }

    dest = new node(*source);
    copy_all(dest->get_left(), source->get_left());
    copy_all(dest->get_right(), source->get_right());

}

////////////////////////////
// Tree class
// //////////////////


//Constructors
tree::tree():counter(0),tree_name("Unamed Directory")
{
}

//Constructor taking in a simple_string for the name of the tree. See the
//Simple_String class
tree::tree(const simple_string & name):counter(0),tree_name(name)
{
}

//Constructor using a char * for a name, then takes advantage of the
//simple_string's assignment operator to deep copy the char * into the name. 
tree::tree(const char * name):counter(0)
{
    tree_name = name;
}

//Tree destructor, setting zero-values. The base-class destructor will run as
//well since this isn't used in dynamic binding. 
tree::~tree()
{
    counter = 0;
    tree_name = "";
}


// Tree class wrapper function for displaying everything in a tree. It makes it
// pretty for the client, by adding in additional details like the name of the
// tree and number of items in the tree. 
void tree::display_all()
{
    cout << "Displaying contents of: "
         << tree_name 
         << endl;

    avl::display_all();

    cout << "\n\nTotal size of directory: "
         << counter 
         << endl;
}

//Tree wrapper to insert a node, and updates the counter. The counter is just
//for the user, not used by the functions. 
void tree::insert(const node & to_add)
{
    bool result = avl::insert(to_add);
    if (result) 
        ++counter;
}


//Tree wrapper for delete entry to update the counter. 
bool tree::delete_entry(const node & key)
{
    bool result = avl::delete_entry(key);
    if (result)
        --counter;

    return result;
}


//A tree 'read' menu for the reading of messages. 
void tree::read_menu()
{
    int result;

    cout << endl << tree_name
         << "\nYou have " << counter << " messages."
         << "\n1) Read all"
         << "\n2) Read one"
         << "\n3) Delete all"
         << "\n4) Delete one"
         << "\n5) return to main menu.\n";

    cin >> result;
    cin.ignore(100,'\n');

    while (result < 1 || result > 5)
    {
        cout << "Please select one of the numbers above: ";
        cin >> result;
        cin.ignore(100,'\n');
    }

    if (result == 1)
    {
        display_all();
    }
    else if (result == 2)
    {
        cout << "\nMessage to read? (use ID#): ";
        int response;
        cin >> response;
        cin.ignore(100,'\n');
        //packaging the key into a node, allowing for the search to take
        //advantage of the data comparisons.

        message temp(response);
        node to_find(temp);
        
        if (!find_entry(to_find) )
            cout << "\nMessage not found.";
    }
    else if(result == 3)
    {
        destroy_all(head);
        cout << "\nMessages deleted.";
    }
    else if(result == 4)
    {
        cout << "\nMessage to delete? (use ID#): ";
        int response;
        cin >> response;
        cin.ignore(100,'\n');
        //packaging the key into a node, allowing for the search to take
        //advantage of the data comparisons.

        message temp(response);
        node to_find(temp);
        
        if (!delete_entry(to_find) )
            cout << "\nMessage not found.";
        else
            cout << "\nMessage deleted.";
    }

}


//Overloaded << operator for easy access of the number of items in the counter
//by simply using the object name in the ostream. 
ostream & operator << (ostream & out,const tree & to_display)
{
    out << to_display.counter;
}


//Overloaded append/insert operator used to update the counter. 
tree & tree::operator += (const node & to_add)
{
    insert(to_add);
    return *this;
}

//overloaded assignment operator to deep copy the tree and properly set up the
//counter. 
tree & tree::operator = (const tree & source)
{
    if (this == &source) return *this;

    counter = source.counter;

    if (this->head) destroy_all(this->head);

    source.copy_all(this->head);

    return *this;
}

//Overloaded addition operator to add a  node, needed to update the counter. 
tree tree::operator + (const node & to_add) const
{
    tree temp(*this);

    temp += to_add;

    return temp;
}

//Overloaded addition operator needed to update the counter. 
tree operator + (const node & to_add, const tree & a_tree)
{
    return a_tree + to_add;
}

//Overloaded destroy_all function needed to update counter. 
void tree::destroy_all(node *& head)
{
    avl::destroy_all(head);
    counter = 0;
}
