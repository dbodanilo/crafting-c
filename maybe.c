#include <stdio.h>
#include <stdlib.h>

int* maybe(int* p) {
    int* p2 = malloc(sizeof(int));
    *p2 = 0;

    p = p ? p : p2;

    if(p != p2) free(p2);

    return p;
}


int main() {
    int i = 10;

    // int* mInt = &i;
    int* mInt = NULL;

    mInt = maybe(mInt);

    printf("maybe int: %d\n", *mInt);

    int test2 = 2 == 2 ? 3 == 3 ? 3 : NULL : NULL;


    printf("test2: %d\n", test2);

    return 0;
}