/*
 * THis project is free for you to use for personal or commercial
 * Please subscribe, like, comment and share to my channel: https://www.youtube.com/@ardujimmy
 * if you have a question, you can ask me through my channel comments
 */

#include <Servo.h>

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

Servo myservo;

RF24 radio(10, 9); //CE = 4 dan CSN = 3
const byte address[6] = "00001";

#define lampuDepan 2 //led

int motor1N1 = 5;
int motor1N2 = 6;
int motor2N1 = 7;
int motor2N2 = 8;

void setup() {
  Serial.begin(9600);
  pinMode(motor1N1, OUTPUT);
  pinMode(motor1N2, OUTPUT);
  pinMode(motor2N1, OUTPUT);
  pinMode(motor2N2, OUTPUT);

  myservo.attach(3);
  myservo.write(90); // set the servo the mid when powering on
  
  radio.begin();
  radio.openReadingPipe(0,address);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.startListening();
}

void loop() {  
    char text[32] = "";  
    if (radio.available()) {
      radio.read(&text, sizeof(text));
      String transData = String(text);          
      //Serial.println(transData);
      if (transData == "forward") {
           digitalWrite(motor1N1, HIGH); //roda kiri forward
           digitalWrite(motor1N2, LOW);
           digitalWrite(motor2N1, HIGH); //roda kanan forward
           digitalWrite(motor2N2, LOW);           
           transData="";
        }
      else if (transData == "back") {
          digitalWrite(motor1N1, LOW); //roda kiri reverse
          digitalWrite(motor1N2, HIGH);
          digitalWrite(motor2N1, LOW); //roda kanan reverse
          digitalWrite(motor2N2, HIGH);                  
          transData="";
        }     
      else if (transData == "left") {
          digitalWrite(motor1N1, LOW); //roda kiri reverse
          digitalWrite(motor1N2, HIGH);
          digitalWrite(motor2N1, HIGH); //roda kanan forward
          digitalWrite(motor2N2, LOW);       
          transData="";
        }
      else if (transData == "right") {
          digitalWrite(motor1N1, HIGH); //roda kiri forward
          digitalWrite(motor1N2, LOW);
          digitalWrite(motor2N1, LOW); //roda kanan reverse
          digitalWrite(motor2N2, HIGH);          
          transData="";
        }         
      else if (transData == "stop") {
          digitalWrite(motor1N1, LOW); //roda kiri
          digitalWrite(motor1N2, LOW);
          digitalWrite(motor2N1, LOW); //roda kanan
          digitalWrite(motor2N2, LOW);                    
          transData="";
        }    



      if (transData == "LampuOn"){ // led on
           digitalWrite(lampuDepan, HIGH);      
           transData="";
        }
      else if (transData == "LampuOff"){ // led off
          digitalWrite(lampuDepan, LOW);       
          transData="";
        } 



      if (transData == "kiri"){ //servo to the left
           myservo.write(45);
           transData="";
        }
      else if (transData == "lurus"){ //servo mid
          myservo.write(90); 
          transData="";
      }        
      else if (transData == "kanan"){ //servo the right
          myservo.write(135); 
          transData="";
      }
     }              
}
