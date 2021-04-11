#include <RelayModule.h>

#define RELAY_PIN   6
#define INVERT_RELAY true

RelayModule* relay;
int peso = 0;                 // peso enviado pela load cell
bool state = false;

void setup() 
{
  relay = new RelayModule(RELAY_PIN,INVERT_RELAY);
  Serial.begin(9600);
}

void loop() 
{
  // TEST1
//  if (relay->isOn()) 
//  {
//    relay->off(); // turn the relay off.
//  } 
//  else if (relay->isOff()) 
//  {
//    relay->on(); // turn the relay on.
//  }
//  delay(1000);

  // TEST2
  while(peso < 13)
  {
    if(peso >= 2 && peso < 10)
    {
      state = true;
      relay->setState(state);         // = relay->on();
      Serial.print(state);
      Serial.print('\n');
    }
    else if(peso >= 10)
    {
      state = false;;
      relay->setState(state);         // = relay->off();
      Serial.print(state);
      Serial.print('\n');
      
    }
    else
    {
      relay->setState(state);
      Serial.print(state);
      Serial.print('\n');
    } 

   peso += 1;
   delay(1000); 
  }

  while(1);

  // CODE
//  if(peso <= 200)
//  {
//    state = true;
//    relay->setState(state);         // = relay->on();
//  }
//  else if(peso >= 1000)
//  {
//    state = false;;
//    relay->setState(state);         // = relay->off();
//  }
//  else
//  {
//    relay->setState(state);
//  }

  
}
