#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

MFRC522 mfrc522(10, 9);
int led1 = 7;
int led2 = 6;
int led3 = 8;
int led4 = 4;
int led5 = 3;
int buzzerPin = 5;
String tagUID = "29 B9 ED 23";
void setup() {
pinMode(buzzer, OUTPUT);
pinMode(led1, OUTPUT);
pinMode(led2, OUTPUT);
pinMode(led3, OUTPUT);
pinMode(led4, OUTPUT);
pinMode(led5, OUTPUT);
lcd.begin();
lcd.backlight();
SPI.begin();
mfrc522.PCD_Init();
lcd.clear();
}
void loop() {
lcd.setCursor(0, 0);
lcd.print(" RFID secured bottle-filler.");
lcd.setCursor(0, 1);
lcd.print(" Show Your Tag ");
if ( ! mfrc522.PICC_IsNewCardPresent()) {
return;
}
if ( ! mfrc522.PICC_ReadCardSerial()) {
return;
}
String tag = "";
for (byte i = 0; i < mfrc522.uid.size; i++) {

tag.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
tag.concat(String(mfrc522.uid.uidByte[i], HEX));
}
tag.toUpperCase();
if (tag.substring(1) == tagUID) {
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Access Granted");
lcd.setCursor(0, 1);
digitalWrite(led1, HIGH);
digitalWrite(led2, HIGH);
digitalWrite(led3, HIGH);
digitalWrite(led4, HIGH);
digitalWrite(led5, HIGH);
lcd.clear();
}
else {
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Wrong Tag Shown");
lcd.setCursor(0, 1);
lcd.print("Access Denied");
digitalWrite(buzzer, HIGH);
delay(3000);
digitalWrite(buzzer, LOW);
lcd.clear();
}
}
