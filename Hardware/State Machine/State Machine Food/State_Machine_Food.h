#include <stdio.h>

// Definition of State and Events
typedef enum {st_Init, st_Disp} sm_state_t;             //Declaration of state
typedef enum {ev_NULL, ev_disp_food, ev_disp_water, ev_Init} sm_event_t;



// Definition of the state machine structure
typedef struct {
    int current_state;
    int initial_state; // Não acho que seja preciso
    sm_event_t last_event;
} sm_t; 

// Set Initial state
void sm_init(sm_t *psm, int initial_state);   //psm = pointer state Machine (acho eu...)
// Reset state execute
void sm_reset(sm_t *psm);
// State Machine Execution
void sm_execute(sm_t *psm);
// SM current State
int sm_get_current_state(sm_t *psm);
// SM event transition
void sm_send_event(sm_t *psm, sm_event_t event);


float bowl_weigth();
float reservoir_weigth();