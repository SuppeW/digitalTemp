#include <dht.h>
#include "SevSeg.h";
#include <ctime>

//sevseg er biblioteket til en 4 digit display. Det jeg ikke skjønner er hvorfor linje 26 ikke funker når linje 27 gjør det..

dht DHT;
SevSeg sevseg;

byte dht_pin = 3;
clock_t begin;
clock_t end;

const double CHECK_TEMP_TIME = 1.5;

void setup() {
  byte numDigits = 4;
  byte digitPins[]={1,2,4,5};
  byte segmentPins[]={6,7,8,9,10,11,12,13};
  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins);
  sevseg.setBrightness(90);
  Serial.begin(9600);
  
  begin = clock();
}

void loop() {
  end = clock();
  
  if (CHECK_TEMP_TIME < (double(end - begin) / CLOCKS_PER_SEC) ){
    int chk = DHT.read11(dht_pin);
    int temp = DHT.temperature;
    if (temp > -1){
      String tempString = String(temp);
      String tempC = String("1" + tempString + "C");
      sevseg.setChars(tempC.c_str());
      
      Serial.println(tempC);
    }
    
    //RESET clock
    begin = clock();
  }
  
  sevseg.refreshDisplay();
}
