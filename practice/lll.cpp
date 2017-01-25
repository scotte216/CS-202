#include "lll.h"
using namespace std;

node::node():data(0)
{
    next = NULL;
}

node::node(const node & to_add):data(to_add.data)
{
    next = NULL;
}

node::node(const int num)
{
    data = num;
    next = NULL;
}

node::node(const node & to_add, node * to_next):data(to_add.data),next(to_next)
{
}

node::~node()
{
    data = 0;
    next = NULL;
}
/*
void node::add(const int num)
{
    node temp(num);
    add(temp,this);
}
*/
void node::add(node & to_add,node * &ptr_to_here)
{
    if (to_add.data > data)
        if (!next)
            next = new node(to_add);
        else
            next->add(to_add,next);
    else
        ptr_to_here = new node(to_add,ptr_to_here);
}

void node::display()
{
    cout << data << endl;
}

void node::display_all()
{
    cout << data << endl;
    if(next) next->display_all();
}
