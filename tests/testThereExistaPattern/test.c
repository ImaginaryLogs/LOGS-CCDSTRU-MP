#include "../../src/funcsSystem.h"
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
        set1DCopyFromCoord1D(setS->D2Array + i, Quad[i], i);
        setS->D2Array[i].length = i;
    }
    setS->width = 4;
    setS->maxSize = 4;
}

void 
initializeB(struct set1D *setB){
    int i;
    coord Quad[3] = {{1, 1}, {2, 2}};
    
    int size = 3;

    set1DCopyFromCoord1D(setB, Quad, size);
    setB->length = size;
    setB->maxSize = size;
}

int main(){
    struct set2D setA, psetB;
    struct set1D setB;
    
    initializeA(&setA);
    initializeB(&setB);
    powerSet1D(&setB, &psetB);
    printf("%d\n", thereExistCondition1(&psetB, &setA));
    printf("%d\n", setKencompassesSetP(&setB, &setA));

    return 0;
}