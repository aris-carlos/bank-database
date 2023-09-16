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
//  FILE:        record.h
//
//  DESCRIPTION:
//   This file contains the structure definition for a record from
//   homework 3b to be used in the bank database assignment/project.
//
//
****************************************************************/

#ifndef RECORD_H
#define RECORD_H

struct record
{
    int    accountno;
    char   name[30];
    char   address[50];
    struct record* next;
};

#endif
