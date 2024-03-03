/*
* TODO: 
*   - Set Functions:
*        - Set Union, Intersection, and Difference.
*   - Test Sort Selection.
*   - Board Coordinate Print Function
*   - System States and Behavior:
*       - Next Player Move
*       - Game Over 
*/


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#define MAXSIZE 72

typedef char String15[16];
typedef int coord[2];

// A general struct for a set of 1D
struct set1D {
    coord D1Array[MAXSIZE];
    int length;
    int maxSize;
};

// A general struct for a set of 2D
struct set2D {
    struct set1D D2Array[MAXSIZE];
    int width;
    int maxSize;
};

struct set3D {
    struct set2D D3Array[MAXSIZE];
    int height;
    int maxSize;
};

// #=====| Functions of Coordinates |======#
/**
 * @brief Source := Destination
 * @note Copies coordinate from Source to Destination.
 * @param Destination Coordinate you want to assign.
 * @param Source  Coordinate you want copy from.
 */
void coordCopy(coord Destination, coord Source){
    *Destination = Source[0];
    *(Destination + 1) = Source[1];
}

/**
 * @brief Prints: "(x, y) "
 * @param Coordinate Coordinate you want to print.
 */
void coordPrint(coord Coordinate){
    printf("(%d, %d) ", Coordinate[0], Coordinate[1]);
}

/**
 * @brief  (A, B) == (C, D) 
 * @param  A: 
 * @param  B: 
 * @return Boolean on equality
 * @retval 1 if Equal
 * @retval 0 if Not Equal
 */
bool coordEqual(coord A, coord B){
    return A[0] == B[0] && A[1] == B[1];
}

// #=====| Functions of ARRAY 1D Sets |======#
/**
 * @brief (Array1D) Prints 1D Set 
 * @param set[]: The 1D Array you want to print.
 * @param size: Size of 1D Array
 */
void coord1DPrint(coord set[], int size){
    int i;
    for(i = 0; i < size; i++)
        coordPrint(set[i]);
    printf("\n");
}

/**
 * @brief (Array1D) Srce[] := Dest[]
 * @note Copies SRCE (a set of 1D Array of Coordinates) to DEST (a set of 1D Array of Coordinates)
 * @param *srce: Source Coord
 * @param *dest: Destination
 * @param sizeDest: Size of Destination
 */
void set1DCopyFromCoord1D(coord *srce, coord *dest, int sizeDest){
    int i;
    for(i = 0; i < sizeDest; i++) {
        coordCopy(srce[i], dest[i]);
    }
}

// #=====| Functions of STRUCT 1D Sets |======#
/**
 * @brief (Struct1D) Prints 1D Set 
 * @param *set Pointer to a struct set1D
 */
void set1DPrint(struct set1D *set){
    int size = set->length;
    int i;
    for(i = 0; i < size; i++)
        coordPrint(set->D1Array[i]);
    printf("\n");
}

/**
 * @brief (Struct1D) Copies SRCE (Struct of 1D set) to DEST (Struct of 1D set)
 * @param *setDEST: Pointer to 1D Set you are grabbing from
 * @param *setSRCE: Pointer to 1D Set you want to assign
 */
void set1DCopy(struct set1D *setDEST, struct set1D *setSRCE){
    int i, size = setSRCE->length;
    for(i = 0; i < size; i++){
        coordCopy(setDEST->D1Array[i], setSRCE->D1Array[i]);
    }
}


/**
 * @brief is key ∈ Source True?
 * @note (Struct1D) Searches up setSource (Struct of 1D set) for the key. Location of key is in output - returns (-1, -1) if not found.
 * @param key: Coordinate you want to look for.
 * @param *setSource: 1D Set you want to look into.
 * @param location: Location of key in the array by col.
 * @return Boolean if Key is in the set.
 * @retval 1 if key ∈ Source
 * @retval 0 if key ∉ Source
 */
bool set1DSearch0Dkey(coord key, struct set1D *setSource, int *location){
    int j;
    *location = -1;
    for (j = 0; j < setSource->length; j++){
        if (coordEqual(key, setSource->D1Array[j])){
            *location = j;
            return true;
        }
    }
    
    return false;
}

bool set1DEqual(struct set1D *set1DSRCE, struct set1D *set1DDEST){
    bool isArrayMembersEqual = true;
    int i;
    int size = (set1DSRCE->length >= set1DDEST->length) ? set1DSRCE->length : set1DDEST->length;
    for(i = 0; i < size && isArrayMembersEqual; i++){
        isArrayMembersEqual = isArrayMembersEqual && coordEqual(set1DSRCE->D1Array[i], set1DDEST->D1Array[i]);
    }
    return isArrayMembersEqual && set1DSRCE->length == set1DDEST->length && set1DSRCE->maxSize == set1DDEST->maxSize;
}

