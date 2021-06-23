#include <Wire.h>
#define SLAVE_ADDRESS 0x69

bool RFID_ON = false; // flag para ativação do rfid
int FOOD_DISP; // Comida a dispensar em gramas
String TIME; //Tempo vindo da Rasp
bool FOOD_ON; //Flag para enviar quantidade de ração comida
bool AQUA_ON; //Flag a enviar para o caso do reservatorio de agua
bool STOW_ON; //Quantidade de comida no reservatorio

//char dataOut[] = "hello PI";
//String dataIn = "";
//bool receiveFlag = false;

void setup() {
     Wire.begin(SLAVE_ADDRESS);
     Wire.onReceive(receiveData);
     Wire.onRequest(sendData);
     Serial.begin(9600);
}

void loop() {
  //if(receiveFlag)
  //{
  //  Serial.print("Data Received From PI:");
  //  Serial.println(dataIn);
  //  receiveFlag = false;
  //}
}

void receiveData(int byteCount) {
  //receiveFlag = true;
  char dataIn[32];
  Serial.println("RPI is sending information...");
  int i=0;
  while(Wire.available()) {
        dataIn[i] = (char)Wire.read();
        i++;
        Serial.println(dataIn);
  }

  String command = "    ";
  for(i=0;i<4;i++){
    command[i] = dataIn[i];    //Lê os primeiros 4 carateres da string recebida
  }

  // OUT - RFID
  if(command == "RFID"){
    RFID_ON = !RFID_ON;
  }

  // IN - Food Amount Dispense
  if(command == "DISP"){
    FOOD_DISP = atoi(dataIn); //Obtem diretamente os valores numericos de uma string
  }
  
  // IN - Time
  if(command == "TIME"){
    TIME = atoi(dataIn); //Obtem os valores numericos do tempo
  }

  // OUT - Food Amount Eaten
  if(command == "FOOD"){
    FOOD_ON = true;
  }

  // OUT - Water Needed
  if(command == "AQUA"){
    AQUA_ON = true;
  }

  // OUT - Amount of food in storage
  if(command == "STOW"){
    STOW_ON = true;
  }

  


 


  
  //TODO
  //Isto gera duas vezes, ver melhor este problema
}

void sendData() {
  if(RFID_ON){
    Wire.write("Tag armazenada");
    RFID_ON = false;
  }

  if(FOOD_ON){
    Wire.write("Ração Comida");
    FOOD_ON = false;
  }

  if(AQUA_ON){
    Wire.write("Reservatorio Agua");
    AQUA_ON = false;
  }

   if(STOW_ON){
    Wire.write("Comida Reservatorio");
    STOW_ON = false;
  }
  
  //A implementar:
  //Atribuir uma variavel para a mensagem do tipo string
  //Se for maior que 32bytes, cortar em pedaços! 
  //Wire.write("Hello Raspberry Pi!");
}
