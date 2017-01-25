// Scott Ewing
// CS 202
// Assignment 2
//
// filename: problem.cpp
//
//problem class. Used by the room class.
#include "problem.h"
using namespace std;

//default constructor. Sets the operator to '0' by default.
problem::problem():num1(0),num2(0),operate(0)
{
}

//Constructor taking 2 operands and an operator.
problem::problem(int num1, char operate, int num2):num1(num1),num2(num2),operate(operate)
{
}

//default destructor
problem::~problem()
{
    num1 = 0;
    num2 = 0;
    operate = 0;
}

//Changes the problem in this object to the new parameters.
void problem::change_problem(int new_num1, char new_operate, int new_num2)
{
    num1 = new_num1;
    num2 = new_num2;
    operate = new_operate;
}

//Attempt to solve with 'guess.' Returns 1 on correct, 0 on wrong answer an -1
//if there is an error with the operator.
int problem::solve(int guess)
{
    int solution;
    if (operate == '+')
        solution = num1 + num2;
    else if (operate == '-')
        solution = num1 - num2;
    else if (operate == '*')
        solution = num1 * num2;
    else if (operate == '/')
        solution = num1 / num2;
    else
        return -1;

    return solution == guess;
}


//Displays the mathematical problem, checking to make sure the operator char is
//one of the 4 expected operators. Returns 1 upon success, 0 if there is an
//error with an operator.
int problem::display_problem()
{
    if (operate == '+' || operate == '-' || operate == '*' || operate == '/')
    {
        cout << "Please solve the following problem:\n";
        cout << num1 << ' ' << operate << ' ' << num2 << " = ?\n";
    }
    else
        return 0;

    return 1;
}


//copies source problem here.
void problem::copy_problem(const problem & source)
{
    change_problem(source.num1,source.operate,source.num2);
}
