
#include "Common.h"

void clientNumberWithGivenCarYearHelperSecond(CarNode *carNode, ClientNode *clientNode, int *counter) {
    /*second helper compare license number of car and client and count the ones with the same year */
    if (clientNode == NULL) {
        return;
    }
    if (strcmp(carNode->data->license_number, clientNode->data->license_number) == 0) {
        (*counter)++;
        printf("%s\n", carNode->data->license_number);
        return;
    }
    clientNumberWithGivenCarYearHelperSecond(carNode, clientNode->left, counter);
    clientNumberWithGivenCarYearHelperSecond(carNode, clientNode->right, counter);
}

void clientNumberWithGivenCarYearHelperFirst(CarNode *carNode, ClientNode *clientNode, int *counter,
                                             int carManufactureYear) {
    /*first helper check if the car is in the given year and send it to second helper  */
    if (carNode == NULL) {
        return;
    }
    if (carNode->data->year_manufacture == carManufactureYear) {
        clientNumberWithGivenCarYearHelperSecond(carNode, clientNode, counter);
    }
    clientNumberWithGivenCarYearHelperFirst(carNode->left, clientNode, counter, carManufactureYear);
    clientNumberWithGivenCarYearHelperFirst(carNode->right, clientNode, counter, carManufactureYear);
}

int clientNumberWithGivenCarYear(CarTree *carTree, ClientTree *clientTree) {
    /*return the number of client that have car in the same year */
    int carManufactureYear;
    int counter = 0;
    if (carTree == NULL || clientTree == NULL) {
        printf("Not enough details\n");
        return 0;
    }
    printf("Enter car manufacture year:  \n");
    scanf("%d", &carManufactureYear);
    if (valid_int(carManufactureYear, 1930, 2022) == 0) {
        printf("NOT VALID YEAR\n");
        return 0;
    }
    clientNumberWithGivenCarYearHelperFirst(carTree->root, clientTree->root, &counter, carManufactureYear);
    printf("The number of clients with car in the same year is: %d\n", counter);
    return counter;
}

