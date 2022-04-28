#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2); 
char t[16]="";
void setup()
{int a=0;
  lcd.init();                    
//  lcd.backlight();
lcd.setCursor(2,0);
  lcd.print("Arduinokit.vn");
  delay(1000);
  lcd.setCursor(0,0);
  lcd.print("Xin chao cac ban");

}

void loop()
{ t[15]=' ';t[0]='a'; delay(500);
  for(int i=1;i<16;i++){
    t[i]='a';t[i-1]=' ';delay(500);lcd.clear();lcd.print(t);
   }
}
