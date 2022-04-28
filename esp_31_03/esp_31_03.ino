char a;
char *buff;
int k=0;
void setup() {
  // put your setup code here, to run once:
Serial2.begin(9600);
Serial.begin(9600);
buff=(char*)calloc(10,sizeof(char));
}

void loop() {
  // put your main code here, to run repeatedly:
if(Serial.available()){
  buff[k++]=Serial.read();
  if(buff[k-1]=='\r')
  {
    Serial.write(buff);
    Serial2.write(buff);delay(3);
    k=0;free(buff);buff=(char*)calloc(10,sizeof(char));
    }
  }
}

