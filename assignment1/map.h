// Scott Ewing
// CS 202
// Assignment 1
//
// filename:
// map.h
//
// The Map class is a Graph that has an array of Vertices. Each Vertice is a
// Room object, plus more to deal with the adjacency list. The adjacency list is
// constructed with the node class. Each node represents a connection from one
// Vertex to another.

#include "room.h"

// Vertex class, derived from a Room class
// A Vertex HAS A linear linked list of the Node class
class vertex:public room
{

    public:
        //constructors
        vertex();
        vertex(char * new_name, char * new_desc);
        vertex(room & to_add);
        //destructor
        ~vertex();
        void exits(bool has_flashlight);//names of rooms on the adjacency list 
                                        // wrapper function. boolean flag
                                        // determines if dark rooms are
                                        // displayed
        vertex * travel(char * destination); // Returns the vertex pointer of the
                                             // destination. Wrapper
        void add_adj(vertex * dest); // adds a destination to the adjacency list.
    protected:
        class node * head;//Head of the edge list/adjacency list
        void exits(node * head,bool has_flashlight); // recursive function to
                                                     // display exits
        vertex * travel(char *, node *); // Recursive travel function.
};


//Node Class is used by the Vertex class.
class node
{
    public:
        //constructors
        node();
        node(vertex * dest,node * next);
        //destructor
        ~node();
        node * get_next(); // returns next pointer
        vertex * get_adj(); // returns adjacent pointer. 
        bool match(char *); // Determines if this node points to a desired name
        void display(); // displays the node's info
        bool is_hidden(); // returns hidden state of adjacent room.

    private:
        vertex * adjacent; // adjacent pointer
        node * next; // next pointer. 
};


//Map Class contains an Adjacenty list made of the Vertex Class. 
//Current pointer determines current location on the map. 
class map
{
    public: 
        //constructors
        map();
        map(int size);
        //destructors
        ~map();
        int travel(char * destination,contents &); // travel do destination
        int add_vertex(room & to_add); // add a vertex to the list
        int add_adj(const char * source,const char * dest); // link source and dest
                                                         // via the adjacency list.
        void display(contents &); // Display wrapper for the vertex. Takes a
                                  // contents inventory for required items.
        void display_room_name(); // displays just the room name of the current room
        void add_problem(const char * name,const problem & to_add); // add a problem
                                                                    // to a room.
        int solve_problem(); // Solve problem for current room -- wrapper
        void collect(contents & dest); // collect the items in this room into 
                                       //destination contents. 
    private:
        int list_size;//size of the adjacency list
        vertex * current; // pointer to current room vertex
        vertex * adj_list; // pointer to adjacency list (or the array of rooms)
        vertex * find_vert(const char * name); // return the vertex pointer to a 
                                                //given room name
};
