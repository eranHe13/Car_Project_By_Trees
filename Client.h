
#ifndef CAR_PROJECT_BY_TREES_CLIENT_H
#define CAR_PROJECT_BY_TREES_CLIENT_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ValidInput.h"
#include "matam.h"
#include <ctype.h>
#define LICENSE_LEN 7
#define ID_LEN 9

typedef struct {
    int year;
    int month;
    int day;
}Date;

Date create_date(int year, int month, int day);

void print_date(Date d);

typedef struct{
    int hour;
    int minute;
}Time;

Time create_time(int hour, int minute);

void print_time( Time t);

typedef struct {
    char* first_name;
    char* last_name;
    char id[ID_LEN + 1];
    char license_number[LICENSE_LEN+1];
    Date date_of_rent;
    Time hour_of_rent;
    int price_per_rent;
}Client;
typedef struct ClientNode {
    Client *data;
    struct ClientNode *right;
    struct ClientNode *left;
} ClientNode;


typedef struct ClientTree {
    ClientNode *root;
    int elementCount;
} ClientTree;
ClientTree *createClientTree();
int addNewClient(ClientTree *clientTree);
int deleteClient(ClientTree *tree);
int deleteAllClients(ClientTree* tree);
int printClientCarsForGivenRentDate(ClientTree *clientTree);

#endif
