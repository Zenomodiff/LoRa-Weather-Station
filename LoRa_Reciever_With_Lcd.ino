/*feel free to contact
 * sreeramaj53@gmail.com
 * www.youtube.com/ZenoModiff
 * last updated - time 11:28am - date 12 may 2021
 */

#include <Wire.h> 
#include <SPI.h>
#include <LoRa.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() 
{  
  
  Serial.begin(115200);

  lcd.begin();
  lcd.setCursor(0,0);
  lcd.print("LoRa Weather");
  lcd.setCursor(0,3);
  lcd.print("Station");
  delay(2000);
  lcd.clear();
  lcd.print("By");
  lcd.setCursor(0,3);
  lcd.print("Zeno Modiff");
  delay (2000);
  while (!Serial);

  Serial.println("LoRa Receiver By Zeno Modiff");

  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  
  String packet = "";
  
  int packetSize = LoRa.parsePacket();
  if (packetSize) {

    Serial.print("Received packet :-- ");

    while (LoRa.available()) {
    
    packet = LoRa.readString();
    }
    
    Serial.println(packet);
    Serial.println();

int firstcommaIndex   = packet.indexOf(';');
int secondCommaIndex  = packet.indexOf(';', firstcommaIndex+1);
int thirdCommaIndex   = packet.indexOf(';', secondCommaIndex+1);
int fourthCommaIndex  = packet.indexOf(';', thirdCommaIndex+1);   
int fifthCommaIndex   = packet.indexOf(';', fourthCommaIndex+1);
int sixthCommaIndex   = packet.indexOf(';', fifthCommaIndex+1);

String firstValue  =  packet.substring( 0, firstcommaIndex);
String secondValue =  packet.substring(firstcommaIndex+1, secondCommaIndex);
String thirdValue  =  packet.substring(secondCommaIndex+1, thirdCommaIndex);
String fourthValue =  packet.substring(thirdCommaIndex +1, fourthCommaIndex);
String fifthValue  =  packet.substring(fourthCommaIndex+1, fifthCommaIndex);
String sixthValue  =  packet.substring(fifthCommaIndex+1,  sixthCommaIndex);

Serial.print("Temp:-"); Serial.println(secondValue);
Serial.print("Humi:-"); Serial.println(thirdValue);
Serial.print("Ldr:-"); Serial.println(fourthValue); 
Serial.print("Pressure:-"); Serial.println(fifthValue);  
Serial.print("Altitude:-"); Serial.println(sixthValue); 
Serial.println();

/*since we can't print the first digit 
it is a dummy value sent by the LoRa String 
in case of transmission Loss*/

lcd.clear(); lcd.setCursor(0,0);
lcd.print("Temp:-"); lcd.println(secondValue);
delay(2000);

lcd.clear(); lcd.setCursor(0,0);
lcd.print("Humi:-"); lcd.println(thirdValue);
delay(2000);

lcd.clear(); lcd.setCursor(0,0);
lcd.print("Ldr:-"); lcd.println(fourthValue);
delay(2000);

lcd.clear(); lcd.setCursor(0,0);
lcd.print("Pres:-"); lcd.println(fifthValue);
delay(2000);

lcd.clear(); lcd.setCursor(0,0);
lcd.print("Alti:-"); lcd.println(sixthValue);
delay(2000);

}
}
