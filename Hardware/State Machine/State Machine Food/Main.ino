#include "State_Machine_Food.h"

sm_t food;
int food_weigth;

void setup() {
  sm_init(&food, Init_food);
}

void loop() {
	food_weigth = food_weigth();
   
	if(Time2Disp == 1)
    {
		sm_send_event(&food,ev_disp_food);
		s_execute(&food);
    }
}








