#include "FuncoesComponentes.h"
#include "sm.h"
#include "FuncoesLcd.h"

sm_t water;
sm_t food;

int peso_taca_agua;
int RFID_comida_inicial;
int RFID_comida_cao;
int food_weigth;
int Time2Disp = 0;  // Flag reveived from Rasp to Dispense
int T = 0;
String TAG;

void setup() {
  Serial.begin(9600);


  setup_Peso();
  setup_Relay();
  setup_Ponte_H();
  setup_LCD();
  setup_RFID();

  attachInterrupt(2, main_RFID, RISING);

  sm_init(&water, Init_water);
  sm_init(&food, Init_food);
}

void loop() {
   LCD();
   peso_taca_agua = PesoTaca_Agua();
   Serial.print("\nPeso taca:");
   Serial.print(peso_taca_agua);
   Serial.print("\nTime2Disp: ");
   Serial.print(Time2Disp);
   
   if(peso_taca_agua < 200)
   {
     sm_send_event(&water,ev_disp_water);
   }

   else
   {
    sm_send_event(&water,ev_NULL);
   }

   if(peso_taca_agua > 900)
   {
    Time2Disp = 1;
    T = T+1;
   }
   else
   {
    Time2Disp = 0;
   }
   
   if(Time2Disp == 1)
   {
    sm_send_event(&food,ev_disp_food);
    //sm_execute_food(&food);
   }
   else
   {
    sm_send_event(&food,ev_Init);
   }


    Serial.print("\n T: ");
    Serial.print(T);
    
    Serial.print("\n b: ");
    Serial.print(b);

    
   Serial.print("\n a: ");
    Serial.print(a);
    

    Serial.print("\n i: ");
    Serial.print(i);
   

    Serial.print("\nEstado:");
    Serial.print(sm_get_current_state(&water));
    sm_execute_water(&water);
    sm_execute_food(&food);

}

void main_RFID() {
    RFID_comida_inicial = 1000;//PesoTaca_Comida();
    TAG = RFID();
    delay(5000);  
    RFID_comida_cao = RFID_comida_inicial - 500;//PesoTaca_Comida();
    
    // send TAG e RFID_comida_cao p/ RASP pi
    Serial.print("\nTAG: ");
    Serial.print(TAG);
    Serial.print("\nO cão comeu ");
    Serial.print(RFID_comida_cao);
}
