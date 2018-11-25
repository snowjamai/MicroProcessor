#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
#include <time.h>
#include <stdlib.h>
#include "play.h"
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
#define ROCK 0
#define SCISSOR 1
#define PAPER 2

volatile unsigned char data_flag, RSP_flag;
volatile char playerboard[BOARDSIZE][BOARDSIZE];
volatile char enemyboard[BOARDSIZE][BOARDSIZE];
volatile char playerattack_x[BOARDSIZE * BOARDSIZE], enemyattack_x[BOARDSIZE * BOARDSIZE], playerattack_y[BOARDSIZE * BOARDSIZE], enemyattack_y[BOARDSIZE * BOARDSIZE];
volatile int player_turn = 0, enemy_turn = 0;
volatile int x = 0, y = 0, cnt = 0, state = 0, select = 1, rotate = 1, ship_size = 0, size5 = 0, size4 = 0, size3 = 0, size2 = 0, x5 = 0, y5 = 0, x4 = 0, y4 = 0, x3 = 0, y3 = 0, x2 = 0, y2 = 0, x6 = 0, y6 = 0, rotate5 = 0, rotate3 = 0, rotate6 = 0, rotate2 = 0, rotate4 = 0;
volatile char ship5[SIZE5X][SIZE5Y], ship4[SIZE4X][SIZE5Y], ship3[SIZE3X][SIZE5Y], ship6[SIZE3X][SIZE5Y], ship2[SIZE2X][SIZE5Y];
volatile int enemyRSP = 0, myRSP = 1, cnt_data = 1;
volatile int print_flag = 0, pairing_ready = 0;
volatile int hit = 0, hit_locate = 0, prev_hit_locate = 0, receive_flag = 0;
volatile char Ready[3] = "1";
volatile char Player_RSP[3], SendX[3], SendY[3], Hit[3];

void USART0_Transmit(char data) {
	while (!(UCSR0A & 0x20));
	UDR0 = data;
}


void USART0_str(char *str) {
	while (*str)  USART0_Transmit(*str++);
}

ISR(USART0_RX_vect) {
	if (state == 31)	RSP_flag = UDR0;
	else if (state == 25) {
		if (cnt_data == 1) {
			enemyattack_x[enemy_turn] = UDR0 -'0' ;
			cnt_data = 2;
		}
		else if(cnt_data == 2) {
			enemyattack_y[enemy_turn] = UDR0 -'0';
			cnt_data = 3;
		}
	}
	else if (state == 22) {
		enemyboard[playerattack_y[player_turn]][playerattack_x[player_turn]] = UDR0 -'0';
		player_turn++;
	}
	else 			data_flag = UDR0;
}
//left
ISR(INT0_vect) {
	_delay_ms(200);
	if (state == 0);                                                       // 1.single, 2. multi

	else if (state == 1) {                                          // 1.easy 2. hard
		state = 0;
		GLCD_Clear();
	}

	else if (state >= 2 && state <= 16) {                     // 전함 위치 선택
		x--;                                    // 전함 위치 선택
		if ((rotate == 2 || rotate == 4) && x<0) // 아래, 위
			x = 9;
		else if (rotate == 1 && x<0) //오른쪽
			x = 9 - (ship_size - 1);
		else if (rotate == 3 && x<ship_size - 1) //왼쪽
			x = 9;
	}
	else if (state == 20 || state == 21 || state == 22) {//이김
		x--;                                    // 전함 위치 선택
		if (x<0) x = 9;
	}
}

