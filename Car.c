
#include "Car.h"

CarTree *createCarTree() {
    CarTree *tree = (CarTree *) checked_malloc(sizeof(CarTree));
    tree->root = NULL;
    tree->elementCount = 0;
    return tree;
}

int valid_car(char *license_num, char *chassis_number, char *maker, char *model, char *color, int year_manufacture,
              int year_get_on_road,
              int price_that_paid, int present_car_price, int engine_cap) {
    /* check for car validation details by using functions from ValueChecker*/
    if ((check_equal_size(license_num, LICENSE_NUM_LEN) == 0) || (valid_digit_check(license_num) == 0)) {
        return 0;
    }
    if ((check_equal_size(chassis_number, CHASSIS_NUM_LEN) == 0) || (valid_digit_check(chassis_number) == 0)) {
        return 0;
    }
    if (valid_char_check(maker) == 0) {
        return 0;
    }
    if (valid_char_check(model) == 0) {
        return 0;
    }
    if (valid_char_check(maker) == 0) {
        return 0;
    }
    if (valid_char_check(color) == 0) {
        return 0;
    }

    if (valid_int(year_manufacture, 1930, 2022) == 0)return 0;
    if (valid_int(year_get_on_road, year_manufacture - 1, 2022) == 0)return 0;
    if (valid_int(price_that_paid, 0, 1000000) == 0)return 0;
    if (valid_int(present_car_price, 0, 1000000) == 0)return 0;
    if (valid_int(engine_cap, 1000, 10000) == 0)return 0;
    return 1;
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
    printf("Enter license number (7 digits) : \n");
    scanf("%s", license_number);
    printf("Enter chassis number (5 digits) : \n");
    scanf("%s", chassis_number);
    printf("Enter maker : \n");
    scanf("%s", maker);
    printf("Enter model : \n");
    scanf("%s", model);
    printf("Enter color :\n");
    scanf("%s", color);
    printf("Enter year of manufacture (number of 4 digits):\n");
    scanf("%d", &year_manufacture);
    printf("Enter price that paid for the car:\n");
    scanf("%d", &price_that_paid);
    printf("Enter year that car get on road (number of 4 digits):\n");
    scanf("%d", &year_get_on_road);
    printf("Enter present car price :\n");
    scanf("%d", &present_car_price);
    printf("Enter engine capacity (number of 4 digits):\n");
    scanf("%d", &engine_cap);
    if (valid_car(license_number, chassis_number, maker, model, color, year_manufacture, year_get_on_road,
                  price_that_paid,
                  present_car_price, engine_cap) == 0) {
        checked_free(model);
        checked_free(maker);
        checked_free(color);
        car = NULL;
        return car;
    }
    strcpy(car->license_number, license_number);
    strcpy(car->chassis_number, chassis_number);
    car->model = dupstr(model);
    car->maker = dupstr(maker);
    car->color = dupstr(color);
    car->year_manufacture = year_manufacture;
    car->year_get_on_road = year_get_on_road;
    car->present_car_price = present_car_price;
    car->price_that_paid = price_that_paid;
    car->engine_cap = engine_cap;
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
    if (newCar->data == NULL) {
        printf("Car was not added!\n");
        checked_free(newCar);
        return FALSE;
    }
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

CarNode *deleteCarHelper(CarNode* root, char *licenseNumberCheck) {
    if (root == NULL) {
        return NULL;
    }
    if (strcmp(licenseNumberCheck, root->data->license_number) != 0) {
        if (strcmp(licenseNumberCheck, root->data->license_number) < 0) {
            root->left = deleteCarHelper(root->left, licenseNumberCheck);
        } else {
            root->right = deleteCarHelper(root->right, licenseNumberCheck);
        }
        return root;
    }
    if ((root->left == NULL) && (root->right == NULL)) {
        freeCar(root);
        return NULL;
    }
    else if(root->left==NULL){
        CarNode* temp = root->right;
        freeCar(root);
        return temp;
    }
    else if(root->right==NULL){
        CarNode* temp = root->left;
        freeCar(root);
        return temp;
    }
    else{
        CarNode*  x = root->right;
        CarNode* temp = NULL;
        CarNode** xParent = &(root->right);
        while (x->left){
            xParent = &(x->left);
            x = x->left;
        }
        temp = x;
        root->data = x->data;
        *xParent = deleteCarHelper(temp,temp->data->license_number);
    }
    return root;
}

int deleteCar(CarTree *tree) {
    char licenseNumberCheck[LICENSE_NUM_LEN + 1];
    if (tree == NULL) {
        printf("NO cars\n");
        return FALSE;
    }
    printf("Enter license number of car to be deleted: \n");
    scanf("%s", licenseNumberCheck);
    if (valid_digit_check(licenseNumberCheck) == 0 || check_equal_size(licenseNumberCheck, LICENSE_NUM_LEN) == 0) {
        printf("License number is not valid\n");
        return FALSE;
    }
    tree->root =  deleteCarHelper(tree->root, licenseNumberCheck);

    return TRUE;

}

void nodeClear(CarNode* node){
    if (node == NULL){
        return;
    }
    nodeClear(node->left);
    nodeClear(node->right);
    freeCar(node);
}

int deleteAllCars(CarTree* tree){
    if (tree == NULL){
        tree->elementCount = 0;
        printf("Tree empty\n");
        return TRUE;
    }
    nodeClear(tree->root);
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
