#include "../../src/funcsSystem.h"
void 
initializeS(struct set2D *setS)
{
    int i;
    coord Quad[6][6] = {
        {{1, 1}, {1, 3}, {2, 2}, {3, 1}, {3, 3}}, 
        {{4, 4}, {4, 6}, {5, 5}, {6, 4}, {6, 6}}, 
        {{1, 5}, {2, 4}, {2, 5}, {2, 6}, {3, 5}}, 
        {{4, 1}, {4, 3}, {5, 1}, {5, 3}, {6, 1}, {6, 3}}
    };

    for (i = 0; i < 3; i++)
        {
            set1DCopyFromCoord1D(setS->D2Array + i, Quad[i], 5);
            setS->D2Array[i].length = 5;
        }
    // i = 3 after loop
    set1DCopyFromCoord1D(setS->D2Array + i, Quad[i], 6);
    setS->D2Array[i].length = 6;
    setS->width = 4;
    setS->maxSize = 6;
}

void 
initializeB(struct set1D *setB)

{
    int i;
    coord Quad2[6] = { {1, 1}, {2, 2}, {3, 3}, {3, 1}, {1, 3} };
    int size = 6;

    set1DCopyFromCoord1D(setB, Quad2, 6);
    coordPrint(Quad2[0]);
    setB->length = 6;
    setB->maxSize = 6;
}

int main()
{
    struct set1D setB;
    struct set2D setS, powerSetB, setC;
    

    set2DClear(&powerSetB);
    set2DClear(&setS);
    set1DClear(&setB);

    initializeS(&setS);
    initializeB(&setB);
    
    powerSet1D(&setB, &powerSetB);
    
    set1DPrint(&setB);
    set2DPrint(&powerSetB);
    set2DPrint(&setS);
    
    printf("%d\n", set2DIntersect(&setS, &powerSetB, &setC));
    set2DPrint(&setC);

    return 0;
}
