#include "State_Machine_Food.h"

// Creation of variables
int Time2Disp = 0;  // Flag reveived from Rasp to Dispense
float bowl_weigth;    // Current weigth in the bowl
float Total_food;     // Quantity of food to dispense (from Rasp pi)
float reservoir_weigth; 
float Final_weigth_reservoir;
float Food2Disp;

// State Machine Execution
void s_execute(sm_t *psm, 200/*int Desired_weigth*/);  //Desired_weigth deverá ser uma variável global da main()
{
    switch((sm_state_p)psm -> current_state)
    {
        case st_Init:
            // Chamar a função da ponte H para que o motor páre
            Ponte_H(0);
			
			if(psm->last_event = ev_disp_water)
			{
			 psm->current_state = disp_water;
			}
			else if(psm->last_event = ev_NULL || psm->last_event = ev_Init)
			{
			 psm->current_state = st_Init;
			}

        case st_Disp:
            // Medir o peso da taça (bowl_weigth)
            bowl_weigth = Sensor_Peso_Taça();

            // Medir o peso do reservatório (reservoir_weigth)
            reservoir_weigth = Sensor_Peso_Reservatorio();

            // Calcular quantidade de comida
            Food2Disp = Total_food - bowl_weigth;

            //Calculo do peso final do reservatorio
            Final_weigth_reservoir = reservoir_weigth - Food2Disp;

            if(Total_food == bowl_weigth)
            {
                Serial.printl("Warning! Bowl already full!");
                break;
            }

            // Chamar a função da ponte H para que o motor comece a rodar
            Ponte_H(1);

            while(reservoir_weigth < Final_weigth_reservoir)
            {
                // Medir o peso da taça (reservoir_weigth)
                reservoir_weigth = Sensor_Peso_Reservatorio();
            }
            
			psm->last_event = ev_Init;
        
			if(psm->last_event = ev_disp_food || psm->last_event = ev_NULL)
			{
			 psm->current_state = st_Disp;
			}
			else if(psm->last_event = ev_Init)
			{
			 psm->current_state = st_Init;
			}
        
        default:
            Serial.printl("ERROR! State not found!");
            break;
    }
}

// State Machine Initialization 
void sm_init(sm_t *psm, int initial_state)
{
    psm -> initial_state = st_Init;
    psm -> current_state = psm -> initial_state;
}

int sm_get_current_state(sm_t *psm)
{
  return psm->current_state; 
}

void sm_send_event(sm_t *psm, sm_event_t event)
{
  psm->last_event = event;