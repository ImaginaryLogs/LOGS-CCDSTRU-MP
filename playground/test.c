#include <stdio.h>
#include <stdbool.h>

#define nullPoint {NULL, NULL}


void set2Dprint(int D2Array[][2]){
    int length = (int) sizeof(D2Array[0])/sizeof(D2Array[0][0]);
    printf("%d", length);
}


int main(){
    int D1Array[4] = {0};

    printf("%d", (int) sizeof(D1Array) / sizeof(D1Array[0]));


    int D2Array[4][2] = {{1, 1}, {2, 2}, {3, 3}, {0, 0}};
    
    // int D3Array[4][4][2] = {nullPoint};
    // int D3Array[4][4][2] = {{{1, 1}, {2, 2}, nullPoint}, {{1, 1}, {2, 2}, nullPoint}};
    return 0;
}