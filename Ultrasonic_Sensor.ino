/*-------------------------------------------------------------------------------
* Projeto: Sensor Ultrassônico
* Saiba mais: https://elcereza.com/sensor-ultrassonico/
* Disponibilizado por: https://elcereza.com/
* Autor: Gustavo Cereza
---------------------------------------------------------------------------------*/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 

#define OLED_RESET     -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#include <Ultrasonic.h>
#define TRIGGER_PIN  5                                                             // Pino digital 5 que vai conectado ao trigger do sensor
#define ECHO_PIN     6                                                             // Pino digital 6 que vai conectado ao echo do sensor

Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);                                      // Atribui a pinagem 

void setup()
{
  Serial.begin(9600);
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {                                 // Caso o display não funcione, teste com outro endereço i2c
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); 
  }
  
  display.display();
  delay(2000); 
  display.clearDisplay();
}

void loop()
{
  float cmMsec, inMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);                           // Obtem o valor em 'cm' da distância
  display.clearDisplay();
  display.setTextSize(2); 
  display.setTextColor(WHITE);
  display.setCursor(10, 10);
  display.print(F("CM: "));
  display.println(cmMsec);                                                         // Exibe a distância em 'cm'
  display.display();      
  delay(100);
}
