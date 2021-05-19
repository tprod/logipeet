#include "FuncoesComponentes.h"

void sm_init(sm_t *psm, int initial_state) {
  psm->initial_state = initial_state;
  psm->current_state = initial_state;
}

int sm_get_current_state(sm_t *psm) {
  return psm->current_state; 
}

void sm_send_event(sm_t *psm, sm_event_t event) {
  psm->last_event = event;
}

void sm_execute_water(sm_t *psm) {
  switch ((sm_state_water_t)psm->current_state)
  {
    case Init_water:
      {
        turn_OnOff_relay(&relay,false)         // = relay->off();
                                               // (??) Nao sei se reconhece relay
  
        if(psm->last_event = ev_disp_water)
        {
          psm->current_state = disp_water;
        }
        else if(psm->last_event = ev_NULL || psm->last_event = ev_Init)
        {
          psm->current_state = Init_water;
        }
      }

    case disp_water:
    {
        int maxWater = 600;
        
        while(weigth(scale_water) < maxWater)   // (??) Nao sei se reconhece scale_water
        {
            turn_OnOff_relay(&relay,true)        // = relay->off();
        }

        psm->last_event = ev_Init;
        
        if(psm->last_event = ev_disp_water || psm->last_event = ev_NULL)
        {
          psm->current_state = disp_water;
        }
        else if(psm->last_event = ev_Init)
        {
          psm->current_state = Init_water;
        }
    }
}
