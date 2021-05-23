/*feel free to contact
 * sreeramaj53@gmail.com
 * www.youtube.com/ZenoModiff
 * last updated - time 11:26am - date 12 may 2021
 */

#include <SPI.h>
#include <LoRa.h>

#include "DHT.h"
#include <Adafruit_BMP280.h>

#define DHTPIN 7
#define DHTTYPE DHT11
Adafruit_BMP280 bmp; 

float Pressure;
float Altitude;
int ldr = 4;
int counter = 0;
int Dummyvalue;

DHT dht(DHTPIN, DHTTYPE);
long randNumber; //Create Random Number To Avoid Transmission Loss For First Digit

void setup() 
{
  Serial.begin(115200);
  
 randomSeed(analogRead(0));
 dht.begin();
 
if (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1);
  }

   pinMode(ldr, OUTPUT);
  while (!Serial);
  
  Serial.println(" Lora Weather Station By ZenoModiff ");

  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
  }
  else
  {
   Serial.println("Starting LoRa Sucesses!");
  }
}
void loop()
{
 Serial.println();
 Serial.print("Sending packet: ");
 Serial.println(counter);
 randNumber = random(1000);

 
 int randNumber = random(100); Dummyvalue = randNumber;
 double ldrvalue = analogRead(ldr);
 float h = dht.readHumidity();
 float t = dht.readTemperature();
 float f = dht.readTemperature(true);
 float pressure = (bmp.readPressure()/100); Pressure = pressure;
 int altitude =  (bmp.readAltitude(1019.66)); Altitude = altitude; 
  

  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  String Datastring = String(Dummyvalue) + (";") + String(t) + (";") + String(h) + (";") + String(ldrvalue) + (";") + String (Pressure) + (";") + String (Altitude);
 
  Serial.println(Datastring);
  LoRa.beginPacket();      
  LoRa.print(Datastring);
  LoRa.print(counter);
  LoRa.endPacket();
  counter++;
  
  delay(3000);
  
}
