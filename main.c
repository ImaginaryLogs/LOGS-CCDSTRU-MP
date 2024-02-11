
#include <stdio.h>
#include <stdbool.h>

typedef char String15[16];
typedef int cord[2];

struct set1D {
    cord D1Array[36];
    int length;
    int maxSize;
};

struct set2D {
    struct set1D D2Array[6];
    int width;
    int maxSize;
};


void cordCopy(cord Source, cord Destination){
    *Source = Destination[0];
    *(Source + 1) = Destination[1];
}

void cordPrint(cord Coordinate){
    printf("(%d, %d) ", Coordinate[0], Coordinate[1]);
}

bool coordEqual(cord A, cord B){
    return A[0] == B[0] && A[1] == B[1];
}


void cord1DPrint(int set[][2], int size){
    int i;
    for(i = 0; i < size; i++)
        cordPrint(set[i]);
    printf("\n");
}

void set1DPrint(struct set1D *set){
    int size = set->length;
    int i;
    for(i = 0; i < size; i++)
        cordPrint(set->D1Array[i]);
    printf("\n");
}

void set1DCopyFromCord1D(cord *srce, cord *dest, int sizeDest){
    int i;
    for(i = 0; i < sizeDest; i++){
        cordCopy(srce[i], dest[i]);
    }
}

void set1DCopy(struct set1D *setSRCE, struct set1D *setDEST){
    int i, size = setDEST->length;
    for(i = 0; i < size; i++){
        cordCopy(setSRCE->D1Array[i], setDEST->D1Array[i]);
    }
}

void set2DCopy(struct set2D *setSRCE, struct set2D *setDEST){
    int i, size = setDEST->width;
    for(i = 0; i < size; i++){
        set1DCopy(&(setSRCE->D2Array[i]), &(setDEST->D2Array[i]));
    }
}

void set2DPrint(struct set2D *set){
    int length, width = set->width;
    int row, col;
    printf("Printing 2D: \n");
    for(row = 0; row < width; row++){
        printf("\t%d: ", row);
        set1DPrint(&(set->D2Array[row]));
    }
}

void initializeS(struct set2D *setS){
    cord Quad[6][6] = {
        {{1, 1}, {1, 3}, {2, 2}, {3, 1}, {3, 3}}, 
        {{4, 4}, {4, 6}, {5, 5}, {6, 4}, {6, 6}}, 
        {{1, 5}, {2, 4}, {2, 5}, {2, 6}, {3, 5}}, 
        {{4, 1}, {4, 3}, {5, 1}, {5, 3}, {6, 1}, {6, 3}}
    };

    int i;
    for(i = 0; i < 3; i++){
        set1DCopyFromCord1D(setS->D2Array[i].D1Array, Quad[i], 5);
        setS->D2Array[i].length = 5;
    }
    // i = 3 after loop
    set1DCopyFromCord1D(setS->D2Array[i].D1Array, Quad[i], 6);
    setS->D2Array[i].length = 6;
    setS->width = 4;
    setS->maxSize = 6;
}

void initializeP(struct set2D *setP){
    cord Duo[2][2] = {
        {{1, 1}, {2, 2}}, 
        {{1, 2}, {2, 1}}
    };

    int i;
    for(i = 0; i < 2; i++){
        set1DCopyFromCord1D(setP->D2Array[i].D1Array, Duo[i], 2);
        setP->D2Array[i].length = 2;
    }
    setP->width = 2;
    setP->maxSize = 2;
}

int main(int argc, char const *argv[])
{

    // Applicable Sets
    struct set1D setU;
    struct set1D setT;

    struct set2D setC;

    struct set2D setF;

    bool setV[2] = {true, false};

    struct set2D setS;
    initializeS(&setS);

    struct set2D setP;
    initializeP(&setP);
    
    // System Variables
    bool good = false;
    bool next = false;
    bool over = false;


    set2DPrint(&setS);


    return 0;
}