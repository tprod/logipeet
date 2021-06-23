#include "FuncoesComponentes.h"
#include "sm.h"
#include "FuncoesLcd.h"

sm_t water;
sm_t food;

int peso_taca_agua;
int RFID_comida_inicial;
int RFID_comida_cao;
int food_weigth;
int Time2Disp = 0;  // Flag reveived from Rasp to Dispense
int T = 0;
String TAG;

void setup() {
  Serial.begin(9600);


  setup_Peso();
  setup_Relay();
  setup_Ponte_H();
  setup_Sensor_Nivel();
  setup_LCD();
  Serial.print("\nP:");
  setup_RFID();
  delay(50);
  sm_init(&water, Init_water);
  sm_init(&food, Init_food);
  
  /////////// Interuupts Setup ///////////////////
  cli();  //stop interrupts
  //set timer1 interrupt at 1/10Hz (10 sec)
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = (16*10^6) / ((1/10)*1024) - 1; //(must be <65536)  
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  sei();//allow interrupts
  delay(5);
}

void loop() {
   LCD();
   peso_taca_agua = PesoTaca_Agua();
   Serial.print("\nPeso taca:");
   Serial.print(peso_taca_agua);
   Serial.print("\nTime2Disp: ");
   Serial.print(Time2Disp);
   
   if(peso_taca_agua < 200 || Flag_DispAgua == true)
   {
     sm_send_event(&water,ev_disp_water);
   }

   else
   {
    sm_send_event(&water,ev_NULL);
   }

   if(peso_taca_agua > 900)
   {
    Time2Disp = 1;
    T = T+1;
   }
   else
   {
    Time2Disp = 0;
   }
   
   if(Time2Disp == 1 || Flag_DispComida == true)
   {
    sm_send_event(&food,ev_calc_food);
   }
   else
   {
    sm_send_event(&food,ev_NULL);
   }


    Serial.print("\n T: ");
    Serial.print(T);
    
    Serial.print("\n b: ");
    Serial.print(b);

    
   Serial.print("\n a: ");
    Serial.print(a);
    

    Serial.print("\n i: ");
    Serial.print(i);
   
    Serial.print("\n Sensor nivel: ");
    Serial.print(Sensor_Nivel());
    
    Serial.print("\nEstado:");
    Serial.print(sm_get_current_state(&water));
    sm_execute_water(&water);
    sm_execute_food(&food);
  
}


///////////////////////////////////////////////////////////////////////////////////////////////////
ISR(TIMER1_COMPA_vect){  //change the 0 to 1 for timer1 and 2 for timer2
    RFID_comida_inicial = 1000; //PesoTaca_Comida();
    TAG = RFID();
    RFID_comida_cao = RFID_comida_inicial - 500;//PesoTaca_Comida();
    
    // send TAG e RFID_comida_cao p/ RASP pi
    Serial.print("\nTAG: ");
    Serial.print(TAG);
    Serial.print("\nO cão comeu ");
    Serial.print(RFID_comida_cao);
}
///////////////////////////////////////////////////////////////////////////////////////////////////
