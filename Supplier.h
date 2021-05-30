
#ifndef CAR_PROJECT_BY_TREES_SUPPLIER_H
#define CAR_PROJECT_BY_TREES_SUPPLIER_H

#include "matam.h"
#include <stdio.h>
#include <string.h>
#include "ValidInput.h"

#define AUTH_DEALER_NUM_LEN 10
#define SUPP_PHONE_LEN 10
#define MIN_NUM_DEALS 9999
#define MAX_NUM_DEALS 100000
#define MIN_SUM_DEALS 999999999
#define MAX_SUM_DEALS 10000000000
typedef struct {
    char authorized_dealer_num[AUTH_DEALER_NUM_LEN + 1];
    char *supplier_name;
    char supplier_phone_num[SUPP_PHONE_LEN + 1];
    int number_of_deals_withSupp;
    long sum_of_general_deals_withSupp;
} Supplier;

typedef struct SupplierNode {
    Supplier *data;
    struct SupplierNode *right;
    struct SupplierNode *left;
} SupplierNode;


typedef struct SupplierTree {
    SupplierNode *root;
    int elementCount;
} SupplierTree;

SupplierTree* createSupplierTree();


int addNewSupplier(SupplierTree *suppTree);

int  deleteAllSuppliers(SupplierTree *suppTree);

int deleteSupplier(SupplierTree *suppTree);

void display(SupplierNode *suppRoot);
char** threeGreatestSuppliers(SupplierTree* supptree ,char threeGreatSupp[3][11] );

long averageOfSupplierMoney(SupplierNode* supptree   , long * n );


#endif
