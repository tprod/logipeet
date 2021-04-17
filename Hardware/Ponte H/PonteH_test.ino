#include <Stepper.h>    //This library allows you to control unipolar or bipolar stepper motors.
#include <SPI.h>

//Inputs do do arduino (neste caso arduino UNO)
int IN1 = 30;
int IN2 = 31;
//int IN3 = 6;
//int IN4 = 7;

//int enA = 9;

void setup() {

    Serial.begin(9600);
    SPI.begin();
    // Set the output pins

    //Motor A
   // pinMode(enA, OUTPUT);
    pinMode(IN1, OUTPUT);   
    pinMode(IN2, OUTPUT);

    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);

    //Motor B
    //pinMode(IN3, OUTPUT);
    //pinMode(IN4, OUTPUT);
}

void loop() {

    //analogWrite(enA, 255);
    
    // Rotate the Motor A clockwise
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    Serial.println("Clockwise");
    delay(2000);
    // Stopping the Motor A
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, HIGH);
    Serial.println("Stopping");
    delay(500);
    
    // Rotates the Motor A counter-clockwise
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    Serial.println("Counter clockwise");
    delay(2000);
    // Stopping the Motor A
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, HIGH);
    Serial.println("Stopping");
    delay(500);
}

//Para o caso do motor B

//Rotação Horário ->        IN3=5V, IN4=ground
//Rotação Anti-Horário ->   IN3=ground, IN4=5V
//Ponto Morto ->            IN3=IN4=ground
//Parado ->                 IN3=IN4=5V
