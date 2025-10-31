// COMSC-210 | Lab 28 | Dat Hoang Vien
// IDE used: Visual Studio Code

// Libraries and headers
#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <algorithm>
#include "Goat.h"
using namespace std;

// Constants
const int SZ_NAMES = 200;
const int SZ_COLORS = 25;
const int MIN_CHOICE = 1;
const int MAX_CHOICE = 5;

// Function prototypes
int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
int main_menu();
void sortNames(list<Goat> &trip);
void sortAge(list<Goat> &trip);

// Main function
int main()
{
    // Call srand() and time()
    srand(time(0));

    // Create a boolean
    bool again;

    // Read & populate array for names
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();

    // Read & populate array for colors
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    // Create & populate a trip of Goats using std::list of random size 8-15
    int tripSize = rand() % 8 + 8;

    // Create a Goat trip using list
    list<Goat> trip;

    // Create some variables to store the Goat's information
    int age;
    string name, color;


    for (int i = 0; i < tripSize; i++)
    {
        // Populate the variables
        age = rand() % MAX_AGE;
        name = names[rand() % SZ_NAMES];
        color = colors[rand() % SZ_COLORS];

        // Create a Goat object using constructor
        Goat tmp(name, age, color);

        // Add the Goat object to the list
        trip.push_back(tmp);
    }
    
    // Goat Manager 3001 Engine
    int sel = main_menu();
    while (sel != MAX_CHOICE)
    {
        switch (sel)
        {
            // Add a Goat
            case 1:
            {
                cout << "Adding a goat.\n";
                add_goat(trip, names, colors);
                break;
            }

            // Delete a Goat
            case 2:
            {
                cout << "Removing a goat.\n";
                delete_goat(trip);
                break;
            }

            // Display the Goat đata
            case 3:
            {
                cout << "Displaying goat data.\n";
                display_trip(trip);
                break;
            }

            // Sort Goats based on name
            case 4:
            {
                cout << "Sorting goat names.\n";
                sortNames(trip);
                break;
            }

            // Sort Goats based on age

            // Display the younger Goat objects

            // Display the oldest Goat objects

            // Count Goat objects above a certain age

            // Increase all Goat objects' age by 1

            // Find a Goat object by name

            // Display the Goat objects in reversed order

            // Other invalid choices
            default:
            {
                cout << "Invalid selection.\n";
                break;
            }
        }
        
        // Display the menu again
        sel = main_menu();
    }
    

    return 0;
}

// Function implementations
/*
    main_menu()
    Display the menu of operations
    Arguments: none
    Return: 
        - An int representing the user's choice
*/
int main_menu()
{
    // Display all the options
    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Sort goats based on names\n";
    cout << "[5] Quit\n";

    // Prompt the user to enter a choice
    cout << "Choice --> ";

    // Get the user's choice
    int choice;
    cin >> choice;

    // Validate the entered option
    while (choice < MIN_CHOICE || choice > MAX_CHOICE)
    {
        // Display an error message
        cout << "Invalid, again --> ";
        cin >> choice;
    }

    // Return the choice
    return choice;
}

/*
    add_goat()
    Add a Goat object into the Goat set (trip)
    Arguments:
        - trip: the set of Goat objects (passed by reference)
        - nms: an array containing all the Goat names (passed by value)
        - cls: an array containing all the Goat colors (passed by value)
    Return: none
*/
void add_goat(list<Goat> &trip, string nms[], string cls[])
{
    // Display a message
    cout << " --- ADD A GOAT --- \n";

    // Declare and populate some variables to store the Goat object's data
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];

    // Create the Goat object
    Goat tmp(nm, age, cl);

    // Add the Goat object into the trip
    trip.push_back(tmp);

    // Display a message notifying the addition
    cout << "Goat added. New trip size: " << trip.size() << endl;
}

/*
    delete_goat()
    Delete a Goat object from the Goat set (trip)
    Arguments:
        - trip: the set of Goat objects (passed by reference)
    Return: none
*/
void delete_goat(list<Goat> &trip)
{
    // Display a message
    cout << " --- DELETE A GOAT --- \n";

    // Declare an int and store the Goat to delete
    int index = select_goat(trip);

    // Declare an iterator and advance it to the index
    auto it = trip.begin();
    advance(it, index-1);

    // Delete the Goat object from the list
    trip.erase(it);

    // Display a message notifying the deletion
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
}

/*
    display_trip()
    Display the whole Goat set
    Arguments: 
        - trp: the set of Goat objects (passed by value)
    Return: none
*/
void display_trip(list<Goat> trp)
{
    // Create an int counter
    int i = 1;

    // Iterate through the trip
    for (auto gt: trp)
    {
        // Display all the Goat objects
        cout << "\t" 
             << "[" << i++ << "] "
             << gt.get_name() 
             << " (" << gt.get_age() 
             << ", " << gt.get_color() << ")\n";
    }
}

/*
    select_goat()
    Allow user to select a Goat object from the trip
    Arguments:
        - trp: the set of Goat objects (passed by value)
    Return:
        - the index of the Goat in the set
*/
int select_goat(list<Goat> trp)
{
    // Create an int to store the user's input
    int input;

    // Display the Goat trip
    cout << "Make a selection:\n";
    display_trip(trp);

    // Prompt the user to select the Goat
    cout << "Choice --> ";
    cin >> input;

    // Validate the input
    while (input < 1 || input > trp.size())
    {
        // Prompt the user to enter a new choice
        cout << "Invalid choice, again --> ";
        cin >> input;
    }

    // Return the selected index
    return input;
}

/*
    sortNames()
    Sort the Goat obbjects based on names
*/
void sortNames(list<Goat> &trip)
{
    // Call the built-in sort() from list
    trip.sort();
}

void sortAge(list<Goat> &trip)
{

}