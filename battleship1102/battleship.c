#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
#include <time.h>
#include "t6963c.h"
#include "graphic.h"
#include "print.h"
#include "ship.h"

#define BOARDSIZE 10
#define SIZE5X 46
#define SIZE4X 36
#define SIZE3X 26
#define SIZE2X 16
#define SIZE5Y 8
#define LEFT 1
#define UP 2
#define RIGHT 3
#define DOWN 4

char playerboard[BOARDSIZE][BOARDSIZE] = {0};
volatile int x = 0, y = 0, cnt = 0, state = 0, select = 1, rotate = 1, ship_size = 0, size5 = 0, size4 = 0, size3 = 0, size2 = 0;
volatile int cnt1 = 0, cnt2 = 0, cnt3= 0, cnt4 = 0;
volatile int ship5[SIZE5X][SIZE5Y] = {0}, ship4[SIZE4X][SIZE5Y] = {0}, ship3[SIZE3X][SIZE5Y] = {0}, ship6[SIZE3X][SIZE5Y] = {0}, ship2[SIZE2X][SIZE5Y] = {0};
//left
ISR(INT0_vect) {
cnt1++;
	SREG &= 0x7F;
	_delay_ms(300);
	if(state == 0);                          							        // 1.single, 2. multi
	
	else if(state == 1) {														// 1.easy 2. hard
		state = 0;
		GLCD_Clear();
	}

	else if(state == 2 || state == 3 || state == 4 ) {							// 전함 위치 선택
	      x--;                                    // 전함 위치 선택
      if((rotate==2||rotate==4)&& x<0) // 아래, 위
         x=9;
      else if(rotate==1&&x<0) //오른쪽
         x=9-(ship_size-1);
      else if(rotate==3&&x<ship_size-1) //왼쪽
         x=9;
	}
	
	else if(state == 5);															//공격 좌표 선택
			_delay_ms(100);					
	_delay_ms(150);
	SREG |= 0x80;
}

//up
ISR(INT1_vect) {
	_delay_ms(150);

	if(state == 0) {                           							        // 1.single, 2. multi
		if(select == 1)
			select = 2;
		else if(select == 2)
			select =1;
	}
	
	else if(state == 1) {														// 1.easy 2. hard
		if(select == 1)
			select = 2;
		else if(select == 2)
			select =1;
	}

	else if(state == 2 || state == 3 || state == 4 ) {							// 전함 위치 선택
	      y--;
      if((rotate==1||rotate==3)&&y<0) //오른쪽, 왼쪽
         y=9;
      else if(rotate==2&&y<0) //아래, 5짜리배
         y=9-(ship_size-1);
      else if(rotate==4&&y<ship_size-1) //위, 5짜리배
         y=9;	
	}
	
	else if(state == 5)	;														//공격 좌표 선택
	_delay_ms(150);
}

ISR(INT2_vect) {
cnt3++;
	SREG &= 0x7F;
	_delay_ms(300);
//	switch_direction = RIGHT;
/*	if(state == 0) {                           							        // 1.single, 2. multi
		state = 1;
		GLCD_Clear();
	}
	
	else if(state == 1) {														// 1.easy 2. hard
		state = 1 + select;
		GLCD_Clear();
		PrintBoard(BOARDSIZE);
	}*/

	if(state == 2 || state == 3 || state == 4 ) {							// 전함 위치 선택
		    x++;
      if((rotate==2||rotate==4)&&x>9) //아래,위 (배 크기 상관x)
         x=0;
      else if(rotate==1&&x>9-(ship_size-1))
         x=0;
      else if(rotate==3&&x>9)
         x=ship_size-1;
	}
	
	else if(state == 5)	;														//공격 좌표 선택

	_delay_ms(300);
	SREG |= 0x80;
}

//DOWN
ISR(INT3_vect) {
cnt4++;
SREG &= 0x7F;
_delay_ms(300);
		if(state == 0) {                           							        // 1.single, 2. multi
			if(select == 1)
				select = 2;
			else if(select == 2)
				select =1;
		}
		else if(state == 1) {														// 1.easy 2. hard
			if(select == 1)
				select = 2;
			else if(select == 2)
				select =1;				
		}

		else if(state == 2 || state == 3 || state == 4 ) {							// 전함 위치 선택
			            y++;
         if((rotate==1||rotate==3)&&y>9) //오른쪽, 왼쪽
            y=0;
         else if(rotate==2&&y>9-(ship_size-1)) //아래, 5짜리배
            y=0;
         else if(rotate==4&&y>9) //위, 5짜리배
            y=ship_size-1;
		}
	
		else if(state == 5)	;														//공격 좌표 선택
	_delay_ms(150);
		SREG |= 0x80;
}

