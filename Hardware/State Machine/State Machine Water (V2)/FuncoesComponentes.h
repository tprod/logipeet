#ifndef FuncoesComponentes_h
#define FuncoesComponentes_h

// ->definição dos pinos para HX711 (Load Cell)
#define DOUT_water        A1
#define SCK_water         A2
#define DOUT_food         A3
#define SCK_food          A4
#define DOUT_reserv_food  A5
#define SCK_reserv_food   A6
// ->definição dos pinos para Relay
#define RELAY_PIN     3
#define INVERT_RELAY  true
// ->definição de variáveis para LCD
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5


// ->State Machine
typedef enum {calc_food, disp_food, Init_food} sm_state_food_t;
typedef enum {Init_water, disp_water} sm_state_water_t;
typedef enum {ev_NULL, ev_calc_food, ev_disp_food, ev_disp_water, ev_Init} sm_event_t;

typedef struct {
  int current_state;
  int initial_state;
  sm_event_t last_event;
} sm_t;

void sm_init(sm_t *psm, int initial_state);
void sm_reset(sm_t *psm);
int sm_get_current_state(sm_t *psm);
void sm_send_event(sm_t *psm, sm_event_t event);
void sm_execute_water(sm_t *psm);

// Componentes
void init_LoadCell(HX711& scale,uint8_t DOUT,uint8_t SCK);
void init_LCD();
float weight(HX711& scale);
void turn_OnOff_relay(RelayModule* relay,bool state);
int read_LCD_buttons();
int LCD()


#endif
