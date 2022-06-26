/*
 * This is a simple example show the Heltec.LoRa sended data in OLED.
 */

#include "heltec.h"

#define BAND    915E6  //you can set band here directly,e.g. 868E6,915E6

unsigned int counter = 0;
String rssi = "RSSI --";
String packSize = "--";
String packet ;

void setup()
{
   //WIFI Kit series V1 not support Vext control
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.Heltec.Heltec.LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);
 
  Heltec.display->init();
  Heltec.display->clear();
  // Heltec.display->flipScreenVertically();  
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawString(0, 0, "LoRa Init - Success");
  Heltec.display->display();
  delay(1000);
}

void loop()
{
  Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawString(0, 10, "Sending message");
  Heltec.display->drawString(0, 20, String(counter));
  Heltec.display->display();

  // send packet
  LoRa.beginPacket();
  delay(1000);
/*
 * LoRa.setTxPower(txPower,RFOUT_pin);
 * txPower -- 0 ~ 20
 * RFOUT_pin could be RF_PACONFIG_PASELECT_PABOOST or RF_PACONFIG_PASELECT_RFO
 *   - RF_PACONFIG_PASELECT_PABOOST -- LoRa single output via PABOOST, maximum output 20dBm
 *   - RF_PACONFIG_PASELECT_RFO     -- LoRa single output via RFO_HF / RFO_LF, maximum output 14dBm
*/
  LoRa.setTxPower(15,RF_PACONFIG_PASELECT_PABOOST);
  LoRa.print("Message number: ");
  LoRa.print(counter);
  LoRa.endPacket();

  counter++;
}
