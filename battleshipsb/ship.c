#include "ship.h"

#define SIZE5Y 8

void MakeShip5(char arr[][SIZE5Y])
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

void MakeShip4(char arr[][SIZE5Y]) {
	int i, j;

	for(i=7;i<=19;i++)
		arr[i][0] = 1;
	arr[31][0] = 1;
	arr[32][0] = 1;

	arr[6][1] = 1;
	arr[20][1] = 1;
	arr[24][1] = 1;
	arr[25][1] = 1;
	arr[27][1] = 1;
	arr[28][1] = 1;
	arr[29][1] = 1;
	arr[31][1] = 1;
	arr[32][1] = 1;

	arr[5][2] = 1;
	arr[21][2] = 1;
	arr[24][2] = 1;
	arr[25][2] = 1;
	arr[27][2] = 1;
	arr[28][2] = 1;
	arr[29][2] = 1;
	arr[31][2] = 1;
	arr[32][2] = 1;

	for(i=0;i<=35;i++)
		arr[i][3] = 1;
	arr[0][4] = 1;
	arr[35][4] = 1;

	arr[1][5] = 1;
	arr[34][5] = 1;

	for(i=2;i<=33;i++)
		arr[i][6] = 1;

	for(i=2;i<=33;i++)
		arr[i][7] = 1;
}

void MakeShip3(char arr[][SIZE5Y]) {
	int i;
	
	for(i=4;i<=14;i++)
		arr[i][0] = 1;
	arr[4][1] = 1;
	arr[15][1] = 1;
	arr[19][1] = 1;
	arr[20][1] = 1;

	arr[4][2] = 1;
	arr[16][2] = 1;
	arr[19][2] = 1;
	arr[20][2] = 1;
	
	for(i=0;i<=25;i++)
		arr[i][3] = 1;
	arr[0][3] = 1;
	arr[25][4] = 1;
	arr[1][5] = 1;
	arr[24][5] = 1;

	for(i=2 ; i<=23;i++)
		arr[i][6] = 1;
	for(i=2 ; i<=23;i++)
		arr[i][7] = 1;
}

void MakeShip2(char arr[][SIZE5Y]) {
	int i, j;

	for(i=5;i<=12;i++)
		arr[i][0] = 1;
	arr[0][1] = 1;
	for(i=4;i<=12;i++)
		arr[i][1] = 1;
	arr[0][2] = 1;
	arr[1][2] = 1;
	arr[3][2] = 1;
	arr[14][2] = 1;

	arr[0][3] = 1;
	arr[2][3] = 1;
	arr[5][3] = 1;
	arr[6][3] = 1;
	arr[8][3] = 1;
	arr[9][3] = 1;
	arr[11][3] = 1;
	arr[12][3] = 1;
	arr[15][3] = 1;

	arr[0][4] = 1;
	arr[5][4] = 1;
	arr[6][4] = 1;
	arr[8][4] = 1;
	arr[9][4] = 1;
	arr[11][4] = 1;
	arr[12][4] = 1;
	arr[15][4] = 1;

	arr[0][5] = 1;
	arr[2][5] = 1;
	arr[15][5] = 1;

	arr[0][6] = 1;
	arr[1][6] = 1;

	for(i=3;i<=14;i++)
		arr[i][6] = 1;
	
	arr[0][7] = 1;
	for(i=4;i<=13;i++)
		arr[i][7] = 1;


}
