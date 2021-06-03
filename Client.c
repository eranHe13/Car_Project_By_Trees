
#include "Client.h"

ClientTree *createClientTree() {
    ClientTree *tree = (ClientTree *) checked_malloc(sizeof(ClientTree));
    tree->root = NULL;
    tree->elementCount = 0;
    return tree;
}

Date create_date(int year, int month, int day) {
    /*CREATING A DATE BY GIVEN DETAILS RETURN TRUE IF SUCCEED ELSE FALSE*/
    Date today = {0, 0, 0};
    if (date_valid(year, month, day) == FALSE) {
        printf("date not valid \n");
        return today;
    } else {
        today.year = year;
        today.month = month;
        today.day = day;
    }
    return today;
}

Time create_time(int hour, int minute) {
    /*CREATING A TIME STRUCT BY GIVEN DETAILS RETURN TRUE IF SUCCEED ELSE FALSE*/
    Time current_hour = {0, 0};
    if (time_valid(hour, minute) == FALSE) {
        printf("time not valid \n");
        return current_hour;
    } else {
        current_hour.hour = hour;
        current_hour.minute = minute;
    }
    return current_hour;
}

void print_date(Date d) {
    /*PRINTING DATE FORMAT*/
    smaller_than_ten(d.day);
    printf("%d/", d.day);
    smaller_than_ten(d.month);
    printf("%d/%d\n", d.month, d.year);
}

void print_time(Time t) {
    /*PRINTING TIME FORMAT*/
    smaller_than_ten(t.hour);
    printf("%d:", t.hour);
    smaller_than_ten(t.minute);
    printf("%d\n", t.minute);
}

Client *initClient() {
    /*INIT CLIENT BY GIVEN DETAILS AND USING client_valid func*/
    Client *client = (Client *) checked_malloc(sizeof(Client));
    char id[ID_LEN * 3];
    char license_num[LICENSE_LEN * 3];
    char *first_name = (char *) checked_malloc(sizeof(char) * 1024);
    char *last_name = (char *) checked_malloc(sizeof(char) * 1024);
    Date date_of_rent;
    int year, month, day, hour, minute;
    Time time_of_rent;
    int price_per_rent;
    int check = 0;
    printf("NEW CLIENT : \n");
    /* Check ID*/
    while (check != 1) {
        printf("Enter ID (9 digits): \n");
        scanf("%s", id);
        if (valid_digit_check(id) == FALSE || check_equal_size(id, ID_LEN) == FALSE) {
            printf("Id client number not valid\n");
        } else{
            strcpy(client->id, id);
            check = 1;}
    }
    check = 0;
    /* Check first name*/
    while (check != 1) {
        printf("Enter first name: \n");
        scanf("%s", first_name);
        if (valid_char_check(first_name) == FALSE) {
            printf("Client first name not valid\n");
        } else{
            client->first_name = dupstr(first_name);
            check = 1;}
    }
    check = 0;
    /* Check last name*/
    while (check != 1) {
        printf("Enter last name: \n");
        scanf("%s", last_name);
        if (valid_char_check(last_name) == FALSE) {
            printf("Client last name not valid\n");
        } else{
            client->last_name = dupstr(last_name);
            check = 1;}
    }
    check = 0;
    /* Check license number*/
    while (check != 1) {
        printf("Enter license number (7 digits): \n");
        scanf("%s", license_num);
        if (valid_digit_check(license_num) == FALSE || check_equal_size(license_num, LICENSE_LEN) == FALSE) {
            printf("Client license number not valid\n");
        } else{
                strcpy(client->license_number, license_num);
            check = 1;}
    }
    check = 0;
    /* Check date*/
    while (check != 1) {
        printf("Enter date: year , month , day\n");
        scanf("%d %d %d", &year, &month, &day);
        date_of_rent = create_date(year, month, day);
        if (date_of_rent.day == 0) {
            printf("Date not valid\n");
        } else{
            client->date_of_rent = date_of_rent;
            check = 1;}
    }
    check = 0;
    /* Check time*/
    while (check != 1) {
        printf("Enter time: hour , minute\n");
        scanf("%d %d", &hour, &minute);
        time_of_rent = create_time(hour, minute);
        if (time_of_rent.hour == 0) {
            printf("Time not valid\n");
        } else{
            client->hour_of_rent = time_of_rent;
            check = 1;}
    }
    check = 0;
    /* Check price per rent for 24 hours*/
    while (check != 1) {
        printf("Enter price per rent for 24 hours (number of 3 digits): \n");
        scanf("%d", &price_per_rent);

        if (valid_int(price_per_rent, 100, 999) == FALSE) {
            printf("Price per rent not valid\n");
        } else{
            client->price_per_rent = price_per_rent;
            check = 1;}
    }

    return client;

}

