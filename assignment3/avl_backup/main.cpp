#include "avl.h"
using namespace std;
bool again()
{
    char response;

    cout << "\nAnother? ";
    cin >> response;
    cin.ignore(100,'\n');

    if (response == 'y' )
        return true;
    return false;
}

int main()
{
    avl my_tree;
    int counter = 0;
    do {
        int response = ++counter;
        cout << "Enter a number: ";
        cout << response;

        node temp(response);

        my_tree += temp;

    } while(again());

    my_tree.display_all();


    int to_find;
    cout << "Enter a number to delete: ";
    cin >> to_find;
    cin.ignore(100,'\n');

    node temp(to_find);

    if (my_tree.delete_entry(temp))
        cout << "Entry deleted!\n";
    else
        cout << "Not found. \n";


    my_tree.display_all();

    return 0;
}
