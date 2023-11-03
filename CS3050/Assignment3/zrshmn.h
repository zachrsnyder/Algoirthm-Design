#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct Bucket{
    float buck_min;
    float buck_max;
    int isEmpty;
}Bucket;

float findClusterExtreme(float array[], int n);

int comparison(const void * a, const void * b);

float findClusterExtremeQ(float array[], int n);

void testClusterExtremes();

float timeClusterExtreme(float array[], int n);

float timeClusterExtremeQ(float array[], int n);

float findClusterExtremeBubble(float array[], int n);

float timeClusterExtremeBubble(float array[], int n);

void swap(float* xp, float* yp);

