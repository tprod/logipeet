#include <RelayModule.h>

#define RELAY_PIN   6
#define INVERT_RELAY true

typedef enum {calc_food, disp_food, Init_food} sm_state_food_t;
typedef enum {disp_water, Init_water} sm_state_water_t;
typedef enum {ev_NULL, ev_calc_food, ev_disp_food, ev_Init} sm_event_t;

typedef struct {
  int current_state
  int initial_state
  sm_event_t last_event
} sm_t;


void sm_init(sm_t *psm, int initial_state)

void sm_reset(sm_t *psm)

int sm_get_current_state(sm_t *psm)

void sm_send_event(sm_t *psm, sm_event_t event)

void sm_execute_water(sm_t *psm)



void setup() {
    relay = new RelayModule(RELAY_PIN,INVERT_RELAY);
    Serial.begin(9600);

}



void loop() {
  

}



void sm_init(sm_t *psm, int initial_state)
{
  (sm_state_t)psm 
}




void sm_execute_water(sm_t *psm)
{
  switch ((sm_state_t)psm->current_state)
  {
    case Init_water:
      {
        stateRelay = false;
        relay->setState(stateRelay);               // = relay->off();
        break;
      }


    case disp_water
      {
//____________________ Calculo do Peso ______________________________ //
        
         
        if (peso <= 200)
            {
              stateRelay = true;
              relay->setState(stateRelay);         // = relay->on();
            }
        else if(peso >= 500)
            {
              stateRelay = false;
              relay->setState(stateRelay);         // = relay->off();
            }
        else
            {
              relay->setState(stateRelay);
            }
        }
  }

}
