// Scott Ewing
// CS 202
// Assignment 1
//
// filename: problem.h
//
// This is the problem class, for determining and solving math problems. The
// Room class HAS A problem.
//
#include <iostream>

#ifndef PROBLEM
#define PROBLEM

class problem
{
    public:
        //constructors
        problem();
        problem(int, char, int);
        //destructor
        ~problem();
        int solve(int); // attempt to solve the problem with an input int.
        void change_problem(int, char, int); // change the problem to a new one.
        int display_problem(); // display the problem
        void copy_problem(const problem & source); // copy the source problem here.
    protected:
        int num1; // first operand
        int num2; // second operand
        char operate; // operator
};

#endif
