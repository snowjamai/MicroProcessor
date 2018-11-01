#include <time.h>
#include <iom128v.h>
#include <macros.h>
#include "graphic.h"
#include "t6963c.h"

void write_instruction(char data);
void write_data(char data);
void init_LCD(void);
void lcd_clear(void);
volatile int x=66,y=19;
void up(void);
void down(void);
void left(void);
void right(void);
char flag;
char *BUFF;
unsigned int baudrate[15]={832, 416, 207, 138, 103, 68, 51, 34, 25, 16, 8, 7, 3, 1, 0};

void tx_char(unsigned char tx_data)
{
  //�ø�����Ʈ�� ������ �۽��� �Ϸ�ǰ� �۽Ź��۰� �غ�Ǿ����� �˻�
  while((UCSR0A&0x20) == 0x00);
  UDR0 = tx_data; //�ø��� ��Ʈ�� ���Ͽ� ������ ����
}



void tx_string(unsigned char *str_data)
{
  while(*str_data != 0x00){  //���ڿ��� ���κ��� �ƴ϶��
    tx_char(*str_data);      //�ø�����Ʈ�� �Ѱ��� ���ڸ� �۽��Ѵ�.
    str_data++;
  }
}
#pragma interrupt_handler Bluetooth:iv_USART1_RX
void Bluetooth(void)
{
    flag=UDR0;
}
void GLCD_select(unsigned char x, unsigned char y)
{
    unsigned char j,i;

    for(j=0;j<8;j++)
        for(i=0;i<8;i++)
        {
            GLCD_SetPixel(x+j, y+i, 1);
        }
        delay_ms(100);
}

void GLCD_dselect(unsigned char x,unsigned char y)
{
    unsigned char j,i;
    for(j=0;j<8;j++)
        for(i=0;i<8;i++)
        {
            GLCD_SetPixel(x+j, y+i, 0);
        }
        delay_ms(100);
}

#pragma interrupt_handler up:iv_EXT_INT0
void up(void)
{
    SREG &=0X7f;
    GLCD_dselect(x,y);
    y-=11;
    if(y<19)     y=118;

    GLCD_select(x,y);
    delay_ms(300);
}
#pragma interrupt_handler down:iv_EXT_INT1
void down(void)
{
        SREG &=0X7f;
        GLCD_dselect(x,y);
        y+=11;
        if(y>118)   y=19;

        GLCD_select(x,y);
        delay_ms(300);
}
#pragma interrupt_handler right:iv_EXT_INT3
void right(void)
{
        SREG &=0X7f;
        GLCD_dselect(x,y);
        x+=11;
        if(x>165)    x=66;

        GLCD_select(x,y);
        delay_ms(300);
}
#pragma interrupt_handler left:iv_EXT_INT2
void left(void)
{
        SREG &=0X7f;
        GLCD_dselect(x,y);
        x=x-11;
        if(x<66)    x=165;

        GLCD_select(x,y);
        delay_ms(300);
}


int main(void)
{
    DDRD=0x00;
    DDRA=0xff;
    UCSR0A=0x02;
    UCSR0B=0x98;
    UCSR0C=0x06;
    DDRE = 0xFE;  //�ø�������� ���� PE0���� RXD0�μ� �Է����� �����ϰ�, PE1 ���� TXD0�μ� ������� ����
  UBRR0H = baudrate[2]>>8; // ������Ʈ ���� 9600 bps
  UBRR0L = baudrate[2];
    EIMSK = 0x1f;
    EICRA = 0xaa;
    EICRB = 0x02;
    SREG |=0X80;

    int i=0;
    GLCD_Initialize();
    GLCD_Clear();
     BUFF="blue";
    while(1)
    {
    tx_string(BUFF);
    }
    return 0;
}
