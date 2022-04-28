/***************************************************
  Adafruit MQTT Library FONA Example

  Designed specifically to work with the Adafruit FONA
  ----> http://www.adafruit.com/products/1946
  ----> http://www.adafruit.com/products/1963
  ----> http://www.adafruit.com/products/2468
  ----> http://www.adafruit.com/products/2542

  These cellular modules use TTL Serial to communicate, 2 pins are
  required to interface.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/
#include <Adafruit_SleepyDog.h>
#include <SoftwareSerial.h>
#include "Adafruit_FONA.h"
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_FONA.h"

/*************************** FONA Pins ***********************************/

// Default pins for Feather 32u4 FONA
#define FONA_RX  11
#define FONA_TX  10
#define FONA_RST 4
SoftwareSerial fonaSS = SoftwareSerial(FONA_TX, FONA_RX);

Adafruit_FONA fona = Adafruit_FONA(FONA_RST);

/************************* WiFi Access Point *********************************/

  // Optionally configure a GPRS APN, username, and password.
  // You might need to do this to access your network's GPRS/data
  // network.  Contact your provider for the exact APN, username,
  // and password values.  Username and password are optional and
  // can be removed, but APN is required.
#define FONA_APN       "M-WAP"
#define FONA_USERNAME  ""
#define FONA_PASSWORD  ""

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      ""
#define AIO_SERVERPORT  
#define AIO_USERNAME    ""
#define AIO_KEY         ""

/************ Global State (you don't need to change this!) ******************/

// Setup the FONA MQTT class by passing in the FONA class and MQTT server and login details.
Adafruit_MQTT_FONA mqtt(&fona, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

// You don't need to change anything below this line!
#define halt(s) { Serial.println(F( s )); while(1);  }

// FONAconnect is a helper function that sets up the FONA and connects to
// the GPRS network. See the fonahelper.cpp tab above for the source!
boolean FONAconnect(const __FlashStringHelper *apn, const __FlashStringHelper *username, const __FlashStringHelper *password);

/****************************** Feeds ***************************************/
void pupblic();       //public tu server ve client
void vong();
uint32_t a=0;         //public len temp
char x;
int k=0;            // luu trang thai on/off
// Setup a feed called 'Temp' for publishing.
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
Adafruit_MQTT_Publish  lcd = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/temp");

// Setup a feed called 'LED' for subscribing to changes.
Adafruit_MQTT_Subscribe status1 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/status");

Adafruit_MQTT_Subscribe speed1 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/speed");

/*************************** Sketch Code ************************************/

// How many transmission failures in a row we're willing to be ok with before reset
uint8_t txfailures = 0;
#define MAXTXFAILURES 3

void setup() {
  pinMode(12,OUTPUT);    //dieu khien relay
  while (!Serial);

  // Watchdog is optional!
  //Watchdog.enable(8000);
  
  Serial.begin(9600);

  Serial.println(F("Adafruit FONA MQTT demo"));
 mqtt.subscribe(&speed1);
  mqtt.subscribe(&status1);
 

  Watchdog.reset();
  delay(5000);  // wait a few seconds to stabilize connection
  Watchdog.reset();
  
  // Initialise the FONA module
  while (! FONAconnect(F(FONA_APN), F(FONA_USERNAME), F(FONA_PASSWORD))) {
    Serial.println("Retrying FONA");
  }

  Serial.println(F("Connected to Cellular!"));

  Watchdog.reset();
  delay(5000);  // wait a few seconds to stabilize connection
  Watchdog.reset();
  MQTT_connect();
  a=0;pupblic();
}


void loop() {
  // Make sure to reset watchdog every loop iteration!
  Watchdog.reset();

  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  MQTT_connect();

  Watchdog.reset();
  // Now we can publish stuff!
  Adafruit_MQTT_Subscribe *subscription1;
  while ((subscription1 = mqtt.readSubscription(5000))) {
    if (subscription1 == &speed1 && k==1) {
      Serial.print(F("Got: "));
      Serial.print((char *)speed1.lastread);
      vong();
    pupblic();  
    }
   if (subscription1 == &status1) {
      Serial.print(F("Got: "));
      Serial.println((char *)status1.lastread);
       if(status1.lastread[1]=='N') {k=1;digitalWrite(12,HIGH);Serial.println(F("high led!"));Serial.println("high led");vong();pupblic();} // bat den
       if(status1.lastread[1]=='F')                // tat den
       {k=0;digitalWrite(12,LOW);Serial.println(F("low led!"));Serial.println("low led");a=0;pupblic();}
    }
  delay(5000);
  Watchdog.reset();
  }
  // ping the server to keep the mqtt connection alive, only needed if we're not publishing
  //if(! mqtt.ping()) {
  //  Serial.println(F("MQTT Ping failed."));
  //}

}
void vong(){
    x=(char)speed1.lastread[0];
      switch(x){
      case '0':
          analogWrite(3,0)  ;Serial.println("case 0");a=0;break;
      case '2':
          analogWrite(3,51);Serial.println("case 20");a=20; break;
      case '4':
          analogWrite(3,102);Serial.println("case 40");a=40;break;
      case '6':
          analogWrite(3,153);Serial.println("case 60");a=60;break;
      case '8':
          analogWrite(3,204);Serial.println("case 80");a=80;break;
      case '1':
          analogWrite(3,255);Serial.println("case 100");a=100;break;
      default:
          break;
      }
  }
void pupblic(){
    Watchdog.reset();
   Serial.print(F("\nSending toc do val "));
  Serial.print(a);
  if (! lcd.publish(a)) {
    Serial.println(F("Failed"));
    txfailures++;
  } else {
    Serial.println(F("OK!"));
    txfailures = 0;
  }Watchdog.reset();
}
// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);  // wait 5 seconds
  }
  Serial.println("MQTT Connected!");delay(2000);
}
