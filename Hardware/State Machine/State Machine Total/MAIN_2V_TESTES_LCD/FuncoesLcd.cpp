#include <LiquidCrystal.h> 
//#include <SPI.h>   
#include "FuncoesComponentes.h"
#include "FuncoesLcd.h"


const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int lcd_key = 0;
int adc_key_in = 0;
unsigned int ID = 65535;
int escolha = 1;
int state = 5;
int last_state = 5;


//int PESO_Comida;
//int PESO_Reserv;
//int PESO_Agua;


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


void setup_LCD()
{
    lcd.begin(16, 2);
    lcd.setCursor(4, 0);
    lcd.print("feedEET");
}


void LCD() {
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

  if (escolha % 7 == 0)
  {
    escolha = escolha + pow(-1, escolha) * 6;
  }

  switch (escolha)
  {
    case 1:
      {
        lcd.print("Taca da Comida: ");
        lcd.setCursor(0, 1);
        lcd.print(PesoTaca_Agua());
        lcd.print("g");
        break;
      }
      
    case 2:
      {
        lcd.print("Reser Comida: ");
        lcd.setCursor(0, 1);
        lcd.print(PesoTaca_Agua());
        lcd.print("Kg");
        break;
      }
      
    case 3:
      {
        lcd.print("Reserv Agua: ");
        lcd.setCursor(3, 1);
        if (Sensor_Nivel() == 1)
          lcd.print("Cheio");
        else
          lcd.print("vazio");
        break;
      }

   case 4:
    {
      lcd.print("Disp Comida? ");
      if(lcd_key == btnSELECT || Flag_DispComida == true)
      {
        lcd.setCursor(0, 1);
        lcd.print("A dispensar...");
        Flag_DispComida = true;
      }
      else if (Flag_DispComida == false)
      {
        lcd.setCursor(0, 1);
        lcd.print("              ");
      }    
      break;
    }

    case 5:
    {
      lcd.print("Disp Agua? ");
      if(lcd_key == btnSELECT || Flag_DispAgua == true)
      {
        lcd.setCursor(0, 1);
        lcd.print("A dispensar...");
        Flag_DispAgua = true;
      }
      else if (Flag_DispAgua == false)
      {
        lcd.setCursor(0, 1);
        lcd.print("              ");
      }     
      break;
    }
    
    case 6:
      {
        lcd.print("ID: ");
        lcd.print(ID);
        break;
      }
  }
}
