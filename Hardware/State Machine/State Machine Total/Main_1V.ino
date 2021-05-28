#include "FuncoesComponentes.h"
#include "sm.h"

sm_t water;
sm_t food;

HX711 scale;              // criamos variável scale do tipo HX711 

// RelayModule* relay;
// relay = new RelayModule(RELAY_PIN,INVERT_RELAY);

int peso_taca_agua;
int food_weigth;
int Time2Disp = 0;  // Flag reveived from Rasp to Dispense

void setup() {
  Serial.begin(9600);
  sm_init(&water, Init_water);
  sm_init(&food, Init_food);

  setup_PesoTaca_Agua(scale);
}

void loop() {
   peso_taca_agua = PesoTaca_Agua(scale);
   food_weigth = PesoTaca_Agua(scale);
   
   if(peso_taca_agua < 200)
   {
     sm_send_event(&water,ev_disp_water);
     s_execute(&water);
   }
   
   if(Time2Disp == 1)
   {
    sm_send_event(&food,ev_disp_food);
    s_execute(&food);
   }

}
