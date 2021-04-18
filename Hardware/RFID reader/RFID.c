#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <require_cpp11.h>
#include <deprecated.h>

#include <SPI.h>
#define SS_PIN 53
#define RST_PIN 5

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.

// UID cartão: 
// UID porta chaves: 

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600); // Initiate a serial communication, sets data rate to 9600 bps
    while(!Serial);
    SPI.begin(); // Initiate SPI bus, where SCK and MOSI are low and SS(slave select) is high
    mfrc522.PCD_Init(); // Initiate MFRC522
    delay(4);
    mfrc522.PCD_DumpVersionToSerial();
    Serial.println("Put close your card to the reader...");
    Serial.println();   // Esta função faz avançar uma linha (=enter), ficando uma linha de intervalo

}

void loop() {
  // put your main code here, to run repeatedly:
    // Look for new cards
    delay(1000);
    if ( ! mfrc522.PICC_IsNewCardPresent()) // No caso de não haver TAGS a serem detetadas
    {
        //Serial.println("TAG Não Detetada");  
        return;
    }
    // Select one of the cards
    if ( ! mfrc522.PICC_ReadCardSerial())   // TAG detetada, mas não consegue ser lida
    {
        Serial.println("Erro de leitura da TAG");
        return;
    }
    Serial.println("Card selected");

    //Show UID on serial monitor
    Serial.print("UID tag :");  // diferente de Serial.println() porque só imprime a mensagem, não avança uma linha
    String content= "";
    byte letter;
    for (byte i = 0; i < mfrc522.uid.size; i++)
    {
        Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");   // Nesta linha é acrescentado um zero à esquerda no caso de um byte ser < 0x10 ficando c/ formado 0xBB
        Serial.print(mfrc522.uid.uidByte[i], HEX);  // faz print em hexadecimal do byte
        // modulação da string para ser apresentada no display
        content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ")); // função concat() armazena o byte (neste caso) na variável content por forma a estar 
        content.concat(String(mfrc522.uid.uidByte[i], HEX));                // disponível nos próximos ciclos
    }

    Serial.println();   // Dá enter
    Serial.print("Message : ");
    content.toUpperCase();  // Faz com que os digitos dos bytes fiquem em maiusculas 

    if ( (content.substring(1) == "47 EB D5 B5") || (content.substring(1) == "79 A8 5F B3") ) //change here the UID of the card/cards that you want to give access => myString.substring(from, to)
    {
        Serial.println("Authorized access");
        Serial.println();
        delay(3000);
    }
    else {
        Serial.println(" Access denied");
        delay(3000);
    }
}