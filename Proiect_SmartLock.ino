#include <LiquidCrystal_I2C.h>

#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <Wire.h>
#define SS_PIN 10
#define RST_PIN 2
MFRC522 rfid(SS_PIN, RST_PIN);   // Create MFRC522 instance.
String tagUID = "23 E8 F7 03"; // String to store UID of tag
Servo myservo;
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  // put your setup code here, to run once:
  myservo.attach(6);
  myservo.write(0);
  lcd.init();
  lcd.backlight();
  SPI.begin();      // Initiate  SPI bus
  rfid.PCD_Init();   // Initiate MFRC522
  lcd.setCursor(3,0);
  lcd.print("Smart Lock");
  delay(2000);
  lcd.setCursor(6,1);
  delay(1000);
  lcd.print("By");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Petricele");
  delay(1000);
  lcd.setCursor(4,1);
  lcd.print("Mihaela");
  delay(2000);
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
  lcd.setCursor(0,0);
  lcd.print("Locked Door!");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("Show Your Tag");
  
  // Look for new cards
  if ( ! rfid.PICC_IsNewCardPresent()) 
  {
    delay(500);
    return;
  }
  // Select one of the cards
  if ( ! rfid.PICC_ReadCardSerial()) 
  {
    delay(500);
    return;
  }
  String contentTag= "";
  for (byte i = 0; i < rfid.uid.size; i++) 
  {
     if(rfid.uid.uidByte[i] < 0x10)
     {
        contentTag.concat(String(" 0"));
     }
     else
     {
        contentTag.concat(String(" "));
     }
     contentTag.concat(String(rfid.uid.uidByte[i], HEX));
  }
  contentTag.toUpperCase();
  if (contentTag.substring(1) == tagUID) 
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Access Granted");
    lcd.setCursor(0,1);
    lcd.print("Door Opened");
    myservo.write(180);
    delay(5500);
    lcd.clear();
    myservo.write(0);
    delay(1000);
    lcd.print("Door Closed");
    delay(2000);
    lcd.clear();
  }
 else{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Wrong Tag Shown");
    lcd.setCursor(0,1);
    lcd.print("Access Denied");
    delay(3500);
    lcd.clear();
  }
}
