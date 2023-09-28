#include "lab9.h"

int main()
{
    Flight * list = (Flight*)makeArray(10, sizeof(Flight));
    for(int i = 0; i < 10; ++i)
    {
        list[i].flightNumber = i + 10;
        list[i].distance = 300 - i;
        list[i].passengers = 15;
    };
    for(int i = 0; i < 10; ++i)
    {
        printf("\nFlight Stats:\n\tNumber: %d\n\tDistance: %f\n\tPassengers: %o\n", list[i].flightNumber, list[i].distance, list[i].passengers);
    };
    Flight * query = &list[5];
    Flight * queryTwo = &list[9];
    printf("size of flight list = %d\n", getSize(list));
    printf("Flight Number \"%d\" is at index [%d]\n", 25, searchFlights(list, query));
    printf("Is flight 5 longer than flight 9: %d\n", compareFlights(query, queryTwo));
    freeArray(list);
}