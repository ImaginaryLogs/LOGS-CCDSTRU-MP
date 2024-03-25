#include "funcsSet2D.h"
#include <string.h>
#include <windows.h>

#define FG_WHITE (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)
#define FG_RED FOREGROUND_RED
#define FG_BLUE FOREGROUND_BLUE
#define FG_PURP (FOREGROUND_RED | FOREGROUND_BLUE)
#define FG_GREN FOREGROUND_GREEN

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
bool 
thereExistCondition1(struct set2D *powerSetofSomeSet, struct set2D *setP){
    coord location = {0};
    bool isExist = false;
    int elemXsizeIsNotNull;
    int elemXisInsideSetP = 0;
    int i;
    for (i = 0; i < powerSetofSomeSet->width && !isExist; i++){
        elemXsizeIsNotNull = powerSetofSomeSet->D2Array[i].length > 0;
        elemXisInsideSetP = set2DSearch1Dkey(&powerSetofSomeSet->D2Array[i], setP, location);
        printf("|X| > 0 and isInsideSetP: %d && %d\n", elemXsizeIsNotNull, elemXisInsideSetP);
        if (elemXsizeIsNotNull && elemXisInsideSetP)
            isExist = true;
    }
    return isExist;
}

bool 
setKencompassesSetP(struct set1D * SetK, struct set2D *setP){
    struct set1D sliceOfPowerSet;
    int i, j, elements;
    int elemXsizeIsNotNull;
    int elemXisInsideSetP;
    int isExist = false;
    int powerSetSize = pow(2, SetK->length);
    for(i = 0; i < powerSetSize && !isExist; i++){
        elements = 0;
        set1DClear(&sliceOfPowerSet);
        for(j = 0; j < SetK->length; j++){
            if ((1 << j) & i) {
                coordCopy(sliceOfPowerSet.D1Array[elements], SetK->D1Array[j]);
                elements++;
            }
        }
        sliceOfPowerSet.length = elements;
        elemXsizeIsNotNull = sliceOfPowerSet.length > 0;
        elemXisInsideSetP = set1DEqual(&sliceOfPowerSet, setP->D2Array);
        elemXisInsideSetP = set1DEqual(&sliceOfPowerSet, setP->D2Array + i);
        printf("|X| > 0 and isInsideSetP: %d && %d\n", elemXsizeIsNotNull, elemXisInsideSetP);
        if (elemXsizeIsNotNull && elemXisInsideSetP)
            isExist = true;
    }
    return isExist;
}

int
patternF1inS(struct set1D *F, struct set2D *S){
    struct set2D sliceOfPowerSet, slicePSetFnS, temp, PSetFnS;
    int i, j, elements;
    int isExist = false;
    int powerSetSize = pow(2, F->length);
    set2DClear(&temp);
    set2DClear(&sliceOfPowerSet);
    set2DClear(&slicePSetFnS);
    set2DClear(&PSetFnS);
    sliceOfPowerSet.width = 1;
    
    for(i = 0; i < powerSetSize && !isExist; i++){
        elements = 0;
        set1DClear(&sliceOfPowerSet.D2Array[0]);
        for(j = 0; j < F->length; j++){
            if ((1 << j) & i) {
                coordCopy(sliceOfPowerSet.D2Array[0].D1Array[elements], F->D1Array[j]);
                elements++;
            }
        }
        
        sliceOfPowerSet.D2Array[0].length = elements;
        set2DIntersect(&sliceOfPowerSet, S, &slicePSetFnS);
        if(slicePSetFnS.D2Array->length > 0){
            
            set2DUnion(&slicePSetFnS, &PSetFnS, &temp);
            set2DPrint(&PSetFnS);   
            PSetFnS = temp;
        }
    }
    return PSetFnS.width;
}

/**
 * @brief Initialize (set2D) Set S based on MP Specs  
 * @param *setS: A set2D struct you will assign as S
 */
