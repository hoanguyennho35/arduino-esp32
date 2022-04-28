#include <avr/interrupt.h>
#define led 13
byte boo=false;char a;
volatile int tem=0;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
cli();
TCCR1A =0;
TCCR1B = 0;
TIMSK1=0;

TCCR1B|= (1<<CS10)|(1<<CS12)|(1<<WGM12);  //mode 4 bo chia truoc 1024
OCR1A=15626;
TIMSK1= (1<<OCIE1A);
sei();
pinMode(led,OUTPUT);
}

ISR (TIMER1_COMPA_vect){
  boo = ~boo;
  digitalWrite(led,boo);
  TIMSK1 = 0;
  }

  
void loop() {
  // put your main code here, to run repeatedly:
if(Serial.available()){
  a=Serial.read();
  TIMSK1=(1<<OCIE1A);
  }
}
