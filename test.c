#include <stdio.h>
#include <stdlib.h>

#define str(x) #x
#define xstr(x) str(x)

int test1() {
    return 1 == 1 ? (2 == 2 ? 3 : 4) : 5;
}

int test2() {
    return 1 == 2 ? 3 : 4 == 5 ? 5 : 6 ? 0 : 1;
}

int test3() {
    return 0;
}

int main() {

    int test_1 = test1();
    int test_2 = test2();
    int test_3 = test3();

    printf("test 1: %d\n", test_1);
    printf("test 2: %d\n", test_2);
    printf("test 3: %d\n", test_3);

    return 0;
}


