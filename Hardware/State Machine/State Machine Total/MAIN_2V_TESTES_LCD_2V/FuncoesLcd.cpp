#include <LiquidCrystal.h> 
//#include <SPI.h>   
#include "FuncoesComponentes.h"
#include "FuncoesLcd.h"


const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int lcd_key = 0;
int lcd_key_case7 = 0;
int adc_key_in = 0;
unsigned int ID = 65535;
int escolha = 1;
int state = 5;
int state_case7 = 0;
int last_state = 5;
int last_state_case7 = 0;
int cont = 0;
int array_horas[24] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23};
int array_min[12] = {00, 05, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55};
int horasInit;
int minInit;
int pos_horas;
int pos_min;


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

  if (escolha % 9 == 0)
  {
    escolha = escolha + pow(-1, escolha) * 8;
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
        if (Sensor_Nivel() == true)
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

    case 7:
      {
        lcd.print("Select Hora: ");
        for (int i=0; i<25; i++) 
        {
          if (horasInit = array_horas[i]) 
          {
           pos_horas = i;
           break;
          }
        }


        for (int i=0; i<13; i++) 
        {
          if (minInit = array_min[i]) 
          {
           pos_min = i;
           break;
          }
        }

        lcd.setCursor(1, 1);
        lcd.print(array_horas[pos_horas]);
        lcd.print(":");
        lcd.print(array_min[pos_min]);
        
        if (lcd_key == btnSELECT)
        {
          cont = 1;
          
          while(cont>2)
          {
              lcd_key_case7 = read_LCD_buttons();
              state_case7 = read_LCD_buttons();
            
              if (state_case7 != last_state_case7)
              {
                lcd.clear();
            
                if (lcd_key == btnUP)
                {
                  if(cont == 1)
                    pos_horas = pos_horas + 1;
                  else if(cont == 2)
                    pos_min = pos_min + 1;   
                }
                else if (lcd_key == btnDOWN)
                {
                  if(cont == 1)
                    pos_horas = pos_horas - 1;
                  else if(cont == 2)
                    pos_min = pos_min - 1;
                }
                else if (lcd_key == btnSELECT)
                {
                  cont = cont+1;
                }
              }     
            last_state_case7 = state_case7;

              if ((pos_horas + 1) % 25 == 0)
              {
                pos_horas = pos_horas - pow(-1, pos_horas) * 24;
              }

              if ((pos_min + 1) % 13 == 0)
              {
                pos_min = pos_min - pow(-1, pos_min) * 12;
              }
              
            lcd.setCursor(1, 1);  
            lcd.print(array_horas[pos_horas]);
            lcd.print(":");
            lcd.print(array_min[pos_min]);  
          }
          horasInit = array_horas[pos_horas];
          minInit = array_min[pos_min];
          break;
        }
      }

    case 8:
      {
        lcd.print("As restantes foram");
        break;
      }
  }
}
