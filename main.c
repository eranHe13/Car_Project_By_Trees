

#include <stdio.h>
#include "Supplier.h"
#include "Client.h"
#include "Car.h"
#include "Common.h"

void client(ClientTree *clientTree) {
    /* ask for how many clients would the user add for the list*/
    int i;
    int n_client;
    printf("How many clients you want to add ? : ");
    scanf("%d", &n_client);
    for (i = 0; i < n_client; ++i) {
        printf("\nCLIENT: \n");
        addNewClient(clientTree);

    }
}

void supplier(SupplierTree *supplierTree) {
    /* ask for how many suppliers would the user add for the tree*/
    int n_supplier;
    int i;
    printf("How many supplier you want to add ? : ");
    scanf("%d", &n_supplier);
    for (i = 0; i < n_supplier; ++i) {
        printf("\nSUPPLIER: \n");
        addNewSupplier(supplierTree);
    }
}

void car(CarTree *carTree) {
    /* ask for how many cars would the user add for the tree*/
    int n_car;
    int i;
    printf("How many cars you want to add ? : ");
    scanf("%d", &n_car);
    for (i = 0; i < n_car; ++i) {
        printf("\nCAR: \n");
        addNewCar(carTree);

    }
}

void delete(SupplierTree *supplierTree, ClientTree *clientTree, CarTree *carTree) {
    /* menu for delete options*/
    int n_delete = 9;
    while (n_delete != 0) {
        printf("\n Enter your choice:\n"
               "1 - For delete supplier\n"
               "2 - For delete client\n"
               "3 - For delete car\n"
               "4 - For delete all suppliers\n"
               "5 - For delete all clients\n"
               "6 - For delete all cars\n"
               "0 - Return\n");
        scanf("%d", &n_delete);
        switch (n_delete) {
            case 1:
                deleteSupplier(supplierTree);
                break;
            case 2:
                deleteClient(clientTree);
                break;
            case 3:
                deleteCar(carTree);
                break;
            case 4:
                deleteAllSuppliers(supplierTree);
                break;
            case 5:
                deleteAllClients(clientTree);
                break;
            case 6:
                deleteAllCars(carTree);
                break;
            case 0:
                break;
            default:
                printf("Invalid option %d\n", n_delete);
                break;
        }
    }
}

int deleteAllClientsLinkedList(ClientLinkedNode **ClientHead) {
    /*REMOVE ALL THE CLIENTS*/
    ClientLinkedNode *temp = (*ClientHead);
    while (*ClientHead != NULL) {
        temp = *ClientHead;
        *ClientHead = temp->next;
        checked_free(temp);
    }
    checked_free(ClientHead);
    printf("ALL CLIENTS REMOVED\n");
    return TRUE;
}


void menu(SupplierTree *supplierTree, ClientTree *clientTree, CarTree *carTree) {
    /* menu program for adding and getting details from all the structs*/
    ClientLinkedNode * clientList = (ClientLinkedNode* ) checked_malloc(sizeof(ClientLinkedNode));
    char threeGreatSupplier[3][11];
    int temp ;
    int stop = 20;
    while (stop != 0) {
        printf("----------------------------------");
        printf("\nHello user \n"
               "Enter your choice :\n"
               "1  - For supplier\n"
               "2  - For client\n"
               "3  - For car\n"
               "4  - For client number with given car year\n"
               "5  - For car number with given capacity\n"
               "6  - Find client\n"
               "7  - Three greatest supplier\n"
               "8  - Average of supplier money\n"
               "9  - Print client cars for given rent date\n"
               "10 - Print Suppliers\n"
               "11 - For delete \n"
               "0  - For exit\n"
               " ---->");
        scanf("%d", &stop);
        switch (stop) {
            case 1:
                supplier(supplierTree);
                break;
            case 2:
                client(clientTree);
                break;
            case 3:
                car(carTree);
                break;
            case 4:
                printf("Client number with the same car year : %d\n", clientNumberWithGivenCarYear(carTree , clientTree));
                break;
            case 5:
                printf("Number of cars with the same capacity  : %d\n", carNumberWithGivenCapacity(carTree));
                break;
            case 6:
                clientList =  findClient(clientTree);
                deleteAllClientsLinkedList(&clientList);
                break;
            case 7:
                threeGreatestSuppliers(supplierTree, threeGreatSupplier);
                break;
            case 8:
                printf("Average of suppliers money : %.2f\n", averageOfSupplierMoney(supplierTree->root,supplierTree->elementCount));
                break;
            case 9:
                printClientCarsForGivenRentDate(clientTree);
                break;
            case 10:
                printSuppliers(supplierTree->root);
                break;
            case 11:
                delete(supplierTree, clientTree, carTree);
                break;
            case 0:
                break;
            default:
                printf("Invalid option %d\n", stop);
                break;
        }
    }


}



int main() {
    ClientTree *clientTree = createClientTree();
    SupplierTree *suppHead = createSupplierTree();
    CarTree *carTree = createCarTree();
    menu(suppHead, clientTree, carTree);
    deleteAllCars(carTree);
    deleteAllClients(clientTree);
    deleteAllSuppliers(suppHead);
    checked_free(clientTree);
    checked_free(carTree);
    checked_free(suppHead);
    check_for_exit();
    return 0;
}

