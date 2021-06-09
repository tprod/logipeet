#ifndef FuncoesLcd_h
#define FuncoesLcd_h
#include <LiquidCrystal.h>

#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

//extern LiquidCrystal lcd;

//extern int PESO_Comida;
//extern int PESO_Reserv;
//extern int PESO_Agua;

int read_LCD_buttons();
void setup_LCD();
void LCD();

#endif
