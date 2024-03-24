#include "../src/funcsSet2D.h"
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
initializeB(struct set1D *setB){
    int i;
    coord Quad[6][6] = {
        {}, 
    };
    int size = 0;

    set1DCopyFromCoord1D(setB->D1Array, Quad[0], size);
    setB->length = size;

}

int main(){
    struct set1D setB;
    struct set2D setA;
    initializeA(&setA);
    initializeB(&setB);
    coord loc;
    printf("%d\n", set2DSearch1Dkey(&setB, &setA, loc));
    printf("{%d, %d}\n", loc[0], loc[1]);

    return 0;
}