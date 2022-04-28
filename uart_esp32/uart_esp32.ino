char a;
char *buff=NULL;
int k=0;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
buff=(char*)calloc(40,sizeof(char));
}

void loop() {
  // put your main code here, to run repeatedly:
if(Serial.available()){
  while(Serial.available()){
    buff[k++]=Serial.read();
    Serial.println("trong ham");
    }
    Serial.println("ngoai ham");
    if(buff[k-1]=='.')
    {buff[k-1]=' ';
    Serial.println(buff);
    free(buff);
    buff=(char*)calloc(40,sizeof(char));
    k=0;}
}}
