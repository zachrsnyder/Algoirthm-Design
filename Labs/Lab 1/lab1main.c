#include"lab1.h"

int main(void){
    int array[14] = {
        1,
        4,
        5,
        7,
        9,
        10,
        14,
        15,
        17,
        19,
        20,
        22,
        23,
        34,
    };
    int sum0dd = 0;
    float average = 0;
    getAverage(array, 14, &average);
    sumOdd(array, 14, &sum0dd);
    printf("Sum of Odd Integers: %d\nAverage of Integers: %f\n", sum0dd, average);
}