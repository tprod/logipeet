#ifndef FuncoesLcd_h
#define FuncoesLcd_h
#include <LiquidCrystal.h>

#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5


extern int horasInit1;
extern int minInit1;
extern int horasInit2;
extern int minInit2;
extern int horasInit3;
extern int minInit3;
extern int pesoInit;


int read_LCD_buttons();
void setup_LCD();
void LCD();

#endif
