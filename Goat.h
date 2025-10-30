// COMSC-210 | Lab 28 | Dat Hoang Vien
// IDE used: Visual Studio Code

// Goat.h
#ifndef GOAT_H
#define GOAT_H

// libraries
#include <iostream>
using namespace std;

// Constants
const int MAX_AGE = 20;

class Goat {
private:
    string name;                  // Goat's name
    int age;                      // Goat's age
    string color;                 // Goat's color

public:
    // Constructors
    Goat()                                 // Default constructor
    {
        name = "";
        age = 0;
        color = "";
    }

    Goat(string n)                         // Constructor with name
    {
        name = n;
        age = rand() % MAX_AGE;
        color = "";
    }

    Goat(string n, int a)                  // Constructor with name and age
    {
        name = n;
        age = a;
        color = "";
    }

    Goat(string n, int a, string c)        // Constructor with all parameters
    {
        name = n;
        age = a;
        color = c;
    }

    // Accessors and Mutators (Getters and Setters)
    void set_name(string n)
    { 
        name = n; 
    }

    string get_name() const
    { 
        return name; 
    }

    void set_age(int a)
    { 
        age = a;
    }

    int get_age() const
    {
        return age;
    }

    void set_color(string c)
    {
        color = c;
    }

    string get_color() const
    {
        return color;
    }

    // Member functions
    /*
        operator<()
        Compare the names between 2 Goat objects
        Arguments:
            - other: a constant reference to another Goat object to compare with.
        Return:
            - true if this Goat's name is lexicographically less than the other Goat's name.
            - false otherwise.
    */
    bool operator< (const Goat &other) const
    {
        return name < other.name;
    }
};

#endif