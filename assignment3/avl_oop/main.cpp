#include "avl.h"
using namespace std;
bool again()
{
    char response;

    cout << "Another? ";
    cin >> response;
    cin.ignore(100,'\n');

    if (response == 'y' )
        return true;
    return false;
}

int main()
{
    avl my_tree;

    do {
        int response;

        cout << "Enter a number: ";
        cin >> response;
        cin.ignore(100,'\n');

        node temp(response);

        my_tree.insert(temp);

    } while(again());

    my_tree.display_all();

    return 0;
}
