/*
 * 
 * All the resources for this project: https://github.com/ayanbabi90/rfid
 * Modified by Ayan Chakraborty
 * contact at: ayan.babi90@gmail.com
 */
 
#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
#define Buzzer 3
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

// LED indicators released or denied access 
int led_granted = 5; //for Green led on pin ~5
int led_denied = 6;  // for Red led on pin ~6
int buzzer_beep = 3; // for buzzer on pin ~3
 
void setup() 
{
  pinMode (led_granted, OUTPUT);
  pinMode (led_denied, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  mfrc522.PCD_DumpVersionToSerial(); // Initate frimware version of your rfid module
  Serial.println("Swipe your card to the get acess");
  Serial.println();
}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "40 17 14 19" ) // Put your RFID UID Card No here to get acess
  {
    digitalWrite (led_granted, HIGH);
    Serial.println("Authorized access");
    Serial.println();
    digitalWrite (led_granted, LOW);
    for (int y = 0; y < 3; y++){
      digitalWrite (Buzzer, HIGH) ;// Buzzer On
      delay (50) ;// Delay 1ms 
      digitalWrite (Buzzer, LOW) ;// Buzzer Off
      delay (50) ;// delay 1ms
}
    delay(1000);
  }
 else   {
  Serial.println(" Access denied");
  for (int i = 1; i <5; i ++)  // Flashing Red LED 
    {
      digitalWrite (led_denied, HIGH);
      delay (100);
      digitalWrite (led_denied, LOW);
      delay (100);
      for (int y = 0; y < 3; y++){
        digitalWrite (Buzzer, HIGH) ;// Buzzer On
        delay (200) ;// Delay 1ms 
        digitalWrite (Buzzer, LOW) ;// Buzzer Off
        delay (200) ;// delay 1ms
        }
    }
  Serial.println();
  delay(1000);
  }
} 
