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
     if (recado[0] == '1')
    {
      if(recado[1] == '1')
      {
        digitalWrite(16, HIGH);
      }
      else if (recado[1] == '2')
      {
        digitalWrite(17, HIGH);
      }
      else if (recado[1] == '3')
      {
        digitalWrite(18, HIGH);
      }
      else if(recado[1] == '4')
      {
        digitalWrite(19, HIGH);
      }
      else if (recado[1] == '5')
      {
        digitalWrite(21, HIGH);
      }
      else if (recado[1] == '6')
      {
        digitalWrite(22, HIGH);
      }
    }
     if (recado[0] == '0')
    {
      if(recado[1] == '1')
      {
        digitalWrite(16, LOW);
      }
      else if (recado[1] == '2')
      {
        digitalWrite(17, LOW);
      }
      else if (recado[1] == '3')
      {
        digitalWrite(18, LOW);
      }
      else if(recado[1] == '4')
      {
        digitalWrite(19, LOW);
      }
      else if (recado[1] == '5')
      {
        digitalWrite(21, LOW);
      }
      else if (recado[1] == '6')
      {
        digitalWrite(22, LOW);
      }
    }
}

void setup()
{
  pinMode(16,OUTPUT);
  pinMode(17,OUTPUT);
  pinMode(18,OUTPUT);
  pinMode(19,OUTPUT);
  pinMode(21,OUTPUT);
  pinMode(22,OUTPUT);
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Serial.println("Conectando com a rede WiFi..");

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }

  Serial.println("\nWiFi Conectado");
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
  client.subscribe("teste");
}

void loop()
{
  client.loop();
}
