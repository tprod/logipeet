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
  setup_Sensor_Nivel();
  setup_LCD();
  
  sm_init(&water, Init_water);
  sm_init(&food, Init_food);

  horasInit1 = 7;
  minInit1 = 00;
  horasInit2 = 13;
  minInit2 = 30;
  horasInit3 = 22;
  minInit3 = 15;
  pesoInit = 450;

  a = 0;
  b = 0;

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
    sm_send_event(&food,ev_calc_food);
   }
   else
   {
    sm_send_event(&food,ev_NULL);
   }
   
    //Serial.print("\n\n a: ");
    //Serial.print(a);

    //Serial.print("\n b: ");
    //Serial.print(b);
    
    Serial.print("\n select: ");
    Serial.print(cont2);

    Serial.print("\n\n Horas: ");
    Serial.print(horasInit2);

    Serial.print("\n Min: ");
    Serial.print(minInit2);

    Serial.print("\n Pos_Horas: ");
    Serial.print(pos_horas2);

    Serial.print("\n Pos_Min: ");
    Serial.print(pos_min2);
    Serial.print("\n\n");

    
    
    sm_execute_water(&water);
    sm_execute_food(&food);
  
}
