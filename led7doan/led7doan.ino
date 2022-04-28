char code7seg[]={0xEE,0x22,0x7C,0x76,0xB2,0xD6,0xDE,0x72,0xFE,0xF6};
char chan[]={3,4,5,6,7,8,9,10};
int k=0;
void go(char dat)
{
   for(int i=0;i<8;i++){
      if(dat&0x80)   digitalWrite(chan[i],HIGH);
      else            digitalWrite(chan[i],LOW);
      dat=dat<<1;
    }
}
void setup() {
  // put your setup code here, to run once:
for(int i=0;i<8;i++)
   {
    pinMode(chan[i],OUTPUT);  
    }  
}

void loop() {
  // put your main code here, to run repeatedly:
go(code7seg[k]);
delay(1000);
k++;
if(k==10)    k=0;
}
