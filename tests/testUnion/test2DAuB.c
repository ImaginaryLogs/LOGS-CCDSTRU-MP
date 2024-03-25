#include "../../src/funcsSet2D.h"
#include <string.h>
#include <windows.h>

void 
initializeA(struct set2D *setS){
    int i;
    coord Quad[6][6] = {
        {}, 
        {{1, 1}}, 
        {{1, 1}, {2, 2}}, 
        {{1, 1}, {2, 2}, {3, 3}}
    };

    for (i = 0; i < 4; i++){
        set1DCopyFromCoord1D(setS->D2Array[i].D1Array, Quad[i], i);
        setS->D2Array[i].length = i;
    }
    setS->width = 4;
    setS->maxSize = 4;
}

void 
initializeB(struct set2D *setB){
    int i;
    coord Quad[6][6] = {
        {{1, 1}},
        {{2, 2}} 
    };
    int size = 2;

    for (i = 0; i < 4; i++){
        set1DCopyFromCoord1D(setB->D2Array[i].D1Array, Quad[i], 1);
        setB->D2Array[i].length = 1;
    }
    setB->width = 2;
    setB->maxSize = 2;
}

int main(){
    struct set2D setA, setB, setC;
    initializeA(&setA);
    initializeB(&setB);
    printf("%d\n", set2DIntersect(&setA, &setB, &setC));

    return 0;
}