void 
initializeS(struct set2D *setS){
    int i;
    coord Quad[6][6] = {
        {{1, 1}, {1, 3}, {2, 2}, {3, 1}, {3, 3}}, 
        {{4, 4}, {4, 6}, {5, 5}, {6, 4}, {6, 6}}, 
        {{1, 5}, {2, 4}, {2, 5}, {2, 6}, {3, 5}}, 
        {{4, 1}, {4, 3}, {5, 1}, {5, 3}, {6, 1}, {6, 3}}
    };

    for (i = 0; i < 3; i++){
        set1DCopyFromCoord1D(setS->D2Array + i, Quad[i], 5);
        setS->D2Array[i].length = 5;
    }
    // i = 3 after loop
    set1DCopyFromCoord1D(setS->D2Array + i, Quad[i], 6);
    setS->D2Array[i].length = 6;
    setS->width = 4;
    setS->maxSize = 6;
}

/**
 * @brief Initialize (set2D) Set P based on MP Specs  
 * @param *setP: A set2D struct you will assign as P

 * ==
 * :=
 */
void 
initializeP(struct set2D *setP){
    int i;
    coord Duo[2][2] = {
        {{1, 1}, {2, 2}}, 
        {{1, 2}, {2, 1}}
    };

    for (i = 0; i < 2; i++){
        set1DCopyFromCoord1D(setP->D2Array + i, Duo[i], 2);
        setP->D2Array[i].length = 2;
    }
    setP->width = 2;
    setP->maxSize = 2;
}

void 
initializeF(struct set1D *setF){
    int i, j;
    int countF = 0;

    for (i = 1; i < 7; i++) {
        for (j = 1; j < 7; j++) {
            setF->D1Array[countF][0] = i;
            setF->D1Array[countF][1] = j;
            countF++;
        } 
    }
    setF->length = 36;
    setF->maxSize = 36;
}

void 
initializeC(struct set1D *setC){
    int i, j;
    int countC = 0;

    for (i = 1; i < 3; i++) {
        for (j = 1; j < 3; j++) {
            setC->D1Array[countC][0] = i;
            setC->D1Array[countC][1] = j;
            countC++;
        } 
    }
    setC->length = 4;
    setC->maxSize = 4;
}

void 
printGrid(struct set1D points){
    coord current;
    int isFound = false;
    int i = 0, j = 0, k = 0;

    for (i = 6; i >= 1; i--){
        printf("*---*---*---*---*---*---*\n");

        current[1] = i;
        for (j = 1; j <= 6; j++){
            current[0] = j;
            isFound = false;
            for(k = 0; k < points.length && !isFound; k++){
                if (coordEqual(current, points.D1Array[k])){
                    printf("| # ");
                    isFound = true;
                }
            }
            if (!isFound)
                printf("|   ");
        }
        printf("|\n");
    }
    printf("*---*---*---*---*---*---*\n");
}

void
printPlayerBoard(struct set1D *F1, struct set1D *F2, int size){
	coord current;
    HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsoleOutput, FG_WHITE);
    int isFoundF1 = false, isFoundF2 = false;
    int i = 0, j = 0, k = 0;
    printf("Y: \n");
    for (i = size; i >= 1; i--){
        printf("  *");
        for(j = 1; j <= size; j++){
            printf("---*");
        }
        printf("\n");

        current[1] = i;
        printf("%d ", i);
        for (j = 1; j <= size; j++){
            current[0] = j;
            isFoundF1 = false;
            isFoundF2 = false;

            for(k = 0; k < F1->length && !isFoundF1; k++){
                if (coordEqual(current, F1->D1Array[k])){
                    isFoundF1 = true;
                }
            }

            for(k = 0; k < F2-> length && !isFoundF2; k++){
                if (coordEqual(current, F2->D1Array[k])){
                    isFoundF2 = true;
                }
            }

            printf("|");
            if (isFoundF1 && isFoundF2) {
                SetConsoleTextAttribute(hConsoleOutput, FG_PURP);
                printf(" # ");
            } else if (isFoundF1) {
                SetConsoleTextAttribute(hConsoleOutput, FG_RED);
                printf(" O "); 
            } else if (isFoundF2) {
                SetConsoleTextAttribute(hConsoleOutput, FG_BLUE);
                printf(" X ");
            } else
                printf("   ");

            SetConsoleTextAttribute(hConsoleOutput, FG_WHITE);
        }
        printf("|\n");
    }
    printf("  *");
    for(j = 1; j <= size; j++){
        printf("---*");
    }
    printf("\n  ");
    for(j = 1; j <= size; j++){
        printf("   %d", j);
    }
    printf("  :X\n");
}

