#include "print.h"
#include <stdio.h>
#include <avr/delay.h>

#define SIZE5X 46
#define SIZE4X 36
#define SIZE3X 26
#define SIZE2X 16
#define SIZE5Y 8
#define BOARDSIZE 10

extern char playerboard[BOARDSIZE][BOARDSIZE], enemyboard[BOARDSIZE][BOARDSIZE], playerattack_x[BOARDSIZE * BOARDSIZE], enemyattack_x[BOARDSIZE * BOARDSIZE],playerattack_y[BOARDSIZE * BOARDSIZE], enemyattack_y[BOARDSIZE * BOARDSIZE];
extern int player_turn, enemy_turn;
void PrintBoard(int size){
	int i;

	for(i=0;i <=size;i++) {
        GLCD_Line(64,127-11*i,174,127-11*i);
        GLCD_Line(64+11*i,127,64+11*i,17);
  	}
}

void GLCD_select(unsigned char x, unsigned char y) {
    int j,i;

    for(j=0;j<8;j++)
        for(i=0;i<8;i++)
            GLCD_SetPixel(11*x+66+j, 11*y+19+i, 1);

}

void GLCD_dselect(unsigned char x,unsigned char y) {
    int j,i;
    for(j=0;j<8;j++)
        for(i=0;i<8;i++)
            GLCD_SetPixel(11*x+66+j, 11*y+19+i, 0);
 
}

void DrawSquare(int x, int y) {
	int i,j;

	for(i=0;i<=11;i++)
		for(j=0;j<=11;j++) {
			if(i == 0 || i == 11) 		GLCD_SetPixel(11*x+64+i, 11*y+17+j, 1);
			else if(j==0 || j == 11)	GLCD_SetPixel(11*x+64+i, 11*y+17+j, 1);
			else 	GLCD_SetPixel(11*x+64+i, 11*y+17+j, 0);
		}
			
}

void PrintToggle(int x, int y,int delay) {
		GLCD_select(x,y);
		_delay_ms(delay);
		GLCD_dselect(x,y);
		_delay_ms(delay);	
}

void PrintShip5(char arr[][SIZE5Y], int x, int y, int rotate) {
	int i,j;

	switch(rotate){
		case 1:
			for(i=0;i<SIZE5X;i++)
				for(j=0;j<SIZE5Y;j++)
					if(arr[i][j] == 1)
						GLCD_SetPixel(11*x+66+i, 11*y+19+j, 1);
					else
						GLCD_SetPixel(11*x+66+i, 11*y+19+j, 0);
			break;
		case 2:
			for(i=0;i<SIZE5X;i++)
				for(j=0;j<SIZE5Y;j++)
					if(arr[i][SIZE5Y - 1 -j] == 1)
						GLCD_SetPixel(11*x+66+j, 11*y+19+i, 1);
					else
						GLCD_SetPixel(11*x+66+j, 11*y+19+i, 0);
			break;
		case 3:
			for(i=0;i<SIZE5X;i++)
				for(j=0;j<SIZE5Y;j++)
					if(arr[SIZE5X - i -1][SIZE5Y - j -1] == 1)
						GLCD_SetPixel(11*(x-4)+66+i, 11*(y)+19+j, 1);
					else
						GLCD_SetPixel(11*(x-4)+66+i, 11*(y)+19+j, 0);
			break;
		case 4:
			for(i=0;i<SIZE5X;i++)
				for(j=0;j<SIZE5Y;j++)
					if(arr[SIZE5X - i -1][j] == 1)
						GLCD_SetPixel(11*x+66+j, 11*(y-4)+19+i, 1);
					else
						GLCD_SetPixel(11*x+66+j, 11*(y-4)+19+i, 0);
			break;
	}
}

void PrintShipClear(int x, int y, int size, int rotate) {
	int i;
	switch(rotate){
		case 1:
			for(i=0;i<size;i++)
				DrawSquare(x + i,y);
			break;
		case 2:
			for(i=0;i<size;i++)
				DrawSquare(x,y + i);
			break;
		case 3:
			for(i=0;i<size;i++)
				DrawSquare(x - i,y);
			break;
		case 4:
			for(i=0;i<size;i++)
				DrawSquare(x,y - i);
			break;
	}
}

void PrintMode(int select_mode){
	GLCD_TextGoTo(9,4);
	GLCD_WriteString("Select Mode");
	
	GLCD_TextGoTo(7,7);
	GLCD_WriteString("1. Single Play");
	GLCD_TextGoTo(7,9);
	GLCD_WriteString("2. Multi Play");

	if(select_mode == 1){
			_delay_ms(500);
			GLCD_TextGoTo(7,7);
			GLCD_WriteString("                 ");
			_delay_ms(500);
	}
	else if(select_mode == 2) {
			_delay_ms(500);	
			GLCD_TextGoTo(7,9);
			GLCD_WriteString("                 ");
			_delay_ms(500);
	}
}

