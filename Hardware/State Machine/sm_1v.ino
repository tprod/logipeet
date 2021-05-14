typedef enum{calc_food, disp_food, Init_food} sm_state_food_t;
typedef enum{calc_water, disp_water, Init_water} sm_state_water_t;
typedef enum{ev_NULL, ev_calc_food, ev_disp_food, ev_Init_food} sm_event_t;


typedef struct{
  int current_state
  int initial_state
  sm_event_t last_event
} sm_t;


void sm_init(sm_t *psm, int initial_state)

void sm_reset(sm_t *psm)

int sm_get_current_state(sm_t *psm)

void sm_send_event(sm_t *psm, sm_event_t event)

void sm_execute(sm_t *psm)


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

void sm_execute(sm_t *psm)
{
    switch((sm_state_t)psm->current_state)
    {
      case dips_water:
      
    }

}
