#include<stdio.h>
#include<stdlib.h>

#define CAP 15

void
printCoord(char coordinates[][CAP]){
    int i;
    for(i = 0; i < CAP * CAP;i++){
        printf("%c", coordinates[i/CAP][i%CAP]);
        (i % CAP == CAP - 1) ? printf("\n") : printf(" ");
    }
}

void
initialize(char coordinates[][CAP], int middle){
    int i;
    for(i = 0; i < CAP * CAP;i++){
        if (i/CAP - middle == 0)
            coordinates[i/CAP][i%CAP] = '-';
        else if (i % CAP - middle == 0)
            coordinates[i/CAP][i%CAP] = '|';
        else if (i / CAP - middle == 0 && middle - (i % CAP) == 0)
            coordinates[i/CAP][i%CAP] = '+';
        else
            coordinates[i/CAP][i%CAP] = '.';
    }
}

int
eucledeanAlgo(int a, int m){
    int d = a / m;
    int r = a - d * m;

    if (r < 0)
        d -= 1;
    r = a - d * m;
    return r;
}

int
congruenceMod(int a, int b, int m){

    return (eucledeanAlgo(a, m) == eucledeanAlgo(b, m));
};

int main(){
    
    char coordinates[CAP][CAP];
    int m = 5;
    int middle = CAP / 2;
    int i;
    initialize(coordinates, middle);
    printCoord(coordinates);
    
    while (1){
        printf("\nEnter num: ");
        scanf(" %d", &m);
        printf("\n");
        for(i = 0; i<= CAP*CAP; i++){
            if (congruenceMod(middle - i / CAP, i % CAP - middle, m))
                coordinates[i / CAP][ i % CAP] = 'X';
            else if (middle - i / CAP == 0) 
                coordinates[i / CAP][ i % CAP] = '-';
            else if (i%CAP - middle == 0)
                coordinates[i/CAP][i%CAP] = '|';
            else if (middle - i / CAP == 0 && i % CAP - middle == 0)
                coordinates[i/CAP][i%CAP] = '+';
            else
                coordinates[i/CAP][i%CAP] = '.';

        }
        printf("\n");
        printCoord(coordinates);
    }

    return 0;
}