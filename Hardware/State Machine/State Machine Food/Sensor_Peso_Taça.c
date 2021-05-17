#include <HX711.h>

HX711 scale;              // criamos variável scale do tipo HX711 

float main() 
{
  //Serial.print("\nScale ");
 // Serial.print(scale.get_scale());
  Serial.print("\nPrint ");
  Serial.print(scale.get_units());

  delay(1000);
  return scale.get_units();
}
