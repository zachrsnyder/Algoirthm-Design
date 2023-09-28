#include"lab1.h"

int getAverage(int array[], int size, float *result)
{
    if(size == 0)
        {printf("***Cannot Calculate Average***");
        return 1;} //prints message if the array is of size 0;
    else {
        float resultP = 0;
        for(int i = 0; i < size; ++i)
        {
            resultP += array[i]; //adds all elements together
        }
        resultP /= size; //divides by size of array
        *result = resultP; //gives the variable result points to the value of resultP
        return 0;
    };
}

int sumOdd(int array[], int size, int *result)
{
    if(size == 0)
        {printf("***Cannot Calculate sumOdd***");
        return 1;} //prints message if the array is of size 0;
    else {
        int resultA = 0;
        for(int i = 0; i < size; ++i)
        {
            if(array[i] % 2 > 0) //remainder is used to calculate if the value of the array elements is even or odd
            {resultA += array[i];}; //adds the odd values together.
        }
        *result = resultA; //gives the variable result points to the value of resultA
        return 0;
    };
}