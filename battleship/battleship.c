#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
#include <time.h>
#include "t6963c.h"
#include "graphic.h"
#include "print.h"

#define SIZE5X 46
#define SIZE5Y 8
#define LEFT 1
#define UP 2
#define RIGHT 3
#define DOWN 4

volatile int x = 0, y = 0, cnt = 0, switch_direction;

ISR(INT0_vect) {
	EICRA = 0x00;
    cnt++;
	
	if(cnt>9500){
	switch_direction = LEFT;
	cnt=0;
	_delay_ms(300);
	}
}

ISR(INT1_vect) {
	EICRA = 0x00;
    cnt++;
	
	if(cnt>9500){
	switch_direction = UP;
	cnt=0;
	_delay_ms(300);
	}
}

ISR(INT2_vect) {
	EICRA = 0x00;
    cnt++;
	
	if(cnt>9500){
	switch_direction = RIGHT;

	_delay_ms(300);
	cnt=0;
	}
}

ISR(INT3_vect) {
	EICRA = 0x00;
    cnt++;
	
	if(cnt>9500){
	GLCD_dselect(x,y);
	y++;
	if(y>9)
		y=0;
	GLCD_select(x,y);
	_delay_ms(300);
	cnt=0;
	}
}

int main(void){
	int ship5[SIZE5X][SIZE5Y] = {0};
	sei();

	EICRA = 0xAA;
	EIMSK = 0x0F;

	GLCD_Initialize();
	GLCD_Clear();

	//PrintBoard(10);
	MakeShip5(ship5);
	

	while(1){
		PrintMode();
		_delay_ms(1000);
		GLCD_Clear();
		PrintSelectBoard(x, y,switch_direction);
	}
}
