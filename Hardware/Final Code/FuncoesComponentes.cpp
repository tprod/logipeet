#include <HX711.h>   
#include <RelayModule.h>
#include <SPI.h>
#include "FuncoesComponentes.h"

#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <require_cpp11.h>
#include <deprecated.h>

bool Flag_DispAgua = false;
bool Flag_DispComida = false;
String content= "";

HX711 scaleWater;
HX711 scaleFood;
HX711 scaleReserv;

RelayModule* relay;



/////////////////////////// HX711 - AGUA/////////////////////////////////////
void setup_Peso() {
  scaleWater.begin(DOUT_Water,SCK_Water);          
  scaleFood.begin(DOUT_Food,SCK_Food);
  scaleReserv.begin(DOUT_Reserv,SCK_Reserv);

  scaleWater.set_scale(463.090);         // gramas: 463.090  ;  kilogramas: 463090
  scaleWater.tare();

  scaleFood.set_scale(-463.090);         // gramas: -463.090  ;  kilogramas: -463090
  scaleFood.tare();

  scaleReserv.set_scale(-224920.00);     // gramas: -224.920  ;  kilogramas: -224920.00
  scaleReserv.tare();
}

float PesoTaca_Agua() { 
  return round(scaleWater.get_units());
}

float PesoTaca_Comida() { 
  return scaleFood.get_units();
}

float PesoTaca_Reserv() { 
  return scaleReserv.get_units();
}

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



/////////////////////////// Leitor RFID ////////////////////////////////////
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.

void setup_RFID()
{
    SPI.begin(); // Initiate SPI bus, where SCK and MOSI are low and SS(slave select) is high
    mfrc522.PCD_Init(); // Initiate MFRC522
    delay(4);
    mfrc522.PCD_DumpVersionToSerial();
}

String RFID()
{    
    if ( ! mfrc522.PICC_IsNewCardPresent()) // No caso de não haver TAGS a serem detetadas
    { 
        return "-- -- -- --";
    }
    // Select one of the cards
    if ( ! mfrc522.PICC_ReadCardSerial())   // TAG detetada, mas não consegue ser lida
    {
        return "-- -- -- --";
    }

    for (byte i = 0; i < mfrc522.uid.size; i++)
    {
        Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");   // Nesta linha é acrescentado um zero à esquerda no caso de um byte ser < 0x10 ficando c/ formado 0xBB
        Serial.print(mfrc522.uid.uidByte[i], HEX);  // faz print em hexadecimal do byte
        // modulação da string para ser apresentada no display
        content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ")); // função concat() armazena o byte (neste caso) na variável content por forma a estar 
        content.concat(String(mfrc522.uid.uidByte[i], HEX));                // disponível nos próximos ciclos
    }
    content.toUpperCase();  // Faz com que os digitos dos bytes fiquem em maiusculas 
    
    return content;
}
