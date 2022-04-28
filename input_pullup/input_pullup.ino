int a=0;
void setup() {
  // put your setup code here, to run once:
pinMode(2,INPUT_PULLUP);
Serial.begin(9600);
attachInterrupt(0,tat,RISING);
cli();
TCCR1A =0;
TCCR1B = 0;
TIMSK1=0;

TCCR1B|= (1<<CS10)|(1<<CS12)|(1<<WGM12);  //mode 4 bo chia truoc 1024
OCR1A=15626;
sei();
}
ISR (TIMER1_COMPA_vect){
  a++;if(a==10){
    Serial.write("tat\n");a=0;
    TIMSK1= 0;
    }
    else{
      Serial.write("mo\n");
      }
  }
void tat(){
  TIMSK1 = (1<<OCIE1A);
  if(a==0){
    TCNT1=0;
    }
  }
void loop() {
  // put your main code here, to run repeatedly:
}
