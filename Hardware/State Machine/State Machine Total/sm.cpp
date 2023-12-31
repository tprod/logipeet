#include "sm.h"
#include "FuncoesComponentes.h"

float Total_food;     // Quantity of food to dispense (from Rasp pi)
int maxWater = 600;

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
  
        if(psm->last_event == ev_disp_water)
        {
          psm->current_state = disp_water;
        }
        else if(psm->last_event == ev_NULL || psm->last_event == ev_Init)
        {
          psm->current_state = Init_water;
        }
      }

    case disp_water:
    {   
        while(PesoTaca_Agua() < maxWater)
        {
            Relay(true);               // = relay->off();
        }
        
        
        psm->last_event = ev_Init;
        
        if(psm->last_event == ev_disp_water || psm->last_event == ev_NULL)
        {
          psm->current_state = disp_water;
        }
        else if(psm->last_event == ev_Init)
        {
          psm->current_state = Init_water;
        }
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
  			
  			if(psm->last_event == ev_disp_food)
  			{
  			 psm->current_state = disp_food;
  			}
  			else if(psm->last_event == ev_NULL || psm->last_event == ev_Init)
  			{
  			 psm->current_state = Init_food;
  			}
      }

      case disp_food:
      {
        // Medir o peso da taça (bowl_weigth)
        bowl_weigth = PesoTaca_Comida();

        // Medir o peso do reservatório (reservoir_weigth)
        reservoir_weigth = PesoTaca_Reserv();

        // Calcular quantidade de comida
        Food2Disp = Total_food - bowl_weigth;

        //Calculo do peso final do reservatorio
        Final_weigth_reservoir = reservoir_weigth - Food2Disp;

//        if(Total_food == bowl_weigth)
//        {
//          printf("Warning! Bowl already full!");
//        }

        // Chamar a função da ponte H para que o motor comece a rodar
        Ponte_H(1);

        while(reservoir_weigth < Final_weigth_reservoir)
        {
          // Medir o peso da taça (reservoir_weigth)
          reservoir_weigth = PesoTaca_Reserv(); 
        }
      
            
			psm->last_event = ev_Init;
        
			if(psm->last_event == ev_disp_food || psm->last_event == ev_NULL)
			{
			 psm->current_state = disp_food;
			}
			else if(psm->last_event == ev_Init)
			{
			 psm->current_state = Init_food;
			}
    }
}
