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
//  FILE:        llist.h
//
//  DESCRIPTION:
//   This file contains the class prototype for the linked list
//   to be used as part of implementing the bank database.
//
//
****************************************************************/

#ifndef LLIST_H
#define LLIST_H
#include "record.h"

class llist
{
private:
    struct record * start;
    char     filename[20];
    int      readfile();
    int      writefile();
    void     cleanup();

public:
    llist();
    llist(char[]);
    ~llist();
    void addRecord(int, char [], char []);
    int findRecord(int);
    void printAllRecords();
    int deleteRecord(int);
};

#endif
