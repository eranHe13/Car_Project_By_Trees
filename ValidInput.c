
#include "ValidInput.h"

int isLetter(char letter) {
    /* check if the given char is a letter */
    if ((letter >= 65 && letter <= 90) || (letter >= 97 && letter <= 122)) {
        return 1;
    } else return 0;
}

int isDigit(char isNum) {
    /* check if the given char is a number */
    if (isNum >= 48 && isNum <= 57) return 1;
    else return 0;
}

int valid_char_check(char *str) {
    /* check isChar for a String in a for loop*/
    int i;
    if (strlen(str) == 0) {
        printf("%s is not valid!\n", str);
        return 0;
    }
    for (i = 0; i < strlen(str); i++) {
        if (isLetter(str[i]) == 0) {
            printf("%s is not valid!\n", str);
            return 0;
        }
    }
    return 1;
}

int valid_digit_check(char *str) {
    /* check isDigit for a String in a for loop*/
    int i;
    if (strlen(str) == 0) {
        printf("%s is not valid!\n", str);
        return 0;
    }
    for (i = 0; i < strlen(str); i++) {
        if (isDigit(str[i]) == 0) {
            printf("%s is not valid!\n", str);
            return 0;
        }
    }
    return 1;
}

int date_valid(int year, int month, int day) {
    /* check validation for a given Date details*/
    int month_with_30[4] = {4, 6, 9, 11};

    if (year < 1930 || year > 2022) {
        return 0;
    }
    if (month < 1 || month > 12) {
        return 0;
    }
    if (day < 1 || day > 31) {
        return 0;
    }
    if (day > 30) {
        int i;
        for (i = 0; i < 4; i++) {
            if (month == month_with_30[i]) {
                return 0;
            }
        }
    }
    if (month == 2 && day > 28) {
        return 0;
    }
    return 1;
}

void smaller_than_ten(int num) {
    /* if number is smaller then ten print a zero before the number*/
    if (num < 10 && num >= 0) {
        printf("0");
    }
}

int time_valid(int hour, int minute) {
    /* check for time validation*/
    if (hour < 0 || hour > 23) {
        return 0;
    }
    if (minute < 0 || minute > 60) {
        return 0;
    }
    return 1;
}

int check_equal_size(char *str, int size) {
    /* check for equal string size*/
    if (strlen(str) == 0) {
        printf("%s is not valid!\n", str);
        return 0;
    }
    if (strlen(str) != size) {
        printf("%s is not valid!\n", str);
        return 0;
    } else return 1;
}

int valid_int(int num, int min, int max) {
    /* min and max for given int*/
    if (num < min || num > max) {
        printf("%d is not valid!\n", num);
        return 0;
    } else return 1;
}

int valid_long(long num, long min, long max) {
    /* min and max for given long*/
    if (num < min || num > max) {
        printf("%ld is not valid!\n", num);
        return 0;
    } else return 1;
}

char *dupstr(const char *str) {
    /* function as strdup in c99*/
    return strcpy(malloc(strlen(str) + 1), str);
}
