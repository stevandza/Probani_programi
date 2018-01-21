#include <avr/interrupt.h>   

#define T2Speed 50

const int LED = 13;
const int channelA = 2;
const int channelB = 3;

volatile byte tmrCount = 0;
//Timer2 overflow interrupt vector handler
ISR(TIMER2_OVF_vect) {
  TCNT2 = T2Speed;      //reset timer
  digitalWrite(LED,HIGH);
  switch (tmrCount) {
  case 0:
    digitalWrite(channelA,HIGH);
    break;
  case 1:
    digitalWrite(channelB,HIGH);
    break;
  case 2:
    digitalWrite(channelA,LOW);
    break;
  case 3:
    digitalWrite(channelB,LOW);
  }
  tmrCount++;
  if (tmrCount >= 4) {
    tmrCount = 0;
  }
  digitalWrite(LED,LOW);
  TIFR2 = 0x00;
};  

void setup() {
  Serial.begin(115200);
  pinMode(LED,OUTPUT);   // UNO LED, just for show
  pinMode(channelA,OUTPUT);
  pinMode(channelB,OUTPUT);

  TCCR2A = 0;           //Timer2 Settings: WGM mode 0
  TCCR2B = _BV(CS22);   //Timer2 Settings: Timer Prescaler /64
  TIMSK2 = _BV(TOIE2);  //Timer2 Overflow Interrupt Enable 
  TCNT2 = T2Speed;      //reset timer
}

void loop() {
}

