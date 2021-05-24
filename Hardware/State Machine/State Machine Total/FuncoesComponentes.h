#ifndef FuncoesComponentes_h
#define FuncoesComponentes_h

#include <RelayModule.h>

//typedef bool boolean;

/////////////////////////// HX711 /////////////////////////////////////
const int DDOUT_Agua;      
const int SSCK_Agua;


/////////////////////////// RELAY /////////////////////////////////////
#define RELAY_PIN   6
#define INVERT_RELAY true

RelayModule* relay;
relay = new RelayModule(RELAY_PIN,INVERT_RELAY);


/////////////////////////// PONTE H //////////////////////////////////
int IN_PH_1 = 30;
int IN_PH_2 = 31;


/////////////////////////// LCD ///////////////////////////////////// 
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int lcd_key     = 0;
int adc_key_in  = 0;
int PESO = 200;
int ID = 93158;
int escolha = 1;
int state = 5;
int last_state = 5;



// Componentes
float PesoTaca_Agua();
void Ponte_H(int Flag);
// int read_LCD_buttons();
// void LCD();

#endif
