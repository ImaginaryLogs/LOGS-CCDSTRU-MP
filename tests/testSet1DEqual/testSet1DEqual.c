#include "../../src/funcsSet2D.h"
#include <string.h>
#include <windows.h>

void 
initializeA(struct set2D *setS){
    int i;
    coord Quad[6][6] = {
        {}, 
        {{1, 1}}, 
        {{2, 2}, {1, 1}}, 
        {{1, 1}, {2, 2}, {3, 3}}
    };

    for (i = 0; i < 4; i++){
        set1DCopyFromCoord1D(setS->D2Array + i, Quad[i], i);
        setS->D2Array[i].length = i;
    }
    setS->width = 4;
    setS->maxSize = 4;
}

void 
initializeB(struct set1D *setB){
    int i;
    coord Quad[2] = {{1, 1}, {2, 2}};
    
    int size = 2;

    set1DCopyFromCoord1D(&setB, Quad, 2);
    setB->length = 2;
    setB->maxSize = 2;
}

int main(){
    struct set2D setA;
    struct set1D setB;
    initializeA(&setA);
    initializeB(&setB);
    printf("%d\n", set1DEqual(&setB, &setA.D2Array[2]));

    return 0;
}