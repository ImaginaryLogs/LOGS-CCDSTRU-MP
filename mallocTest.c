
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef char String15[16];
typedef int cord[2];


int main(int argc, char const *argv[])
{
    int r = 3, c = 4, i, j, count;
 
    int** arr = (int**) malloc(r * sizeof(int*));
    for (i = 0; i < r; i++)
        arr[i] = (int*) malloc(c * sizeof(int));
 
    // Note that arr[i][j] is same as *(*(arr+i)+j)
    count = 0;
    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            arr[i][j] = ++count; // OR *(*(arr+i)+j) = ++count
 
    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            printf("%d ", arr[i][j]);
 
    /* Code for further processing and free the
       dynamically allocated memory */
 
    for (int i = 0; i < r; i++)
        free(arr[i]);
 
    free(arr);
    
    // System Variables
    bool good = false;
    bool next = false;
    bool over = false;
    cord C1;
    cord C2;
    cord F1;
    cord F2;
    cord F3; 

    return 0;
}