// 확인
ISR(INT4_vect) {
int i;
_delay_ms(150);
	if(state == 0) {                           							        // 1.single, 2. multi
		state = 1;
		GLCD_Clear();
	}
	
	else if(state == 1) {														// 1.easy 2. hard
		state = 1 + select;
		GLCD_Clear();
		PrintBoard(BOARDSIZE);
	}

	else if(state == 2 || state == 3 || state == 4 ) {							// 전함 위치 선택
	      if(size5 == 0)   {
         size5 = 1;
         switch(rotate){
            case 1:
               for(i=0;i<5;i++)
                  playerboard[x+i][y]=5;
               break;
            case 2:
               for(i=0;i<5;i++)
                  playerboard[x][y+i]=5;
               break;
            case 3:
               for(i=0;i<5;i++)
                  playerboard[x-i][y]=5;
               break;
            case 4:
               for(i=0;i<5;i++)
                  playerboard[x][y-i]=5;
               break;
         }
		 PrintShip5(ship5, x, y, rotate);
      }
      else if(size4 == 0) {
         size4 = 1;
         switch(rotate){
            case 1:
               for(i=0;i<4;i++)
                  playerboard[x+i][y]=4;
               break;
            case 2:
               for(i=0;i<4;i++)
                  playerboard[x][y+i]=4;
               break;
            case 3:
               for(i=0;i<4;i++)
                  playerboard[x-i][y]=4;
               break;
            case 4:
               for(i=0;i<4;i++)
                  playerboard[x][y-i]=4;
               break;
         }
		 PrintShip4(ship4, x, y, rotate);
      }
      else if(size3 == 0 || size3 == 1) {
         size3++;
         switch(rotate){
            case 1:
               for(i=0;i<3;i++){
                  if(size3 == 0) playerboard[x+i][y]=3;
				  else playerboard[x+i][y]=6;
				  }
               break;
            case 2:
               for(i=0;i<3;i++) {
                  if(size3 == 0) playerboard[x][y+i]=3;
				  else	playerboard[x][y+i] = 6;
				  }
               break;
            case 3:
               for(i=0;i<3;i++) {
                  if(size3 == 0) playerboard[x-i][y]=3;
				  else playerboard[x-i][y]= 6;
				  }
               break;
            case 4:
               for(i=0;i<3;i++) {
                  if(size3 == 0) playerboard[x][y-i]=3;
				  else playerboard[x][y-i] = 6;
				  }
               break;
         }
		 if(size3 == 1 )	PrintShip3(ship3, x, y, rotate);
		 else				PrintShip3(ship6, x, y, rotate);
      }
      else if(size2 == 0) {
         size2 = 1;
         switch(rotate){
            case 1:
               for(i=0;i<2;i++)
                  playerboard[x+i][y]=2;
               break;
            case 2:
               for(i=0;i<2;i++)
                  playerboard[x][y+i]=2;
               break;
            case 3:
               for(i=0;i<2;i++)
                  playerboard[x-i][y]=2;
               break;
            case 4:
               for(i=0;i<2;i++)
                  playerboard[x][y-i]=2;
               break; 
         }
		 PrintShip2(ship2, x, y, rotate);
		 state+=3;
      }
   }

	
	else if(state == 5)	;	
	_delay_ms(150);													//공격 좌표 선택
}
//취소
ISR(INT5_vect){
_delay_ms(150);

	if(state == 0);                          							        // 1.single, 2. multi
	
	else if(state == 1) {														// 1.easy 2. hard
		state = 0;
		GLCD_Clear();
	}

	else if(state == 2 || state == 3 || state == 4 ) {							// 전함 위치 선택
		state = 1;
		GLCD_Clear();
	}
	
	else if(state == 5);	
	_delay_ms(300);														//공격 좌표 선택
}
//왼쪽 회전
ISR(INT6_vect){
   //EICRB=0x00;
   _delay_ms(150);
   if(state == 2 || state == 3 || state == 4){
   if((ship_size-2)<x&&x<9-(ship_size-2)&&(ship_size-2)<y&&y<9-(ship_size-2)){  //가운데
      if(rotate<4)
         rotate++;
      else
         rotate=1;
   }
   else if(x<ship_size-1&&ship_size-2<y&&y<9-(ship_size-2))  //십자가 왼쪽
   {
      if(rotate==2)
         rotate=4;
      else
         rotate++;
      if(rotate==5)
         rotate=1;
   }
   else if(ship_size-2<x&&x<9-(ship_size-2)&&y>9-(ship_size-2))    //십자가 아래
   {
      if(rotate==1)
         rotate=3;
      else
         rotate++;
      if(rotate==5)
         rotate=1;
   }
   else if(x>9-(ship_size-2)&&y<9-(ship_size-2)&&y>ship_size-2){  //십자가 오른쪽
      if(rotate==4)
         rotate=2;
      else
         rotate++;
   }
   else if(ship_size-2<x&&x<9-(ship_size-2)&&y<ship_size-1){  //십자가 위
      if(rotate==3)
         rotate=1;
      else
         rotate++;
   }
   else if(x<ship_size-1&&y<ship_size-1){   //왼쪽 위
      if(rotate==1)
         rotate=2;
      else
         rotate=1;
   }
   else if(x>=9-(ship_size-2)&&y<ship_size-1)  //오른쪽 위
   {
      if(rotate==2)
         rotate=3;
      else
         rotate=2;
   }
   else if(x<ship_size-1&&y>=9-(ship_size-2)){  //왼쪽 아래
      if(rotate==1)
         rotate=4;
      else
         rotate=1;
   }
   else if(x>9-(ship_size-2)&&y>=9-(ship_size-2)) //오른쪽 아래
   {
      if(rotate==3)
         rotate=4;
      else
         rotate=3;
   }
}
   _delay_ms(150);
}

