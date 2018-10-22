#define SIZE5Y 8
 
void PrintBoard(int size);
void GLCD_select(unsigned char x, unsigned char y);
void GLCD_dselect(unsigned char x,unsigned char y);
void PrintToggle(int x, int y,int delay);
void PrintShip5(int arr[][SIZE5Y], int x, int y, int rotate);
void PrintShipClear(int x, int y, int size, int rotate);
void PrintSelectBoard(int x, int y, int switch_direction);
