	
#include "funcsSystem.h"

int main()
{
    struct set1D F, F1, F2, F3, C, C1, C2;
    struct set2D setS, setP;
	
    int i = 0;
    int a, b;
	
    set1DClear(&F);
    set1DClear(&F1);
    set1DClear(&F2);
    set1DClear(&F3);
    set1DClear(&C);
    set1DClear(&C1);
    set1DClear(&C2);
    initializeF(&F);
    initializeC(&C);
    initializeS(&setS);
    initializeP(&setP);
    updateF3(&F, &F1, &F2, &F3);
    // System Variables
	
    bool good = false;
    bool next = false;	
    bool over = false;
    coord input = {1, 1};
	
    do
	{
		printf("Welcome To The MP Project\n");
		printf("    [0]: Play the game\n");
		printf("    [1]: Exit program\n");
		printf("Input: ");
		scanf("%d", &a);
		
		if (a == 1) 
		{
			printf("Game Ended.\n");
		} 
		
		else if (a == 0) 
		{
			while (!over) 
			{
	                RepeatGetCoord2(&F1, &F2, &F3, &C1, &C2, input, &next);
	                updateOver(&F3, &C1, &C2, &over, &setP);
	                NextPlayerMove1(input, &F, &F1, &F2, &F3, over, &good, next, &setS, &C1, &C2, i);
	                updateOver(&F3, &C1, &C2, &over, &setP);
	                GameOver2(&over, &next, &C1, &C2, &setP, &F1, &F2, &F3, input);
	                i++;
	          	}
			
		} else
			{
			printf("Invalid Number. Please Enter 0 or 1");
			}
	}
	while (b == 0);

    return 0;
}
