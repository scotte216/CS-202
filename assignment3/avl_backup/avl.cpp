#include "avl.h"

using namespace std;


node::node():data(NULL),height(0),left(NULL),right(NULL)
{
}


node::node(const int x):height(0),left(NULL),right(NULL)
{
    data = new message(x);
}

node::node(const node & to_add):height(0),left(NULL),right(NULL)
{
    data = new message(to_add->data);
}

node::~node()
{
    if (data) delete data;
    data = NULL;
    height = 0;
    left = NULL;
    right = NULL;
}

void node::set_left(node *& next)
{
    left = next;
}

void node::set_right(node *& next)
{
    right = next;
}

void node::set_height(int num)
{
    height = num;
}

node *& node::get_left()
{
    return left;
}

node *& node::get_right()
{
    return right;
}

bool node::operator < (const node * to_comp) const
{
    return this->data < to_comp->data;
}

bool node::operator > (const node * to_comp) const
{
    return this->data > to_comp->data;
}

bool node::operator == (const node * to_comp) const
{
    return this->data == to_comp->data;
}

bool node::operator <= (const node * to_comp) const
{
    return this->data <= to_comp->data;
}

bool node::operator >= (const node * to_comp) const
{
    return this->data >= to_comp->data;
}

bool node::operator != (const node * to_comp) const
{
    return this->data != to_comp->data;
}

node & node::operator = (const node & to_copy)
{
    if ( & to_copy == this) return *this;

    this->data = to_copy.data;
//    this->height = to_copy.height;

    return *this;
}

int node::get_height()
{
    return height;
}

void node::display()
{
    cout << data << endl;
}



avl::avl():head(NULL)
{
}

avl::avl(const avl & source)
{
    head = NULL;
    copy_all(head,source.head);
}

avl::~avl()
{
    if (head) destroy_all(head);
}

void avl::destroy_all(node *& head)
{
    if (!head) return;

    destroy_all(head->get_left());
    destroy_all(head->get_right());

    delete head;
    head = NULL;
}

void avl::display_all()
{
    display_all(head);
}

void avl::display_all(node * head)
{
    if (!head) return;
    
    display_all(head->get_left());

    head->display();

    display_all(head->get_right());
}

void avl::insert(const node & to_add)
{
    insert(to_add, head);
}

void avl::insert(const node & to_add, node *& ptr)
{

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
        }
    }
    
    //adjust the height of each node upon return.
    int temp_height = 1 + max(height(ptr->get_left()),height(ptr->get_right())); 
    ptr->set_height(temp_height); 
}

bool avl::find_entry(const node & key)
{
    return find_entry(key,head);
}

bool avl::find_entry(const node & key, node *& ptr)
{
    if (!ptr) return false;

    if (key == ptr)
        return true;
    else if (key < ptr)
        return find_entry(key,ptr->get_left());
    else
        return find_entry(key,ptr->get_right());
}

bool avl::delete_entry(const node & key)
{
    return delete_entry(key,head);
}

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

avl operator + (const avl & tree, const node & to_add)
{
    avl temp(tree);

    temp += to_add;

    return temp;
}

avl operator + (const node & to_add, const avl & tree)
{
    return tree + to_add;
}

int avl::height(node * ptr)
{
    int result;

    if (!ptr)
        result = -1;
    else
        result = ptr->get_height();

    return result;
}

int avl::max(int x,int y)
{
    if (y > x)
        return y;
    
    return x;
}

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
