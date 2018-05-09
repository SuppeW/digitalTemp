#include <dht.h>
#include "SevSeg.h";


//sevseg er biblioteket til en 4 digit display. Det jeg ikke skjønner er hvorfor linje 26 ikke funker når linje 27 gjør det..

dht DHT;
SevSeg sevseg;

byte dht_pin = 3;

void setup() {
  byte numDigits = 4;
  byte digitPins[]={1,2,4,5};
  byte segmentPins[]={6,7,8,9,10,11,12,13};
  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins);
  sevseg.setBrightness(90);
  Serial.begin(9600);
}

void loop() {
  int chk = DHT.read11(dht_pin);
  int temp = DHT.temperature;
  if (temp > -1){
    String tempString = String(temp);
    String tempC = String("1" + tempString + "C");
    sevseg.setChars(tempC.c_str());
    Serial.println(tempC);
  }
  sevseg.refreshDisplay();
}
