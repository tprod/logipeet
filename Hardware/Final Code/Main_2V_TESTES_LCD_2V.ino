#include "FuncoesComponentes.h"
#include "sm.h"
#include "FuncoesLcd.h"

sm_t water;
sm_t food;

int peso_taca_agua;
int food_weigth;

int RFID_comida_inicial;
int RFID_comida_cao;
int Time2Disp = 0;  // Flag reveived from Rasp to Dispense
String TAG;
String TAG_armazenada;
bool RFID_ON = false; //Vem da RASP



void setup() {
  Serial.begin(9600);


  setup_Peso();
  setup_Relay();
  setup_Ponte_H();
  setup_Sensor_Nivel();
  setup_LCD();
  setup_RFID();
  
  sm_init(&water, Init_water);
  sm_init(&food, Init_food);

  horasInit1 = 7;
  minInit1 = 00;
  horasInit2 = 13;
  minInit2 = 30;
  horasInit3 = 22;
  minInit3 = 15;
  pesoInit = 40;

}


void loop() {
   LCD();
   peso_taca_agua = PesoTaca_Agua();
   
   
   if(peso_taca_agua < 200 || Flag_DispAgua == true)
   {
     sm_send_event(&water,ev_disp_water);
   }
   else
   {
    sm_send_event(&water,ev_NULL);
   }

   
   if(Flag_DispComida == true)
   {
    sm_send_event(&food,ev_calc_food);
   }
   else
   {
    sm_send_event(&food,ev_NULL);
   }
   
    sm_execute_water(&water);
    sm_execute_food(&food);

    Serial.print("\n\n Peso da taça: ");
    Serial.print(PesoTaca_Comida());
    Serial.print("\n Peso da agua: ");
    Serial.print(PesoTaca_Agua());
    Serial.print("\n Peso do Reservatório: ");
    Serial.print(PesoTaca_Reserv());
    Serial.print("\n Final Reserv: ");
    Serial.print(Final_weigth_reservoir);
    Serial.print("\n Peso Init: ");
    Serial.print(pesoInit);


///////////////////////////// RFID ///////////////////////////////////////////////////////

  if(RFID_ON){  //Rasp envia esta flag
      RFID_comida_inicial = PesoTaca_Comida();  //1000; PesoTaca_Comida();
      TAG = RFID();

      if(TAG != "-- -- -- --")
      {
        TAG_armazenada = TAG;
      }
      RFID_comida_cao = RFID_comida_inicial - 500;//PesoTaca_Comida();
      
      // send TAG e RFID_comida_cao p/ RASP pi
      //Serial.print("\nTAG: ");
      //Serial.print(TAG);
      Serial.print("\nTAG_armazenada: ");
      Serial.print(TAG_armazenada);
      Serial.print("\nO cão comeu ");
      Serial.print(RFID_comida_cao);

      digitalWrite(LED_BUILTIN, HIGH);  //Led para testes
    }
    else
    {
      digitalWrite(LED_BUILTIN, LOW);
    }
    delay(1);

}