void 
RepeatGetCoord(coord pos){
    coord Temp;
    int typeReturnedX, typeReturnedY, typeReturnedC;
    char endingChar; 
    char choiceChar;
    bool isXInvalid = true; 
    bool isYInvalid = true;
    bool isNotVerified = true;
    bool isChoiceInvalid = true;

    while (isNotVerified){
        isXInvalid = true;
        isYInvalid = true;
        isChoiceInvalid = true;
        while (isXInvalid){
            printf("Print X: ");
            typeReturnedX = scanf("%d%c", Temp, &endingChar);
            if (typeReturnedX != 2) {    
                printf("Invalid X position.\n");
            } 

            if (endingChar != '\n')
                while(getchar() != '\n');

            if (typeReturnedX == 2 && endingChar == '\n')
                isXInvalid = false;
        }

        while (isYInvalid){
            printf("Print Y: ");
            typeReturnedY = scanf("%d%c", Temp + 1, &endingChar);
            if (typeReturnedY != 2 || Temp[1] > 7 || Temp[1] < 1) {    
                printf("Invalid Y position.\n");
            } 
            if (endingChar != '\n')
                while(getchar() != '\n');
            if (typeReturnedY == 2 && endingChar == '\n' && !(Temp[1] > 7 || Temp[1] < 1))
                isYInvalid = false;
        }

        while (isChoiceInvalid){
            printf("Confirm (%d, %d)? [Y/N]: ", *Temp, *(Temp+1));
            typeReturnedC = scanf("%c%c", &choiceChar, &endingChar);
            if (typeReturnedC != 2) {    
                printf("Invalid choice.\n");
            } 

            if (endingChar != '\n')
                while(getchar() != '\n');
            
            switch (choiceChar){
                case 'y':
                case 'Y':
                    isChoiceInvalid = false;
                    isNotVerified = false;
                    *pos = Temp[0];
                    *(pos + 1) = Temp[1];
                    return;
                    break;
                case 'n':
                case 'N':
                    isChoiceInvalid = false;
                    break;
                default:
                    printf("Invalid Choice!");
            }
        }
    }

    
}

void
updateF3(struct set1D *F, struct set1D *F1, struct set1D *F2, struct set1D *F3){
    struct set1D F1UnionF2;
    set1DUnion(F1, F2, &F1UnionF2);
    set1DDiff(F, &F1UnionF2, F3);
}

void
updateOver(struct set1D *F3, struct set1D *C1, struct set1D *C2, bool *over, struct set2D *P){
    struct set2D pSetC1, pSetC2;
    powerSet1D(C1, &pSetC1);
    powerSet1D(C2, &pSetC2);
    *over = (F3->length == 0) ||
            thereExistCondition1(&pSetC1, P) ||
            thereExistCondition1(&pSetC2, P);
}



