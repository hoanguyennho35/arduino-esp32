#include <SerialCommand.h>
#include <SoftwareSerial.h>
SerialCommand scm;
byte a = false;
#define led 13
void setup() {
  // put your setup code here, to run once:
pinMode(led,OUTPUT);
Serial.begin(9600);
scm.addCommand("led",led_);
}

void loop() {
  // put your main code here, to run repeatedly:
scm.readSerial();

}
void led_(){
  char *arg;
  arg = scm.next();
  Serial.println(arg);
  arg = scm.next();
  Serial.println(arg);
  a=atoi(arg);
  if(a)
{digitalWrite(led,1);Serial.println("true");}
else
{digitalWrite(led,0);Serial.println("False");
}
delay(1000);
  }
