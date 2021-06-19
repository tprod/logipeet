#include <LiquidCrystal.h> 
//#include <SPI.h>   
#include "FuncoesComponentes.h"
#include "FuncoesLcd.h"


const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int lcd_key = 0;
int lcd_key_case = 0;
int adc_key_in = 0;
unsigned int ID = 65535;
int escolha = 1;
int state = 5;
int last_state = 5;
int state_case7 = 0;
int state_case8 = 0;
int state_case9 = 0;
int state_case10 = 0;
int last_state_case7 = 0;
int last_state_case8 = 0;
int last_state_case9 = 0;
int last_state_case10 = 0;
int cont1 = 0;
int cont2 = 0;
int cont3 = 0;
int array_horas[24] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23};
int array_min[12] = {00, 05, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55};
int array_peso[20] = {000, 050, 100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 950};
int horasInit1;
int horasInit2;
int horasInit3;
int minInit1;
int minInit2;
int minInit3;
int pesoInit;
int pos_horas1 = 0;
int pos_horas2 = 0;
int pos_horas3 = 0;
int pos_min1 = 0;
int pos_min2 = 0;
int pos_min3 = 0;
int pos_peso = 0;
int pos_pesoFinal = 0;
int flagInit1 = 0;
int flagInit2 = 0;
int flagInit3 = 0;
int flagInitPeso = 0;
int a = 0;
int b = 0;




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
    lcd.setCursor(2, 0);
    lcd.print("->feedEET<-");
    delay(3000);
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

  if (escolha % 11 == 0)
  {
    escolha = escolha + pow(-1, escolha) * 10;
  }

  switch (escolha)
  {
    case 1:
      {
        cont1 = 0;
        cont2 = 0;
        cont3 = 0;
        flagInitPeso = 0;
        lcd.print("Taca da Comida: ");
        lcd.setCursor(0, 1);
        lcd.print("                ");
        lcd.print(PesoTaca_Agua());
        lcd.print("g");
        break;
      }
      
    case 2:
      {
        cont1 = 0;
        cont2 = 0;
        cont3 = 0;
        flagInitPeso = 0;
        lcd.print("Reser Comida: ");
        lcd.setCursor(0, 1);
        lcd.print("                ");
        lcd.print(PesoTaca_Agua());
        lcd.print("Kg");
        break;
      }
      
    case 3:
      {
        cont1 = 0;
        cont2 = 0;
        cont3 = 0;
        flagInitPeso = 0;
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
      cont1 = 0;
      cont2 = 0;
      cont3 = 0;
      flagInitPeso = 0;
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
      cont1 = 0;
      cont2 = 0;
      cont3 = 0;
      flagInitPeso = 0;
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

//////////  RFID  ///////////////////////////    
    case 6:
      {
        flagInitPeso = 0;
        cont1 = 0;
        cont2 = 0;
        cont3 = 0;
        lcd.print("ID: ");
        lcd.print(ID);
        break;
      }

/////////////////////////////////////////////
    case 7:
      {
        flagInitPeso = 0;
        cont2 = 0;
        cont3 = 0;
        lcd.setCursor(0, 0);
        lcd.print("Select Hora 1: ");
        
        for (int i=0; i<25; i++) 
        {
          if (horasInit1 == array_horas[i]) 
          {
           pos_horas1 = i;
           break;
          }
        }


        for (int i=0; i<13; i++) 
        {
          if (minInit1 == array_min[i]) 
          {
           pos_min1 = i;
           break;
          }
        }

        lcd.setCursor(0, 1);
        lcd.print(array_horas[pos_horas1]);
        lcd.setCursor(2, 1);
        lcd.print(":");
        lcd.setCursor(3, 1);
        lcd.print(array_min[pos_min1]);



        if (lcd_key == btnSELECT && cont1==0)
        {
          flagInit1 = 1;
          cont1 = 1;
        }
        
        if (flagInit1 == 1 || cont1>0)
        {
          flagInit1 = 0;
          
          if(cont1<3)
          {
              lcd_key_case = read_LCD_buttons();
              state_case7 = read_LCD_buttons();
            
              if (state_case7 != last_state_case7)
              {
                if (lcd_key_case == btnUP)
                {
                  if(cont1 == 1)
                    pos_horas1 = pos_horas1 + 1;
                  else if(cont1 == 2)
                    pos_min1 = pos_min1 + 1;   
                }
                else if (lcd_key_case == btnDOWN)
                {
                  if(cont1 == 1)
                    pos_horas1 = pos_horas1 - 1;
                  else if(cont1 == 2)
                    pos_min1 = pos_min1 - 1;
                }
                else if (lcd_key_case == btnSELECT)
                {
                  cont1 = cont1+1;
                }
              }     
            last_state_case7 = state_case7;

              if ((pos_horas1+1) % 25 == 0)
              {
                pos_horas1 = pos_horas1 - pow(-1, pos_horas1) * 24;
              }

              if ((pos_min1+1) % 13 == 0)
              {
                pos_min1 = pos_min1 - pow(-1, pos_min1) * 12;
              }
            
            lcd.setCursor(0, 1);  
            lcd.print(array_horas[pos_horas1]);
            lcd.setCursor(2, 1);
            lcd.print(":");
            lcd.setCursor(3, 1);
            lcd.print(array_min[pos_min1]);  
          }
          else
          {
            cont1 = 0;
          }
          horasInit1 = array_horas[pos_horas1];
          minInit1 = array_min[pos_min1];
        }
        break;
      }


    case 8:
      {
        flagInitPeso = 0;
        cont1 = 0;
        cont3 = 0;
        lcd.setCursor(0, 0);
        lcd.print("Select Hora 2: ");
        
        for (int i=0; i<25; i++) 
        {
          if (horasInit2 == array_horas[i]) 
          {
           pos_horas2 = i;
           break;
          }
        }


        for (int i=0; i<13; i++) 
        {
          if (minInit2 == array_min[i]) 
          {
           pos_min2 = i;
           break;
          }
        }

        lcd.setCursor(0, 1);
        lcd.print(array_horas[pos_horas2]);
        lcd.setCursor(2, 1);
        lcd.print(":");
        lcd.setCursor(3, 1);
        lcd.print(array_min[pos_min2]);



        if (lcd_key == btnSELECT && cont2==0)
        {
          flagInit2 = 1;
          cont2 = 1;
        }
        
        if (flagInit2 == 1 || cont2>0)
        {
          flagInit2 = 0;
          
          if(cont2<3)
          {
              lcd_key_case = read_LCD_buttons();
              state_case8 = read_LCD_buttons();
            
              if (state_case8 != last_state_case8)
              {
                if (lcd_key_case == btnUP)
                {
                  if(cont2 == 1)
                    pos_horas2 = pos_horas2 + 1;
                  else if(cont2 == 2)
                    pos_min2 = pos_min2 + 1;   
                }
                else if (lcd_key_case == btnDOWN)
                {
                  if(cont2 == 1)
                    pos_horas2 = pos_horas2 - 1;
                  else if(cont2 == 2)
                    pos_min2 = pos_min2 - 1;
                }
                else if (lcd_key_case == btnSELECT)
                {
                  cont2 = cont2+1;
                }
              }     
            last_state_case8 = state_case8;

              if ((pos_horas2+1) % 25 == 0)
              {
                pos_horas2 = pos_horas2 - pow(-1, pos_horas2) * 24;
              }

              if ((pos_min2+1) % 13 == 0)
              {
                pos_min2 = pos_min2 - pow(-1, pos_min2) * 12;
              }
            
            lcd.setCursor(0, 1);  
            lcd.print(array_horas[pos_horas2]);
            lcd.setCursor(2, 1);
            lcd.print(":");
            lcd.setCursor(3, 1);
            lcd.print(array_min[pos_min2]);  
          }
          else
          {
            cont2 = 0;
          }
          horasInit2 = array_horas[pos_horas2];
          minInit2 = array_min[pos_min2];
        }
        break;
      }


      case 9:
      {
        cont1 = 0;
        cont2 = 0;
        flagInitPeso = 0;
        lcd.setCursor(0, 0);
        lcd.print("Select Hora 3: ");
        
        for (int i=0; i<25; i++) 
        {
          if (horasInit3 == array_horas[i]) 
          {
           pos_horas3 = i;
           break;
          }
        }


        for (int i=0; i<13; i++) 
        {
          if (minInit3 == array_min[i]) 
          {
           pos_min3 = i;
           break;
          }
        }

        lcd.setCursor(0, 1);
        lcd.print(array_horas[pos_horas3]);
        lcd.setCursor(2, 1);
        lcd.print(":");
        lcd.setCursor(3, 1);
        lcd.print(array_min[pos_min3]);



        if (lcd_key == btnSELECT && cont3==0)
        {
          flagInit3 = 1;
          cont3 = 1;
        }
        
        if (flagInit3 == 1 || cont3>0)
        {
          flagInit3 = 0;
          
          if(cont3<3)
          {
              lcd_key_case = read_LCD_buttons();
              state_case9 = read_LCD_buttons();
            
              if (state_case9 != last_state_case9)
              {
                if (lcd_key_case == btnUP)
                {
                  if(cont3 == 1)
                    pos_horas3 = pos_horas3 + 1;
                  else if(cont3 == 2)
                    pos_min3 = pos_min3 + 1;   
                }
                else if (lcd_key_case == btnDOWN)
                {
                  if(cont3 == 1)
                    pos_horas3 = pos_horas3 - 1;
                  else if(cont3 == 2)
                    pos_min3 = pos_min3 - 1;
                }
                else if (lcd_key_case == btnSELECT)
                {
                  cont3 = cont3+1;
                }
              }     
            last_state_case9 = state_case9;

              if ((pos_horas3+1) % 25 == 0)
              {
                pos_horas3 = pos_horas3 - pow(-1, pos_horas3) * 24;
              }

              if ((pos_min3+1) % 13 == 0)
              {
                pos_min3 = pos_min3 - pow(-1, pos_min3) * 12;
              }
            
            lcd.setCursor(0, 1);  
            lcd.print(array_horas[pos_horas3]);
            lcd.setCursor(2, 1);
            lcd.print(":");
            lcd.setCursor(3, 1);
            lcd.print(array_min[pos_min3]);  
          }
          else
          {
            cont3 = 0;
          }
          horasInit3 = array_horas[pos_horas3];
          minInit3 = array_min[pos_min3];
        }
        break;
      }

      
    case 10:
      {
        cont1 = 0;
        cont2 = 0;
        cont3 = 0;
        lcd.setCursor(0, 0);
        lcd.print("Quant. Racao:");

        for (int i=0; i<21; i++) 
        {
          if (pesoInit == array_peso[i]) 
          {
           pos_peso = i;
           break;
          }
        }

        pos_pesoFinal = pos_peso;
        
        lcd.setCursor(0, 1);
        lcd.print("                ");
        lcd.print(array_peso[pos_pesoFinal]);
        lcd.print("g");
        
        if (lcd_key == btnSELECT)
          flagInitPeso = 1;
          

        if (flagInitPeso == 1)
        { 
            lcd_key_case = read_LCD_buttons();
            state_case10 = read_LCD_buttons();
          
            if (state_case10 != last_state_case10)
            {
              if (lcd_key_case == btnUP)
                  pos_peso = pos_peso + 1;  

              else if (lcd_key_case == btnDOWN)
                  pos_peso = pos_peso - 1;

              else if (lcd_key_case == btnSELECT)
                  flagInitPeso = 0;
            }     
            
            last_state_case10 = state_case10;


            if ((pos_peso+1) % 21 == 0)
              pos_peso = pos_peso - pow(-1, pos_peso) * 20;


            
            lcd.setCursor(0, 1);  
            lcd.print("                ");
            lcd.print(array_peso[pos_peso]);
            lcd.print("g");
        }
        else
        {
          pos_pesoFinal = pos_peso;
        }
          
        pesoInit = array_peso[pos_pesoFinal];
          
        break;
      }
  }
}
