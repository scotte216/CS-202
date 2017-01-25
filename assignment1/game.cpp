// Scott Ewing
// CS 202
// Assignment 1
//
// filename: game.cpp
//
#include "game.h"

using namespace std;

const int MAX = 100; // used for user input


//Default constructor, sets up the map with 6 rooms and a score of 0. Runs
//setup()
game::game():my_map(6),score(0)
{
    setup();
}

//default destructor. No dynamic memory allocated, so nothing in here. 
game::~game()
{
}

// Sets up the game.
void game::setup()
{
    //temporary problem for determining math problems in each room.
    problem temp_problem;

    // sets up temp room for setting name and description of each room. 
    room temp("Introduction","Welcome to Math-venture! \nYour goal is to move from room to room, solve the math problems and collect the items to win. \nTo collect an item, solve the problem in each room. \nYou must collect all the items to complete the level. \nGood luck!");
    //adds a room to the map.
    my_map.add_vertex(temp);
    
    //changes temp to next room
    temp.set_name("Warehouse");
    temp.set_desc("Rows upon rows of crates line this warehouse. After a cursory inspection, you determine that there are 35 rows of crates. Each row contains 15 crates. At first it seem like the crates are countless, but then you start to wonder how many crates exactly there are in this dusty old warehouse...");

    //sets up problem for the room and adds it.
    temp_problem.change_problem(35,'*',15);
    temp.add_problem(temp_problem);
    //Sets up an item into the room and adds it.
    attributes item("Screw driver","A normal philip's head screw driver.");
    temp.add_item(item);
    //adds the room to the map.
    my_map.add_vertex(temp);
    //clears out the items in the temp room.
    temp.remove_all_items();
    //Repeats these steps for each room

    temp.set_name("Manufacturing");
    temp.set_desc("This room looks like an assembly line, but at the moment the machinery is silent. As you start making your way through the room you start to fill your pockets with nails that you find laying about. Once you're satisfied that you've collected them all, you determine that you have 27 in one pocket and 14 in the other. Now, if you only had a hammer...");
    temp_problem.change_problem(27,'+',14);
    temp.add_problem(temp_problem);
    item.set_name("Nails");
    item.set_desc("Plain steel nails, each about 1 inch long.");
    temp.add_item(item);
    my_map.add_vertex(temp);
    temp.remove_all_items();

    temp.set_name("Offices");
    temp.set_desc("Cubicles. So many cubicles. This must be where the busy-work of the office routine is completed. Day in and day out, the drones push their pencils and partake in the tedium of their work. Looking at the schedules you determine that the workers put in a total of 3000 hours over the last 5 days and you wonder how many hours that is per day...");
    temp_problem.change_problem(3000,'/',5);
    temp.add_problem(temp_problem);
    item.set_name("Flashlight");
    item.set_desc("A standard flashlight.");
    temp.add_item(item);
    my_map.add_vertex(temp);
    temp.remove_all_items();

    temp.set_name("Shipping");
    temp.set_desc("This room seems to be where the products are shipped out. Judging by the marks on the floor, it looks like there were 60 containers to be shipped, but 32 are missing. But it's so dark in here, you can't find a way out except back into the complex. If you find a flashlight you might reveal new exits.");
    temp_problem.change_problem(60,'-',32);
    temp.add_problem(temp_problem);
    item.set_name("Hammer");
    item.set_desc("This is a typical hammer, useful for driving nails, removing nails, and breaking things.");
    temp.add_item(item);
    my_map.add_vertex(temp);
    temp.remove_all_items();

    temp.set_name("Escape");
    temp.set_desc("You made it! After collecting all the items, you were able to find the exit and break your way out. You've reached freedom! \n\nIf you are finished, type 'quit'\n");

    //sets the last room to hidden and locked. The user will need to find a
    //flashlight to find the room and collect all items to pass into the locked
    //room. 
    temp.set_hidden(true);
    temp.set_locked(true);
    my_map.add_vertex(temp);

    // Sets up the connections between all rooms.
    //
    //            Introduction
    //                 |
    //             Warehouse
    //            /         \
    //        Offices    Manufacturing
    //               \   /
    //                 |
    //              Shipping
    //                 | (hidden, locked)
    //               Escape
    my_map.add_adj("Introduction","Warehouse");
    my_map.add_adj("Warehouse","Introduction");

    my_map.add_adj("Warehouse","Manufacturing");
    my_map.add_adj("Warehouse","Offices");

    my_map.add_adj("Manufacturing","Warehouse");
    my_map.add_adj("Manufacturing","Shipping");

    my_map.add_adj("Offices","Warehouse");
    my_map.add_adj("Offices","Shipping");

    my_map.add_adj("Shipping","Manufacturing");
    my_map.add_adj("Shipping","Offices");
    my_map.add_adj("Shipping","Escape");
}

