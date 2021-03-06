
#include "matam.h"
#include <stdio.h>

static unsigned int allocated_blocks = 0;

void *checked_malloc(unsigned int size)
{
    void * ret;

    ret = malloc(size);
    if (!ret) {
        perror ("Memory allocation error");
        exit (1);
    }
    allocated_blocks++;
    return ret;
}

void checked_free (void *ptr)
{

    free(ptr);
    allocated_blocks--;
    return;
}

void check_for_exit() {
    if (allocated_blocks) {
        fprintf (stderr, "Memory leak: %d memory blocks still allocated \n", allocated_blocks);
        exit(1);
    }
    return;
}
