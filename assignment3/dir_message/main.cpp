#include "message.h"
#include "simple_string.h"

using namespace std;

int main()
{ 
    simple_string name,address,body;
    message * a_message;
    name = "Scott";
    address = "345 ad";
    body = "Hi there! This is a message.";

    a_message = new facebook(body,address,name);
    
    a_message->display();
    
    delete a_message;
    return 0;
}

