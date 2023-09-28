#include"zrshmn.h"

int main()
{
    int * array = malloc(sizeof(int) * 131072);
    for(int i = 0; i < 131072; ++i)
    {
        array[i] = i;
    };
    printf("Total # of Nodes Visited: %d\n", testInsertRBST(131072,array));
    printf("Nodes Freed: %d\n", testFreeRBST(131072,array));
    free(array);
    printf("Test for Scaling: %d\n", scalingTests(3));
}