ClientNode *addClientNodeToTree(ClientNode *clientRoot, ClientNode *newClient) {
    if (clientRoot == NULL) {
        return newClient;
    } else {
        if (clientRoot->right == NULL || clientRoot->left == NULL) {
            if (strcmp(newClient->data->id, clientRoot->data->id) <= 0) {
                clientRoot->left = addClientNodeToTree(clientRoot->left, newClient);
            } else {
                clientRoot->right = addClientNodeToTree(clientRoot->right, newClient);
            }
        } else {
            if (strcmp(newClient->data->id, clientRoot->data->id) <= 0) {
                addClientNodeToTree(clientRoot->left, newClient);
            } else {
                addClientNodeToTree(clientRoot->right, newClient);
            }
        }
    }
    return clientRoot;
}

int addNewClient(ClientTree *clientTree) {
    /* if client is valid add new car to the list*/
    ClientNode *newClient = (ClientNode *) checked_malloc(sizeof(ClientNode));
    newClient->data = initClient();
    newClient->left = NULL;
    newClient->right = NULL;
    if (clientTree->root == NULL) {
        clientTree->root = newClient;
    } else {
        clientTree->root = addClientNodeToTree(clientTree->root, newClient);
    }
    clientTree->elementCount++;
    return 1;
}

void freeClient(ClientNode *clientNode) {
    checked_free(clientNode->data->first_name);
    checked_free(clientNode->data->last_name);
    checked_free(clientNode->data);
    checked_free(clientNode);
}

ClientNode *deleteClientHelper(ClientNode *root, char *idCheck, int *elementCounter) {
    if (root == NULL) {
        return NULL;
    }
    if (strcmp(idCheck, root->data->id) != 0) {
        if (strcmp(idCheck, root->data->id) < 0) {
            root->left = deleteClientHelper(root->left, idCheck, elementCounter);
        } else {
            root->right = deleteClientHelper(root->right, idCheck, elementCounter);
        }
        return root;
    }
    if ((root->left == NULL) && (root->right == NULL)) {
        freeClient(root);
        (*elementCounter)--;
        return NULL;
    } else if (root->left == NULL) {
        ClientNode *temp = root->right;
        freeClient(root);
        (*elementCounter)--;
        return temp;
    } else if (root->right == NULL) {
        ClientNode *temp = root->left;
        freeClient(root);
        (*elementCounter)--;
        return temp;
    } else {
        ClientNode *x = root->right;
        Client *temp = root->data;
        ClientNode **xParent = &(root->right);
        while (x->left) {
            xParent = &(x->left);
            x = x->left;
        }
        root->data = x->data;
        x->data = temp;
        *xParent = deleteClientHelper(x, x->data->id, elementCounter);
    }
    return root;
}

int deleteClient(ClientTree *tree) {
    char idCheck[ID_LEN + 1];
    if (tree == NULL) {
        printf("NO clients\n");
        return FALSE;
    }
    printf("Enter ID of client to be deleted: \n");
    scanf("%s", idCheck);
    if (valid_digit_check(idCheck) == 0 || check_equal_size(idCheck, ID_LEN) == 0) {
        printf("ID is not valid\n");
        return FALSE;
    }
    tree->root = deleteClientHelper(tree->root, idCheck, &tree->elementCount);
    return TRUE;

}

void clientNodeClear(ClientNode *node) {
    if (node == NULL) {
        return;
    }
    clientNodeClear(node->left);
    clientNodeClear(node->right);
    freeClient(node);
}

int deleteAllClients(ClientTree *tree) {
    if (tree == NULL) {
        tree->elementCount = 0;
        printf("Tree empty\n");
        return TRUE;
    }
    clientNodeClear(tree->root);
    tree->elementCount = 0;
    tree->root = NULL;
    printf("Tree has been deleted\n");
    return TRUE;
}

