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

extern int horasInit1;
extern int minInit1;
extern int horasInit2;
extern int minInit2;
extern int horasInit3;
extern int minInit3;
extern int pesoInit;

// TESTES:
extern int cont2;
extern int pos_horas2;
extern int pos_min2;


extern int a;
extern int b;

int read_LCD_buttons();
void setup_LCD();
void LCD();

#endif
