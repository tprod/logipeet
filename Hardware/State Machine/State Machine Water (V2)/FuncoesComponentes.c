#include <HX711.h>
#include <LiquidCrystal.h>
#include <RelayModule.h>
#include "FuncoesComponentes.h"


// -----> FUNCTIONS <------
void init_LoadCell(HX711& scale,uint8_t DOUT,uint8_t SCK) {
  scale.begin(DOUT,SCK);

  scale.set_scale(-463.090);    // gramas: -463.090  ;  kilogramas: -463090
  scale.tare();
}

void init_LCD() {
  lcd.begin(16, 2);
  lcd.setCursor(4, 0);
  lcd.print("feedEET");
}

float weight(HX711& scale) { 
  // Print para testar (eliminar depois!)
  Serial.begin(9600);
  Serial.print("\nPeso: ");
  Serial.print(scale.get_units(),3);
  Serial.print(" g");
  ////////////

  return scale.get_units();
}

void turn_OnOff_relay(RelayModule* relay,bool state) {
   relay->setState(state);    
   // se state=true, então o relay liga
   // se state=falsa, então o raley desliga
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


// ->variáveis para LCD (onde meter??)
int lcd_key     = 0;
int adc_key_in  = 0;
int escolha = 1;
int state = 5;
int last_state = 5;

int LCD() {
  disp_water = 1;
  no_disp_water = 0;
  
  lcd.setCursor(0, 0);
  lcd_key = read_LCD_buttons();
  state = read_LCD_buttons();

  if (state != last_state)
  {
    lcd.clear();

    if (lcd_key == btnRIGHT)
      escolha = escolha + 1;
    else if (lcd_key == btnLEFT)
      escolha = escolha - 1;
  }
  last_state = state;

  if (escolha % 5 == 0)
    escolha = escolha + pow(-1, escolha) * 4;

  switch (escolha)
  {
    case 1:
      {
        lcd.print("Taca Agua: ");
        lcd.setCursor(0, 1);
        lcd.print(weigth(scale_water));
        lcd.print("Kg");
        return no_disp_water;
      }
    case 2:
      {
        lcd.print("Taca Comida: ");
        lcd.setCursor(0, 1);
        lcd.print(weigth(scale_food));
        lcd.print("Kg");
        return no_disp_water;
      }
    case 3:
      {
        lcd.print("Reser Comida: ");
        lcd.setCursor(0, 1);
        lcd.print(weigth(scale_reserv_food));
        lcd.print("Kg");
        return no_disp_water;
      }
    case 4:
      {
        lcd.print("Disp Comida? ");
        if(lcd_key == btnSELECT)
          return disp_water;
        else
          return no_disp_water;
      }
  }
}
