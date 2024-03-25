
#include "funcsSystem.h"

int main()
{
    struct set1D F, F1, F2, F3, C, C1, C2;
    struct set2D setS, setP;
    int i = 0;

    set1DClear(&F);
    set1DClear(&F1);
    set1DClear(&F2);
    set1DClear(&F3);
    set1DClear(&C);
    set1DClear(&C1);
    set1DClear(&C2);
	
    //bool setV[2] = {true, false};
    
    initializeF(&F);
    initializeC(&C);
    initializeS(&setS);
    initializeP(&setP);
    updateF3(&F, &F1, &F2, &F3);

    // System Variables
    bool good = false;
    bool next = false;	
    bool over = false;
    coord input;
    set1DPrint(&F);

    printf("\n\n");
    printf("F1, F2:\n");
    printPlayerBoard(&F1, &F2, 6);
    printf("F3 :\n");
    printGrid(F3);
    printf("C1, C2:\n");
    printPlayerBoard(&C1, &C2, 2);

    while (!over) {
        printf("\n\n");
        printf("F1, F2:\n");
        printPlayerBoard(&F1, &F2, 6);
        printf("F3 :\n");
        printGrid(F3);
        printf("C1, C2:\n");
        printPlayerBoard(&C1, &C2, 2);
        printf("\n\n");

        RepeatGetCoord(input);
        updateOver(&F3, &C1, &C2, &over, &setP);
        NextPlayerMove1(input, &F, &F1, &F2, &F3, over, &good, next, &setS, &C1, &C2, i);
        updateOver(&F3, &C1, &C2, &over, &setP);
        GameOver2(&over, &next, &C1, &C2, &setP);
        i++;
    }
    
    return 0;
}
