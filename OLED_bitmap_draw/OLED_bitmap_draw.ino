#include <Arduino.h>
#include <heltec.h>
#include "bitmap_toy.h"

// Defina o tamanho da tela OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

void opened_frame()
{
  Heltec.display->drawXbm(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, eyes_open);
  Heltec.display->display();
}


void closed_frame()
{
  Heltec.display->drawXbm(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, eyes_closed);
  Heltec.display->display();
}


void look_left_frame()
{
  Heltec.display->drawXbm(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, eyes_left);
  Heltec.display->display();
  delay(200);
  Heltec.display->clear();
  opened_frame();
  delay(200);
  Heltec.display->clear();
}


void look_right_frame()
{
  Heltec.display->drawXbm(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, eyes_right);
  Heltec.display->display();
  delay(200);
  Heltec.display->clear();
  opened_frame();
  delay(200);
  Heltec.display->clear();
}


void blink_frame()
{
  closed_frame();
  delay(200);
  Heltec.display->clear();
  opened_frame();
  delay(200);
  Heltec.display->clear();
  closed_frame();
  delay(200);
  Heltec.display->clear();
  opened_frame();
}


void setup()
{
  // Inicie o display OLED
  Heltec.begin(true /* Display */, false /* LoRa */, true /* Serial */);
  Heltec.display->clear();
}


void loop()
{
  opened_frame();
  delay(2000);
  Heltec.display->clear();

  look_left_frame();
  look_right_frame();
  blink_frame();
}
