#include <HX711.h>
#include <LiquidCrystal.h>
#include "FuncoesComponentes.h"

#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

uint8_t DDOUT_Agua = A1;      
uint8_t SSCK_Agua = A2;
const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int lcd_key     = 0;
int adc_key_in  = 0;
int PESO = 200;
int ID = 93158;
int escolha = 1;
int state = 5;
int last_state = 5;
  
float PesoTaca_Agua() { 
  HX711 scale;              // criamos variável scale do tipo HX711 
  
  scale.begin(DDOUT_Agua,SSCK_Agua);

  scale.set_scale(-463.090);    // gramas: -463.090  ;  kilogramas: -463090
  scale.tare();

  Serial.print("\nPeso: ");
  Serial.print(scale.get_units(),3);
  Serial.print(" g");

  return get_units();
}

int read_LCD_buttons() {
  adc_key_in = analogRead(0);          // read analog A0 value
  if (adc_key_in > 1000) return btnNONE;
  if (adc_key_in < 50)   return btnRIGHT;
  if (adc_key_in < 250)  return btnUP;
  if (adc_key_in < 450)  return btnDOWN;
  if (adc_key_in < 650)  return btnLEFT;
  if (adc_key_in < 850)  return btnSELECT;

  return btnNONE;
}

void LCD() {
  lcd.begin(16, 2);
  lcd.setCursor(4, 0);
  lcd.print("feedEET");

  lcd.setCursor(0, 0);
  lcd_key = read_LCD_buttons();
  state = read_LCD_buttons();

  if (state != last_state)
  {
    lcd.clear();

    if (lcd_key == btnRIGHT)
    {
      escolha = escolha + 1;
    }
    else if (lcd_key == btnLEFT)
    {
      escolha = escolha - 1;
    }
  }
  last_state = state;

  if (escolha % 5 == 0)
  {
    escolha = escolha + pow(-1, escolha) * 4;
    Serial.print(escolha);
  }

  switch (escolha)
  {
    case 1:
      {

        lcd.print("Peso na Taca: ");
        lcd.setCursor(0, 1);
        lcd.print(PESO);
        lcd.print("Kg");1
        break;
      }
    case 2:
      {

        lcd.print("Reser Comida: ");
        lcd.setCursor(0, 1);
        lcd.print(PESO);
        lcd.print("Kg");
        break;
      }
    case 3:
      {

        lcd.print("Reserv Agua: ");
        lcd.setCursor(0, 1);
        lcd.print(PESO);
        lcd.print("Kg");
        break;
      }
    case 4:
      {

        lcd.print("ID: ");
        lcd.print(ID);
        break;
      }
  }
}
