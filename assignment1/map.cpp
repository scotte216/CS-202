// Scott Ewing
// CS 202
// Assignment 1
//
// filename: map.cpp
// 
// The Map has an array of Vertex objects. Each Vertex object has a linear
// linked list of nodes to determine the edges/adjacencies of each room.
//
// Vertex objects are children of the Room class.
//
#include "map.h"
using namespace std;


//-------------
// VERTEX CLASS
// ------------

//Default constructor
vertex::vertex():head(NULL)
{
}

// Constructor with a room name and description passed in.
vertex::vertex(char * new_name, char * new_desc):room(new_name,new_desc),head(NULL)
{
}

//Constructor with a room object passed in.
vertex::vertex(room & to_add):room(to_add),head(NULL)
{
}

//default destructor. traverses the LLL of edges and deletes each node
vertex::~vertex()
{
    node * temp;
    while(head)
    {
        temp = head;
        head = head->get_next();
        delete temp;
    }
    delete head;
    head = NULL;
}

// Wrapper function to display the exits from the room/Vertex as determined by
// the edge list. The boolean flag determines if the required item is present
// for rooms set dark.
void vertex::exits(bool has_flashlight)
{
    exits(head,has_flashlight);
}


//Recursive function, with a boolean indicator for hidden rooms.
void vertex::exits(node * head,bool has_flashlight)
{
    if (!head) return;

    if (!head->is_hidden() || has_flashlight)
        head->display();

    exits(head->get_next(),has_flashlight);
}

//Wrapper function for the travel function. Returns a vertex pointer to the
//destination, if found, NULL if not found.
vertex * vertex::travel(char * destination)
{
    return travel(destination,head);
}


//Recursive function to find if destination name is found in the edge list of
//this room/vertex.
vertex * vertex::travel(char * dest,node * head)
{
    if (!head) return NULL;

    if (head->match(dest))
        return head->get_adj();
    else
        return travel(dest,head->get_next());
}

// Adds a new adjacency node to the edge list, using one of the node
// constructors that will properly set up the next pointers and adjacency
// pointers.
void vertex::add_adj(vertex * dest)
{
    head = new node(dest,head);
}


// ----------
// NODE CLASS
// ----------

//Default constructor
node::node():adjacent(NULL),next(NULL)
{
}

//Constructor with an adjacency pointer and next pointer passed in.
node::node(vertex * dest, node * next):adjacent(dest),next(next)
{
}

//default node destructor
node::~node()
{
    adjacent = NULL;
    next = NULL;
}

// Returns the next pointer.
node * node::get_next()
{
    return next;
}

// returns the adjacency pointer from a given node.
vertex * node::get_adj()
{
    return adjacent;
}

//wrapper to find if this node's adjacent room matches 'match'
bool node::match(char *match)
{
    return adjacent->find_name(match);
}

// Causes node to display the adjacent room/vertex's name. Used for exit list.
void node::display()
{
    adjacent->display_name();
}

//Returns hidden flag of this node's adjacent room/vertex.
bool node::is_hidden()
{
    return adjacent->is_hidden();
}

// --------- 
// MAP CLASS
// ---------

// Map default constructor. Prompts for the number of rooms in the map for
// dynamic array of vertices. Not used in this program.
map::map()
{
    int size = 0;
    cout << "How many rooms are in the map? ";
    cin >> size;
    cin.ignore(100,'\n');

    list_size = size;

    adj_list = new vertex[list_size];

    current = &adj_list[0];
}

// Constructor which takes a size to set up dynamic array for # of rooms.
map::map(int size)
{
    list_size = size;

    adj_list = new vertex[list_size];

    current = &adj_list[0];
}

//default destructor
map::~map()
{
    delete [] adj_list;
    adj_list = NULL;
}

