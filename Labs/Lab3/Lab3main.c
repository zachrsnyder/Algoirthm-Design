#include"lab3.h"

int main(void){
    printf("%ld\n", sizeof(char));
    char * source;
    char * dest;
    source = strAlloc(6);
    dest = strAlloc(8);
    printf("size of source string is %d\n", strLen(source));
    printf("size of dest string is %d\n", strLen(dest));
    source = "Hello";
    dest = "HelLo00";
    strCpy(source, dest);
    printf("%s\n", source);
    printf("%s\n", dest);
    printf("%d", strCmp(source, dest));
    //strFree(source);
    //strFree(dest);
}