/*==========================================================================
// Author : Handson Technology
// Project : Arduino Uno
// Description : L298N Motor Driver
// Source-Code : L298N_Motor.ino
// Program: Control 2 DC motors using L298N H Bridge Driver
//==========================================================================
*/
// Definitions Arduino pins connected to input H Bridge


#include <Stepper.h>    //This library allows you to control unipolar or bipolar stepper motors.

//Inputs do do arduino (neste caso arduino UNO)
int IN1 = 4;
int IN2 = 5;
int IN3 = 6;
int IN4 = 7;

void setup()
{
    // Set the output pins

    //Motor A
    pinMode(IN1, OUTPUT);   
    pinMode(IN2, OUTPUT);

    //Motor B
    //pinMode(IN3, OUTPUT);
    //pinMode(IN4, OUTPUT);
}

void loop()
{
    // Rotate the Motor A clockwise
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    delay(2000);
    // Stopping the Motor A
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, HIGH);
    delay(500);
    
    // Rotates the Motor A counter-clockwise
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    delay(2000);
    // Stopping the Motor A
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, HIGH);
    delay(500);
}

//Para o caso do motor B

//Rotação Horário ->        IN3=5V, IN4=ground
//Rotação Anti-Horário ->   IN3=ground, IN4=5V
//Ponto Morto ->            IN3=IN4=ground
//Parado ->                 IN3=IN4=5V