//up
ISR(INT1_vect) {
	_delay_ms(200);
	if (state == 0) {                                                        // 1.single, 2. multi
		if (select == 1)
			select = 2;
		else if (select == 2)
			select = 1;
	}

	else if (state == 1) {                                          // 1.easy 2. hard
		if (select == 1)
			select = 2;
		else if (select == 2)
			select = 1;
	}

	else if (state >= 2 && state <= 16) {                     // 전함 위치 선택
		y--;
		if ((rotate == 1 || rotate == 3) && y<0) //오른쪽, 왼쪽
			y = 9;
		else if (rotate == 2 && y<0) //아래, 5짜리배
			y = 9 - (ship_size - 1);
		else if (rotate == 4 && y<ship_size - 1) //위, 5짜리배
			y = 9;
	}
	else if (state == 17 || state == 18 || state == 19) {
		myRSP--;
		if (myRSP<1)
			myRSP = 3;
	}
	else if (state == 20 || state == 21 || state == 22) {//이김
		y--;                                    // 전함 위치 선택
		if (y<0) y = 9;
	}

}

ISR(INT2_vect) {
	_delay_ms(200);
	//   switch_direction = RIGHT;
	/*   if(state == 0) {                                                        // 1.single, 2. multi
	state = 1;
	GLCD_Clear();
	}

	else if(state == 1) {                                          // 1.easy 2. hard
	state = 1 + select;
	GLCD_Clear();
	PrintBoard(BOARDSIZE);
	}*/

	if (state >= 2 && state <= 16) {                     // 전함 위치 선택
		x++;
		if ((rotate == 2 || rotate == 4) && x>9) //아래,위 (배 크기 상관x)
			x = 0;
		else if (rotate == 1 && x>9 - (ship_size - 1))
			x = 0;
		else if (rotate == 3 && x>9)
			x = ship_size - 1;
	}
	else if (state == 20 || state == 21 || state == 22) {
		x++;
		if (x>9) x = 0;
	}

}

//DOWN
ISR(INT3_vect) {
	_delay_ms(200);
	if (state == 0) {                                                        // 1.single, 2. multi
		if (select == 1)
			select = 2;
		else if (select == 2)
			select = 1;
	}
	else if (state == 1) {                                          // 1.easy 2. hard
		if (select == 1)
			select = 2;
		else if (select == 2)
			select = 1;
	}

	else if (state >= 2 && state <= 16) {                     // 전함 위치 선택
		y++;
		if ((rotate == 1 || rotate == 3) && y>9) //오른쪽, 왼쪽
			y = 0;
		else if (rotate == 2 && y>9 - (ship_size - 1)) //아래, 5짜리배
			y = 0;
		else if (rotate == 4 && y>9) //위, 5짜리배
			y = ship_size - 1;
	}
	else if (state == 17 || state == 18 || state == 19) {
		myRSP++;
		if (myRSP>3)
			myRSP = 1;
	}
	else if (state == 20 || state == 21 || state == 22) {//이김
		y++;                                    // 전함 위치 선택
		if (y>9) y = 0;
	}
}

