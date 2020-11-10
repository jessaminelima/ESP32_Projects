#include <WiFi.h>

const char* ssid = "SSID";
const char* password =  "Password";

void setup()
{
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Serial.println("Conectando com a rede WiFi...");

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }

  Serial.println("WiFi Conectado");
  Serial.print("IP:");
  Serial.print(WiFi.localIP());
}

void loop()
{
  if ((WiFi.status() == WL_CONNECTED))
  {
    Serial.println("\nVc pode testar");
    delay(5000);
  }
  else
  {
    Serial.println("\nSem conexao");
  }
}
