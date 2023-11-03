#include"zrshmn.h"

float findClusterExtreme(float array[], int n)
{
    float min = array[0];
    float max = array[0];
    int i = 1, calculation;
    Bucket * list = malloc(sizeof(Bucket) * (n-1));
    for(;i < n; i++)
    {
        if(array[i] < min)
            min = array[i];
        else if(array[i] > max)
            max = array[i];
        list[i-1].isEmpty = 0;
    };
    for(int j = 0; j < n; ++j)
    {
        calculation = ((array[j] - min) / (max - min)) * (n-1);
        if(array[j] == min || array[j] == max)
            continue;
        else{
            if(list[calculation].isEmpty == 0)
            {
                list[calculation].isEmpty = 1;
                list[calculation].buck_min = array[j];
                list[calculation].buck_max = array[j];
            }else if(array[j] < list[calculation].buck_min)
                list[calculation].buck_min = array[j];
            else if(array[j] > list[calculation].buck_max)
                list[calculation].buck_max = array[j];
        }
    }
    float curr_min = min;
    float maxdist_min = min;
    float max_distance = 0;
    for(int k = 0; k < n-1; ++k)
    {
        if(list[k].isEmpty == 0)
            continue;
        else{
            if(list[k].buck_min - curr_min > max_distance)
            {
                max_distance = list[k].buck_min - curr_min;
                maxdist_min = curr_min;
            }
            curr_min = list[k].buck_max;
        }
    }
    if(max - curr_min > max_distance)
    {
        maxdist_min = curr_min;
        max_distance = max - curr_min;
    }
    free(list);
    return maxdist_min;
}

int comparison(const void * a, const void * b)
{
    float fa = *(const float*)a;
    float fb = *(const float*)b;

    if (fa < fb) {
        return -1;
    }
    if (fa > fb) {
        return 1;
    }
    return 0;
}

float findClusterExtremeQ(float array[], int n){
    qsort(array, n ,sizeof(float), comparison);
    float max_distance = 0;
    float max_distance_min = array[0];
    for(int i = 0; i < n-1; ++i)
    {
        if(array[i+1] - array[i] > max_distance)
        {
            max_distance = array[i+1] - array[i];
            max_distance_min = array[i];
        }
    }
    return max_distance_min;
}

void swap(float* xp, float* yp)
{
    float temp = *xp;
    *xp = *yp;
    *yp = temp;
}

float findClusterExtremeBubble(float array[], int n){
    int i, j;
    bool swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = false;
        for (j = 0; j < n - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                swap(&array[j], &array[j + 1]);
                swapped = true;
            }
        }
        // If no two elements were swapped by inner loop,
        // then break
        if (swapped == false)
            break;
    }
    float max_distance = 0;
    float max_distance_min = array[0];
    for(i = 0; i < n-1; ++i)
    {
        if(array[i+1] - array[i] > max_distance)
        {
            max_distance = array[i+1] - array[i];
            max_distance_min = array[i];
        }
    }
    return max_distance_min;
}
//bubble sort and swap algorithmn pulled from GeeksForGeeks and is used only to compare to other time complexities.

float timeClusterExtreme(float array[], int n){
    clock_t start, end;
    float time;
    start = clock();
    printf("\t\t*Cluster Extreme via Hashing: %f\n", findClusterExtreme(array, n));
    end = clock();
    time = ((double)(end - start)) / CLOCKS_PER_SEC;
    return time;
}

float timeClusterExtremeQ(float array[], int n){
    clock_t start, end;
    float time;
    start = clock();
    printf("\t\t*Cluster Extreme via NLogn Algorithm: %f\n", findClusterExtremeQ(array, n));
    end = clock();
    time = ((double)(end - start)) / CLOCKS_PER_SEC;
    return time;
}

float timeClusterExtremeBubble(float array[], int n){
    clock_t start, end;
    float time;
    start = clock();
    printf("\t\t*Cluster Extreme via N^2 Algorithm: %f\n", findClusterExtremeBubble(array, n));
    end = clock();
    time = ((double)(end - start)) / CLOCKS_PER_SEC;
    return time;
}

void testClusterExtremes(){
    char * array[] = {"8k.txt", "16k.txt", "32k.txt", "64k.txt", "128k.txt", "256k.txt", "512k.txt"};
    FILE * fptr = fopen("dataHash.csv", "w");
    FILE * fptr2 = fopen("dataQSort.csv", "w");
    FILE * fptr3 = fopen("dataBubble.csv", "w");
    for(int i = 0; i < 3; i++){
        printf("************Test Sequence #%d************\n", i+1);
        for(int j = 8000, y = 0; j < 1024000; j = j * 2, ++y){
            FILE * f = fopen(array[y], "r");
            float * test_array = malloc(sizeof(float) * j);
            float * test_array2 = malloc(sizeof(float) * j);
            for(int k = 0; k < j; k++)
            {
                fscanf(f, "%f, ", &test_array[k]);
                test_array2[k] = test_array[k];
            }
            fclose(f);
            printf("\tDataset of size %d\n", j);
            float hash = timeClusterExtreme(test_array, j);
            float NLogN = timeClusterExtremeQ(test_array, j);
            float NN = timeClusterExtremeBubble(test_array2, j);
            printf("\t\tTime it took with Hash: %f\n", hash);
            printf("\t\tTime it took NLogN: %f\n", NLogN);
            printf("\t\tTime it took with Bubble Sort: %f\n", NN);
            fprintf(fptr, "%f, ", hash);
            fprintf(fptr2, "%f, ", NLogN);
            fprintf(fptr3, "%f, ", NN);
            free(test_array);
            free(test_array2);
        }
        fprintf(fptr, "\n");
        fprintf(fptr2, "\n");
        fprintf(fptr3, "\n");
    }
    fclose(fptr);
    fclose(fptr2);
    fclose(fptr3);
}

