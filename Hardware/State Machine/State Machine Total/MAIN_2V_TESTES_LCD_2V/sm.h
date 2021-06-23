#ifndef sm_h
#define sm_h

// State Machine
typedef enum {Init_food, calc_food, disp_food} sm_state_food_t;
typedef enum {Init_water, disp_water} sm_state_water_t;
typedef enum {ev_NULL, ev_disp_food, ev_calc_food, ev_disp_water, ev_Init} sm_event_t;

extern float Final_weigth_reservoir;
extern float Total_food;     


typedef struct {
  int current_state;
  int initial_state;
  sm_event_t last_event;
} sm_t;

void sm_init(sm_t *psm, int initial_state);
int sm_get_current_state(sm_t *psm);
void sm_send_event(sm_t *psm, sm_event_t event);
void sm_execute_water(sm_t *psm);
void sm_execute_food(sm_t *psm);

#endif
