
#include "Car.h"




CarTree *createCarTree() {
    CarTree *tree = (CarTree *) checked_malloc(sizeof(CarTree));
    tree->root = NULL;
    tree->elementCount = 0;
    return tree;
}


Car *init_car() {
    /* init a Vehicle struct by given details*/
    Car *car = (Car *) checked_malloc(sizeof(Car));
    char license_number[LICENSE_NUM_LEN * 3];
    char chassis_number[CHASSIS_NUM_LEN * 3];
    char *maker = (char *) checked_malloc(sizeof(char) * 1024);
    char *model = (char *) checked_malloc(sizeof(char) * 1024);
    char *color = (char *) checked_malloc(sizeof(char) * 1024);
    int year_manufacture;
    int year_get_on_road;
    int price_that_paid;
    int present_car_price;
    int engine_cap;
    int check = 0;
    printf("NEW CAR : \n");
    /* Check license number*/
    while (check != 1) {
        printf("Enter license number (7 digits) : \n");
        scanf("%s", license_number);
        if ((check_equal_size(license_number, LICENSE_NUM_LEN) == 0) || (valid_digit_check(license_number) == 0)) {
            printf("license number not valid\n");
        } else{
            strcpy(car->license_number, license_number);
            check = 1;}
    }
    check = 0;
    /* Check chassis number*/
    while (check != 1) {
        printf("Enter chassis number (5 digits) : \n");
        scanf("%s", chassis_number);
        if ((check_equal_size(chassis_number, CHASSIS_NUM_LEN) == 0) || (valid_digit_check(chassis_number) == 0)) {
            printf("Chassis number not valid\n");
        } else{
            strcpy(car->chassis_number, chassis_number);
            check = 1;}
    }
    check = 0;
    /* Check maker*/
    while (check != 1) {
        printf("Enter maker : \n");
        scanf("%s", maker);
        if (valid_char_check(maker) == 0) {
            printf("Maker not valid\n");
        } else{
            car->maker = dupstr(maker);
            check = 1;}
    }
    check = 0;
    /* Check model*/
    while (check != 1) {
        printf("Enter model : \n");
        scanf("%s", model);
        if (valid_char_check(model) == 0) {
            printf("Model not valid\n");
        } else{
            car->model = dupstr(model);
            check = 1;}
    }
    check = 0;
    /* Check color*/
    while (check != 1) {
        printf("Enter color :\n");
        scanf("%s", color);
        if (valid_char_check(color) == 0) {
            printf("Color not valid\n");
        } else{
            car->color = dupstr(color);
            check = 1;}
    }
    check = 0;
    /* Check year of manufacture*/
    while (check != 1) {
        printf("Enter year of manufacture (number of 4 digits):\n");
        scanf("%d", &year_manufacture);
        if (valid_int(year_manufacture, 1930, 2022) == 0){
            printf("Manufacture year not valid\n");
        } else{
            car->year_manufacture = year_manufacture;
            check = 1;}
    }
    check = 0;
    /* Check price that paid */
    while (check != 1) {
        printf("Enter price that paid for the car:\n");
        scanf("%d", &price_that_paid);
        if (valid_int(price_that_paid, 0, 1000000) == 0){
            printf("Price that paid not valid\n");
        } else{
            car->price_that_paid = price_that_paid;
            check = 1;}
    }
    check = 0;
    /* Check year that car get on road */
    while (check != 1) {
        printf("Enter year that car get on road (number of 4 digits):\n");
        scanf("%d", &year_get_on_road);
        if (valid_int(year_get_on_road, year_manufacture - 1, 2022) == 0){
            printf("Year that car get on road not valid\n");
        } else{
            car->year_get_on_road = year_get_on_road;
            check = 1;}
    }
    check = 0;
    /* Check present car price */
    while (check != 1) {
        printf("Enter present car price :\n");
        scanf("%d", &present_car_price);
        if (valid_int(present_car_price, 0, 1000000) == 0){
            printf("Present car price not valid\n");
        } else{
            car->present_car_price = present_car_price;
            check = 1;}
    }
    check = 0;
    /* Check engine capacity */
    while (check != 1) {
        printf("Enter engine capacity (number of 4 digits):\n");
        scanf("%d", &engine_cap);
        if (valid_int(engine_cap, 1000, 10000) == 0){
            printf("Engine capacity not valid\n");
        } else{
            car->engine_cap = engine_cap;
            check = 1;}
    }

    return car;
}

