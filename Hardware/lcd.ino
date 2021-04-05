#include <LiquidCrystal.h>

const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int lcd_key     = 0;
int adc_key_in  = 0;

int PESO = 200;
//int escolha = 1;

#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

int read_LCD_buttons()
{
 adc_key_in = analogRead(0);          // read analog A0 value
 if (adc_key_in > 1000) return btnNONE;
 if (adc_key_in < 50)   return btnRIGHT;
 if (adc_key_in < 250)  return btnUP;
 if (adc_key_in < 450)  return btnDOWN;
 if (adc_key_in < 650)  return btnLEFT;
 if (adc_key_in < 850)  return btnSELECT;

 return btnNONE;
}

void setup()
{
 lcd.begin(16, 2);   
 lcd.setCursor(4,0); 
 lcd.print("feedEET");

}

void loop()
{
 lcd.setCursor(0,0);         
 lcd_key = read_LCD_buttons();  

 
//  lcd.print("1- A")
//  delay(1500);
//  lcd.clear();
//  lcd.print("2- B")
//  delay(1500);
//  lcd.clear();
//  lcd.print("3- C")
//  delay(1500);
//  lcd.clear();
//  lcd.print("4- D")
//  delay(1500);
//  lcd.clear();
//
//  while(lcd_key != btnSELECT)
//  {
//    if(lcd_key == btnUP)
//      escolha += 1;
//    else if(lcd_key == btnDOWN)
//      escolha -= 1;
//
//    if(escolha < 1 && escolha > 4)
//      escolha = 0;
//  }
 
 switch (lcd_key)              
 {
   case btnRIGHT:
     {
     lcd.clear();
     lcd.print("Peso = ");
     lcd.print(PESO);
     lcd.print("Kg");
     break;
     }
   case btnLEFT:
     {
      lcd.clear();
     lcd.print("Reservatorio");
     break;
     }
   case btnUP:
     {
      lcd.clear();
     lcd.print("UP");
     break;
     }
   case btnDOWN:
     {
      lcd.clear();
     lcd.print("DOWN");
     break; 
     }
   case btnSELECT:
     {
      lcd.clear();
      lcd.print("SELECT");
      break;
     }
//   case btnNONE:
//     {
//     lcd.clear();
//     lcd.print("NONE");
//     break;
//     }
 }
}