void PrintSelectBoard(int x, int y, int switch_direction){

	PrintBoard(10);
/*switch(switch_direction){
	case LEFT:
		GLCD_dselect(x,y);
		y--;
			if(x<0)
				x=9;
		GLCD_select(x,y);
		switch_direction=0;
		break;
	case UP:
		GLCD_dselect(x,y);
		y--;
			if(y<0)
				y=9;
		GLCD_select(x,y);
		switch_direction=0;
		break;
	case RIGHT:
		GLCD_dselect(x,y);
		x++;
			if(x>9)
				x=0;
		GLCD_select(x,y);
		switch_direction=0;
		break;
	case DOWN:
		GLCD_dselect(x,y);
		x++;
			if(x<0)
				x=9;
		GLCD_select(x,y);
		switch_direction=0;
		break;
	}
	*/
}

void PrintDifficulty(int select_mode){
	GLCD_TextGoTo(6,4);
	GLCD_WriteString("Select Difficulty");
	
	GLCD_TextGoTo(7,7);
	GLCD_WriteString("1. Easy Mode");
	GLCD_TextGoTo(7,9);
	GLCD_WriteString("2. Hard Mode");

	if(select_mode == 1){
			_delay_ms(500);
			GLCD_TextGoTo(7,7);
			GLCD_WriteString("                 ");
			_delay_ms(500);
	}
	else if(select_mode == 2) {
			_delay_ms(500);	
			GLCD_TextGoTo(7,9);
			GLCD_WriteString("                 ");
			_delay_ms(500);
	}
}

void PrintSelectShip5(char arr[][SIZE5Y],int x, int y, int rotate) {
	PrintShip5(arr, x, y, rotate);
	_delay_ms(500);
	PrintShipClear(x,y,5,rotate);
	_delay_ms(500);
}

void PrintSelectShip4(char arr[][SIZE5Y],int x, int y, int rotate) {
	PrintShip4(arr, x, y, rotate);
	_delay_ms(500);
	PrintShipClear(x,y,4,rotate);
	_delay_ms(500);
}

void PrintSelectShip3(char arr[][SIZE5Y],int x, int y, int rotate) {
	PrintShip3(arr, x, y, rotate);
	_delay_ms(500);
	PrintShipClear(x,y,3,rotate);
	_delay_ms(500);
}

void PrintSelectShip2(char arr[][SIZE5Y],int x, int y, int rotate) {
	PrintShip2(arr, x, y, rotate);
	_delay_ms(500);
	PrintShipClear(x,y,2,rotate);
	_delay_ms(500);
}

void PrintShip4(char arr[][SIZE5Y], int x, int y, int rotate) {
	int i,j;

	switch(rotate){
		case 1:
			for(i=0;i<SIZE4X;i++)
				for(j=0;j<SIZE5Y;j++)
					if(arr[i][j] == 1)
						GLCD_SetPixel(11*x+66+i, 11*y+19+j, 1);
					else
						GLCD_SetPixel(11*x+66+i, 11*y+19+j, 0);
			break;
		case 2:
			for(i=0;i<SIZE4X;i++)
				for(j=0;j<SIZE5Y;j++)
					if(arr[i][SIZE5Y - 1 -j] == 1)
						GLCD_SetPixel(11*x+66+j, 11*y+19+i, 1);
					else
						GLCD_SetPixel(11*x+66+j, 11*y+19+i, 0);
			break;
		case 3:
			for(i=0;i<SIZE4X;i++)
				for(j=0;j<SIZE5Y;j++)
					if(arr[SIZE4X - i -1][SIZE5Y - j -1] == 1)

						GLCD_SetPixel(11*(x-3)+66+i, 11*(y)+19+j, 1);
					else
						GLCD_SetPixel(11*(x-3)+66+i, 11*(y)+19+j, 0);
			break;
		case 4:
			for(i=0;i<SIZE4X;i++)
				for(j=0;j<SIZE5Y;j++)
					if(arr[SIZE4X - i -1][j] == 1)
						GLCD_SetPixel(11*x+66+j, 11*(y-3)+19+i, 1);
					else
						GLCD_SetPixel(11*x+66+j, 11*(y-3)+19+i, 0);
			break;
	}
}