// 확인
ISR(INT4_vect) {
	_delay_ms(200);
	int i;

	if (state == 0) {                                                        // 1.single, 2. multi
		if (select == 2)	select = 30;
		state = select;
		GLCD_Clear();
	}

	else if (state == 1) {                                          // 1.easy 2. hard
		MakeEnemyBoard();
		state = 1 + select;
		GLCD_Clear();
		PrintBoard(BOARDSIZE);
	}

	else if (state == 2 || state == 3 || state == 4) {                     // 전함 위치 선택
		switch (rotate) {
		case 1:
			for (i = 0; i<5; i++)
				playerboard[y][x + i] = 5;
			break;
		case 2:
			for (i = 0; i<5; i++)
				playerboard[y + i][x] = 5;
			break;
		case 3:
			for (i = 0; i<5; i++)
				playerboard[y][x - i] = 5;
			break;
		case 4:
			for (i = 0; i<5; i++)
				playerboard[y - i][x] = 5;
			break;
		}
		PrintShip5(ship5, x, y, rotate);
		x5 = x;
		y5 = y;
		rotate5 = rotate;

		rotate = 1;
		x = 0;
		y = 0;
		state += 3;
	}
	else if (state == 5 || state == 6 || state == 7) {
		switch (rotate) {
		case 1:
			for (i = 0; i<4; i++)
				if (playerboard[x + i][y] != 0)	return;
			for (i = 0; i<4; i++)	playerboard[y][x + i] = 4;
			break;
		case 2:
			for (i = 0; i<4; i++)
				if (playerboard[x + i][y] != 0)	return;
			for (i = 0; i<4; i++)	playerboard[y + i][x] = 4;
			break;
		case 3:
			for (i = 0; i<4; i++)
				if (playerboard[x + i][y] != 0)	return;
			for (i = 0; i<4; i++)	playerboard[y][x - i] = 4;
			break;
		case 4:
			for (i = 0; i<4; i++)
				if (playerboard[x + i][y] != 0)	return;
			for (i = 0; i<4; i++)	playerboard[y - i][x] = 4;
			break;
		}
		PrintShip4(ship4, x, y, rotate);
		x4 = x;
		y4 = y;
		rotate4 = rotate;

		rotate = 1;
		x = 0;
		y = 0;
		state += 3;
	}
	else if (state == 8 || state == 9 || state == 10) {
		switch (rotate) {
		case 1:
			for (i = 0; i<3; i++)
				if (playerboard[x + i][y] != 0)	return;
			for (i = 0; i<3; i++)  playerboard[y][x + i] = 3;

			break;
		case 2:
			for (i = 0; i<3; i++)
				if (playerboard[x][y + i] != 0)		return;
			for (i = 0; i<3; i++)    playerboard[y + i][x] = 3;

			break;
		case 3:
			for (i = 0; i<3; i++)
				if (playerboard[x - i][y] != 0)		return;
			for (i = 0; i<3; i++) 	playerboard[y][x - i] = 3;

			break;
		case 4:
			for (i = 0; i<3; i++)
				if (playerboard[x][y - i] != 0) 	return;
			for (i = 0; i<3; i++)  playerboard[y - i][x] = 3;

			break;
		}
		PrintShip3(ship3, x, y, rotate);
		x3 = x;
		y3 = y;
		rotate3 = rotate;

		rotate = 1;
		x = 0;
		y = 0;
		state += 3;
	}
	else if (state == 11 || state == 12 || state == 13) {
		switch (rotate) {
		case 1:
			for (i = 0; i<3; i++)
				if (playerboard[x + i][y] != 0)	return;
			for (i = 0; i<3; i++)  playerboard[y][x + i] = 6;

			break;
		case 2:
			for (i = 0; i<3; i++)
				if (playerboard[x][y + i] != 0)		return;
			for (i = 0; i<3; i++)    playerboard[y + i][x] = 6;

			break;
		case 3:
			for (i = 0; i<3; i++)
				if (playerboard[x - i][y] != 0)		return;
			for (i = 0; i<3; i++) 	playerboard[y][x - i] = 6;

			break;
		case 4:
			for (i = 0; i<3; i++)
				if (playerboard[x][y - i] != 0) 	return;
			for (i = 0; i<3; i++)  playerboard[y - i][x] = 6;

			break;
		}
		PrintShip3(ship6, x, y, rotate);
		x6 = x;
		y6 = y;
		rotate6 = rotate;

		rotate = 1;
		x = 0;
		y = 0;
		state += 3;
	}
	else if (state == 14 || state == 15 || state == 16) {
		switch (rotate) {
		case 1:
			for (i = 0; i<2; i++)
				if (playerboard[x + i][y] != 0)	return;
			for (i = 0; i<2; i++)  playerboard[y][x + i] = 2;

			break;
		case 2:
			for (i = 0; i<2; i++)
				if (playerboard[x][y + i] != 0)		return;
			for (i = 0; i<2; i++)    playerboard[y + i][x] = 2;

			break;
		case 3:
			for (i = 0; i<2; i++)
				if (playerboard[x - i][y] != 0)		return;
			for (i = 0; i<2; i++) 	playerboard[y][x - i] = 2;

			break;
		case 4:
			for (i = 0; i<2; i++)
				if (playerboard[x][y - i] != 0) 	return;
			for (i = 0; i<2; i++)  playerboard[y - i][x] = 2;

			break;
		}
		PrintShip2(ship2, x, y, rotate);
		x2 = x;
		y2 = y;
		rotate2 = rotate;

		rotate = 1;
		x = 0;
		y = 0;
		state += 3;
	}
	else if (state == 17 || state == 18)
	{
		int win_val = 0;
		srand(TCNT0);
		enemyRSP = rand() % 3;
		win_val = (3 + myRSP - enemyRSP) % 3;

		switch (win_val) {
		case 0:
			GLCD_Clear();
			GLCD_TextGoTo(13, 8);
			GLCD_WriteString("Draw!");
			_delay_ms(800);
			GLCD_Clear();
			break;
		case 1:
			GLCD_Clear();
			GLCD_TextGoTo(13, 8);
			GLCD_WriteString("YOU LOSE!");
			_delay_ms(800);
			GLCD_Clear();
			state += 6;
			break;
		case 2:
			GLCD_Clear();
			GLCD_TextGoTo(13, 8);
			GLCD_WriteString("YOU WIN!");
			_delay_ms(800);
			GLCD_Clear();
			state += 3;
			break;

		}

	}
	else if (state == 19) {
		Player_RSP[0] = myRSP + '0';
		Player_RSP[1] = '\0';
		state = 31;
	}
	else if (state == 20 || state == 21) {//이김
		for (i = 0; i < player_turn; i++) {
			if ((playerattack_x[i] == x) && (playerattack_y[i] == y))
				return;
		}
		playerattack_x[player_turn] = x;
		playerattack_y[player_turn] = y;
		player_turn++;


		if ((enemyboard[playerattack_y[player_turn - 1]][playerattack_x[player_turn - 1]] != 0))
			hit++;
		else	hit = 0;

		if (hit == 0) {
			state += 3;
			print_flag = 0;
			hit = 0;
		}
		GLCD_dselect(x, y);
		PrintEnemyBoard();

		_delay_ms(1000);
	}
	else if (state == 22) {
		for (i = 0; i < player_turn; i++) {
			if ((playerattack_x[i] == x) && (playerattack_y[i] == y))
				return;
		}
		playerattack_x[player_turn] = x;
		playerattack_y[player_turn] = y;
		SendX[0] = playerattack_x[player_turn] + '0';
		SendX[1] = '\0';
		SendY[0] = playerattack_y[player_turn] + '0';
		SendY[1] = '\0';
		USART0_str(SendX);
		_delay_ms(500);
		USART0_str(SendY);
		_delay_ms(500);
	}
	else if (state == 23 || state == 24 || state == 25) {//짐
	}
}