/**
 * @brief setSRCE = P(setDEST)
 * @note Computes the power set of setDEST
 * @param *setDEST: A set1D struct you want to get the power set from
 * @param *setSRCE: A set2D struct the power set will copy to
 */
void powerSet1D(struct set1D *setDEST, struct set2D *setSRCE){
    int i, j, elements;
    int powerSetSize = pow(2, setDEST->length);
    setSRCE->maxSize = powerSetSize;
    setSRCE->width = powerSetSize;
    for(i = 0; i < powerSetSize; i++){
        elements = 0;
        for(j = 0; j < setDEST->length; j++){
            if(i & (1 << j)){
                coordPrint(setDEST->D1Array[j]);
                coordCopy(setSRCE->D2Array[i].D1Array[elements], setDEST->D1Array[j]);
                elements++;
            }
        }
        setSRCE->D2Array[i].length = elements;
        printf("\n");
    }

};

/**
 * @brief sorts set1D  
 * @param  *setDEST: A set1D struct you want to help copy from
 */
void sortSelection1DSet(struct set1D *setDEST){
    int i, j, max;
    coord temp = {0};
    for(i = 0; i < setDEST->maxSize - 1; i++){
        max = i;
        for(j = i; j < setDEST->maxSize; j++){
            if(setDEST->D1Array[j] > setDEST->D1Array[max])
                max = j;
            
        }
        if (max != i){
            coordCopy(temp, setDEST->D1Array[max]);
            coordCopy(setDEST->D1Array[max], setDEST->D1Array[i]);
            coordCopy(setDEST->D1Array[i], temp);
        }
    }
}

// #=====| Functions of STRUCT 2D Sets |======#
/**
 * @brief (Struct2D) Prints 2D Set
 * @param *set The 2D Array you want to print.
 */
void set2DPrint(struct set2D *set){
    int length, width = set->width;
    int row, col;
    printf("Printing 2D: \n");
    for(row = 0; row < width; row++){
        printf("\t%02d: ", row);
        set1DPrint(&(set->D2Array[row]));
    }
}

/**
 * @brief (Struct2D) Copies SRCE (Struct of 2D set) to DEST (Struct of 2D set)
 * @param *setDEST: Pointer to 2D Set you are grabbing from
 * @param *setSRCE: Pointer to 2D Set you want to assign
 */
void set2DCopy(struct set2D *setSRCE, struct set2D *setDEST){
    int i, size = setDEST->width;
    for(i = 0; i < size; i++)
        set1DCopy(&(setSRCE->D2Array[i]), &(setDEST->D2Array[i]));
    
}

/**
 * @brief is key ∈ Source True?
 * @note (Struct2D) Searches up setSource (Struct of 2D set) for the key. Location of key is in output - returns (-1, -1) if not found.
 * @param key: Coordinate you want to look for.
 * @param *setSource: 2D Set you want to look into.
 * @param location: Location of key in the array by (row, col).
 * @return Boolean if Key is in the set.
 * @retval 1 if key ∈ Source
 * @retval 0 if key ∉ Source
 */
