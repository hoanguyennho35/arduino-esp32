int a=0;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(8,INPUT_PULLUP);
cli();
TCCR1A =0;
TCCR1B = 0;
TIMSK1=0;

TCCR1B= 0b11001101;  //mode 4 bo chia truoc 1024
OCR1A=15626;
TIMSK1= (1<<ICIE1);
sei();
}
ISR (TIMER1_COMPA_vect){
  a++;if(a==10){
    Serial.write("tat\n");a=0;TIMSK1=(1<<ICIE1);
    }else 
    Serial.write("mo\n");
  }
 ISR (TIMER1_CAPT_vect){
  Serial.write("nhan nut\n");
  TIMSK1|=(1<<OCIE1A);
  }
void loop() {
  // put your main code here, to run repeatedly:

}
