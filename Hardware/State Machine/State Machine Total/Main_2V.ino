#include "FuncoesComponentes.h"
#include "sm.h"
#include "FuncoesLcd.h"

sm_t water;
sm_t food;

int peso_taca_agua;
int Time2Disp = 0;  // Flag reveived from Rasp to Dispense

void setup() {
  Serial.begin(9600);
  sm_init(&water, Init_water);
  sm_init(&food, Init_food);

  setup_Peso();
  setup_Relay();
  setup_Ponte_H();
  setup_LCD();
}

void loop() {
   LCD();
   peso_taca_agua = PesoTaca_Agua();
   
   if(peso_taca_agua < 200)
   {
     sm_send_event(&water,ev_disp_water);
     sm_execute_water(&water);
   }
   
   if(Time2Disp == 1)
   {
    sm_send_event(&food,ev_disp_food);
    sm_execute_food(&food);
   }

}