//오른쪽 회전
ISR(INT7_vect){
   cli();
   EICRB=0xAA;
   if(state == 2 || state == 3 || state == 4){
   if((ship_size-2)<x&&x<9-(ship_size-2)&&(ship_size-2)<y&&y<9-(ship_size-2)){  //가운데
      if(rotate>1)
         rotate--;
      else
         rotate=4;
   }
   else if(x<ship_size-1&&ship_size-2<y&&y<9-(ship_size-2))  //십자가 왼쪽
   {
      if(rotate==4)
         rotate=2;
      else if(rotate==1)
         rotate=4;
      else
         rotate=1;
   }
   else if(ship_size-2<x&&x<9-(ship_size-2)&&y>9-(ship_size-2))    //십자가 아래
   {
      if(rotate==3)
         rotate=1;
      else if(rotate==4)
         rotate=3;
      else
         rotate=4;
   }
   else if(x>9-(ship_size-2)&&y<9-(ship_size-2)&&y>ship_size-2){  //십자가 오른쪽
      if(rotate==2)
         rotate=4;
      else if(rotate==4)
         rotate=3;
      else
         rotate=2;

   }
   else if(ship_size-2<x&&x<9-(ship_size-2)&&y<ship_size-1){  //십자가 위
      if(rotate==1)
         rotate=3;
      else if(rotate==3)
         rotate=2;
      else
         rotate=1;
   }
   else if(x<ship_size-1&&y<ship_size-1){   //왼쪽 위
      if(rotate==2)
         rotate=1;
      else
         rotate=2;
   }
   else if(x>=9-(ship_size-2)&&y<ship_size-1)  //오른쪽 위
   {
      if(rotate==2)
         rotate=3;
      else
         rotate=2;
   }
   else if(x<ship_size-1&&y>=9-(ship_size-2)){  //왼쪽 아래
      if(rotate==1)
         rotate=4;
      else
         rotate=1;
   }
   else if(x>9-(ship_size-2)&&y>=9-(ship_size-2)) //오른쪽 아래
   {
      if(rotate==3)
         rotate=4;
      else
         rotate=3;
   }
   }
   _delay_ms(50);
}

int main(void){
	int size5 = 0, size4 = 0, size3 = 0, size2 = 0;
	char myBoard[BOARDSIZE][BOARDSIZE] = {0};
	sei();

	EICRA = 0xAA;
	EICRB = 0xAA;
	EIMSK = 0xFF;
	
	GLCD_Initialize();
	GLCD_Clear();

	//PrintBoard(10);
	MakeShip5(ship5);
	MakeShip4(ship4);	
	MakeShip3(ship3);
	MakeShip3(ship6);
	MakeShip2(ship2);
	while(1){
		if(state == 0)
			PrintMode(select);
		else if(state == 1) 
			PrintDifficulty(select);
		else if(state == 2 || state == 3 || state ==4){
			if(size5 == 0) {
				ship_size = 5;
				PrintSelectShip5(ship5,x,y,rotate);
				}
			else if(size4 == 0) {
				ship_size = 4;
				PrintSelectShip4(ship4,x,y,rotate);
				}
			else if(size3 == 0 || size3 == 1) {
				ship_size = 3;
				PrintSelectShip3(ship3,x,y,rotate);
				}
			else {
				ship_size = 2;
				PrintSelectShip2(ship2,x,y,rotate);
				}
			}
		else if(state == 7 || state ==8 || state == 9);	//가위바위보
		}
	}

