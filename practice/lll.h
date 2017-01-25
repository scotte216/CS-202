#include <iostream>


class node
{
    public:
        node();
        node(const node &);
        node(const int);
        node(const node &, node *);
        ~node();
//        void add(const int);
        void display();
        void display_all();
        void add(node &,node *&);
    protected:
        int data;
        node * next;
};
