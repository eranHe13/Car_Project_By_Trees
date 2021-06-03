#include <stdio.h>
#include "Supplier.h"




int main() {

    char threeGreatestSuppliers1[3][11];
    long * deals_l;
    long * deals_r ;
    long  deals_t  = 8;
    SupplierTree *head = createSupplierTree();
    addNewSupplier(head);
    addNewSupplier(head);
    threeGreatestSuppliers(head , threeGreatestSuppliers1);
    printf("%ld\n" ,  averageOfSupplierMoney(head->root , &deals_t, head->elementCount));
    printf("--\n");
    printSuppliers(head->root);
    deleteAllSuppliers(head);
    check_for_exit();
    free(head);
    check_for_exit();
    return 0;
}
