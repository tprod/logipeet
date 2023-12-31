#include "sm.h"
#include "FuncoesComponentes.h"

float Total_food = 800;     // Quantity of food to dispense (from Rasp pi)
int maxWater = 800;
int i = 0;
int a = 0;
int b = 0;
float bowl_weigth;    // Current weigth in the bowl
float reservoir_weigth; 
float Final_weigth_reservoir;
float Food2Disp;
  
void sm_init(sm_t *psm, int initial_state)
{
  psm->initial_state = initial_state;
  psm->current_state = initial_state;
}



int sm_get_current_state(sm_t *psm)
{
  return psm->current_state; 
}



void sm_send_event(sm_t *psm, sm_event_t event)
{
  psm->last_event = event;
}



void sm_execute_water(sm_t *psm)
{ 
  switch ((sm_state_water_t)psm->current_state)
  {
    case Init_water:
      {
         Relay(false);         // = relay->off();
        // Relay(true);         // = relay->off();
        b = b+1;
        
        if(psm->last_event == ev_disp_water)
        {
          psm->current_state = disp_water;
          //Relay(true);
        }
        else if(psm->last_event == ev_NULL || psm->last_event == ev_Init)
        {
          psm->current_state = Init_water;
        }
        break;
      }

    case disp_water:
    {   
        Relay(true);
        
        if(PesoTaca_Agua() > maxWater)
        {
           psm->last_event = ev_Init;           // = relay->off();
           //Relay(false);
           i = i+1;
        }
        else
        {
          psm->last_event = ev_disp_water;
          a=a+1;
        }
        
        
        
        if(psm->last_event == ev_disp_water || psm->last_event == ev_NULL)
        {
          psm->current_state = disp_water;
        }
        else if(psm->last_event == ev_Init)
        {
          psm->current_state = Init_water;
        }
        break;
    }
  }
}



void sm_execute_food(sm_t *psm)  //Desired_weigth deverá ser uma variável global da main()
{    
   switch((sm_state_food_t)psm -> current_state)
   {
      case Init_food:
      {
        Ponte_H(0);           // Chamar a função da ponte H para que o motor páre
  			//b = b+1;
  			if(psm->last_event == ev_disp_food)
  			{
  			 psm->current_state = disp_food;
  			}
  			else if(psm->last_event == ev_NULL || psm->last_event == ev_Init)
  			{
  			 psm->current_state = Init_food;
  			}

       break;
      }

      case disp_food:
      {
        // Medir o peso da taça (bowl_weigth)
        bowl_weigth = 100;

        // Medir o peso do reservatório (reservoir_weigth)
        reservoir_weigth = PesoTaca_Agua();
        //reservoir_weigth = 1240;
        // Calcular quantidade de comida
         Food2Disp = Total_food - bowl_weigth;
        //Food2Disp = 210;
        //Calculo do peso final do reservatorio
        Final_weigth_reservoir = reservoir_weigth - Food2Disp;

//        if(Total_food == bowl_weigth)
//        {
//          printf("Warning! Bowl already full!");
//        }

        // Chamar a função da ponte H para que o motor comece a rodar
        Ponte_H(1);

        while(PesoTaca_Agua() > Final_weigth_reservoir)
        {
          // Medir o peso da taça (reservoir_weigth)
          
          //i = i+1;
          printf("i: %i", i);
        }
        printf("a: %i",a);
        //a = a+1;
            
			psm->last_event = ev_Init;
        
			if(psm->last_event == ev_disp_food || psm->last_event == ev_NULL)
			{
			 psm->current_state = disp_food;
			}
			else if(psm->last_event == ev_Init)
			{
			 psm->current_state = Init_food;
			}
     break;
    }
  }
}
