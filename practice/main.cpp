#include "lll.h"

using namespace std;


int main()
{
    node my_list(5);

    node temp(4);
    my_list.add(temp,&my_list);

    temp(7);
    my_list.add(temp,&my_list);

    temp(10);
    my_list.add(temp,&my_list);

    temp(1);
    my_list.add(temp,&my_list);

    my_list.display();
    my_list.display_all();


    return 0;
}
