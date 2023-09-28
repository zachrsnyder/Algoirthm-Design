#include"Lab1.h"

int obtainRandomSample(int *sequence) // INT_MAX terminated
{
    int output= 0; //the return value
    double j = 0,k = 1; 
    int * num = sequence;
    while(*num != INT_MAX){ //indexes array until terminating character INT_MAX
        j = 1/k;
        if(drand48() <= j) output = *num; //produces random decimal value between zero and one then compares it to the probability of it's selection
        ++k;
        ++num; //indexes through sequence
    };
    return output;  
};

int testRandomSample() // You’ll need to provide your test file
{
    FILE *test = fopen("testsample2.txt", "r"); //opens file of number sequence.
    int length = 0;
    srand48(time(0)); //seeds the random number genarator so that is different each time.
    if(test){ //tests if file opened successfully 
        fscanf(test, "%d", &length); //gets length from first line of the sample sequence.
    }else return 1; //file couldn't be opened
    int *array;
    array = malloc(sizeof(int) * (length+1)); //mallocs array to contain the file of integers
    if(array){
        for(int i = 0; i < length; ++i) 
        {
            fscanf(test, "%d", &array[i]);
        }
        array[length] = INT_MAX; //appends terminating character to the end of the array
    }else return 1; //malloc failed
    double ones=0, twos=0, threes=0; 
    for(int i = 0; i < 99999; ++i) //runs sampling algorithm 99999 times to total it's return of each number.
    {
        switch(obtainRandomSample(array))
        {
            case 1: ++ones;
            break;
            case 2: ++twos;
            break;
            case 3: ++threes;
            break;
        };
    };
    printf("Ones Count: %f\nTwos Count: %f\nThrees Count: %f\n", ones, twos, threes); 
    double expected = 33333, oneserr = 0, twoserr = 0, threeserr = 0, averageerr = 0; //expected return from each possible value and the percent errors to be calculated
    oneserr = fabs(((ones-expected) / ones) * 100); //finds percent error
    twoserr = fabs(((twos-expected) / twos) * 100);
    threeserr = fabs(((threes-expected) / threes) * 100);
    averageerr = (threeserr + twoserr + oneserr) / 3;
    printf("Ones %% error: %lf\nTwos %% error: %lf\nThrees %% error: %lf\nAverage %% error: %lf", oneserr, twoserr, threeserr, averageerr);
    fclose(test); //close txt file
    free(array); //frees malloced array
    if(averageerr <= 1)
    {
        return 0; //tests average percent error to a benchmark standard.
    }else return 1;
}

