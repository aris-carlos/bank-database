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
//  FILE:        llist.cpp
//
//  DESCRIPTION:
//   This source code file contains the class definition for the linked list
//   to be used for the bank database. These methods are called
//   in user_interface.cpp which allows the user to pass in and view
//   stored data.
//
//
****************************************************************/

#include <iostream>
#include <fstream>
#include <cstring>
#include "llist.h"
#include "record.h"

using namespace std;

struct record * start;
char filename[20];

/*****************************************************************
//
//  Function name: readfile
//
//  DESCRIPTION:   Reads the file that contains the saved record
//                 contents and loads them into the linked list.
//
//  Parameters:    N/A
//
//  Return values: N/A : void return type
//
****************************************************************/

int llist::readfile()
{
    ifstream filein(this->filename);
    char name[30], address[50];
    int status, accountno, idx, eofcheck;

    #ifdef DEBUG
    cout << "DEBUG\nFunction call: readfile" << endl;
    cout << "Object fields:\n - start: " << this->start << "\n - filename: " << this->filename << endl;
    cout << "Reading file " << this->filename << "and loading saved records into database" << endl;
    #endif

    if (filein.fail())
    {
        status = -1;
        #ifdef DEBUG
        cout << "Failed to open file!" << endl;
        #endif
    }
    else
    {
        eofcheck = filein.peek();
        if (eofcheck == EOF)
        {
            #ifdef DEBUG
            cout << "File is empty!" << endl;
            #endif
            status = -1;
        }
        else
        {
            #ifdef DEBUG
            cout << "Reading lines from " << this->filename << endl;
            #endif

            while (filein.getline(address, 50))
            {
                for (idx = 0; address[idx] != '\0'; idx++) {
                    if (address[idx] == '\t' && address[idx + 1] == '\n') {
                        address[idx] = '\n';
                        address[idx + 1] = '\0';
                    } else if (address[idx] == '\t') {
                        address[idx] = '\n';
                    }
                }
                #ifdef DEBUG
                cout << "DEBUG\nRecord read from file" << endl;
                cout << " - address: " << address << endl;
                #endif
                filein.getline(name, 30);
                #ifdef DEBUG
                cout << " - name: " << name << endl;
                #endif
                filein >> accountno;
                #ifdef DEBUG
                cout << " - accountno: " << accountno << endl;
                #endif
                filein.ignore(100, '\n'); 
                addRecord(accountno, name, address);
            }
        }
        filein.close();
        status = 0;
    }

    return status;
}

/*****************************************************************
//
//  Function name: writefile
//
//  DESCRIPTION:   Writes the contents of the records in the database
//                 to a file so the records can be saved and reloaded.
//
//  Parameters:    N/A
//
//  Return values: N/A : void return type
//
****************************************************************/

int llist::writefile()
{
    ofstream fileout(this->filename);
    struct record * curr = this->start;
    char address[50];
    int status, idx;

    #ifdef DEBUG
    cout << "DEBUG\nFunction call: writefile" << endl;
    cout << "Object fields:\n - start: " << this->start << "\n - filename: " << this->filename << endl;
    cout << "Writing records in the databse to file " << this->filename << endl;
    #endif

    if (fileout.fail())
    {
        status = -1;
    }
    else
    {
        while (curr != NULL)
        {
            strcpy(address, curr->address);
            for (idx = 0; address[idx] != '\0'; idx++)
            {
                if (address[idx] == '\n')
                {
                    address[idx] = '\t';
                }
            }
            fileout << address << '\n';
            fileout << curr->name << '\n';
            fileout << curr->accountno << '\n';

            curr = curr->next;
        }
        fileout.close();
        status = 0;
    }
    return status;
}

/*****************************************************************
//
//  Function name: cleanup
//
//  DESCRIPTION:   Frees all the allocated memory spaces on the heap
//                 that were used to store the records in memory.
//
//  Parameters:    N/A
//
//  Return values: N/A : void return type
//
****************************************************************/

void llist::cleanup()
{
    struct record *curr, *next;

    #ifdef DEBUG
    cout << "DEBUG\nFunction call: cleanup" << endl;
    cout << "Object fields:\n - start: " << this->start << "\n - filename: " << this->filename << endl;
    cout << "Deallocating the stored records on the heap" << endl;
    #endif

    curr = this->start;

    while (curr != NULL)
    {
        next = curr->next;
        delete curr;
        curr = next;
    }

    this->start = NULL;
}

/*****************************************************************
//
//  Function name: llist
//
//  DESCRIPTION:   Constructs a linked list object to store records in
//
//  Parameters:    N/A
//
//  Return values: N/A : void return type
//
****************************************************************/

llist::llist()
{
    this->start = NULL;
    strcpy(this->filename, "recordsdb");
    readfile();
}

/*****************************************************************
//
//  Function name: llist
//
//  DESCRIPTION:   Constructs a linked list object to store records in
//
//  Parameters:    savefile (char[]) : name of file to read/write from
//
//  Return values: N/A : void return type
//
****************************************************************/