//Function to prompt the user for an input and parses the response
int game::prompt()
{
    char * response = new char[MAX];
    int result = 0;

    cout << "> ";
    cin.get(response,MAX,'\n');
    cin.ignore(MAX,'\n');
    
    // Sets the response from the map for travelings. Could be 1 for succes, -1
    // for locked or 0 for no available room to travel to. 
    int travel_response = my_map.travel(response,inventory);

    if (!strcmp(response,"help"))
    {
        display_help();
        result = -1;
    }
    else if (!strcmp(response,"look"))
        result = 1;
    else if (!strcmp(response,"quit"))
        result = 2;
    else if (!strcmp(response,"solve"))
        result = 3;
    else if (!strcmp(response,"inventory"))
        result = 4;
    else if(travel_response == 1)
        result = 1;
    else if(travel_response == -1)
        result = 5;
    else
        result = 0;

    delete [] response;
    return result;
}


// Displays the help file
void game::display_help()
{
    cout << "This is the help file.\n-------------"
         << "\nTo travel type the complete destination name"
         << " (ex: warehouse)"
         << "\nType \"look\" to see the room you are in."
         << "\nType \"inventory\" to see what you have collected and your score."
         << "\nType \"solve\" to attempt the puzzle in the room."
         << "\nType \"quit\" to end the game."
         << "\nType \"help\" to see this message again.\n";
}

// Displays the intro message.
void game::display_intro()
{
    cout << "Welcome to the game! Be sure to read all the instructions carefully.\n"
         << "Type 'help' to get detailed help.\n\n";
}


//Displays the farewell message
void game::display_goodbye()
{
    cout << "You ended the game with " << score << " points out of 400."
         << "\nThanks for playing!\n";
}


// Puts it all together. Takes the results from prompt and executes proper
// commands based on user input. 
void game::run()
{
    int prompt_result;
    //intro message.
    display_intro();
    
    //Displays first room
    my_map.display(inventory);

    //prompts user for input, parses.
    prompt_result = prompt();

    //result of 2 is QUIT and exits.
    while (prompt_result !=2 )
    {
        // Result of 0 is an invalid response.
        if (prompt_result == 0)
            cout << "Huh?  (Type \"help\" for help.)\n";
        //response of 1 means successful movement through the map
        else if (prompt_result == 1)
        { 
            //display new room
            my_map.display_room_name();
            cout << endl;
            my_map.display(inventory);
        }
        // a 3 is an attempt to solve the puzzle in a given room.
        else if (prompt_result == 3)
        {
            int response = my_map.solve_problem();
            if (1 == response)
            {
                cout << "Correct! +100 points!\n";
                my_map.collect(inventory); 
                score +=100;
            }
            else if (-1 == response)
                cout << "There is no problem in this room.\n";
            else
                cout << "Incorrect. Type 'solve' to try again.\n";
            
        }
        // A 4 results in displaying the users's current inventory of collected
        // objects and current score. 
        else if (prompt_result == 4)
        {
            cout << "You have collected the following:\n";
            inventory.inventory();
            cout << "Current score: " << score << endl;
        }

        // Display prompt for parsing next input from user.
        prompt_result = prompt();
    }

    //display goodbye message.
    display_goodbye();

}
