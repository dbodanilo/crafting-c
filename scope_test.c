#include <stdio.h>

int main() 
{
    int a = 1;
    {
        int b = a;
        int a = b + 2;

        printf("a: %d\n", a);
    }

    printf("a: %d\n", a);

    return 0;
}
