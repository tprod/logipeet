#include "FuncoesComponentes.h"

sm_t water;
int peso_taca_agua;

void setup() {
  sm_init(&water, Init_water);
}

void loop() {
   peso_taca_agua = PesoTaca_Agua();
   
   if(peso_taca_agua < 200)
     sm_send_event(&water,ev_disp_water);

}