//취소
ISR(INT5_vect) {
	int i;
	_delay_ms(200);
	if (state == 0);                                                       // 1.single, 2. multi

	else if (state == 1) {                                                // 1.easy 2. hard
		state = 0;
		GLCD_Clear();
	}

	else if (state == 2 || state == 3 || state == 4) {
		MakeRandomBoard();
		PrintBoard(10);
		PrintShip5(ship5, x5, y5, rotate5);
		PrintShip4(ship4, x4, y4, rotate4);
		PrintShip3(ship3, x3, y3, rotate3);
		PrintShip3(ship6, x6, y6, rotate6);
		PrintShip2(ship2, x2, y2, rotate2);
		_delay_ms(1000);
		state += 15;
	}
	else if (state == 20 || state == 21 || state == 22) {
		srand(TCNT0);
		x = rand() % 10;
		y = rand() % 10;
		for (i = 0; i < player_turn; i++) {
			if ((playerattack_x[i] == x) && (playerattack_y[i] == y))
				return;
		}
		playerattack_x[player_turn] = x;
		playerattack_y[player_turn] = y;
		player_turn++;

		if ((enemyboard[playerattack_y[player_turn - 1]][playerattack_x[player_turn - 1]] != 0))
			hit++;
		else	hit = 0;

		if (hit == 0) {
			state += 3;
			print_flag = 0;
			hit = 0;
			x = 0;
			y = 0;
		}
		GLCD_dselect(x, y);
		PrintEnemyBoard();

		_delay_ms(1000);
	}

}
ISR(INT6_vect) {
	_delay_ms(200);

	if (state >= 2 && state <= 16) {
		if ((ship_size - 2)<x&&x<9 - (ship_size - 2) && (ship_size - 2)<y&&y<9 - (ship_size - 2)) {  //가운데
			if (rotate<4)
				rotate++;
			else
				rotate = 1;
		}
		else if (x <= (ship_size - 2) && ship_size - 2<y&&y<9 - (ship_size - 2))  //십자가 왼쪽
		{
			if (rotate == 2)
				rotate = 4;
			else
				rotate++;
			if (rotate == 5)
				rotate = 1;
		}
		else if (ship_size - 2<x&&x<9 - (ship_size - 2) && y >= 9 - (ship_size - 2))    //십자가 아래
		{
			if (rotate == 1)
				rotate = 3;
			else
				rotate++;
			if (rotate == 5)
				rotate = 1;
		}
		else if (x >= 9 - (ship_size - 2) && y<9 - (ship_size - 2) && y>ship_size - 2) {  //십자가 오른쪽
			if (rotate == 4)
				rotate = 2;
			else
				rotate++;
		}
		else if (ship_size - 2<x&&x<9 - (ship_size - 2) && y <= ship_size - 2) {  //십자가 위
			if (rotate == 3)
				rotate = 1;
			else
				rotate++;
		}
		else if (x <= (ship_size - 2) && y <= (ship_size - 2)) {   //왼쪽 위
			if (rotate == 1)
				rotate = 2;
			else
				rotate = 1;
		}
		else if (x >= 9 - (ship_size - 2) && y <= (ship_size - 2))  //오른쪽 위
		{
			if (rotate == 2)
				rotate = 3;
			else
				rotate = 2;
		}
		else if (x <= (ship_size - 2) && y >= 9 - (ship_size - 2)) {  //왼쪽 아래
			if (rotate == 1)
				rotate = 4;
			else
				rotate = 1;
		}
		else if (x >= 9 - (ship_size - 2) && y >= 9 - (ship_size - 2)) //오른쪽 아래
		{
			if (rotate == 3)
				rotate = 4;
			else
				rotate = 3;
		}
	}

}

