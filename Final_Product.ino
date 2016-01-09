//--------------------------------------------------------------------------
//Name:  - Senior Design Project of Counting the Crowd entering the Jamaraat
//         area during the Hajj.
//       - Arduino Uno R3 is used as a main microcontroller in the system.  
//       - Assuming a room temp of 25 degrees centigrade.
//Autor:   Ahmed Abdulaziz Abualsaud
//Version: v 1.0
//Date:    Dec, 2, 2015
//--------------------------------------------------------------------------
//Arduino Uno R3 connection:
//        Pin Name - Board Label - Wire Color
//        enP2     - A0          - Green
//        enP3     - A1          - Yellow
const int B        = 13;         //Orange
const int A        = 12;         //White 
const int TRIG     = 11;         //Green
const int D        = 10;         //Orange
const int C        = 9;          //White
const int done     = 8;          //Orange
const int stP1     = 7;          //Black
const int exP1     = 6;          //Red
const int stP2     = 5;          //White
const int exP2     = 4;          //Blue
const int stP3     = 3;          //Yellow
const int exP3     = 2;          //Green

//Declear the Global Variable        
int count = 1;//Control Signal Varaiable

void setup() {
  // Initialize serial communication:
  Serial.begin(9600);
  // Initilaize the pins as In/Out port
  pinMode(TRIG,OUTPUT);
  pinMode(B,OUTPUT);
  pinMode(A,OUTPUT);
  pinMode(C,OUTPUT);
  pinMode(D,OUTPUT);
  pinMode(stP1,INPUT);
  pinMode(exP1,INPUT);
  pinMode(done,OUTPUT);
  pinMode(stP2,INPUT);
  pinMode(exP2,INPUT);
  pinMode(stP3,INPUT);
  pinMode(exP3,INPUT);
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  
  // Initilaize the digital output pins as 0/1
  digitalWrite(TRIG, LOW);
  digitalWrite(B, LOW);
  digitalWrite(A, LOW);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(done, LOW);
  digitalWrite(A0, LOW);
  digitalWrite(A1, LOW); 
  Serial.println("\nArduino Uno R3!");//print a message to know if the serial monitor working correctlly
} 
 
void loop()
{
  //Start sending the control signals to control teh Demultiplixer 
  //and Multiplixer
  switch (count){
  case 1:
  digitalWrite(B, LOW);
  digitalWrite(A, LOW); 
  break;
  case 2:
  digitalWrite(B, LOW);
  digitalWrite(A, HIGH);
  break;
  case 3:
  digitalWrite(B, HIGH);
  digitalWrite(A, LOW);
  break;
  case 4:
  digitalWrite(B, HIGH);
  digitalWrite(A, HIGH);
  break;
  }
  
  //Send teh trigger signal to turn on teh ultrasonic sensor
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  
  //Start communicating with PICs one by one
  //PIC#1
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  while(digitalRead(stP1) == 0);
  delayMicroseconds(0.25);
  while(Serial.read() != 'G');
  Serial.println(Serial.readStringUntil('!'));
  while(digitalRead(exP1) == 0);
  digitalWrite(done,HIGH);
  delayMicroseconds(0.25);
  digitalWrite(done,LOW);
  
  //PIC#2
  digitalWrite(C, HIGH);
  digitalWrite(D, LOW);
  digitalWrite(A0,HIGH);//enP2
  while(digitalRead(stP2) == 0);
  digitalWrite(A0,LOW);//enP2
  delayMicroseconds(0.25);
  while(Serial.read() != 'G');
  Serial.println(Serial.readStringUntil('!'));
  while(digitalRead(exP2) == 0);
  digitalWrite(done,HIGH);
  delayMicroseconds(0.25);
  digitalWrite(done,LOW);
  
  //PIC#3
  digitalWrite(C, LOW);
  digitalWrite(D, HIGH);
  digitalWrite(A1,HIGH);//enP3
  while(digitalRead(stP3) == 0);
  digitalWrite(A1,LOW);//enP3
  delayMicroseconds(0.25);
  while(Serial.read() != 'G');
  Serial.println(Serial.readStringUntil('!'));
  while(digitalRead(exP3) == 0);
  digitalWrite(done,HIGH);
  delayMicroseconds(0.25);
  digitalWrite(done,LOW);
  
  //Increment the conter to switch to the next stage  
  if (count < 4)
    count = count + 1;
  else
    count = 1;
} 