int printClientCarsForGivenRentDateHelper(ClientNode *clientNode, int year, int month, int day,int* counter) {
    if (clientNode == NULL) {
        return 0;
    }
    if ((clientNode->data->date_of_rent.day == day) && (clientNode->data->date_of_rent.month == month)
        && (clientNode->data->date_of_rent.year == year)) {
        printf("CLIENT :\n"
               "first name : %s\n"
               "last name : %s\n"
               "id : %s\n"
               "car licence number : %s\n"
               "rent price for 24 hours : %d \n", clientNode->data->first_name, clientNode->data->last_name,
               clientNode->data->id,
               clientNode->data->license_number, clientNode->data->price_per_rent);
        printf("rent date : ");
        print_date(clientNode->data->date_of_rent);
        printf("rent time : ");
        print_time(clientNode->data->hour_of_rent);
        (*counter)++;
    }
    printClientCarsForGivenRentDateHelper(clientNode->left, year, month, day, counter);
    printClientCarsForGivenRentDateHelper(clientNode->right, year, month, day,counter);
    return *counter;
}

int printClientCarsForGivenRentDate(ClientTree *clientTree) {
    /*PRINT CLIENTS WITH THE SAME RENT DATE*/
    int check = 0;
    int year, month, day;
    if (clientTree->root == NULL) {
        printf("THERE NO CLIENTS\n");
        return FALSE;
    }

    printf("Enter date: year , month , day\n");
    scanf("%d %d %d", &year, &month, &day);
    if (date_valid(year, month, day) == 0) {
        printf("date not valid \n");
        return 0;
    }
    printClientCarsForGivenRentDateHelper(clientTree->root, year, month, day,&check);
    if (check==0) printf("Clients were not found\n");
    return TRUE;
}

ClientLinkedNode *addToListC(ClientLinkedNode **ClientHead, Client *client) {
    /*CREATE CLIENT LIST AND CLIENT STRUCT AND ADD TO THE LINKED LIST */
    ClientLinkedNode *new;
    new = (ClientLinkedNode *) checked_malloc(sizeof(ClientLinkedNode));
    new->data = client;
    new->next = (*ClientHead);
    (*ClientHead) = new;
    return (*ClientHead);
}


ClientLinkedNode *findClientById(ClientNode *root, ClientLinkedNode **head, char idCheck[ID_LEN + 1]) {
    if ((root) == NULL) {
        return NULL;
    }
    findClientById(root->left, head, idCheck);
    if (strcmp(root->data->id, idCheck) == 0) {
        (*head) = addToListC(head, root->data);
    }
    findClientById(root->right, head, idCheck);
    return (*head);
}

ClientLinkedNode *findClientByDate(ClientNode *root, ClientLinkedNode **head, int year, int month, int day) {
    if ((root) == NULL) {
        return NULL;
    }
    findClientByDate(root->left, head, year, month, day);
    if (root->data->date_of_rent.day == day && root->data->date_of_rent.year == year &&
        root->data->date_of_rent.month == month) {
        (*head) = addToListC(head, root->data);
    }
    findClientByDate(root->right, head, year, month, day);
    return (*head);
}

ClientLinkedNode *findClient(ClientTree *clientTree) {
    int option, year, month, day;
    int flag = FALSE;
    char idCheck[ID_LEN + 1];
    ClientLinkedNode *head = NULL;
    if (clientTree->root == NULL) {
        printf("No clients\n");
        return NULL;
    }

    printf("For find by ID enter 1:\n");
    printf("For find by date enter 2:\n");
    scanf("%d", &option);
    if (option == 1) {
        while (flag == FALSE) {
            printf("Enter ID for finding: \n");
            scanf("%s", idCheck);
            if (valid_digit_check(idCheck) == FALSE || check_equal_size(idCheck, ID_LEN) == FALSE) {
                printf("Invalid ID try again\n");
            } else flag = TRUE;
        }
        if (((strcmp(idCheck, clientTree->root->data->id) == 0))) {
            head = findClientById(clientTree->root, &head, idCheck);
        } else if ((strcmp(idCheck, clientTree->root->data->id) < 0)) {
            head = findClientById(clientTree->root->left, &head, idCheck);
        } else {
            head = findClientById(clientTree->root->right, &head, idCheck);
        }

    }
    if (option == 2) {
        while (flag == FALSE) {
            printf("Enter date: year , month , day\n");
            scanf("%d %d %d", &year, &month, &day);
            if (date_valid(year, month, day) == FALSE) {
                printf("Date not valid try again\n");
            } else flag = TRUE;
        }
        head = findClientByDate(clientTree->root, &head, year, month, day);

    }

    return head;
}
