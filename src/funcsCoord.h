#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include"defin.h"

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
 * @param coordInput Coordinate you want to print.
 */
void coordPrint(int *coordInput){
    printf("(%d, %d) ", *coordInput, *(coordInput + 1));
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
