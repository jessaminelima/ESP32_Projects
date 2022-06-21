/*
 * 
 * WIFI connection and Basic OLED function test;
 * by Jessamine Azevedo
 * 
 */

#include "heltec.h"
#include "WiFi.h"

void WIFISetUp(void)
{
	// Set WiFi to station mode and disconnect from an AP if it was previously connected
	WiFi.disconnect(true);
	delay(1000);
	WiFi.mode(WIFI_STA);
	WiFi.setAutoConnect(true);
	WiFi.begin("LSE","HubLS3s2");
	delay(100);

	byte count = 0;
	while(WiFi.status() != WL_CONNECTED && count < 10)
	{
		count ++;
		delay(500);
		Heltec.display -> drawString(0, 0, "Connecting...");
		Heltec.display -> display();
	}
	Heltec.display -> clear();
	if(WiFi.status() == WL_CONNECTED)
	{
		Heltec.display -> drawString(0, 0, "Connected.");
		Heltec.display -> display();
	}
	else
	{
		Heltec.display -> clear();
		Heltec.display -> drawString(0, 0, "Connection Failed");
		Heltec.display -> display();
	}
	Heltec.display -> drawString(0, 10, "WIFI Setup done");
	Heltec.display -> display();
}

void setup()
{
	pinMode(LED,OUTPUT);
	
	Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Enable*/, true /*Serial Enable*/);

	Heltec.display->clear();
	WIFISetUp();
  
  WiFi.disconnect(true);
  delay(1000);
  WiFi.mode(WIFI_STA);
  WiFi.setAutoConnect(true);
}

void loop()
{

}
