// Scott Ewing
// CS202
// Assignment 3
//
// Filename: avl.h
//
// This is the header file for the avl class
//
#include <iostream>
#include "message.h"
class node
{
    public:
        node();
        node(const int x);
        node(const node &);
        ~node();
        
        void set_left(node *&);
        void set_right(node *&);
        void set_height(int);
        
        node *& get_left();
        node *& get_right();
        
        int get_height();
        void display();
        
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

        node & operator = (const node &);

    protected:
        message * data;
        int height;
        node * left;
        node * right;

};


class avl
{
    public:
        avl();
        avl(const avl &);
        ~avl();
        void display_all();
        void insert(const node &);
        void copy_all(node * & destination)const;
        bool find_entry(const node & key);
        bool delete_entry(const node & key);

        avl & operator += (const node &);
        avl & operator = (const avl &);
        friend avl operator + (const avl &, const node &);
        friend avl operator + (const node &, const avl &);

    protected: 
        node * head;
        void destroy_all(node *&);
        void display_all(node *);
        void insert(const node &, node *&);
        node * single_rot_right(node *&);
        node * single_rot_left(node *&);
        node * double_rot_right(node *&);
        node * double_rot_left(node *&);
        int height(node *);
        int max(int,int);
        void copy_all(node * & dest,node * source)const ;
        bool find_entry(const node &, node *&);
        bool delete_entry(const node &, node *&);
        void delete_entry(node *&);
        node *& find_min(node *&);
};

