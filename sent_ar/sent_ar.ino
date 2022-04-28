char buff;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial2.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
if(Serial.available()){
  while(Serial.available()){
    buff=Serial.read();
    }
  Serial2.write("ON");
  Serial.write("goi\n");
  }
 delay(1000);
}
