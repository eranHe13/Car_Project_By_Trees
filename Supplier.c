
#include "Supplier.h"


void printSuppliers(SupplierNode *suppRoot) {
    /* Prints all supplier*/
    SupplierNode *tmp = suppRoot;
    if (tmp == NULL)
        return;
    printSuppliers(tmp->left);
    printf("-------------------------\n");
    printf("SUPPLIER : \n");
    printf("Supplier name: %s\nDealer number: %s\nSupplier phone number: %s\nNumber of deals: %d\n"
           "Sum of deals in general: %ld\n\n",
           tmp->data->supplier_name,
           tmp->data->authorized_dealer_num,
           tmp->data->supplier_phone_num, tmp->data->number_of_deals_withSupp,
           tmp->data->sum_of_general_deals_withSupp);
    printSuppliers(tmp->right);
}

SupplierTree *createSupplierTree() {
    /*Creat binary tree os suppliers*/
    SupplierTree *suppTree = (SupplierTree *) checked_malloc(sizeof(SupplierTree));
    suppTree->elementCount = 0;
    suppTree->root = NULL;
    return suppTree;
}

Supplier *initSupplier() {
    /*Initializing supplier struct */
    int check = 9;
    char authorized_dealer_num[AUTH_DEALER_NUM_LEN + 1];
    char *supplier_name = (char *) checked_malloc(sizeof(char) * 1024);
    char supplier_phone_num[SUPP_PHONE_LEN + 1];
    long sum_of_general_deals_withSupp;
    int number_of_deals_withSupp;
    Supplier *temporarySupp = (Supplier *) checked_malloc(sizeof(Supplier));
    /*authorized_dealer_num check */
    while (check != 1) {
        printf("enter authorized dealer num (10 DIGITS): ");
        scanf("%s", authorized_dealer_num);
        if ((valid_digit_check(authorized_dealer_num) == 0) ||
            (check_equal_size(authorized_dealer_num, AUTH_DEALER_NUM_LEN) == 0)) {
            printf("authorized dealer number not valid\n");
        } else{
            strcpy(temporarySupp->authorized_dealer_num, authorized_dealer_num);
            check = 1;}
    }
    check = 0;
    /*supplier_name check */
    while (check != 1) {
        printf("enter supplier name : ");
        scanf("%s", supplier_name);
        if (valid_char_check(supplier_name) == 0) {
            printf("supplier name not valid\n");
        } else{
            temporarySupp->supplier_name = dupstr(supplier_name);
            check = 1;}
    }
    check = 0;
    /*supplier_phone_num check*/
    while (check != 1) {
        printf("enter  supplier phone num (10 DIGITS): ");
        scanf("%s", supplier_phone_num);
        if ((check_equal_size(supplier_phone_num, SUPP_PHONE_LEN) == 0) ||
            (valid_digit_check(supplier_phone_num) == 0)) {
            printf("supplier phone number not valid\n");
        } else{
            strcpy(temporarySupp->supplier_phone_num, supplier_phone_num);
            check = 1;}
    }
    check = 0;
    /*number of deals withSupp check*/
    while (check != 1) {
        printf("enter  number of deals withSupp (5 DIGITS): ");
        scanf("%d", &number_of_deals_withSupp);
        if (valid_int(number_of_deals_withSupp, MIN_NUM_DEALS, MAX_NUM_DEALS) == 0) {
            printf("number of deals not valid\n");
        } else{
            temporarySupp->number_of_deals_withSupp = number_of_deals_withSupp;
            check = 1;}
    }
    check = 0;
    /*sum of general deals withSupp check*/
    while (check != 1) {
        printf("enter  sum of general deals withSupp (10 DIGITS): ");
        scanf("%ld", &sum_of_general_deals_withSupp);
        if (valid_long(sum_of_general_deals_withSupp, MIN_SUM_DEALS, MAX_SUM_DEALS) == 0) {
            printf("sum of general deals not valid\n");
        } else{
            temporarySupp->sum_of_general_deals_withSupp = sum_of_general_deals_withSupp;
            check = 1;}
    }
    return temporarySupp;
}

SupplierNode *addNodeToTree(SupplierNode *suppRoot, SupplierNode *newSupp) {
    /*Add new supplier to the tree*/
    if (suppRoot == NULL) {
        return newSupp;
    } else {
        if (suppRoot->right == NULL || suppRoot->left == NULL) {
            if (strcmp(newSupp->data->authorized_dealer_num , suppRoot->data->authorized_dealer_num)<=0) {
                suppRoot->left = addNodeToTree(suppRoot->left, newSupp);
            } else {
                suppRoot->right = addNodeToTree(suppRoot->right, newSupp);
            }
        } else {
            if (strcmp(newSupp->data->authorized_dealer_num , suppRoot->data->authorized_dealer_num)<=0) {
                addNodeToTree(suppRoot->left, newSupp);
            } else {
                addNodeToTree(suppRoot->right, newSupp);
            }
        }
    }
    return suppRoot;
}

int addNewSupplier(SupplierTree *suppTree) {
    /*Crate new supplier and adding to the tree*/
    SupplierNode *newSupp = (SupplierNode *) checked_malloc(sizeof(SupplierNode));
    newSupp->data = initSupplier();
    newSupp->left = NULL;
    newSupp->right = NULL;
    if (suppTree->root == NULL) {
        suppTree->root = newSupp;
    } else {
        suppTree->root = addNodeToTree(suppTree->root, newSupp);
    }
    suppTree->elementCount++;
    return 1;
}

