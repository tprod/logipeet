#ifndef FuncoesComponentes_h
#define FuncoesComponentes_h
#include <HX711.h>
#include <RelayModule.h>



/////////////////////////// HX711 /////////////////////////////////////
#define DOUT_Water A1      
#define SCK_Water  A2

#define DOUT_Food  A3      
#define SCK_Food A4

#define DOUT_Reserv  A5      
#define SCK_Reserv A6

extern HX711 scaleWater;
extern HX711 scaleFood;
extern HX711 scaleReserv;


/////////////////////////// RELAY /////////////////////////////////////
#define RELAY_PIN   6
#define INVERT_RELAY true

extern RelayModule* relay;


/////////////////////////// PONTE H //////////////////////////////////
#define IN_PH_1 30
#define IN_PH_2 31


/////////////////////////// Sensor de Nível //////////////////////////////////
#define SL_PIN 2



// Componentes
void setup_Peso();
float PesoTaca_Agua();
float PesoTaca_Comida();
float PesoTaca_Reserv();
void setup_Relay();
void Relay(bool stateRelay);
void setup_Ponte_H();
void Ponte_H(int Flag);
void setup_Sensor_Nivel();
int Sensor_Nivel();


#endif
