/*****************************************************************
//
//  NAME:        Aris Carlos
//
//  HOMEWORK:    Project 2
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        April 25, 2023
//
//  FILE:        user_interface.cpp
//
//  DESCRIPTION:
//   This source code file contains the user interface to be used
//   for the bank database using a linked list.
//
//
****************************************************************/

#include <iostream>
#include <iomanip>
#include <cstring>
#include "llist.h"
#include "record.h"

using namespace std;

void getaddress(char [], int);
void getAccountNum(int *);

/*****************************************************************
//
//  Function name: main
//
//  DESCRIPTION:   Provides a menu to the user with options that
//                 allow the user to interact with the records in
//                 the bank database.
//
//  Parameters:    argc (int) : number of arguments
//                 argv (char*[]): array of arguments
//
//  Return values:  0 : successful run
//                 -1 : error running the program
//
****************************************************************/

int main(int argc, char* argv[])
{
    llist bank;
    char selection[12], name[30], address[50], buffer[20];
    int running, select_len, accountno;

    running = 1;
    
    #ifdef DEBUG
    cout << "\nDEBUG MODE ON\n";
    #endif
    cout << "\n$$$ Welcome to the 'YourBank' user database! $$$" << endl;

    while(running == 1)
    {
        cout << "\nTo perform an action, please type in your selection from the list of options below:\n\n";
        cout << "add: create and add a new record to the banking database\n";
        cout << "printall: displays all the current bank records to your screen\n";
        cout << "find: find an existing record in the bank database\n";
        cout << "delete: remove an existing record from the bank database\n";
        cout << "quit: exit the bank database interface\n";
        
        cin.getline(selection, 12);
        select_len = strlen(selection);
        selection[select_len] = '\0';
        
        #ifdef DEBUG
        cout << " - selection: " << selection << "\n - select_len: " << select_len << endl;
        #endif

        if(select_len > 0 && strncmp(selection, "add", select_len) == 0)
        {
            cout << "Please provide an Account Number for the new entry:\n";
            getAccountNum(&accountno);
            cin.getline(buffer, 20);

            cout << "Please enter the User's Name:\n(Max 30 characters)\n";
            cin.getline(name, 30);

            getaddress(address, 50);
            cin.getline(buffer, 20);

            bank.addRecord(accountno, name, address);
            cout << "The new record has been added to the database.";
        }
        else if(select_len > 0 && strncmp(selection, "printall", select_len) == 0)
        {
            bank.printAllRecords();
        }
        else if(select_len > 0 && strncmp(selection, "find", select_len) == 0)
        {
            cout << "Enter the Account Number to search for:\n";
            getAccountNum(&accountno);
            cin.getline(buffer, 20);

            if (bank.findRecord(accountno) == 0)
            {
                cout << "Records with the Account Number '" << accountno << "' found:\n";
            }
            else
            {
                cout << "No records with the Account Number '" << accountno << "' found.";
            }
        }
        else if(select_len > 0 && strncmp(selection, "delete", select_len) == 0)
        {
            cout << "Enter the Account Number of the record to be deleted:\n";
            getAccountNum(&accountno);
            cin.getline(buffer, 20);

            if (bank.deleteRecord(accountno) == 0)
            {
                cout << "Records with the Account Number '" << accountno << "' have been deleted.";
            }
            else
            {
                cout << "Could not find records with the Account Number '" << accountno << "' to delete.";
            }
        }
        else if(select_len > 0 && strncmp(selection, "quit", select_len) == 0)
        {
            cout << "Exiting 'YourBank' user database, have a nice day!\n";
            running = 0;
        }
        else
        {
            cout << "Not a valid menu option, please enter an option that matches an option listed on the menu\n";
        }
    }

    return 0;
}

/*****************************************************************
//
//  Function name: getaddress
//
//  DESCRIPTION:   Obtains the address of a user to be kept in 
//                 a bank record.
//
//  Parameters:    address (char[]) : String for user's address
//                 size (int) : Size of the char array for address
//
//  Return values:  N/A : void return type
//
****************************************************************/

void getaddress(char address[], int size)
{
    int idx = 0;
    
    #ifdef DEBUG
    cout << "DEBUG\nFunction call: getaddress\nParameters received:" << endl;
    cout << " - address: " << address << "\n - size: " << size << endl;
    #endif

    cout << "Please enter the user's address:\n";
    cout << "(Type in ';' to complete address entry, max 50 characters)\n";

    do
    {
        address[idx] = cin.get();
        idx = idx + 1;
    }
    while(idx < size && address[idx - 1] != ';');

    address[idx - 1] = '\0';
}

/*****************************************************************
//
//  Function name: getAccountNum
//
//  DESCRIPTION:   Obtains the account number of a bank record to 
//                 be used in database actions.
//
//  Parameters:    accountno (int*) : Pointer to where the account
//                 number is stored
//
//  Return values:  N/A : void return type
//
****************************************************************/

void getAccountNum(int *accountno)
{
    int input, running;
    
    running = 1;

    while (running == 1)
    {
        running = 0;
        cin >> input;
        #ifdef DEBUG
        cout << " - input: " << input << endl;
        #endif

        if (cin.fail())
        {
            running = 1;
            cout << "Invalid input, please enter an integer\n" << endl;
            cin.clear();
            cin.ignore(100, '\n');
        }
        else if (input <= 0)
        {
            running = 1;
            cout << "Number cannot be 0 or negative, please enter a positive integer" << endl;
            cin.ignore(100, '\n');
        }
    }

    *accountno = input;
}

