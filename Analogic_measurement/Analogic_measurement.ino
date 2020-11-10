/*****************************************************************************
* Conversor Analógico Digital
* Microcontrolador: ESP32
*****************************************************************************/


#define ANALOG_PIN 36
int readed_value = 0;
float value = 0;
void setup()
{
  Serial.begin(115200); // Configurando o baudrate da porta serial
  readed_value = analogRead(ANALOG_PIN);// Lendo o ADC selecionado (GPIO 36)
}
 
void loop()
{
  for(int i = 0; i < 100; i++) // Adicionando filtro de média no valor lido
    {
      readed_value = (readed_value*9+analogRead(ANALOG_PIN))/10;  
    }
  value = 3.3 * readed_value/4096; // Convertendo o valor digital em tensão
  Serial.print("A tensão lida é: ");
  Serial.print(value); // Imprimindo na serial o valor lido
  Serial.println("V");
  delay(500);  // Tempo em ms para repetir  
}
