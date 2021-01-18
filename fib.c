#include <stdio.h>
#include <stdlib.h>
#include <time.h>

size_t fib(size_t n) {
    if(n < 2) return n;
    return fib(n - 1) + fib(n - 2);
}

void main() {
    size_t x = 40;

    clock_t before, after;

    before = clock();
    size_t fib_x = fib(x);
    after = clock();

    printf("fib(%zu) = %zu\n", x, fib_x);

    double seconds = (double)(after - before)/CLOCKS_PER_SEC;
    printf("%.4f seconds\n", seconds);
}