void PrintShip3(char arr[][SIZE5Y], int x, int y, int rotate) {
	int i,j;

	switch(rotate){
		case 1:
			for(i=0;i<SIZE3X;i++)
				for(j=0;j<SIZE5Y;j++)
					if(arr[i][j] == 1)
						GLCD_SetPixel(11*x+66+i, 11*y+19+j, 1);
					else
						GLCD_SetPixel(11*x+66+i, 11*y+19+j, 0);
			break;
		case 2:
			for(i=0;i<SIZE3X;i++)
				for(j=0;j<SIZE5Y;j++)
					if(arr[i][SIZE5Y - 1 -j] == 1)
						GLCD_SetPixel(11*x+66+j, 11*y+19+i, 1);
					else
						GLCD_SetPixel(11*x+66+j, 11*y+19+i, 0);
			break;
		case 3:
			for(i=0;i<SIZE3X;i++)
				for(j=0;j<SIZE5Y;j++)
					if(arr[SIZE3X - i -1][SIZE5Y - j -1] == 1)
						GLCD_SetPixel(11*(x-2)+66+i, 11*(y)+19+j, 1);
					else
						GLCD_SetPixel(11*(x-2)+66+i, 11*(y)+19+j, 0);
			break;
		case 4:
			for(i=0;i<SIZE3X;i++)
				for(j=0;j<SIZE5Y;j++)
					if(arr[SIZE3X - i -1][j] == 1)
						GLCD_SetPixel(11*x+66+j, 11*(y-2)+19+i, 1);
					else
						GLCD_SetPixel(11*x+66+j, 11*(y-2)+19+i, 0);
			break;
	}
}


void PrintShip2(char arr[][SIZE5Y], int x, int y, int rotate) {
	int i,j;

	switch(rotate){
		case 1:
			for(i=0;i<SIZE2X;i++)
				for(j=0;j<SIZE5Y;j++)
					if(arr[i][j] == 1)
						GLCD_SetPixel(11*x+66+i, 11*y+19+j, 1);
					else
						GLCD_SetPixel(11*x+66+i, 11*y+19+j, 0);
			break;
		case 2:
			for(i=0;i<SIZE2X;i++)
				for(j=0;j<SIZE5Y;j++)
					if(arr[i][SIZE5Y - 1 -j] == 1)
						GLCD_SetPixel(11*x+66+j, 11*y+19+i, 1);
					else
						GLCD_SetPixel(11*x+66+j, 11*y+19+i, 0);
			break;
		case 3:
			for(i=0;i<SIZE2X;i++)
				for(j=0;j<SIZE5Y;j++)
					if(arr[SIZE2X - i -1][SIZE5Y - j -1] == 1)
						GLCD_SetPixel(11*(x-1)+66+i, 11*(y)+19+j, 1);
					else
						GLCD_SetPixel(11*(x-1)+66+i, 11*(y)+19+j, 0);
			break;
		case 4:
			for(i=0;i<SIZE2X;i++)
				for(j=0;j<SIZE5Y;j++)
					if(arr[SIZE2X - i -1][j] == 1)
						GLCD_SetPixel(11*x+66+j, 11*(y-1)+19+i, 1);
					else
						GLCD_SetPixel(11*x+66+j, 11*(y-1)+19+i, 0);
			break;
	}
}

void PrintRSP(int select_mode){
	GLCD_TextGoTo(5,4);
	GLCD_WriteString("Rock, Scissor, Paper!");
	
	GLCD_TextGoTo(13,7);
	GLCD_WriteString("Rock");
	GLCD_TextGoTo(11,9);
	GLCD_WriteString("Scissor");
	GLCD_TextGoTo(12,11);
	GLCD_WriteString("Paper");

	if(select_mode == 1){
			_delay_ms(500);
			GLCD_TextGoTo(13,7);
			GLCD_WriteString("       ");
			_delay_ms(500);
	}
	else if(select_mode == 2) {
			_delay_ms(500);	
			GLCD_TextGoTo(11,9);
			GLCD_WriteString("        ");
			_delay_ms(500);
	}
	else if(select_mode == 3) {
			_delay_ms(500);	
			GLCD_TextGoTo(12,11);
			GLCD_WriteString("        ");
			_delay_ms(500);
	}
}

void PrintEnemyBoard(void) {
	int i;
	PrintBoard(10);
	
	for(i=0;i<player_turn;i++) {
		if(enemyboard[playerattack_y[i]][playerattack_x[i]] != 0)
			GLCD_select(playerattack_x[i], playerattack_y[i]);
		else
			PrintX(playerattack_x[i], playerattack_y[i]);
		}
}

void PrintX(char x, char y)
{
	for(int i=0; i<8; i++)
		GLCD_SetPixel(11*x+66+i, 11*y+19+i, 1);
	for(int j=0; j<8; j++)
		GLCD_SetPixel(11*x+73-j, 11*y+19+j, 1);
	
}

void PrintEnemyAttack(void) {
	int i;
		
				for(i = 0; i<enemy_turn; i++) {
					if( playerboard[enemyattack_y[i]][enemyattack_x[i]] != '0')
							GLCD_select(enemyattack_x[i], enemyattack_y[i]);
					else 	PrintX(enemyattack_x[i],enemyattack_y[i]);
				}
			
		}


void PrintWaitingEnemy(void) {
		GLCD_TextGoTo(5,4);
		GLCD_WriteString("Waiting For Enemy!");
		_delay_ms(400);
		GLCD_TextGoTo(5,4);
		GLCD_WriteString("                   ");
		_delay_ms(400);
}
