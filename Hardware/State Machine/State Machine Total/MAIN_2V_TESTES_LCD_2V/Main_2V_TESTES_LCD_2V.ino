#include "FuncoesComponentes.h"
#include "sm.h"
#include "FuncoesLcd.h"

sm_t water;
sm_t food;

int peso_taca_agua;
int food_weigth;
int Time2Disp = 0;  // Flag reveived from Rasp to Dispense
int T = 0;

void setup() {
  Serial.begin(9600);


  setup_Peso();
  setup_Relay();
  setup_Ponte_H();
  setup_LCD();
  
  sm_init(&water, Init_water);
  sm_init(&food, Init_food);

  horasInit = 12;
  minInit = 15;
}

void loop() {
   LCD();
   peso_taca_agua = PesoTaca_Agua();
   Serial.print("\nPeso taca:");
   Serial.print(peso_taca_agua);
   Serial.print("\nTime2Disp: ");
   Serial.print(Time2Disp);
   
   if(peso_taca_agua < 200 || Flag_DispAgua == true)
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
   
   if(Time2Disp == 1 || Flag_DispComida == true)
   {
    sm_send_event(&food,ev_disp_food);
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
