#include <HX711.h>
#include <LiquidCrystal.h>
#include <RelayModule.h>
#include "FuncoesComponentes.h"

sm_t water;

HX711 scale_water;              // criamos variável scale do tipo HX711 
//HX711 scale_food;
//HX711 scale_reserv_food;
int weigth_water;

RelayModule* relay;
relay = new RelayModule(RELAY_PIN,INVERT_RELAY); 

const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int dispensar = 0;



void setup() {
  sm_init(&water,Init_water);
  
  init_LoadCell(scale_water,DOUT_water,SCK_water);  
//  init_LoadCell(scale_food,DOUT_food,SCK_food);
//  init_LoadCell(scale_reserv_food,DOUT_reserv_food,SCK_reserv_food);

  init_LCD();
}



void loop() {
   weigth_water = weigth(scale_water);
   
   if(weigth_water < 200)
     sm_send_event(&water,ev_disp_water);

   dispensar = LCD();
   if(dispensar == 1)
    sm_send_event(&water,ev_disp_water);
   else if(dispensar == 0)
    sm_send_event(&water,ev_Init);     
}
