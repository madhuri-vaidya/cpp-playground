#include<stdio.h>
#include<assert.h>

int main() {
    int dividend = 10;
    int divisor = 0;

    printf("Attempting to divide....\n");

    assert(divisor != 0);

    int result = dividend / divisor;
    printf("Result is %d\n", result);

    return 0;
}
