#include"lab4.h"

int main(void)
{
    InventoryItem * array;
    array = makeArray(5,sizeof(InventoryItem));
    int id = 0;
    for(int i = 0; i < getSize(array); ++i)
    {
        array[i].ID = id;
        array[i].weight = 15.4;
        array[i].stockCount = 4;
        array[i].colors = 6;
        ++id;
    };
    printf("items with stockount of 5: %d\nsize of array is %d\n", countWithStock(array,5), getSize(array));

    freeArray(array);


}