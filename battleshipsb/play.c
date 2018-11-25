#include "play.h"
#include <stdlib.h>
#include <avr/io.h>

#define BOARDSIZE 10
extern char enemyboard[BOARDSIZE][BOARDSIZE], playerboard[BOARDSIZE][BOARDSIZE],playerattack_x[BOARDSIZE * BOARDSIZE], enemyattack_x[BOARDSIZE * BOARDSIZE],playerattack_y[BOARDSIZE * BOARDSIZE], enemyattack_y[BOARDSIZE * BOARDSIZE];
extern int enemy_turn, state, hit, x5, y5, x4, y4, x3, y3, x6, y6, x2, y2, rotate5, rotate4, rotate3, rotate6, rotate2;

void EnemyThinkAttack(void) {
	int i;
	switch (state % 3) {
	case 2:																//easy
	think_easy:
		if(hit == 0) {
		srand(TCNT0);
		enemyattack_x[enemy_turn] = (char)(rand() % 10);
		enemyattack_y[enemy_turn] = (char)(rand() % 10);
		}
		else {
			enemyattack_x[enemy_turn] =  enemyattack_x[enemy_turn - 1] + ((rand() % 3) - 1);
			enemyattack_y[enemy_turn] =  enemyattack_y[enemy_turn - 1] + ((rand() % 3) - 1);
		}
		for (i = 0; i< enemy_turn; i++)
			if ((enemyattack_x[i] == enemyattack_x[enemy_turn]) && (enemyattack_y[i] == enemyattack_y[enemy_turn]) || ( enemyattack_x[enemy_turn] < 0 || enemyattack_x[enemy_turn] > 9 || enemyattack_y[enemy_turn] < 0 || enemyattack_y[enemy_turn] > 9))
				goto think_easy;



		if (playerboard[enemyattack_y[enemy_turn]][enemyattack_x[enemy_turn]] != 0) {
			enemy_turn++;
			hit++;
		}
		else {
			enemy_turn++;
			hit = 0;
		}

		break;
	case 0:												//hard
	think_hard:
		if(hit == 0) {
		srand(TCNT0);
		enemyattack_x[enemy_turn] = (char)(rand() % 10);
		enemyattack_y[enemy_turn] = (char)(rand() % 10);
		}
		else {
			if(rand() % 2 ) {
			enemyattack_x[enemy_turn] =  enemyattack_x[enemy_turn - 1] + ((rand() % 3) - 1);
			enemyattack_y[enemy_turn] =  enemyattack_y[enemy_turn - 1];
			}
			else {
			enemyattack_x[enemy_turn] =  enemyattack_x[enemy_turn - 1];
			enemyattack_y[enemy_turn] =  enemyattack_y[enemy_turn - 1] + ((rand() % 3) - 1);
			}
		}
		for (i = 0; i< enemy_turn; i++)
			if ((enemyattack_x[i] == enemyattack_x[enemy_turn]) && (enemyattack_y[i] == enemyattack_y[enemy_turn]) || ( enemyattack_x[enemy_turn] < 0 || enemyattack_x[enemy_turn] > 9 || enemyattack_y[enemy_turn] < 0 || enemyattack_y[enemy_turn] > 9))
				goto think_hard;



		if (playerboard[enemyattack_y[enemy_turn]][enemyattack_x[enemy_turn]] != 0) {
			enemy_turn++;
			hit++;
		}
		else {
		enemy_turn++;
		hit = 0;
		}
		break;
	}
}


void MakeEnemyBoard(void) {
	ChooseShip(5);
	ChooseShip(4);
	ChooseShip(3);
	ChooseShip(6);
	ChooseShip(2);
}

void MakeRandomBoard(void) {
	RandomShip(5);
	RandomShip(4);
	RandomShip(3);
	RandomShip(6);
	RandomShip(2);
}
void RandomShip(int size) {
int start_i, start_j;
	int column, i;

start:
	srand(TCNT0);
	column = rand() % 2;

	if (column) {

		start_i = rand() % BOARDSIZE;
		start_j = rand() % (BOARDSIZE - size);
		switch(size) {
			case 5: 
				x5 = start_i;
				y5 = start_j;
				rotate5 = 2;
				break;
			case 4:
				x4 = start_i;
				y4 = start_j;
				rotate4 = 2;
				break;
			case 3:
				x3 = start_i;
				y3 = start_j;
				rotate3 = 2;
				break;
			case 6:
				x6 = start_i;
				y6 = start_j;
				rotate6 = 2;
				break;
			case 2:
				x2 = start_i;
				y2 = start_j;
				rotate2 = 2;
				break;
		}
		for (i = 0; i < (size == 6 ? 3: size); i++) {
			if (playerboard[start_j + i][start_i] != 0) {
				while (i) {
					i--;
					playerboard[start_j + i][start_i] = 0;
				}
				goto start;
			}
			else
				playerboard[start_j + i][start_i] = size;
		}
	}
	else {
		start_i = rand() % (BOARDSIZE - size);
		start_j = rand() % BOARDSIZE;
		switch(size) {
			case 5: 
				x5 = start_i;
				y5 = start_j;
				rotate5 = 1;
				break;
			case 4:
				x4 = start_i;
				y4 = start_j;
				rotate4 = 1;
				break;
			case 3:
				x3 = start_i;
				y3 = start_j;
				rotate3 = 1;
				break;
			case 6:
				x6 = start_i;
				y6 = start_j;
				rotate6 = 1;
				break;
			case 2:
				x2 = start_i;
				y2 = start_j;
				rotate2 = 1;
				break;
		}
		for (i = 0; i < (size == 6 ? 3: size); i++) {
			if (playerboard[start_j][start_i + i] != 0) {
				while (i) {
					i--;
					playerboard[start_j][start_i + i] = 0;
				}
				goto start;
			}
			else
				playerboard[start_j][start_i + i] = size;
		}
	}
}

void ChooseShip(int size) {
	int start_i, start_j;
	int column, i;

start:
	srand(TCNT0);
	column = rand() % 2;

	if (column) {

		start_i = rand() % BOARDSIZE;
		start_j = rand() % (BOARDSIZE - size);

		for (i = 0; i < (size == 6 ? 3: size); i++) {
			if (enemyboard[start_j + i][start_i] != 0) {
				while (i) {
					i--;
					enemyboard[start_j + i][start_i] = 0;
				}
				goto start;
			}
			else
				enemyboard[start_j + i][start_i] = size;
		}
	}
	else {
		start_i = rand() % (BOARDSIZE - size);
		start_j = rand() % BOARDSIZE;

		for (i = 0; i < (size == 6 ? 3: size); i++) {
			if (enemyboard[start_j][start_i + i] != 0) {
				while (i) {
					i--;
					enemyboard[start_j][start_i + i] = 0;
				}
				goto start;
			}
			else
				enemyboard[start_j][start_i + i] = size;
		}
	}
}

void InitBoard(char arr[][BOARDSIZE]) {
	int i, j;

	for (i = 0; i<BOARDSIZE; i++)
		for (j = 0; j<BOARDSIZE; j++)
			arr[i][j] = 0;
}