bool set2DSearch0Dkey(coord key, struct set2D *setSource, coord location){
    location[0] = -1;
    location[1] = -1;
    int i, j;
    for (i = 0; i < setSource->width; i++){
        for (j = 0; j < setSource->D2Array[i].length; j++){
            if (coordEqual(key, setSource->D2Array[i].D1Array[j])){
                location[0] = i;
                location[1] = j;
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief is key ∈ Source True?
 * @note (Struct2D) Searches up setSource (Struct of 2D set) for the key. Location of key is in output - returns -1 if not found.
 * @param key: Coordinate you want to look for.
 * @param *setSource: 2D Set you want to look into.
 * @param location: Location of key in the array by row.
 * @return Boolean if Key is in the set.
 * @retval 1 if key ∈ Source
 * @retval 0 if key ∉ Source
 */
bool set2DSearchFor1Dkey(struct set1D *key, struct set2D *setSource, int *location){
    int i, j;
    int isSearch0DSuccessful;
    int isFound = false;

    printf("Searching: Set with size %d\n", key->length);
    set1DPrint(key);
    printf("inside the set\n");
    set2DPrint(setSource);

    for (i = 0; i < key->length && !isFound; i++){
        isSearch0DSuccessful = true;

        for (j = 0; j < setSource->D2Array[i].length && isSearch0DSuccessful; j++)
            isSearch0DSuccessful = set1DEqual(key, &setSource->D2Array[j]);

        if (j == setSource->D2Array[i].length){
            isFound = true;
            *location = i;
        }
    }
    return isFound; 
}

// #=====| Other functions |=================#

/**
 * @brief ∃x ( x∈P(S) ∧ |x| > 0 ∧ x ∈ P )
 * @note Is there a subset of S that exist that is not empty and is an element of set P?
 * @param *powerSetofSomeSet: A set2D struct of a power set created before hand of some set
 * @param *setP: A set2D struct of a set assigned as set P
 * @return boolean if it exists or not.
 * @retval TRUE if ∃x
 * @retval FALSE if ¬∃x
 */
bool thereExistCondition1(struct set2D *powerSetofSomeSet, struct set2D *setP){
    coord location = {0};
    struct set1D elemX;
    bool isExist = false;
    int elemXsizeIsNotNull;
    int elemXisInsideSetP = 0;
    int i, j;
    for (i = 0; i < powerSetofSomeSet->width && !isExist; i++){
        elemX = powerSetofSomeSet->D2Array[i];
        elemXsizeIsNotNull = powerSetofSomeSet->D2Array[i].length > 0;
        elemXisInsideSetP = set2DSearchFor1Dkey(&powerSetofSomeSet->D2Array[i], setP, location);
        if (elemXsizeIsNotNull && elemXisInsideSetP)
            isExist = true;
    }
    return isExist;
}

/**
 * @brief Initialize (set2D) Set S based on MP Specs  
 * @param *setS: A set2D struct you will assign as S
 */
void initializeS(struct set2D *setS){
    int i;
    coord Quad[6][6] = {
        {{1, 1}, {1, 3}, {2, 2}, {3, 1}, {3, 3}}, 
        {{4, 4}, {4, 6}, {5, 5}, {6, 4}, {6, 6}}, 
        {{1, 5}, {2, 4}, {2, 5}, {2, 6}, {3, 5}}, 
        {{4, 1}, {4, 3}, {5, 1}, {5, 3}, {6, 1}, {6, 3}}
    };

    for (i = 0; i < 3; i++){
        set1DCopyFromCoord1D(setS->D2Array[i].D1Array, Quad[i], 5);
        setS->D2Array[i].length = 5;
    }
    // i = 3 after loop
    set1DCopyFromCoord1D(setS->D2Array[i].D1Array, Quad[i], 6);
    setS->D2Array[i].length = 6;
    setS->width = 4;
    setS->maxSize = 6;
}

/**
 * @brief Initialize (set2D) Set P based on MP Specs  
 * @param *setP: A set2D struct you will assign as P
 */
void initializeP(struct set2D *setP){
    int i;
    coord Duo[2][2] = {
        {{1, 1}, {2, 2}}, 
        {{1, 2}, {2, 1}}
    };

    for (i = 0; i < 2; i++){
        set1DCopyFromCoord1D(setP->D2Array[i].D1Array, Duo[i], 2);
        setP->D2Array[i].length = 2;
    }
    setP->width = 2;
    setP->maxSize = 2;
}

void NextPlayerMove(coord pos, struct set1D *F1, struct set1D *F2, struct set1D *F3, bool over, bool good, bool next){
    int a = pos[0];
    int b = pos[0];
    int c = (a - 1) / 3 + 1;
    int d = (b - 1) / 3 + 1;
    
}

void GameOver(bool *over, bool *next){
    String15 result;

    if (!*over) 
        *next = !(*next);
}


int main(int argc, char const *argv[])
{
    // Applicable Sets
    struct set1D setU, setT;

    bool setV[2] = {true, false};

    struct set2D setC, setF, setS, setP, setPowerSetS;

    coord output = {0};
    coord key = {4, 6};

    initializeS(&setS);
    initializeP(&setP);
    set2DSearch0Dkey(key, &setS, output);
    coordPrint(output);
    printf("\n");
    // System Variables
    bool good = false;
    bool next = false;
    bool over = false;
    
    coord C1;
    coord C2;
    coord F1;
    coord F2;
    coord F3; 

    set2DPrint(&setS);
    set2DPrint(&setPowerSetS);
    powerSet1D(&setS.D2Array[0], &setPowerSetS);
    set2DPrint(&setPowerSetS);
    printf("%d", thereExistCondition1(&setPowerSetS, &setP));
    GameOver(&over, &next);
    return 0;
}