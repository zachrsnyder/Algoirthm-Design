#include"A2.h"

int main()
{
    int array[] = {
        1,
        2,
        3,
        4,
        5,
        6,
        7,
        8,
        9,
        10,
        11,
        12,
        13,
        14,
        15,
        16,
        17,
        18,
        19,
        20
    };
    RBST rbst = initRBST();
    for(int i = 0; i < 20; ++i)
    {
        printf("%d \n", insertRBST(rbst, array[i]));
    };
    inOrderPrintBST(rbst);
    Node * list = ripApart(rbst.info->root->right, 100);
    int size = 0;
    int visits = 0;
    inOrderRec(list);
    flattenRec(list, &size, &visits);
    inOrderRec(list);
    //inOrderPrintBST(rbst);
    freeRBST(rbst);
}