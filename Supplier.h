
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

typedef struct SupplierList {
    Supplier *data;
    struct SupplierTree *right;
    struct SupplierTree *left;
} SupplierList;


typedef struct SupplierTree {
    SupplierList *root;
    int elementCount;
} SupplierTree;


SupplierList *createSupplierList();

int addNewSupplier(SupplierList **head);

int deleteSupplier(SupplierList **head);

int deleteAllSuppliers(SupplierList **head);

char **threeGreatestSuppliers_REC(SupplierList **head, char threeGreatSupp[3][11]);

char **threeGreatestSuppliers(SupplierList **head, char threeGreatSupplier[3][11]);





#endif //CAR_PROJECT_BY_TREES_SUPPLIER_H