llist::llist(char savefile[])
{
    this->start = NULL;
    strcpy(this->filename, savefile);
    readfile();
}

/*****************************************************************
//
//  Function name: ~llist
//
//  DESCRIPTION:   Calls cleanup to free up the memory used on the heap
//                 for the linked list object.
//
//  Parameters:    N/A
//
//  Return values: N/A : void return type
//
****************************************************************/

llist::~llist()
{
    writefile();
    cleanup();
}

/*****************************************************************
//
//  Function name: addRecord
//
//  DESCRIPTION:   Using information obtained by the user, this
//                 function creates a new record and adds the
//                 record to the linked-list database
//
//  Parameters:    accountno (int) : account number for the new record
//                 name (char[]) : person's name for the new record
//                 address (char[]) : person's address for the new
//                                    record
//
//  Return values: N/A : void return type
//
****************************************************************/

void llist::addRecord(int accountno, char name[], char address[])
{
    struct record *temp, *temp2, *curr;

    #ifdef DEBUG
    cout << "DEBUG\nFunction call: addRecord\nParameters received:" << endl;
    cout << " - accountno: " << accountno << "\n - name: " << name << "\n - address: " << address << endl;
    cout << "Object fields:\n - start: " << this->start << "\n - filename: " << this->filename << endl;
    #endif

    temp = new struct record;

    temp->accountno = accountno;
    strcpy(temp->name, name);
    strcpy(temp->address, address);

    curr = this->start;

    while (curr != NULL && accountno > curr->accountno)
    {
        #ifdef DEBUG
        cout << " - curr: " << curr << "\n - curr->accountno: " << curr->accountno << endl;
        #endif
        temp2 = curr;
        curr = curr->next;
    }

    if (start == NULL)
    {
        this->start = temp;
        temp->next = curr;
    }
    else if (curr == this->start)
    {
        temp->next = this->start;
        this->start = temp;
    }
    else
    {
        temp->next = curr;
        temp2->next = temp;
    }
}

/*****************************************************************
//
//  Function name: findRecord
//
//  DESCRIPTION:   Using the account number provided, this function
//                 prints the records in the database with matching
//                 account number.
//
//  Parameters:    accountno (int) : account number to print the
//                                 records of
//
//  Return values:  0 : found records with the provided account number
//                 -1 : no records with the provided account number
//                      found
//
****************************************************************/

int llist::findRecord(int accountno)
{
    struct record * curr = this->start;
    int status = -1;

    #ifdef DEBUG
    cout << "DEBUG\nFunction call: findRecord\nParameters received:" << endl;
    cout << " - accountno: " << accountno << endl;
    cout << "Object fields:\n - start: " << this->start << "\n - filename: " << this->filename << endl;
    #endif

    while (curr != NULL)
    {
        if (curr->accountno == accountno)
        {
            cout << "\nAccount #: " << curr->accountno << endl;
            cout << "Name: " << curr->name << endl;
            cout << "Address:\n" << curr->address << endl;
            status = 0;
        }
        curr = curr->next;
    }
    
    return status;
}

/*****************************************************************
//
//  Function name: printAllRecords
//
//  DESCRIPTION:   This function prints all of the stored
//                 records in the bank database.
//
//  Parameters:    N/A
//
//  Return values:  N/A : void return type
//
****************************************************************/

void llist::printAllRecords()
{
    struct record * curr = this->start;
    
    #ifdef DEBUG
    cout << "DEBUG\nFunction call: printAllRecords" << endl;
    cout << "Object fields:\n - start: " << this->start << "\n - filename: " << this->filename << endl;
    #endif

    if (curr == NULL)
    {
        cout << "No records to be printed. The database is empty." << endl;
    }
    else
    {
        cout << "Printing all bank records..." << endl;
        while (curr != NULL)
        {
            cout << "\nAccount #: " << curr->accountno << endl;
            cout << "Name: " << curr->name << endl;
            cout << "Address:\n" << curr->address << endl;
            curr = curr->next;
        }
    }

}

/*****************************************************************
//
//  Function name: deleteRecord
//
//  DESCRIPTION:   Deletes a record from the linked list.
//
//  Parameters:    accountno (int) : account number of record to be
//                                   deleted
//                 
//  Return values:  0 : record deleted
//                 -1 : no record found
//
****************************************************************/

int llist::deleteRecord(int accountno)
{
    struct record *curr, *prev, *next;
    int status = -1;

    #ifdef DEBUG
    cout << "DEBUG\nFunction call: deleteRecord\nParameters received:" << endl;
    cout << " - accountno: " << accountno << endl;
    cout << "Object fields:\n - start: " << this->start << "\n - filename: " << this->filename << endl;
    #endif

    curr = this->start;
    
    while (curr != NULL)
    {
        next = curr->next;
        if (curr->accountno == accountno && curr == this->start)
        {
            delete curr;
            this->start = next;
            status = 0;
        }
        else if (curr->accountno == accountno)
        {
            delete curr;
            prev->next = next;
            status = 0;
        }
        else
        {
            prev = curr;
        }
        curr = next;
    }

    return status;
}
