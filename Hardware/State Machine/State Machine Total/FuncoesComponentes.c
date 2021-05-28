#include <HX711.h>
#include <LiquidCrystal.h>
#include <Stepper.h>          
#include <RelayModule.h>
#include <SPI.h>
#include "FuncoesComponentes.h"

//typedef bool boolean;


/////////////////////////// HX711 - AGUA/////////////////////////////////////
void setup_PesoTaca_Agua(HX711& scale) {
  scale.begin(A1,A2);     // A1-DOUT ; A2-SCK

  scale.set_scale(-463.090);    // gramas: -463.090  ;  kilogramas: -463090
  scale.tare();
}

float PesoTaca_Agua(HX711& scale) { 
  return scale.get_units();
}



/////////////////////////// RELAY //////////////////////////////////
void Relay(_Bool stateRelay){
  relay->setState(stateRelay);        
}



/////////////////////////// PONTE H //////////////////////////////////
void Ponte_H(int Flag) {

    //Motor A
   // pinMode(enA, OUTPUT);
    pinMode(IN_PH_1, OUTPUT);   
    pinMode(IN_PH_2, OUTPUT);

    digitalWrite(IN_PH_1, LOW);
    digitalWrite(IN_PH_2, LOW);


    //analogWrite(enA, 255);
    
    if(Flag == 1)
    {
        // Rotate the Motor A clockwise
        digitalWrite(IN_PH_1, HIGH);
        digitalWrite(IN_PH_2, LOW);
        printf("Clockwise");
        delay(2000);
    }
    else
    {
        // Stopping the Motor A
        digitalWrite(IN_PH_1, HIGH);
        digitalWrite(IN_PH_2, HIGH);
        printf("Stopping");
        delay(500);
    }
}



/////////////////////////// LCD ///////////////////////////////////// 
//int read_LCD_buttons() {
//  adc_key_in = analogRead(0);          // read analog A0 value
//  if (adc_key_in > 1000) return btnNONE;
//  if (adc_key_in < 50)   return btnRIGHT;
//  if (adc_key_in < 250)  return btnUP;
//  if (adc_key_in < 450)  return btnDOWN;
//  if (adc_key_in < 650)  return btnLEFT;
//  if (adc_key_in < 850)  return btnSELECT;
//
//  return btnNONE;
//}
//
//
//
//void LCD() {
//  lcd.begin(16, 2);
//  lcd.setCursor(4, 0);
//  lcd.print("feedEET");
//
//  lcd.setCursor(0, 0);
//  lcd_key = read_LCD_buttons();
//  state = read_LCD_buttons();
//
//  if (state != last_state)
//  {
//    lcd.clear();
//
//    if (lcd_key == btnRIGHT)
//    {
//      escolha = escolha + 1;
//    }
//    else if (lcd_key == btnLEFT)
//    {
//      escolha = escolha - 1;
//    }
//  }
//  last_state = state;
//
//  if (escolha % 5 == 0)
//  {
//    escolha = escolha + pow(-1, escolha) * 4;
//    Serial.print(escolha);
//  }
//
//  switch (escolha)
//  {
//    case 1:
//      {
//        lcd.print("Peso na Taca: ");
//        lcd.setCursor(0, 1);
//        lcd.print(PESO);
//        lcd.print("Kg");1
//        break;
//      }
//      
//    case 2:
//      {
//        lcd.print("Reser Comida: ");
//        lcd.setCursor(0, 1);
//        lcd.print(PESO);
//        lcd.print("Kg");
//        break;
//      }
//      
//    case 3:
//      {
//        lcd.print("Reserv Agua: ");
//        lcd.setCursor(0, 1);
//        lcd.print(PESO);
//        lcd.print("Kg");
//        break;
//      }
//      
//    case 4:
//      {
//        lcd.print("ID: ");
//        lcd.print(ID);
//        break;
//      }
//  }
//}