//오른쪽 회전
ISR(INT7_vect) {
	_delay_ms(200);
	if (state >= 2 && state <= 16) {
		if ((ship_size - 2)<x&&x<9 - (ship_size - 2) && (ship_size - 2)<y&&y<9 - (ship_size - 2)) {  //가운데
			if (rotate>1)
				rotate--;
			else
				rotate = 4;
		}
		else if (x <= ship_size - 2 && ship_size - 2<y&&y<9 - (ship_size - 2))  //십자가 왼쪽
		{
			if (rotate == 4)
				rotate = 2;
			else if (rotate == 1)
				rotate = 4;
			else
				rotate = 1;
		}
		else if (ship_size - 2<x&&x<9 - (ship_size - 2) && y >= 9 - (ship_size - 2))    //십자가 아래
		{
			if (rotate == 3)
				rotate = 1;
			else if (rotate == 4)
				rotate = 3;
			else
				rotate = 4;
		}
		else if (x >= 9 - (ship_size - 2) && y<9 - (ship_size - 2) && y>ship_size - 2) {  //십자가 오른쪽
			if (rotate == 2)
				rotate = 4;
			else if (rotate == 4)
				rotate = 3;
			else
				rotate = 2;

		}
		else if (ship_size - 2<x&&x<9 - (ship_size - 2) && y <= ship_size - 2) {  //십자가 위
			if (rotate == 1)
				rotate = 3;
			else if (rotate == 3)
				rotate = 2;
			else
				rotate = 1;
		}
		else if (x <= (ship_size - 2) && y <= (ship_size - 2)) {   //왼쪽 위
			if (rotate == 2)
				rotate = 1;
			else
				rotate = 2;
		}
		else if (x >= 9 - (ship_size - 2) && y <= (ship_size - 2))  //오른쪽 위
		{
			if (rotate == 2)
				rotate = 3;
			else
				rotate = 2;
		}
		else if (x <= (ship_size - 2) && y >= 9 - (ship_size - 2)) {  //왼쪽 아래
			if (rotate == 1)
				rotate = 4;
			else
				rotate = 1;
		}
		else if (x >= 9 - (ship_size - 2) && y >= 9 - (ship_size - 2)) //오른쪽 아래
		{
			if (rotate == 3)
				rotate = 4;
			else
				rotate = 3;
		}
	}

}