// Wrapper function for traveling from current to destination. Takes the
// inventory contents object for determining if the inventory contains all the
// required items to enter locked rooms. 
// returns 1 on succes, 0 on fail (no room destinations match) and -1 if
// destination is locked and the inventory doesn't contain all the required
// items.
int map::travel(char * destination,contents & inventory)
{
    vertex * temp = NULL;

    // from the current room, returns a pointer to the destination if it can be
    // reached, NULL otherwise.
    temp = current->travel(destination);

    //sets up the required inventory items to pass in to locked rooms.
    char item1[] = "Flashlight";
    char item2[] = "Hammer";
    char item3[] = "Screw driver";
    char item4[] = "Nails";
    bool has_all = inventory.find_name(item1) && inventory.find_name(item2) 
                && inventory.find_name(item3) && inventory.find_name(item4);

    // If temp is NULL, the room can't be reached from current location. 
    if (!temp)
        return 0;
    // else if the room is locked and they don't have all the required items,
    // return -1 and give a message.
    else if (temp->is_locked() && !has_all)
    {
        cout << "That direction is locked.\n";
        return -1;
    }
    //else set the current room to the destination and return 1
    else 
    {
        current = temp;
        return 1;
    }
}


//Add a room to the vertex array in the first empty spot. Return 1 on succes, 0
//on fail. 
int map::add_vertex(room & to_add)
{
    for (int i = 0; i < list_size; ++i)
    {
        if (!adj_list[i].has_name())
        {
            adj_list[i].copy(to_add);
            return 1;
        }
    }
    return 0;
}


// Adds an adjacency list from Source to Destination. Returns 1 on succes 0 on
// failure. This is a one-way connection.
int map::add_adj(const char * source,const char * dest)
{
    vertex * source_ptr = NULL;
    vertex * dest_ptr = NULL;


    // sets source and destination pointers to the source and destination rooms, 
    // NULL if it doesn't exist
    source_ptr = find_vert(source);
    dest_ptr = find_vert(dest);

    if (source_ptr && dest_ptr)
    {
        source_ptr->add_adj(dest_ptr);
        return 1;
    }
    else
        return 0;
}

// Finds a vertex based on a name for a room/vertex, returning a pointer to the
// room if found, NULL otherwise.
vertex * map::find_vert(const char * to_find)
{
    for (int i= 0; i < list_size; ++i)
    {
        if (adj_list[i].find_name(to_find))
            return &adj_list[i];
    }
    return NULL;
}

// Displays the current room's name/description, contents, and obvious exist, as
// determined by the vertice's adjacency list. If the required 'flashlight' is
// in the inventory, hidden rooms will be displayed as well. 
void map::display(contents & inventory)
{
    cout << "You see the following:\n";
    current->display();

    cout << "Contains:\n";
    current->contents();

    cout << "Obvious exits:\n";
    char required_item[] = "Flashlight";
    bool has_item = inventory.find_name(required_item); 
    current->exits(has_item);
    cout << "\nTo navigate, type the name of exit. (ex. warehouse)\n";

}

// Displays just the current room's name. Wrapper for the vertex of the current
// room. 
void map::display_room_name()
{
    current->display_name();
}

// Adds a problem object to a given room by name. 
void map::add_problem(const char * name, const problem & to_add)
{
    vertex * temp = find_vert(name);
    if (temp)
        temp->add_problem(to_add);
}

// Wrapper function to solve the current vertex's problem by displaying the problem
//  and  prompting for the answer.
//  Returns 1 on success, 0 on fail, an -1 on error.
int map::solve_problem()
{
    int answer;

    //If display_problem returns 1, the problem has been successfully displayed
    //and it prompts for an answer. Else -1. The problem might have been already
    //answered, or there might be a problem with the operator. 
    if (current->display_problem() == 1)
    {
        cin >> answer;
        cin.ignore(100,'\n');
    }
    else
        return -1;

    //If it gets to this point the problem was displayed and prompted for an
    //answer. The answer is sent to the problem and the result is returns 1 or
    //0. 
    return current->solve_problem(answer);
}


// Collect the current room's contents and put them into the destination content
// object.
void map::collect(contents & dest)
{
    current->collect(dest);
    current->remove_all_items();
    cout << "You collect the required item from this room.\n";
}
