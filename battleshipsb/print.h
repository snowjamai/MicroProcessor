#define SIZE5Y 8
#define BOARDSIZE 10

void PrintBoard(int size);
void GLCD_select(unsigned char x, unsigned char y);
void GLCD_dselect(unsigned char x,unsigned char y);
void PrintToggle(int x, int y,int delay);
void PrintShipClear(int x, int y, int size, int rotate);
void PrintSelectBoard(int x, int y, int switch_direction);
void PrintMode(int);
void PrintDifficulty(int select_mode);
void PrintSelectShip5(char arr[][SIZE5Y],int x, int y, int rotate);
void PrintSelectShip4(char arr[][SIZE5Y],int x, int y, int rotate);
void PrintSelectShip3(char arr[][SIZE5Y],int x, int y, int rotate);
void PrintSelectShip2(char arr[][SIZE5Y],int x, int y, int rotate);
void PrintShip5(char arr[][SIZE5Y], int x, int y, int rotate);
void PrintShip4(char arr[][SIZE5Y], int x, int y, int rotate);
void PrintShip3(char arr[][SIZE5Y], int x, int y, int rotate);
void PrintShip2(char arr[][SIZE5Y], int x, int y, int rotate);
void PrintRSP(int select_mode);
void PrintSelectEnemyBoard(void);
void PrintX(char x, char y);
void PrintEnemyAttack(void);
void PrintWaitingEnemy(void);
