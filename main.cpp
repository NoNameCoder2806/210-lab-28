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
const int MAX_CHOICE = 10;

// Function prototypes
int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
int main_menu();
void sortNames(list<Goat> &trip);
void sortAge(list<Goat> &trip);
void displayYoungest(const list<Goat> &trip);
void displayOldest(const list<Goat> &trip);
void countAboveAge(const list<Goat> &trip);
void increaseAge(list<Goat> &trip);

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
                cout << "Sorting goat by name.\n";
                sortNames(trip);
                break;
            }

            // Sort Goats based on age
            case 5:
            {
                cout << "Sorting goat by age.\n";
                sortAge(trip);
                break;
            }

            // Display the youngest Goat objects
            case 6:
            {
                cout << "Displaying the youngest goats.\n";
                displayYoungest(trip);
                break;
            }

            // Display the oldest Goat objects
            case 7:
            {
                cout << "Displaying the oldest goats.\n";
                displayOldest(trip);
                break;
            }

            // Count Goat objects above a certain age
            case 8:
            {
                cout << "Counting and displaying goats above a certain age.\n";
                countAboveAge(trip);
                break;
            }

            // Increase all Goat objects' age by 1
            case 9:
            {
                cout << "Increasing all goats' age.\n";
                increaseAge(trip);
                break;
            }

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
    cout << "[4] Sort goats by names\n";
    cout << "[5] Sort goats by age\n";
    cout << "[6] Display the youngest goats\n";
    cout << "[7] Display the oldest goats\n";
    cout << "[8] Count and display goats above a certain age.\n";
    cout << "[9] Increase goats age by 1.\n";
    cout << "[10] Quit.\n";

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
    Add a Goat object into the Goat list (trip)
    Arguments:
        - trip: the list of Goat objects (passed by reference)
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
    Delete a Goat object from the Goat list (trip)
    Arguments:
        - trip: the list of Goat objects (passed by reference)
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
    Display the whole Goat list
    Arguments: 
        - trp: the list of Goat objects (passed by value)
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
        - trp: the list of Goat objects (passed by value)
    Return:
        - the index of the Goat in the list
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
    Sort the Goat objects by name
    Arguments:
        - trip: the list of Goat objects (passed by reference)
    Return: none
*/
void sortNames(list<Goat> &trip)
{
    // Display a message
    cout << " --- SORT GOATS BY NAME --- \n";

    // Call the built-in sort() from list
    trip.sort();

    // Display a message
    cout << " --- SORTED GOATS BY NAME! --- \n";
}

/*
    sortAge()
    Sort the Goat objects by age
    Arguments:
        - trip: the list of Goat objects (passed by reference)
    Return: none
*/
void sortAge(list<Goat> &trip)
{
    // Display a message
    cout << " --- SORT GOATS BY AGE --- \n";

    // Call the built-in sort() from list
    trip.sort([](const Goat &a, const Goat &b)
    {   
        // Create a lambda that compares the age of the 2 Goat objects
        return a.get_age() < b.get_age();
    });
    
    // Display a message
    cout << " --- SORTED GOATS BY AGE! --- \n";
}

/*
    displayYoungest()
    Display all the youngest goats in the list
    Arguments:
        - trip: the list of Goat objects (passed by const reference)
    Return: none
*/
void displayYoungest(const list<Goat> &trip)
{
    // Display a message
    cout << " --- DISPLAY THE YOUNGEST GOATS IN THE TRIP --- \n";

    // Declare a variable to hold the min age
    int min_age = MAX_AGE;

    // Iterate through the list and store the min age
    auto min_it = min_element(trip.begin(), trip.end(), [](const Goat &a, const Goat &b)
    {
        // Create a lambda and compare the age between the 2 goats
        return a.get_age() < b.get_age();
    });

    // Store the min age
    min_age = min_it->get_age();

    // Create a counter
    int i = 1;

    // Iterate through the list
    for (auto g : trip)
    {
        // Check the goats' age
        if (g.get_age() == min_age)
        {
            // Display all the Goat objects
            cout << "\t" 
                << "[" << i++ << "] "
                << g.get_name() 
                << " (" << g.get_age() 
                << ", " << g.get_color() << ")\n";
        }
    }
}

/*
    displayOldest()
    Display all the oldest goats in the list
    Arguments:
        - trip: the list of Goat objects (passed by const reference)
    Return: none
*/
void displayOldest(const list<Goat> &trip)
{
    // Display a message
    cout << " --- DISPLAY THE OLDEST GOATS IN THE TRIP --- \n";

    // Declare a variable to hold the min age
    int max_age = 0;

    // Iterate through the list and store the min age
    auto max_it = max_element(trip.begin(), trip.end(), [](const Goat &a, const Goat &b)
    {
        // Create a lambda and compare the age between the 2 goats
        return a.get_age() < b.get_age();

        // Note: for both the min_element() and max_element() function,
        // the first object has to be less than / smaller than the second object
    });

    // Store the min age
    max_age = max_it->get_age();

    // Create a counter
    int i = 1;

    // Iterate through the list
    for (auto g : trip)
    {
        // Check the goats' age
        if (g.get_age() == max_age)
        {
            // Display all the Goat objects
            cout << "\t" 
                << "[" << i++ << "] "
                << g.get_name() 
                << " (" << g.get_age() 
                << ", " << g.get_color() << ")\n";
        }
    }
}

/*
    countAboveAge()
    Counts and display all the goats above a certain age
    Arguments:
        - trip: the list of Goat objects (passed by const reference)
    Return: none
*/
void countAboveAge(const list<Goat> &trip)
{
    // Display a message
    cout << " --- COUNT AND DISPLAY GOATS ABOVE A CERTAIN AGE --- \n";

    // Declare variables to hold the age and count
    int age = 0;
    int count = 0;

    // Prompt user to enter an age
    cout << " - Enter an age: ";
    cin >> age;
    cin.ignore(1000, 10);

    // Validate the input
    while(age < 0 || age > MAX_AGE)
    {
        // Display an error message and prompt the user to enter a new age
        cout << "Error! Please enter a valid age (0-20): ";
        cin >> age;
        cin.ignore(1000, 10);
    }

    // Count the goats
    count = count_if(trip.begin(), trip.end(), [age](const Goat &g)
    {
        return g.get_age() > age;
    });

    // Display a message
    cout << "There are " << count << " goat(s) above the age of " << age << endl;

    // Declare another counter
    int i = 1;

    // Iterate through the list
    for (auto g: trip)
    {
        // Check the goat's age
        if (g.get_age() > age)
        {
            // Display all the Goat objects
            cout << "\t" 
                << "[" << i++ << "] "
                << g.get_name() 
                << " (" << g.get_age() 
                << ", " << g.get_color() << ")\n";
        }
    }
}

/*
    increaseAge()
    Increase all the goats age by 1
    Arguments:
        - trip: the list of Goat objects (passed by reference)
    Return: none
*/
void increaseAge(list<Goat> &trip)
{
    // Display a message
    cout << " --- INCREASE GOATS AGE BY 1 --- " << endl;

    // Use for_each() from <algorithm> to modify the goats age
    for_each(trip.begin(), trip.end(), [](Goat &g)
    {
        // Check the age limit
        if (g.get_age() < MAX_AGE)
        {
            // Increase the age by 1
            g.set_age(g.get_age() + 1);
        }
    });
}