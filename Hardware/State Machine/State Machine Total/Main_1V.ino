#include "FuncoesComponentes.h"
#include "sm.h"

sm_t water;
sm_t food;

// RelayModule* relay;
// relay = new RelayModule(RELAY_PIN,INVERT_RELAY);

int peso_taca_agua;
int food_weigth;
// bool Time2Disp=0;

void setup() {
  Serial.begin(9600);
  sm_init(&water, Init_water);
  sm_init(&food, st_Init);

  DDOUT_Agua = A1;
  SSCK_Agua = A2;
}

void loop() {
   peso_taca_agua = PesoTaca_Agua();
   food_weigth = PesoTaca_Agua();
   
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
