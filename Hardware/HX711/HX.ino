#include <HX711.h>

HX711 scale;              // criamos variável scale do tipo HX711 

//uint8_t DDOUT = A0;      
//uint8_t SSCK = A1;

void setup() 
{
  Serial.begin(9600);
  
  scale.begin(A0,A1);

  scale.set_scale(-463.090);    // gramas: -463.090  ;  kilogramas: -463090
  scale.tare();
 // scale.callibrate_scale(500,10);
  
  //Serial.print("\nScale: ");
  //Serial.print(scale.get_scale());
  //Serial.print("\nTara ");
  //Serial.print(scale.get_tare());     // imprime o valor da tara (peso da taça s/comida)
}

void loop() 
{
  //Serial.print("\nScale ");
 // Serial.print(scale.get_scale());
  Serial.print("\nPeso: ");
  Serial.print(scale.get_units(),3);
  Serial.print(" g");
  delay(500);

}
