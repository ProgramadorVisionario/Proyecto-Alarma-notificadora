#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;


void setup()
{
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);
  
  
  
  myDFPlayer.setTimeOut(500); //Set serial communictaion time out 500ms
  
  //----Set volume----
  myDFPlayer.volume(30);  //Set volume value (0~30).
  

  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);

 myDFPlayer.next();  
    delay(3000);
  
  

  
}

void loop()
{
  
   static unsigned long timer = millis();
  
  if (millis() - timer > 3000) {
    timer = millis();
    myDFPlayer.next();  //Play next mp3 every 3 second.
  }
  
  
}