void supplierNodeClear(SupplierNode *node) {
    /*Removing all suppliers*/
    if (node == NULL) {
        return;
    }
    supplierNodeClear(node->left);
    supplierNodeClear(node->right);
    checked_free(node->data->supplier_name);
    checked_free(node->data);
    checked_free(node);
}

void deleteTree(SupplierTree *suppTree) {
    /*Removing the tree*/
    checked_free(suppTree);
    printf("Tree has been deleted\n");
}

int deleteAllSuppliers(SupplierTree *suppTree) {
    /*Removing all the suppliers and tree by functions help*/
    if (suppTree->root == NULL) {
        suppTree->elementCount = 0;
        printf("Tree empty\n");
        return TRUE;
    }
    supplierNodeClear(suppTree->root);
    suppTree->elementCount = 0;
    suppTree->root = NULL;
    deleteTree(suppTree);
    return 1;
}

SupplierNode *deleteSupplierHelper(SupplierNode *root, char *authorized_dealer_num, int *elementCounter) {
    /*Remove supplier from the tree*/
    if (root == NULL) {
        return NULL;
    }
    if (strcmp(root->data->authorized_dealer_num, authorized_dealer_num) != 0) {
        if (strcmp(root->data->authorized_dealer_num ,authorized_dealer_num)<=0){
            root->left = deleteSupplierHelper(root->left, authorized_dealer_num, elementCounter);
        } else{
            root->right = deleteSupplierHelper(root->right, authorized_dealer_num, elementCounter);
        }
    }

    if ((root->left == NULL) && (root->right == NULL)) {
        checked_free(root->data->supplier_name);
        checked_free(root->data);
        checked_free(root);
        (*elementCounter)--;
        return NULL;
    } else if (root->left == NULL) {
        SupplierNode *temp = root->right;
        checked_free(root->data->supplier_name);
        checked_free(root->data);
        checked_free(root);
        (*elementCounter)--;
        return temp;
    } else if (root->right == NULL) {
        SupplierNode *temp = root->left;
        checked_free(root->data->supplier_name);
        checked_free(root->data);
        checked_free(root);
        (*elementCounter)--;
        return temp;
    } else {
        SupplierNode *x = root->right;
        Supplier *temp = root->data;
        SupplierNode **xParent = &(root->right);
        while (x->left) {
            xParent = &(x->left);
            x = x->left;
        }
        root->data = x->data;
        x->data = temp;
        *xParent = deleteSupplierHelper(x, x->data->authorized_dealer_num, elementCounter);
        (*elementCounter)--;
    }
    return root;
}

int deleteSupplier(SupplierTree *suppTree) {
    /*Removing supplier by authorized dealer number get help from  deleteSupplierHelper func*/
    char authorized_dealer_num[AUTH_DEALER_NUM_LEN + 1];
    if (suppTree->root == NULL) {
        printf("NO SUPPLIERS\n");
        return 0;
    }
    printf("enter authorized_dealer_num (10 DIGITS): ");
    scanf("%s", authorized_dealer_num);
    suppTree->root = deleteSupplierHelper(suppTree->root, authorized_dealer_num, &suppTree->elementCount);

    return 1;
}


void threeGreatSuppliersHelper(SupplierNode *head, long check, char biggestSupplier[AUTH_DEALER_NUM_LEN + 1],
                               char threeGreatSupp[3][11]) {
    /*Find the three greatest Suppliers  */
    SupplierNode *temp = head;
    if (temp == NULL) {
        return;
    }
    if ((temp->data->sum_of_general_deals_withSupp > check) &&
        (strcmp(temp->data->authorized_dealer_num, threeGreatSupp[0]) != 0) &&
        (strcmp(temp->data->authorized_dealer_num, threeGreatSupp[1]) != 0)) {
        check = temp->data->sum_of_general_deals_withSupp;
        strcpy(biggestSupplier, temp->data->authorized_dealer_num);
    }
    threeGreatSuppliersHelper(temp->left, check, biggestSupplier, threeGreatSupp);
    threeGreatSuppliersHelper(temp->right, check, biggestSupplier, threeGreatSupp);
}


char **threeGreatestSuppliers(SupplierTree *supptree, char threeGreatSupp[3][11]) {
    /*return and prints the three greatest suppliers get help from threeGreatSuppliersHelper func*/
    int countDown = 3;
    long check = 0;
    int index = 0;
    int i = 0;
    char biggestSupplier[AUTH_DEALER_NUM_LEN + 1];
    SupplierNode *temp = supptree->root;
    if (supptree == NULL || temp == NULL) {
        printf("NO SUPPLIERS \n");
    }
    while (countDown > 0) {
        strcpy(biggestSupplier, "0");
        threeGreatSuppliersHelper(temp, check, biggestSupplier, threeGreatSupp);
        strcpy(threeGreatSupp[index], biggestSupplier);
        countDown--;
        index++;
    }
    printf("Three great suppliers are: \n");
    printf("[ ");
    for (i = 0; i < 3; i++) {
        if (i < 2) {
            printf(" %s |", threeGreatSupp[i]);
        } else printf(" %s ", threeGreatSupp[i]);
    }
    printf("]\n");
    return (char **) threeGreatSupp;
}


long averageOfSupplierMoney(SupplierNode *temp , int supplierCounter){
    long sumRight= 0;
    long sumLeft= 0;
    if(temp == NULL) {
        return 0;}
    sumLeft = averageOfSupplierMoney(temp->left , supplierCounter);
    sumLeft = averageOfSupplierMoney(temp->right , supplierCounter);
        return (sumLeft + sumRight + temp->data->sum_of_general_deals_withSupp) / supplierCounter;
    }



