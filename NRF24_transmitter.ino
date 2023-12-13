/*
 * THis project is free for you to use for personal or commercial
 * Please subscribe, like, comment and share to my channel: https://www.youtube.com/@ardujimmy
 * if you have a question, you can ask me through my channel comments
 */

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(4, 3); //atau, CE = 4 dan CSN = 3
const byte address[6] = "00001";

#define JoyStick_X_PIN     A1
#define JoyStick_Y_PIN     A0

#define potArah A6 // potentiometer
#define knobLampu 7 //toggle switch

void setup() {
  Serial.begin(9600);  
  pinMode(knobLampu, INPUT);
  digitalWrite(knobLampu, LOW);
  
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.stopListening();
}

void loop() {
  int posisiX = analogRead(JoyStick_X_PIN);
  int posisiY = analogRead(JoyStick_Y_PIN);

  int Ppotentio = analogRead(potArah);

  if (posisiY >= 700 && posisiY <= 1023) {
        const char text[] = "back";
        radio.write(&text, sizeof(text));
      }
  else if (posisiY >= 0 && posisiY <= 450) {
        const char text[] = "forward";
        radio.write(&text, sizeof(text));
      }
  else if (posisiX >= 700 && posisiX <= 1023) {
        const char text[] = "left";
        radio.write(&text, sizeof(text));
      }
  else if (posisiX >= 0 && posisiX <= 450) {
        const char text[] = "right";
        radio.write(&text, sizeof(text));
      }
  else {
        const char text[] = "stop";
        radio.write(&text, sizeof(text));    
      }

  if (digitalRead(knobLampu) == HIGH){
        const char text[] = "LampuOn"; // led on
        radio.write(&text, sizeof(text));
      }
  else if (digitalRead(knobLampu) == LOW){
        const char text[] = "LampuOff"; // led off
        radio.write(&text, sizeof(text));
      }


  if (Ppotentio >= 700 && Ppotentio <= 1023) {
        const char text[] = "kiri"; // servo to the left
        radio.write(&text, sizeof(text));
      }
  else if (Ppotentio >= 470 && Ppotentio <= 620) {
        const char text[] = "lurus"; // servo to the mid
        radio.write(&text, sizeof(text));
      }
  else if (Ppotentio >= 0 && Ppotentio <= 450) {
        const char text[] = "kanan"; // servo to the right
        radio.write(&text, sizeof(text));
      }
  delay(100);
}