int main(void) {
	int size5 = 0, size4 = 0, size3 = 0, size2 = 0;
	int win_val = 0;
	sei();

	EICRA = 0x00;
	EICRB = 0x00;
	EIMSK = 0xFF;
	TCCR0 = 0x01;
	UCSR0A = 0x00;
	UCSR0B = 0x98;
	UCSR0C = 0x06;
	UBRR0H = 0;
	UBRR0L = 103;

	InitBoard(playerboard);
	InitBoard(enemyboard);
	GLCD_Initialize();
	GLCD_Clear();

	MakeShip5(ship5);
	MakeShip4(ship4);
	MakeShip3(ship3);
	MakeShip3(ship6);
	MakeShip2(ship2);


	while (1) {
		if (state == 0)	PrintMode(select);

		else if (state == 1)	PrintDifficulty(select);
		else if (state == 2 || state == 3 || state == 4) {               //5선택
			ship_size = 5;
			GLCD_TextGoTo(6, 1);
			GLCD_WriteString("Select Ship Length 5");
			PrintSelectShip5(ship5, x, y, rotate);
		}
		else if (state == 5 || state == 6 || state == 7) {               //4선택
			GLCD_TextGoTo(6, 1);
			GLCD_WriteString("Select Ship Length 4");
			PrintShip5(ship5, x5, y5, rotate5);
			ship_size = 4;
			PrintSelectShip4(ship4, x, y, rotate);
		}
		else if (state == 8 || state == 9 || state == 10) {            //3선택
			GLCD_TextGoTo(6, 1);
			GLCD_WriteString("Select Ship Length 3");
			PrintShip5(ship5, x5, y5, rotate5);
			PrintShip4(ship4, x4, y4, rotate4);
			ship_size = 3;
			PrintSelectShip3(ship3, x, y, rotate);
		}
		else if (state == 11 || state == 12 || state == 13) {
			GLCD_TextGoTo(6, 1);
			GLCD_WriteString("Select Ship Length 3");
			PrintShip5(ship5, x5, y5, rotate5);
			PrintShip4(ship4, x4, y4, rotate4);
			PrintShip3(ship3, x3, y3, rotate3);
			ship_size = 3;
			PrintSelectShip3(ship6, x, y, rotate);
		}
		else if (state == 14 || state == 15 || state == 16) {            //2선택
			GLCD_TextGoTo(6, 1);
			GLCD_WriteString("Select Ship Length 2");
			PrintShip5(ship5, x5, y5, rotate5);
			PrintShip4(ship4, x4, y4, rotate4);
			PrintShip3(ship3, x3, y3, rotate3);
			PrintShip3(ship6, x6, y6, rotate6);
			ship_size = 2;
			PrintSelectShip2(ship2, x, y, rotate);
		}
		else if (state == 17 || state == 18 || state == 19) {                  //가위바위보
			GLCD_Clear();
			PrintRSP(myRSP);
		}
		else if (state == 20 || state == 21 || state == 22) {               //자신이 이겼을 때
			if (print_flag == 1) {
				PrintEnemyBoard();
				PrintToggle(x, y, 200);
			}
			else if (print_flag == 0) {
				GLCD_Clear();
				GLCD_TextGoTo(8, 1);
				GLCD_WriteString("Player Turn!");
				print_flag = 1;
			}
			if (receive_flag == 1) {
				if ((enemyboard[playerattack_y[player_turn]][playerattack_x[player_turn]] != 0))
					hit++;
				else	hit = 0;
				player_turn++;
				if (hit == 0) {
					state += 3;
					print_flag = 0;
					hit = 0;
				}
			}
			GLCD_dselect(x, y);
			PrintEnemyBoard();

			_delay_ms(1000);
		}
		else if (state == 23 || state == 24) {               //자신이 졌을 때 
			if (print_flag == 0) {
				GLCD_Clear();
				GLCD_TextGoTo(8, 1);
				GLCD_WriteString("Enemy Turn!");
				PrintBoard(10);
				print_flag = 1;
			}
			PrintShip5(ship5, x5, y5, rotate5);
			PrintShip4(ship4, x4, y4, rotate4);
			PrintShip3(ship3, x3, y3, rotate3);
			PrintShip3(ship6, x6, y6, rotate6);
			PrintShip2(ship2, x2, y2, rotate2);
			PrintEnemyAttack();
			_delay_ms(1000);
			EnemyThinkAttack();
			PrintEnemyAttack();
			_delay_ms(1500);
			if (hit == 0) {
				state -= 3;
				print_flag = 0;
			}
		}
		else if (state == 25) {
			if (print_flag == 0) {
				GLCD_Clear();
				GLCD_TextGoTo(8, 1);
				GLCD_WriteString("Wating Enemy Attack");
				PrintBoard(10);
				print_flag = 1;
			}
			PrintShip5(ship5, x5, y5, rotate5);
			PrintShip4(ship4, x4, y4, rotate4);
			PrintShip3(ship3, x3, y3, rotate3);
			PrintShip3(ship6, x6, y6, rotate6);
			PrintShip2(ship2, x2, y2, rotate2);
			PrintEnemyAttack();

			if (cnt_data == 3) {
				cnt_data = 1;

				Hit[0] = playerboard[enemyattack_y[enemy_turn]][enemyattack_x[enemy_turn]] + '0';
				Hit[1] = '\0';
				USART0_str(Hit);
				enemy_turn++;
				PrintEnemyAttack();
				if (playerboard[enemyattack_y[enemy_turn-1]][enemyattack_x[enemy_turn-1]] != 0)
					hit++;
				_delay_ms(1500);
				if (hit == 0) {
					state -= 3;
					print_flag = 0;
				
			}
		}
		else if (state == 30) {
			if (pairing_ready == 0 && data_flag != '1') {
				USART0_str(Ready);
				pairing_ready = 1;
			}
			else {
				PrintWaitingEnemy();
				if (data_flag == '1') {
					pairing_ready = 0;
					USART0_str(Ready);
					state = 4;
					PrintBoard(10);
				}
			}
		}
		else if (state == 31) {
			if (pairing_ready == 0) {
				GLCD_Clear();
				USART0_str(Player_RSP);
				pairing_ready = 1;
			}
			else {
				PrintWaitingEnemy();
				if (RSP_flag == '1' || RSP_flag == '2' || RSP_flag == '3') {
					pairing_ready = 0;
					USART0_str(Player_RSP);
					state = 32;
				}
			}
		}
		else if (state == 32) {
			enemyRSP = RSP_flag - '0';
			state = 19;
			win_val = (3 + myRSP - enemyRSP) % 3;
			switch (win_val) {
			case 0:
				GLCD_Clear();
				GLCD_TextGoTo(13, 8);
				GLCD_WriteString("Draw!");
				_delay_ms(800);
				GLCD_Clear();
				RSP_flag = 0;
				break;
			case 1:
				GLCD_Clear();
				GLCD_TextGoTo(13, 8);
				GLCD_WriteString("YOU LOSE!");
				_delay_ms(800);
				GLCD_Clear();
				state += 6;
				break;
			case 2:
				GLCD_Clear();
				GLCD_TextGoTo(13, 8);
				GLCD_WriteString("YOU WIN!");
				_delay_ms(800);
				GLCD_Clear();
				state += 3;
				break;
			}
		}
	}
}
}