CarNode *addCarNodeToTree(CarNode *carRoot, CarNode *newCar) {
    if (carRoot == NULL) {
        return newCar;
    } else {
        if (carRoot->right == NULL || carRoot->left == NULL) {
            if (strcmp(newCar->data->license_number, carRoot->data->license_number) <= 0) {
                carRoot->left = addCarNodeToTree(carRoot->left, newCar);
            } else {
                carRoot->right = addCarNodeToTree(carRoot->right, newCar);
            }
        } else {
            if (strcmp(newCar->data->license_number, carRoot->data->license_number) <= 0) {
                addCarNodeToTree(carRoot->left, newCar);
            } else {
                addCarNodeToTree(carRoot->right, newCar);
            }
        }
    }
    return carRoot;
}

int addNewCar(CarTree *carTree) {
    /* if car is valid add new car to the list*/
    CarNode *newCar = (CarNode *) checked_malloc(sizeof(CarNode));
    newCar->data = init_car();
    newCar->left = NULL;
    newCar->right = NULL;
    if (carTree->root == NULL) {
        carTree->root = newCar;
    } else {
        carTree->root = addCarNodeToTree(carTree->root, newCar);
    }
    carTree->elementCount++;
    return 1;
}

void freeCar(CarNode *carNode) {
    checked_free(carNode->data->color);
    checked_free(carNode->data->maker);
    checked_free(carNode->data->model);
    checked_free(carNode->data);
    checked_free(carNode);
}

CarNode *deleteCarHelper(CarNode* root, char *licenseNumberCheck, int* elementCounter) {
    if (root == NULL) {
        return NULL;
    }
    if (strcmp(licenseNumberCheck, root->data->license_number) != 0) {
        if (strcmp(licenseNumberCheck, root->data->license_number) < 0) {
            root->left = deleteCarHelper(root->left, licenseNumberCheck,elementCounter);
        } else {
            root->right = deleteCarHelper(root->right, licenseNumberCheck,elementCounter);
        }
        return root;
    }
    if ((root->left == NULL) && (root->right == NULL)) {
        freeCar(root);
        (*elementCounter)--;
        return NULL;
    }
    else if(root->left==NULL){
        CarNode* temp = root->right;
        freeCar(root);
        (*elementCounter)--;
        return temp;
    }
    else if(root->right==NULL){
        CarNode* temp = root->left;
        freeCar(root);
        (*elementCounter)--;
        return temp;
    }
    else{
        CarNode*  x = root->right;
        Car* temp = root->data;
        CarNode** xParent = &(root->right);
        while (x->left){
            xParent = &(x->left);
            x = x->left;
        }
        root->data = x->data;
        x->data = temp;
        *xParent = deleteCarHelper(x,x->data->license_number,elementCounter);
    }
    return root;
}

int deleteCar(CarTree *tree) {
    char licenseNumberCheck[LICENSE_NUM_LEN + 1];
    if (tree->root == NULL) {
        printf("NO cars\n");
        return FALSE;
    }
    printf("Enter license number of car to be deleted: \n");
    scanf("%s", licenseNumberCheck);
    if (valid_digit_check(licenseNumberCheck) == 0 || check_equal_size(licenseNumberCheck, LICENSE_NUM_LEN) == 0) {
        printf("License number is not valid\n");
        return FALSE;
    }
    tree->root =  deleteCarHelper(tree->root, licenseNumberCheck,&tree->elementCount);
    return TRUE;

}

void carNodeClear(CarNode* node){
    if (node == NULL){
        return;
    }
    carNodeClear(node->left);
    carNodeClear(node->right);
    freeCar(node);
}

int deleteAllCars(CarTree* tree){
    if (tree->root == NULL){
        tree->elementCount = 0;
        printf("Tree empty\n");
        return TRUE;
    }
    carNodeClear(tree->root);
    tree->elementCount = 0;
    tree->root = NULL;
    printf("Tree has been deleted\n");
    return TRUE;
}

int carNumberWithGivenCapacityHelper(CarNode* root, int engineCapacity){
    int sumR,sumL;
    int counter = 0;
    if (root==NULL){
        return 0;
    }
    if (root->data->engine_cap==engineCapacity){
        counter = 1;
    } else{
        counter = 0;
    }
    sumR = carNumberWithGivenCapacityHelper(root->right,engineCapacity);
    sumL = carNumberWithGivenCapacityHelper(root->left,engineCapacity);
    return sumR + sumL +counter;
}

int carNumberWithGivenCapacity(CarTree* tree){
    int counter = 0;
    int engineCapacity;
    if (tree == NULL) {
        printf("No cars\n");
        return 0;
    }
    printf("Enter engine capacity\n");
    scanf("%d",&engineCapacity);

    counter = carNumberWithGivenCapacityHelper(tree->root,engineCapacity);
    return counter;

}
