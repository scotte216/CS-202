// Scott Ewing
// CS 202
// Assignment 1
//
// filename: game.cpp
//
#include "game.h"


using namespace std;

const int MAX = 500; // used for user input
const int MAPSIZE = 6; //rooms in the map

//Default constructor, sets up the map with 6 rooms and a score of 0. Runs
//setup()
game::game():my_map(MAPSIZE),score(0),num_actions(2)
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
////////////
//Load rooms
////////////

    problem temp_problem;
    attributes item;
    room temp;
    char temp_name[MAX];
    char temp_desc[MAX];
    int problem_num1;
    int problem_num2;
    char problem_operator;

    ifstream file_in;
    char room_file[] = "rooms.txt";
    file_in.open(room_file);
    
    if (file_in)
    {
        //grab room name
        file_in.get(temp_name,MAX,'\n');
        file_in.ignore(MAX,'\n');
        
        while(!file_in.eof())
        {
            //check if the room's entrance should be hidden
            if (file_in.peek() != '~')
            { // set hidden;
                temp.set_hidden(true);
                temp.set_locked(true);
            }
            file_in.ignore(MAX,'\n');

            //grab the room description
            file_in.get(temp_desc,MAX,'|');
            file_in.ignore(MAX,'\n');

            //set the name and description on the temporary room
            temp.set_name(temp_name);
            temp.set_desc(temp_desc);

            //check for a problem in the room
            if (file_in.peek() != '~')
            { // Give the room a problem
                file_in >> problem_num1;
                file_in >> problem_operator;
                file_in >> problem_num2;

                temp_problem.change_problem(problem_num1,problem_operator,problem_num2);
                temp.add_problem(temp_problem);
            }

            file_in.ignore(MAX,'\n');

            //check for items in the room.
            if (file_in.peek() != '~')
            {
                file_in.get(temp_name,MAX,'\n');
                file_in.ignore(MAX,'\n');
                
                file_in.get(temp_desc,MAX,'\n');

                item.set_name(temp_name);
                item.set_desc(temp_desc);
                temp.add_item(item);
            } 

            file_in.ignore(MAX,'\n');

            //add temporary room to the map
            my_map.add_vertex(temp);

            //Clear the temporary room's hidden and locked flag, 
            //get rid of the any problems, and remove all items.
            if (temp.is_locked()) temp.set_locked(false);
            if (temp.is_hidden()) temp.set_hidden(false);
            temp_problem.change_problem(0,0,0);
            temp.add_problem(temp_problem);
            temp.remove_all_items();

            //Get the next room's desc and repeat while-loop until end of file
            file_in.get(temp_name,MAX,'\n');
            file_in.ignore(MAX,'\n');
        }

        //close the file
        file_in.close();
        file_in.clear();

//        cout << "Map loaded from: " << room_file << endl;
    }
    else
    {
        cout << "Error: " << room_file << " not found.\n";
        room_file[0] = '\0';
    }
    setup_adjacencies();
}

void game::setup_adjacencies()
{
////////////////////////
// Create adjacencies
////////////////////////
    char room1[MAX];
    char room2[MAX];
    char map_file[] = "room-connections.txt";
    ifstream file_in;
   
    file_in.open(map_file);

    if (file_in)
    {
        if (file_in.peek() != '/')
        {
            file_in.get(room1,MAX,'|');
            file_in.ignore(MAX,'|');
        }
        while(!file_in.eof())
        {
            file_in.get(room2,MAX,'\n');
            file_in.ignore(MAX,'\n');

            my_map.add_adj(room1,room2);

            if (file_in.peek() != '/')
            {
                file_in.get(room1,MAX,'|');
                file_in.ignore(MAX,'|');
            }
        }
    }
    else
    {
        cout << "Error: " << map_file << " not found.\n";
        map_file[0] = '\0';
    }
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
         << "\nType \"help\" to see this message again.\n"
         << "\nEach turn you will have " << num_actions << " actions. Everything"
         << "\nin this help file is considered an action.\n";
    ++num_actions;//The help file doens't count as an action.
}

// Displays the intro message.
void game::display_intro()
{
    cout << "Welcome to the game! Be sure to read all the instructions carefully.\n"
         << "Type 'help' to get detailed help.\n\n";
}




// Puts it all together. Takes the results from prompt and executes proper
// commands based on user input. 
int game::run()
{
    display_intro();
    return resume();
}

int game::resume()
{
    my_map.display(inventory);
    return input();
}

int game::input()
{
    int turn_result = 1;
    int counter = 0;
    //prompts user for input, parses.
    int prompt_result;

    //result of 2 is QUIT and exits.
    while (counter < num_actions && 1 == turn_result)
    {
        cout << num_actions - counter << " moves remaining.\n";
        
        prompt_result = prompt();

        // Result of 0 is an invalid response.
        // refund turn
        if (prompt_result == 0)
        {    
            cout << "Huh?  (Type \"help\" for help.)\n";
            --counter;
        }
        //response of 1 means successful movement through the map
        else if (prompt_result == 1)
        { 
            //display new room
            my_map.display_room_name();
            cout << endl;
            my_map.display(inventory);
            //If they have reached the last room, they have won! Return 2
            if (my_map.finished())
                turn_result = 2;
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
            {
                cout << "There is no problem in this room.\n";
                //refund turn if there is no problem to solve
                --counter;
            }
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
        //2 is a quit result: return's 0 to the calling program.
        else if (prompt_result == 2)
        {
            //If you don't want to quit, give them their turn back and continue.
            if (!are_you_sure())
            {
                --counter;
            }
            //else quit the game for all players.
            else 
            {
                turn_result = 0;
            }
        }
        counter++;
    }
    return turn_result;
}

bool game::are_you_sure()
{
    char * response = new char[MAX];
    bool result;

    cout << "Are you sure you want to quit? This will end the game for all players."
         << "\nType \"yes\" to confirm: ";

    cin.get(response,MAX,'\n');
    cin.ignore(MAX,'\n');

    if (!strcmp(response,"yes") || !strcmp(response,"Yes") )
        result = true;
    else
        result = false;

    delete [] response;
    return result;
}

void game::display_score()
{
    cout << score;
}

void game::display_inventory()
{
    inventory.inventory();
}
