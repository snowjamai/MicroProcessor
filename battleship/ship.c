#include "ship.h"

#define SIZE5Y 8

void MakeShip5(int arr[][SIZE5Y])
{
    int i, j;

    for(i=10;i<20;i++)
		arr[i][0]=1;
	for(i=23;i<26;i++)
		arr[i][0]=1;
	arr[9][1]=1;
	arr[20][1]=1;
	arr[23][1]=1;
	arr[25][1]=1;
	arr[28][1]=1;
	arr[29][1]=1;
	arr[32][1]=1;
	arr[33][1]=1;
	arr[36][1]=1;
	arr[37][1]=1;
	arr[40][1]=1;
	arr[41][1]=1;
		
	arr[8][2] = 1;
	arr[21][2] = 1;
	arr[23][2] = 1;
	arr[25][2] = 1;
	arr[28][2] = 1;
	arr[29][2] = 1;
	arr[32][2] = 1;
	arr[33][2] = 1;
	arr[36][2] = 1;
	arr[37][2] = 1;
	arr[40][2] = 1;
	arr[41][2] = 1;

	for(i=0;i<46;i++)
		arr[i][3]=1;
	
	arr[1][4]=1;
	arr[44][4]=1;
	
	arr[2][5]=1;
	arr[43][5]=1;


	for(i=3;i<43;i++)
		arr[i][6]=1;
	for(i=3;i<43;i++)
		arr[i][7]=1;

}
