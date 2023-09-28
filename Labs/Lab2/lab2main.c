#include"lab2.h"
int main(void)
{
    int * array;
    int size = 20;
    makeArray(&array, size);
    initArray(array, size);
    for(int i = 0; i < size; ++i)
    {
        printf("Element %d of the array is: %d\n", i, *(array+i));
    };
    int arraytest[5] = 
    {
        5,
        7,
        10,
        22,
        0,
    };
    freeArray(&array);
    printf("There are %d even numbers in the array\n", multiplyPositive(arraytest, 5, 3));
    for(int i = 0; i < 5; ++i)
    {
        printf("%d\n", arraytest[i]);
    };
}