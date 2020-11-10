#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "SSID";
const char* password =  "Password";
const char* mqttServer = "192.168.1.112";
const int mqttPort = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topico, byte* recado, unsigned int tamanho)
{
 
  Serial.print("Messagem do topico: ");
  Serial.println(topico);
  Serial.print("Messagem:");
  for (int i = 0; i < tamanho; i++)
  {
    Serial.print((char)recado[i]);
  }
  Serial.println("\n-----------------------");
 
}

void setup()
{
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Serial.println("Conectando com a rede WiFi..");

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }

  Serial.println("\nWiFi Conectado");
  Serial.print("IP:");
  Serial.print(WiFi.localIP());
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
  
  while (!client.connected())
  {
    Serial.println("\nConectando ao MQTT...");
    if (client.connect("ESP32Client"))
    {
      Serial.println("Conectado");
    }
    else
    {

      Serial.print("\nFalha na Conexao");
      Serial.print(client.state());
      delay(2000);

    }
  }
  client.publish("teste", "Hello World");
  client.subscribe("teste");
}

void loop()
{
  client.loop();
}
