// http://www.bajdi.com
// Sending a struct with the nRF24L01 module
// Data to be sent is the reading of 2 analog pins
// Data received is the analog reading of 2 pins on the other Arduino 
// RADIIIII
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

RF24 radio(7,8);  // make sure this corresponds to the pins you are using
const uint64_t pipes[2] = { 
  0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

const int led = 0;

typedef struct{
  int A;
  int B;
  float C;
  float D;
  char E[20];
}
A_t;

typedef struct{
  int W;
  int X;
  float Y;
  float Z;
  char Q[20];
}
B_t;

A_t duino1;  
B_t duino2; 

void setup()
{
  Serial.begin(57600);
  pinMode(led, OUTPUT);

  
  
  radio.begin();
  
  radio.setChannel(125);
  radio.setPALevel(RF24_PA_MAX);
  
  radio.openWritingPipe(pipes[1]);
  radio.openReadingPipe(1,pipes[0]);
  
  Serial.println(radio.getPALevel()); 
  Serial.println(radio.getChannel());
  Serial.println(radio.getDataRate());  
  Serial.println(radio.getCRCLength());
  }

void loop(void)
{
  // we need data to sent...
  duino1.A = analogRead(A0);
  duino1.B = analogRead(A1);
  duino1.C = analogRead(A0)/102.3;
  duino1.D = analogRead(A1)/102.3;
  memcpy(duino1.E, "POZDRAV OD MEGA", 20);
 
  // end of analog reading

  // radio stuff
  radio.stopListening();
  bool ok = radio.write( &duino1, sizeof(duino1) );
  radio.startListening();

  unsigned long started_waiting_at = millis();
  bool timeout = false;
  while ( ! radio.available() && ! timeout )
    if (millis() - started_waiting_at > 250 )
      timeout = true;

  if ( timeout )
  {
    Serial.println("Failed, response timed out.");
    digitalWrite(led, HIGH);
  }
  else
  {
    radio.read( &duino2, sizeof(duino2) );
    digitalWrite(led, LOW);
  }
  // end of radio stuff
  Serial.print("Velicina paketa za slanje je: ");
  Serial.println(sizeof(A_t));
  // serial print received data 
  Serial.print("duino2.W = ");
  Serial.println(duino2.W);
  Serial.print("duino2.X = ");
  Serial.println(duino2.X);
  Serial.print("duino2.Y = ");
  Serial.println(duino2.Y);
  Serial.print("duino2.Z = ");
  Serial.println(duino2.Z);
  Serial.print("duino2.Q = ");
  Serial.println(duino2.Q);
  // end of serial printing
}
