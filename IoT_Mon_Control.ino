#define BLYNK_PRINT Serial
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#include <DHT.h>

char auth[] = "b3cda8def9554d959e7be6c8667018ed"; //enter your token
char ssid[] = "duinoelektronik";  //Enter your WIFI Name
char pass[] = "usbasp88";  //Enter your WIFI Password

#define DHTPIN 4 //dht11 connect to pin GPIO4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

SimpleTimer timer;

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Blynk.virtualWrite(V1, h);  //V1 is for Humidity
  Blynk.virtualWrite(V2, t);  //V2 is for Temperature
}

void setup()
{
  Serial.begin(9600);
  pinMode(D1,OUTPUT); //relay GPIO 5
  pinMode(D5,OUTPUT); //led1 GPIO 13
  pinMode(D6,OUTPUT); //buzzer GPIO 12
  pinMode(D7,OUTPUT); //led2 GPIO 14

  digitalWrite(D1,LOW);
  digitalWrite(D5,LOW);
  digitalWrite(D6,LOW);
  digitalWrite(D7,LOW);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run(); // Initiates Blynk  
  timer.run(); // Initiates SimpleTimer
}
