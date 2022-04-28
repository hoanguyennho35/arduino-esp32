#define but 27
int a=0;
byte sl=false;
void IRAM_ATTR ngat(){
  if(sl){
  Serial.printf("so lan nhan %d\n",++a);
    sl=false;
    }
  }
void setup(){
  Serial.begin(9600);
  pinMode(but,INPUT);
  attachInterrupt(but,ngat,RISING);
  }
void loop(){
  if(!sl){
  delay(1000);sl=true;}
  }