void 
NextPlayerMove(coord pos, 
    struct set1D *F, struct set1D *F1, struct set1D *F2, struct set1D *F3, 
    bool over, bool *good, bool next, 
    struct set2D *setS, struct set1D *C1, struct set1D *C2, 
    int iteration){
    int a, b, c, d, loc;   
    struct set1D set1DAandB, set1DCandD, temp;
    struct set2D powerSetF1, powerSetF2, pF1IntersectS, pF2IntersectS;
    
    set1DClear(&set1DAandB);
    set1DClear(&set1DCandD);
    set1DClear(&temp);
    set2DClear(&pF1IntersectS);
    set2DClear(&pF2IntersectS);
    set2DClear(&powerSetF1);
    set2DClear(&powerSetF2);


    a = pos[0];
    b = pos[1];
    c = (a - 1) / 3 + 1;
    d = (b - 1) / 3 + 1;

    coordCopy(set1DAandB.D1Array[0], pos);
    set1DAandB.length = 1;

    set1DCandD.D1Array[0][0] = c;
    set1DCandD.D1Array[0][1] = d;
    set1DCandD.length = 1;

    printf("Sysinfo Turn %02d:\n", iteration);
    printf("\t(a, b): ");
    coordPrint(set1DAandB.D1Array[0]);
    printf("\n\t(c, d): (%d, %d)\n", c, d);
    printf("\tO = %d; G = %d; N = %d\n", over, *good, next);
    printf("\n(!over & next & pos in F3):\n");
    printf("   %d   &   %d   &    %d\n", !over, next, set1DSearch0Dkey(pos, F3, &loc));
    if(!over && next && set1DSearch0Dkey(pos, F3, &loc)){
        printf("\t=> Good = !Good\n");
        *good = !*good;
        set1DUnion(F1, &set1DAandB, &temp);
        //printf("New F1: %d\n", temp.length);
        //set1DPrint(&temp);
        printf("\t=> F1 = F1 U {pos}\n");
        *F1 = temp;
        updateF3(F, F1, F2, F3);
        //printf("B2 1\n");
    }
    printf("\n!over & !next & pos in F3:\n");
    printf("   %d   &   %d   &    %d\n", !over, !next, set1DSearch0Dkey(pos, F3, &loc));
    if(!over && !next && set1DSearch0Dkey(pos, F3, &loc)){

        printf("\t=> Good = !Good\n");
        *good = !*good;

        set1DUnion(F2, &set1DAandB, &temp);
        //set1DPrint(&temp); 
        //printf("New F2: %d\n", temp.length);
        printf("\t=> F2 = F2 U {pos}\n");
        *F2 = temp;
        updateF3(F, F1, F2, F3);
        //set1DPrint(F1);
        //printf("B2 2\n");
    }   
    //printf("F1 F2 size: %d %d\n", F1->length, F2->length);
    powerSet1D(F1, &powerSetF1);
    powerSet1D(F2, &powerSetF2);

    //printf("powerSetF1: \n");
    //set2DPrint(&powerSetF1);
    //printf("powerSetF2: \n");
    //set2DPrint(&powerSetF2);

    set2DIntersect(setS, &powerSetF1, &pF1IntersectS);
    set2DIntersect(setS, &powerSetF2, &pF2IntersectS);
    // printf("pF1IntersectS: \n");   
    // set2DPrint(&pF1IntersectS);
    // printf("pF2IntersectS: \n");
    // set2DPrint(&pF2IntersectS);
    printf("\n!O & G & N & |P(F1) n S| > |C1|:\n");
    printf(" %d & %d & %d & |%d| > |%d| :\n", !over, *good, next, set2DTotalSize(&pF1IntersectS), C1->length);
    if(!over && *good && next && set2DTotalSize(&pF1IntersectS) > C1->length){
        
        set1DClear(&temp);
        set1DUnion(C1, &set1DCandD, &temp);
        //set1DPrint(&temp);
        printf("\tC1 = C1 u {(c, d)}\n");
        *C1 = temp;
        //printf("B3\n");
    }
    
    printf("\n!O & G & !N & |P(F2) n S| > |C2|:\n");
    printf(" %d & %d & %d & |%d| > |%d| :\n", !over, *good, !next, set2DTotalSize(&pF2IntersectS), C2->length);
    if(!over && *good && !next && set2DTotalSize(&pF2IntersectS) > C2->length){
        set1DClear(&temp);
        set1DUnion(C2, &set1DCandD, &temp);
        //set1DPrint(&temp);
        printf("\tC1 = C1 u {(c, d)}\n");
        *C2 = temp;
        //printf("B4\n");
    }
    
    if(!over && *good)
        *good = !*good;
}

void 
GameOver(bool *over, bool *next, struct set1D *C1, struct set1D *C2, struct set2D *setP){
    String15 result = "";
    struct set2D pSetC1, pSetC2;
    powerSet1D(C1, &pSetC1);
    powerSet1D(C2, &pSetC2);

    if (*over && *next && thereExistCondition1(&pSetC1, setP))
        strcpy(result, "A wins.\n");

    if (*over && !*next && thereExistCondition1(&pSetC2, setP))
        strcpy(result, "B wins.\n");

    printf("%s", result);
    
    if (*over && thereExistCondition1(&pSetC2, setP))
        getchar();

    if (!*over) 
        *next = !(*next);
}

