/*
 * This is a simple example show the Heltec.LoRa recived data in OLED.
 */
#include "heltec.h" 

#define BAND    915E6  //you can set band here directly,e.g. 868E6,915E6
String rssi = "RSSI --";
String packSize = "--";
String packet ;

void callback(int packetSize)
{
  packet ="";
  packSize = String(packetSize,DEC);
  for (int i = 0; i < packetSize; i++)
  {
    packet += (char) LoRa.read();
  }
  Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawStringMaxWidth(0 , 26 , 128, packet);
  Heltec.display->display();
  
}

void setup()
{ 
   //WIFI Kit series V1 not support Vext control
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.Heltec.Heltec.LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);
 
  Heltec.display->init();
  // Heltec.display->flipScreenVertically();
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->clear();
  Heltec.display->drawString(0, 0, "LoRa Init -> Success!");
  Heltec.display->drawString(0, 10, "Wait for incoming data...");
  Heltec.display->display();
  delay(1000);
  
  LoRa.receive();
}

void loop()
{
  int packetSize = LoRa.parsePacket();
  if (packetSize)
  {
    callback(packetSize);
  }
  delay(10);
}
