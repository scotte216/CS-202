// Scott Ewing
// CS 202
// Assignment 2
//
// Filename: session.h
//


#include "multiplayer.h"

//The session class is what the client will interact with. It handles single
//player games vs multiplayer games from the multiplayer.h and games.h classes.
class session
{
    public:
        session();
        session(int players);
        void run();

    private:
        int players;

};


