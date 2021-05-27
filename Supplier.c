
#include "Supplier.h"

SupplierTree *createSupplierTree() {
    SupplierTree *suppTree = (SupplierTree *) checked_malloc(sizeof(SupplierTree));
    suppTree->elementCount = 0;
    suppTree->root = NULL;
    return suppTree;
}

int checkValues(char *authorized_dealer_num, char *supplier_name, char *supplier_phone_num,
                long sum_of_general_deals_withSupp, int number_of_deals_withSupp) {
    /*CHECK IF THE VALUES INPUT IS ACCORDING THE LEGALITY*/
    /*LEN CHECK*/
    if (valid_digit_check(authorized_dealer_num) == 0) {
        printf("authorized dealer number not valid\n");
        return FALSE;
    }
    if (check_equal_size(authorized_dealer_num, AUTH_DEALER_NUM_LEN) == 0) {
        printf("authorized dealer number not valid\n");
        return FALSE;
    }
    if (valid_char_check(supplier_name) == 0) {
        printf("supplier name not valid\n");
        return FALSE;
    }
    if (check_equal_size(supplier_phone_num, SUPP_PHONE_LEN) == 0) {
        printf("supplier phone number not valid\n");
        return FALSE;
    }

    if (valid_digit_check(supplier_phone_num) == 0) {
        printf("supplier phone number not valid\n");
        return FALSE;
    }

    if (valid_long(sum_of_general_deals_withSupp, MIN_SUM_DEALS, MAX_SUM_DEALS) == 0) {
        printf("sum of general deals not valid\n");
        return FALSE;
    }
    if (valid_int(number_of_deals_withSupp, MIN_NUM_DEALS, MAX_NUM_DEALS) == 0) {
        printf("number of deals not valid\n");
        return FALSE;
    }

    return TRUE;
}

Supplier *initSupplier() {
    /*INITIALIZING THE SUPPLIER*/
    char authorized_dealer_num[AUTH_DEALER_NUM_LEN + 1];
    char *supplier_name = (char *) checked_malloc(sizeof(char) * 1024);
    char supplier_phone_num[SUPP_PHONE_LEN + 1];
    long sum_of_general_deals_withSupp;
    int number_of_deals_withSupp;
    Supplier *temporarySupp = (Supplier *) checked_malloc(sizeof(Supplier));

    printf("enter authorized_dealer_num (10 DIGITS): ");
    scanf("%s", authorized_dealer_num);
    printf("enter supplier_name : ");
    scanf("%s", supplier_name);
    printf("enter  supplier_phone_num (10 DIGITS): ");
    scanf("%s", supplier_phone_num);
    printf("enter  number_of_deals_withSupp (5 DIGITS): ");
    scanf("%d", &number_of_deals_withSupp);
    printf("enter  sum_of_general_deals_withSupp (10 DIGITS): ");
    scanf("%ld", &sum_of_general_deals_withSupp);

    if (checkValues(authorized_dealer_num, supplier_name, supplier_phone_num,
                    sum_of_general_deals_withSupp, number_of_deals_withSupp) == 1) {

        strcpy(temporarySupp->supplier_phone_num, supplier_phone_num);
        temporarySupp->supplier_name = dupstr(supplier_name);
        strcpy(temporarySupp->authorized_dealer_num, authorized_dealer_num);
        temporarySupp->sum_of_general_deals_withSupp = sum_of_general_deals_withSupp;
        temporarySupp->number_of_deals_withSupp = number_of_deals_withSupp;
    } else {
        strcpy(temporarySupp->authorized_dealer_num, "-1");
        checked_free(supplier_name);
    }
    return temporarySupp;
}


SupplierNode *addNodeToTree(SupplierNode *suppRoot, SupplierNode *newSupp) {
    if (suppRoot == NULL) {
        return newSupp;
    } else {
        if (suppRoot->right == NULL || suppRoot->left == NULL) {
            if (newSupp->data->sum_of_general_deals_withSupp > suppRoot->data->sum_of_general_deals_withSupp) {
                suppRoot->left = addNodeToTree(suppRoot->left, newSupp);
            } else {
                suppRoot->right = addNodeToTree(suppRoot->right, newSupp);
            }
        } else {
            if (newSupp->data->sum_of_general_deals_withSupp > suppRoot->data->sum_of_general_deals_withSupp) {
                addNodeToTree(suppRoot->left, newSupp);
            } else {
                addNodeToTree(suppRoot->right, newSupp);
            }
        }
    }
}


int addNewSupplier(SupplierTree *suppTree) {
    SupplierNode *newSupp = (SupplierNode *) checked_malloc(sizeof(SupplierNode));
    newSupp->data = initSupplier();
    newSupp->left = NULL;
    newSupp->right = NULL;
    if (suppTree->root == NULL) {
        suppTree->root = newSupp;
    } else {
        suppTree->root = addNodeToTree(suppTree->root, newSupp);
    }
}

