#include "avl.h"

using namespace std;


node::node():data(0),height(0),left(NULL),right(NULL)
{

}

node::node(const int x):data(x),height(0),left(NULL),right(NULL)
{
}

node::node(const node & to_add):data(to_add.data),height(0),left(NULL),right(NULL)
{
}

node::~node()
{
    data = 0;
    height = 0;
    left = NULL;
    right = NULL;
}
void node::destroy()
{
    if (left) 
    {
        left->destroy();
        delete left;
    }
    if (right) 
    {
        right->destroy();
        delete right;
    }

}
/*
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

int node::get_height()
{
    return height;
}

bool node::if_left()
{
    return left;
}

bool node::if_right()
{
    return right;
}
*/
void node::insert(const node & to_add)
{
    
    if (to_add.data < data)
    {
        //if left pointer is null, connect node here.
        if (!left)
            left = new node(to_add);
        else 
            left->insert(to_add);

        if (get_height(left) - get_height(right) == 2)
        {
            if (to_add.data < left->data)
                single_rot_left();
            else
                double_rot_left();
        }
    }
    else if (to_add.data > data)
    {
        if (!right)
            right = new node(to_add);
        else
            right->insert(to_add);

        if (get_height(right) - get_height(left) == 2)
        {
            if (to_add.data > right->data)
                single_rot_right();
            else
                double_rot_right();
        }
    }
    else
        cout << "Data already exists.\n";


    height = 1 + max(get_height(left), get_height(right));

}

int node::get_height(node * ptr)
{
    int result;
    if (!ptr)
        result = -1;
    else
        result = ptr->height;

    return result;
}

void node::display()
{
    cout << data << endl;
}
/*
bool node::is_gt(node * to_compare) const
{
    return data > to_compare->data;
}

bool node::is_lt(node * to_compare) const
{
    return data < to_compare->data;
}
*/

int node::max(int x,int y)
{
    if (y > x)
        return y;
    
    return x;
}

void node::single_rot_right()
{
    int temp_data = data;

    node * temp;

    temp = right;
    data = temp->data;

    right = temp->right;
    temp->right = temp->left;
    temp->left = left;
    left = temp;

    temp->data = temp_data;

    temp->height = 1 + max(get_height(temp->left),get_height(temp->right));
    height = 1 + max(get_height(left),get_height(right));
}

void node::single_rot_left()
{
    int temp_data = data;

    node * temp;

    temp = left;
    data = temp->data;

    left = temp->left;
    temp->left = temp->right;
    temp->right = right;
    right = temp;

    temp->data = temp_data;

    temp->height = 1 + max(get_height(temp->left),get_height(temp->right));
    height = 1 + max(get_height(left),get_height(right));
}

void node::double_rot_right()
{
    right->single_rot_left();
    
    single_rot_right();
}

void node::double_rot_left()
{
    left->single_rot_right();
    
    single_rot_left();
}
void node::display_all()
{

    if (left) left->display_all();
    display();
    if (right) right->display_all();
}

avl::avl():node()
{
}

avl::avl(const int x):node(x)
{

}

avl::avl(const node & to_add):node(to_add)
{
}

avl::~avl()
{
    destroy();
}

/*
void avl::destroy_all(node *& ptr)
{
    if (!ptr) return;

    destroy_all(ptr->left);
    destroy_all(ptr->right);

    delete ptr;
    ptr = NULL;
}
*/
/*
void avl::insert(const node & to_add)
{
    if (to_add.data < data)
        insert(to_add,left);
    else if (to_add.data > data)
        insert(to_add,right);
    else 
        cout << "Data already exists.";
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
        if(to_add.data < ptr->data)
        {
            insert(to_add, ptr->left);
            //check if the height is unbalanced, sinec we added to the left,
            //if it's unablanced, the left leg will be too big.
            if ((ptr->left->height - ptr->right->height) == 2 )
            {
                if ( to_add.data < ptr->left->data )
                    ptr = single_rot_left(ptr);
                else
                    ptr = double_rot_left(ptr);
            }
        }
        //else, go right
        else if (to_add.data > ptr->data)
        {
            insert(to_add, ptr->right);
            //check if it's unbalanced. Since we added to the right, the right
            //leg will be unbalanced.
            if ((ptr->right->height - ptr->left->height) == 2 )
            {
                if (to_add.data > ptr->right->data)
                    ptr = single_rot_right(ptr);
                else
                    ptr = double_rot_right(ptr);
            }
        }
        else 
            cout << "Data already exists.\n";
    }
    

    //adjust the height of each node upon return.

   ptr->height = 1 + max(ptr->left->height , ptr->right->height); 
}
*/
/*
int avl::height(node * ptr)
{
    int result;

    if (!ptr)
        result = -1;
    else
        result = ptr->get_height();

    return result;
}
*/
/*
int avl::max(int x,int y)
{
    if (y > x)
        return y;
    
    return x;
}

node * avl::single_rot_right(node * ptr)
{
    node * temp;

    temp = ptr->right;
    ptr->right = temp->left;
    temp->left = ptr;

    ptr->height = 1 + max(ptr->left->height,ptr->right->height);

    temp->height = 1 + max(ptr->height,temp->right->height);

    return temp;
}

node * avl::single_rot_left(node * ptr)
{
    node * temp;
    temp = ptr->left;
    ptr->left = temp->right;
    temp->right = ptr;

    ptr->height = 1 + max(ptr->left->height,ptr->right->height);

    temp->height = 1 + max(ptr->height,temp->left->height);

    return temp;
}

node * avl::double_rot_right(node * ptr)
{
    node * temp = single_rot_left(ptr->right);

    ptr->right = temp;
    
    return single_rot_right(ptr);
}

node * avl::double_rot_left(node * ptr)
{
    node * temp = single_rot_right(ptr->left);
    ptr->left = temp;
    
    return single_rot_left(ptr);
}
*/
