#include <stdio.h>

// Definition of State and Events
typedef enum {st_Init, st_Disp} sm_state_t;             //Declaration of states
typedef enum {ev_Time_Disp. ev_Full_Bowl} sm_event_t;   //Declaration of events

// Definition of the state machine structure
typedef struct {
    int current_state;
    int initial_state; // Não acho que seja preciso
    sm_event_t last_event;
} sm_t; 

// Set Initial state
void sm_init(sm_t *psm, int initial_state);   //psm = pointer state Machine (acho eu...)

// State Machine Execution
void sm_execute(sm_t *psm);