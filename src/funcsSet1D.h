#include<math.h>
#include"funcsCoord.h"


// #=====| Functions of STRUCT 1D Sets |======#
/**
 * @brief (Struct1D) Prints 1D Set 
 * @param *set Pointer to a struct set1D
 */
void 
set1DPrint(struct set1D *set){
    int size = set->length;
    int i;
    printf("\t{ ");
    for(i = 0; i < size; i++)
        coordPrint(set->D1Array[i]);
    printf("}\n");
}

/**
 * @brief (Struct1D) Copies SRCE (Struct of 1D set) to DEST (Struct of 1D set)
 * @param *setDEST: Pointer to 1D Set you are grabbing from
 * @param *setSRCE: Pointer to 1D Set you want to assign
 */
void 
set1DCopy(struct set1D *setDEST, struct set1D *setSRCE){
    int i, size = setSRCE->length;
    for(i = 0; i < size; i++){
        coordCopy(setDEST->D1Array[i], setSRCE->D1Array[i]);
    }
    setDEST->length = setSRCE->length;
}

void
set1DClear(struct set1D *A){
    int i;
    for(i = 0; i < A->length; i++){
        A->D1Array[i][0] = 0;
        A->D1Array[i][1] = 0;
    }
    A->length = 0;
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
bool 
set1DSearch0Dkey(coord key, struct set1D *setSource, int *location){
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

bool 
set1DEqual(struct set1D *set1DSRCE, struct set1D *set1DDEST){
    struct set1D biggerSet, smallerSet;

    bool isMembersEqual = true;
    int i, j;
    int maxSize = (set1DSRCE->length >= set1DDEST->length) ? set1DSRCE->length : set1DDEST->length;
    int minSize = (set1DSRCE->length < set1DDEST->length) ? set1DSRCE->length : set1DDEST->length;

    if (set1DSRCE->length > set1DDEST->length) {
        biggerSet = *set1DSRCE;
        smallerSet = *set1DDEST;
    } else {
        smallerSet = *set1DSRCE;
        biggerSet = *set1DDEST;
    }

    for (i = 0; i < maxSize && isMembersEqual; i++){
        isMembersEqual = false;
        for(j = 0; j < minSize && !isMembersEqual; j++){
            if (coordEqual(biggerSet.D1Array[i], smallerSet.D1Array[j])){
                isMembersEqual = true;
            }
        }
    }
    
    //printf("\tEqual? %d\n\n", isMembersEqual);
    return isMembersEqual;
}

/**
 * @brief setSRCE = P(setDEST)
 * @note Computes the power set of setDEST
 * @param *setDEST: A set1D struct you want to get the power set from
 * @param *setSRCE: A set2D struct the power set will copy to
 */
void 
powerSet1D(struct set1D *setDEST, struct set2D *setSRCE){
    int i, j, elements;
    int powerSetSize = pow(2, setDEST->length);
    setSRCE->maxSize = powerSetSize;
    setSRCE->width = powerSetSize;
    for(i = 0; i < powerSetSize; i++){
        elements = 0;
        for(j = 0; j < setDEST->length; j++){
            // The increase binary numbers corresponds to the selection of elements. j shifts 1 and acts as the mask whether or not to copy the function.
            // 10010 means select the 2, 5 element.
            // 11010 means select the 3, 4, 5 element.
            if ((1 << j) & i){ 
                coordCopy(setSRCE->D2Array[i].D1Array[elements], setDEST->D1Array[j]);
                elements++;
            }
        }
        setSRCE->D2Array[i].length = elements;
    }

};

/**
 * @brief sorts set1D  
 * @param  *setDEST: A set1D struct you want to help copy from
 */
void 
sortSelection1DSet(struct set1D *setDEST){
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

int
set1DUnion(struct set1D *A, struct set1D *B, struct set1D *C)
{
	int i;
	int isElemBUnique;
	int countC = 0;
	int loc;

	for(i = 0; i < A->length; i++){
		if (!set1DSearch0Dkey(A->D1Array[i], C, &loc)){
			coordCopy(C->D1Array[countC], A->D1Array[i]);
            C->length++;
			countC++;
		}
	}
	
	
	for(i = 0; i < B->length; i++){
		isElemBUnique = false;
        
		if (!set1DSearch0Dkey(B->D1Array[i], C, &loc)){
			isElemBUnique = true;
		}
		//printf("Is B unique? %d\n", isElemBUnique);
		if (isElemBUnique) {
			coordCopy(C->D1Array[countC], B->D1Array[i]);
            C->length++;
			countC++;
		}
	}
    C->length = countC;
	
	return countC;  //remember to update the return statement
}

int
set1DDiff(struct set1D *A, struct set1D *B, struct set1D *C)
{
	int i;
	int isElemAUnique;
	int countC = 0;
	int loc;

    set1DClear(C);

	for(i = 0; i < A->length; i++){
		isElemAUnique = false;
		set1DSearch0Dkey(A->D1Array[i], B, &loc);
		if (loc == -1)
			isElemAUnique = 1;
			
		if (isElemAUnique){
			coordCopy(C->D1Array[countC], A->D1Array[i]);
            C->length++;
			countC++;
		}
	}
	return countC;  //remember to update the return statement
}

int
set1DIntersect(struct set1D A[], struct set1D B[], struct set1D C[])
{
	int i;
	int isBothPresent = 0;
	int countAUnionB;
	int countC = 0; 
    set1DClear(C); 

	struct set1D AUnionB;
    set1DClear(&AUnionB); 
	countAUnionB = set1DUnion(A, B, &AUnionB);

	int locA, locB, locC;
	
	for(i = 0; i < countAUnionB; i++) {
        set1DSearch0Dkey(AUnionB.D1Array[i], A, &locA);
        set1DSearch0Dkey(AUnionB.D1Array[i], B, &locB);
        set1DSearch0Dkey(AUnionB.D1Array[i], C, &locC);
		isBothPresent = locA != -1 &&  
						locB != -1 &&
						locC == -1;
						
		if(isBothPresent) {
            coordCopy(C->D1Array[countC], AUnionB.D1Array[i]);
            C->length++;
			countC++;
		}
	}
	return countC;
}
