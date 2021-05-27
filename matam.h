

#ifndef CAR_RENTAL_DYNAMIC_MATAM_H
#define CAR_RENTAL_DYNAMIC_MATAM_H

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

void *checked_malloc(unsigned int);
void checked_free(void *);
void check_for_exit();

#define ALLOC(typ,no) ((typ *) checked_malloc(sizeof(typ)*(no)))
#define FREE(ptr) checked_free(ptr)

#endif
