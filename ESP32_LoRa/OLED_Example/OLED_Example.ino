/*
 * 
 * WIFI_Kit_32 factory test code and Basic OLED function test;
 * by Jessamine Azevedo
 * 
 */

#include "heltec.h"

void OLEDWrite(void)
{
  Heltec.display -> setFont(ArialMT_Plain_16);
  digitalWrite(LED,HIGH);
	Heltec.display -> drawString(0, 30, "LED ON");
	Heltec.display -> display();
  Heltec.display -> clear();
  delay(1000);

  digitalWrite(LED,LOW);
	Heltec.display -> drawString(0, 30, "LED OFF");
	Heltec.display -> display();
	Heltec.display -> clear();
  delay(1000);

}

void setup()
{
	pinMode(LED,OUTPUT);
	
	Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Enable*/, true /*Serial Enable*/);

	Heltec.display->clear();
}

void loop()
{
	OLEDWrite();
}
