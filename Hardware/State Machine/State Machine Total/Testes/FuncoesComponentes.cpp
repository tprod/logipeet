#include <HX711.h>   
#include <RelayModule.h>
#include <SPI.h>
#include "FuncoesComponentes.h"


HX711 scaleWater;
//HX711 scaleFood;
//HX711 scaleReserv;

RelayModule* relay;



/////////////////////////// HX711 - AGUA/////////////////////////////////////
void setup_Peso() {
  scaleWater.begin(DOUT_Water,SCK_Water);          
  // scaleFood.begin(DOUT_Food,SCK_Food);
  // scaleReserv.begin(DOUT_Reserv,SCK_Reserv);

  scaleWater.set_scale(-463.090);    // gramas: -463.090  ;  kilogramas: -463090
  scaleWater.tare();

//  scaleFood.set_scale(-463.090);    // gramas: -463.090  ;  kilogramas: -463090
//  scaleFood.tare();
//
//  scaleReserv.set_scale(-463090);    // gramas: -463.090  ;  kilogramas: -463090
//  scaleReserv.tare();
}

float PesoTaca_Agua() { 
  return scaleWater.get_units();
}

//float PesoTaca_Comida() { 
//  return scaleFood.get_units();
//}
//
//float PesoTaca_Reserv() { 
//  return scaleReserv.get_units();
//}

/////////////////////////// RELAY //////////////////////////////////
void setup_Relay()
{
  relay = new RelayModule(RELAY_PIN,INVERT_RELAY);      
}

void Relay(bool stateRelay){
  relay->setState(stateRelay);        
}



/////////////////////////// PONTE H //////////////////////////////////
void setup_Ponte_H()
{
   //Motor A
   // pinMode(enA, OUTPUT);
    pinMode(IN_PH_1, OUTPUT);   
    pinMode(IN_PH_2, OUTPUT);

    digitalWrite(IN_PH_1, LOW);
    digitalWrite(IN_PH_2, LOW);


    //analogWrite(enA, 255);
}


void Ponte_H(int Flag) {
    if(Flag == 1)
    {
        // Rotate the Motor A clockwise
        digitalWrite(IN_PH_1, HIGH);
        digitalWrite(IN_PH_2, LOW);
    }
    else
    {
        // Stopping the Motor A
        digitalWrite(IN_PH_1, HIGH);
        digitalWrite(IN_PH_2, HIGH);
    }
}



/////////////////////////// Sensor Nível //////////////////////////////////
void setup_Sensor_Nivel()
{
    pinMode(SL_PIN,INPUT);       // configuração do port a ser usado
}

int Sensor_Nivel()
{
    return digitalRead(SL_PIN);
}
