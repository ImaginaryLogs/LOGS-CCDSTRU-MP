
#include"funcsSet1D.h"

// #=====| Functions of STRUCT 2D Sets |======#
/**
 * @brief (Struct2D) Prints 2D Set
 * @param *set The 2D Array you want to print.
 */
void 
set2DPrint(struct set2D *set){
    int width = set->width;
	int row;
    printf("\tPrinting 2D: \n");
    for(row = 0; row < width; row++){
        printf("\t\t%02d: ", row);
        set1DPrint(&(set->D2Array[row]));
    }
}

/**
 * @brief (Struct2D) Copies SRCE (Struct of 2D set) to DEST (Struct of 2D set)
 * @param *setDEST: Pointer to 2D Set you are grabbing from
 * @param *setSRCE: Pointer to 2D Set you want to assign
 */
void 
set2DCopy(struct set2D *setSRCE, struct set2D *setDEST){
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
bool 
set2DSearch0Dkey(coord key, struct set2D *setSource, coord location){
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
bool 
set2DSearch1Dkey(struct set1D *key, struct set2D *setSource, int *location){
    int i, j;
    int isSearch1DSuccessful;
    int isFound = false;

    printf("\tSearching: set with size %d\n", key->length);
    set1DPrint(key);
    printf("\tinside the set with width %d\n", setSource->width);
    set2DPrint(setSource);
    *location = -1;
    if (setSource->D2Array[0].length == key->length){
        //printf("Null set found!");
        *location = 0;
        isFound = true;
    } 

    for (i = 0; i < key->length && !isFound; i++){
        isSearch1DSuccessful = false;
        

        for (j = 0; j < setSource->D2Array[i].length && !isSearch1DSuccessful; j++)
            isSearch1DSuccessful = set1DEqual(key, &setSource->D2Array[j]);
        

        if (isSearch1DSuccessful){
            isFound = true;
            *location = i;
        }
    }
    printf("\tReturned: %d\n", isFound);
    return isFound; 
}

int
set2DUnion(struct set2D *A, struct set2D *B, struct set2D *C){
	int i;
	int isElemBUnique;
	int countC = 0;
	int loc;

    // printf("Unionizing: Set 1 with size %d\n and Set 2 with size %d", A->width, B->width);
    
    if (A->D2Array->length == 0 && set2DSearch1Dkey(A->D2Array, C, &loc)) {
        C->width++;
        countC++;   
    }
	for(i = 0; i < A->width; i++){
        
		if (!set2DSearch1Dkey(A->D2Array + i , C, &loc)){
            // printf("Same!\n");
            // set1DPrint(A->D2Array + i);
            // set1DPrint(C->D2Array + countC);
			set1DCopy(C->D2Array + countC, A->D2Array + i);
            // set1DPrint(C->D2Array + countC);
            C->width++;
			countC++;
		}
	}
	
	for(i = 0; i < B->width; i++){
		isElemBUnique = false;
		if (!set2DSearch1Dkey(B->D2Array + i, C, &loc)){
			isElemBUnique = true;
		}
			
		if (isElemBUnique) {
            set1DPrint(B->D2Array + i);      
			set1DCopy(C->D2Array + countC, B->D2Array + i);
            C->width++;
			countC++;
		}
	}
	
    printf("A: %d\n", A->width);
    set2DPrint(A);
    printf("B: %d\n", B->width);
    set2DPrint(B);
    printf("AuB: %d\n", C->width);
    set2DPrint(C);
	return countC;  //remember to update the return statement
}

void
set2DClear(struct set2D *A){
    int i, j;
    for(i = 0; i < 72; i++){
        for(j = 0; j < 72; j++){
            A->D2Array[i].D1Array[j][0] = 0;
            A->D2Array[i].D1Array[j][1] = 0;
        }
        A->D2Array[i].length = 0;
        A->D2Array[i].maxSize = 0;
    }
    A->width = 0;
    A->maxSize = 0;
}

int
set2DDiff(struct set2D *A, struct set2D *B, struct set2D *C)
{
	int i;
	int isElemAUnique;
	int countC = 0;
	int loc;

    set2DClear(C);

	for(i = 0; i < A->width; i++){
		isElemAUnique = false;
		set2DSearch1Dkey(A->D2Array + i, B, &loc);
		if (loc == -1)
			isElemAUnique = 1;
			
		if (isElemAUnique){
			set1DCopy(C->D2Array + countC, A->D2Array + i);
            C->width++;
			countC++;
		}
	}
	return countC;  //remember to update the return statement
}

int
set2DIntersect(struct set2D *A, struct set2D *B, struct set2D *C)
{
	int i;
	int isBothPresent = 0;
	int countAUnionB;
	int countC = 0;
    int locA, locB, locC;
	struct set2D AUnionB;

    set2DClear(C); 
    set2DClear(&AUnionB); 
	countAUnionB = set2DUnion(A, B, &AUnionB);

    printf("AuB: %d\n", countAUnionB);
	locA = 0;
	locB = 0;
    locC = 0;
	for (i = 0; i < countAUnionB; i++) {
        set2DSearch1Dkey(AUnionB.D2Array + i, A, &locA);
        set2DSearch1Dkey(AUnionB.D2Array + i, B, &locB);
        set2DSearch1Dkey(AUnionB.D2Array + i, C, &locC);
        printf("in A, B, and AnB?: %d %d %d\n", locA, locB, locC);
		isBothPresent = locA != -1 && locB != -1 && locC == -1;
						
		if (isBothPresent){
            set1DCopy(C->D2Array + countC, AUnionB.D2Array + i);
            C->width++;
			countC++;
		}
        
	}
    printf("C = A n B\n");
    set2DPrint(C);
	return countC;
}

void
set2DPrintGrid(struct set2D *A){
    coord current;
    int isFound = false;
    int i = 0, j = 0, k = 0, l = 0;
    int stacks = 0;
    for (i = 6; i >= 1; i--){
        printf("*---*---*---*---*---*---*\n");

        current[1] = i;
        for (j = 1; j <= 6; j++){
            current[0] = j;
            isFound = false;
            stacks = 0;
            for(k = 0; k < A->width ; k++){
                for (l = 0; l < A->D2Array[k].length; l++){
                    if (coordEqual(A->D2Array[k].D1Array[l], current)){
                        isFound = true;
                        stacks++;
                    }
                }
            }
            if (!isFound)
                printf("|   ");
            else 
                printf("| %02d", stacks);
        }
        printf("|\n");
    }
    printf("*---*---*---*---*---*---*\n");
}

int
set2DTotalSize(struct set2D *input){
    int i;
    int sum = 0;
    for (i = 0; i < input->width; i++){
        sum += input->D2Array[i].length;
    }
    return sum;
}