void 
NextPlayerMove1(coord pos, 
    struct set1D *F, struct set1D *F1, struct set1D *F2, struct set1D *F3, 
    bool over, bool *good, bool next, 
    struct set2D *setS, struct set1D *C1, struct set1D *C2, 
    int iteration){
    int a, b, c, d, loc;   
    struct set1D set1DAandB, set1DCandD, temp;

    
    set1DClear(&set1DAandB);
    set1DClear(&set1DCandD);
    set1DClear(&temp);


    a = pos[0];
    b = pos[1];
    c = (a - 1) / 3 + 1;
    d = (b - 1) / 3 + 1;

    coordCopy(set1DAandB.D1Array[0], pos);
    set1DAandB.length = 1;

    set1DCandD.D1Array[0][0] = c;
    set1DCandD.D1Array[0][1] = d;
    set1DCandD.length = 1;

    printf("Sysinfo Turn %02d:\n", iteration);
    printf("\t(a, b): ");
    coordPrint(set1DAandB.D1Array[0]);
    printf("\n\t(c, d): (%d, %d)\n", c, d);
    printf("\tO = %d; G = %d; N = %d\n", over, *good, next);
    printf("\n(!over & next & pos in F3):\n");
    printf("   %d   &   %d   &    %d\n", !over, next, set1DSearch0Dkey(pos, F3, &loc));
    printf("Before:");
    printPlayerBoard(F1, F2, 6);
    if(set1DSearch0Dkey(pos, F3, &loc) && !over && next){
        printf("\t=> Good = !Good\n");
        *good = !*good;
        set1DUnion(F1, &set1DAandB, &temp);
        //printf("New F1: %d\n", temp.length);
        //set1DPrint(&temp);
        printf("\t=> F1 = F1 U {pos}\n");
        *F1 = temp;
        updateF3(F, F1, F2, F3);
        //printf("B2 1\n");
    }
    printf("\n!over & !next & pos in F3:\n");
    printf("   %d   &   %d   &    %d\n", !over, !next, set1DSearch0Dkey(pos, F3, &loc));

    if(set1DSearch0Dkey(pos, F3, &loc) && !over && !next){

        printf("\t=> Good = !Good\n");
        *good = !*good;

        set1DUnion(F2, &set1DAandB, &temp);

        printf("\t=> F2 = F2 U {pos}\n");
        *F2 = temp;
        updateF3(F, F1, F2, F3);

    }
    printf("After:"); 
    printPlayerBoard(F1, F2, 6);
    printf("\n!O & G & N & |P(F1) n S| > |C1|:\n");
    printf(" %d & %d & %d & |%d| > |%d| :\n", !over, *good, next, patternF1inS(F1, setS), C1->length);
    if(patternF1inS(F1, setS) > C1->length && !over && *good && next){
        
        set1DClear(&temp);
        set1DUnion(C1, &set1DCandD, &temp);
        //set1DPrint(&temp);
        printf("\tC1 = C1 u {(c, d)}\n");
        *C1 = temp;
        //printf("B3\n");
    }
    
    printf("\n!O & G & !N & |P(F2) n S| > |C2|:\n");
    printf(" %d & %d & %d & |%d| > |%d| :\n", !over, *good, !next, patternF1inS(F2, setS), C2->length);
    if(patternF1inS(F2, setS) > C2->length && !over && *good && !next){
        set1DClear(&temp);
        set1DUnion(C2, &set1DCandD, &temp);
        //set1DPrint(&temp);
        printf("\tC1 = C1 u {(c, d)}\n");
        *C2 = temp;
        //printf("B4\n");
    }
    
    if(!over && *good)
        *good = !*good;
}

void 
GameOver2(bool *over, bool *next, struct set1D *C1, struct set1D *C2, struct set2D *setP){
    String15 result = "";
    int choice;
    if (*over && *next && setKencompassesSetP(C1, setP))
        strcpy(result, "A wins.\n");

    if (*over && !*next && setKencompassesSetP(C2, setP))
        strcpy(result, "B wins.\n");

    printf("%s", result);
    
    if (*over && (setKencompassesSetP(C1, setP) || setKencompassesSetP(C2, setP)))
        scanf("%d", &choice);

    if (!*over) 
        *next = !(*next);
}
