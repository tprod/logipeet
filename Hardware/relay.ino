#include <RelayModule.h>

#define RELAY_PIN   6
#define INVERT_RELAY true

RelayModule* relay;
int peso;                 // peso enviado pela load cell
bool state = false;

void setup() 
{
  relay = new RelayModule(RELAY_PIN,INVERT_RELAY);
}

void loop() 
{
  // TEST
  if (relay->isOn()) 
  {
    relay->off(); // turn the relay off.
  } 
  else if (relay->isOff()) 
  {
    relay->on(); // turn the relay on.
  }
  
  /*
  // CODE
  if(peso <= 200)
  {
    state = true;
    relay->setState(state);         // = relay->on();
  }
  else if(peso >= 1000)
  {
    state = false;;
    relay->setState(state);         // = relay->off();
  }
  else
  {
    relay->setState(state);
  }*/
  
  delay(1000); 
}
