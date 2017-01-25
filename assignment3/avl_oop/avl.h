// Scott Ewing
// CS202
// Assignment 3
//
// Filename: avl.h
//
// This is the header file for the avl class
//
#include <iostream>

class node
{
    public:
        node();
        node(const int x);
        node(const node &);
        ~node();
//        void set_left(node *&);
//        void set_right(node *&);
//        void set_height(int);
//        node *& get_left();
//        node *& get_right();
//        int get_height();
//        bool if_left();
//        bool if_right();
        void display();
//        bool is_gt(node * to_compare) const;
//        bool is_lt(node * to_compare) const;
        void insert(const node & to_add);
        int get_height(node * ptr);
        int max(int x,int y);
        void single_rot_right();
        void single_rot_left();
        void double_rot_right();
        void double_rot_left();
        void display_all();
        
    protected:
        int data;
        int height;
        node * left;
        node * right;
        void destroy();

};


class avl:public node
{
    public:
        avl();
        avl(const int x);
        avl(const node &);
        ~avl();
//        void display_all();
//        void insert(const node &);

    protected: 
//        node * head;
//        void destroy_all(node *& ptr);
//        void display_all(node *);
//        void insert(const node &, node *&);
//        node * single_rot_right(node *);
//        node * single_rot_left(node *);
//        node * double_rot_right(node *);
//        node * double_rot_left(node *);
//        int height(node *);
//        int max(int,int);
};

