/*
*
* All the resources for this project:
* Modified by Handson Technology
* www.handsontec.com
* Created by Handsontec Tech team
*
*/

#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.

void setup()
{
    Serial.begin(9600); // Initiate a serial communication, sets data rate to 9600 bps
    SPI.begin(); // Initiate SPI bus, where SCK and MOSI are low and SS(slave select) is high
    mfrc522.PCD_Init(); // Initiate MFRC522
    Serial.println("Put close your card to the reader...");
    Serial.println();   // Esta função faz avançar uma linha (=enter), ficando uma linha de intervalo
}

void loop()
{
    // Look for new cards
    if ( ! mfrc522.PICC_IsNewCardPresent()) // No caso de não haver TAGS a serem detetadas
    {
        Serial.println("TAG Não Detetada");  
        return;
    }
    // Select one of the cards
    if ( ! mfrc522.PICC_ReadCardSerial())   // TAG detetada, mas não consegue ser lida
    {
        Serial.println("Erro de leitura da TAG");
        return;
    }

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

    if (content.substring(0) == "B0 AC 7E 7A") //change here the UID of the card/cards that you want to give access => myString.substring(from, to)
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

// Sugestão:
// criar array com todos os IDs das Tags a serem usadas
// Terá de returnar uma flag (provavelmente) por forma a dar enable às restantes funções do dispensador (Enable para o próximo estado da State Machine)