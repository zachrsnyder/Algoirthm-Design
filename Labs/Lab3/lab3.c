#include"lab3.h"

char * strAlloc(int size)
{
    char * array;
    array = malloc(size + sizeof(int)); //allocates given space to array
    if(array == NULL) //tests malloc
    {
        printf("***ERROR: Malloc failed***");
        return NULL;
    } else 
    {
    array[0] = size; //gives size to the first part of array
    array = array+4; //indexes four char lengths
    return array;
    };
}

int strLen(char *str)
{
    int size = 0;
    size = *((int*)str-1); //indexes an integer length backwards to find size
    return size;
}

/*void strCpy(char *source, char *dest)
{
    source = dest; //I have no idea what I am doing wrong
    return;
}*/

int strCmp(char *source, char *dest)
{
    if(source == dest) //checks the strings for equality
    {
        return 1; //returns one upon equality and zero if not
    }
    else return 0;
}

/*void strFree(char *str)
{
    free((int*)str-1);// its invalid pointer every time. I would love to know what is wrong
}*/