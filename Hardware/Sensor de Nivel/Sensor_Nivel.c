#include <SPI.h>

int Liquid_level=0;

void setup() {
    Serial.begin(9600);  // opens serial port, sets data rate to 9600 bps   (permite mandar a informação para o arduino)
    pinMode(5,INPUT);   // configuração do port a ser usado
    pinMode(6, OUTPUT); // pin para o led do sensor
}

void loop() {
    Liquid_level=digitalRead(5);    //Verificar se há liquido

    // Made By Dário e Urbano (ajustar os valor, pois pode nunca chegar a 0)
    if(Liquid_level == 1){
        Serial.print("Tem água!");
        digitalWrite(6, HIGH);  // Led do sensor liga quando deteta água
    }
    else{   //if == 0
        Serial.print("AVISO: Não há água!");
        digitalWrite(6, LOW);   // Led do sensor desliga quando não deteta água
    }

    delay(500);
}

// To do:
// Pode ser necessário colocar uma flag dentro de cada condição para ser enviada para a main()