#include "print.h"
#include <avr/delay.h>

#define SIZE5X 46
#define SIZE5Y 8
#define LEFT 1
#define UP 2
#define RIGHT 3
#define DOWN 4

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

void PrintShip5(int arr[][SIZE5Y], int x, int y, int rotate) {
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

void PrintMode(void){
	GLCD_TextGoTo(9,4);
	GLCD_WriteString("Select Mode");
	
	GLCD_TextGoTo(7,7);
	GLCD_WriteString("1. Single Play");
	GLCD_TextGoTo(7,9);
	GLCD_WriteString("2. Multi Play");
}

void PrintSelectBoard(int x, int y, int switch_direction){

	PrintBoard(10);
switch(switch_direction){
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
}
