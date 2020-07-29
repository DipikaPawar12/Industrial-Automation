#include <NewPing.h>
#include <EEPROM.h>
#define TRIGGER_PIN 6
#define ECHO_PIN 7
#define MAX_DISTANCE 500
#define RELAYPIN 8
#define EXTRELAYPIN 13
#define BUZZER 9
#define buttonPin 10
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
byte readval;
int addr = 0;
int addr2 = 1;
int flag;
int buttonState = 0;
int percentage;
int SpmpSensorPin = A0;
int SpmpsensorValue = 0;

float val;
float Ta nk Height, MaxWaterLevel, EmptySpace, SonarReading,
ActualReading, Temp;
void setup() {
Serial.begin(9600);
Serial.println(flag);
pinMode(RELAYPIN,OUTPUT);
pinMode(EXTRELAYPIN,OUTPUT);
digitalWrite(RELAYPIN,LOW);
digitalWrite(EXTRELAYPIN,HIGH);
pinMode(BUZZER,OUTPUT);
digitalWrite(BUZZER,LOW);
for (int i=0; i<=5; i++) {
buttonState = digitalRead(buttonPin);
if (buttonState == HIGH) {
TankHeight =sonar.ping_cm();
EEPROM.write(addr, TankHeight);
}
delay(1000);
}
TankHeight= EEPROM.read(addr);
MaxWaterLevel=0.85*TankHeight;
EmptySpace=TankHeight-MaxWaterLevel;
}
void loop() {
delay(50);
SonarReading=sonar.ping_cm();
SpmpsensorValue=analogRead(SpmpSensorPin);
Serial.println(SpmpsensorValue);
Temp= SonarReading-EmptySpace;
ActualReading= MaxWaterLevel-Temp;
percentage=(ActualReading/MaxWaterLevel*100);
if(SpmpsensorValue>=100) {
if(percentage<=20) {

digitalWrite(RELAYPIN,HIGH);
digitalWrite(EXTRELAYPIN,LOW);
flag=1;
EEPROM.write(addr2, flag);
flag= EEPROM.read(addr2);
}
else if(percentage>20 && percentage<=100) {
flag= EEPROM.read(addr2);
if(percentage>20 && percentage<=100 && flag ==1) {
digitalWrite(RELAYPIN,HIGH);
digitalWrite(EXTRELAYPIN,LOW);
}
else if(percentage>20 && percentage<=100 && flag ==0) {
digitalWrite(RELAYPIN,LOW);
digitalWrite(EXTRELAYPIN,HIGH);
}
}
else if(percentage>100) {
delay(500);
digitalWrite(RELAYPIN,LOW);
digitalWrite(EXTRELAYPIN,HIGH);
flag=0;
EEPROM.write(addr2, flag);
flag= EEPROM.read(addr2);
}
}
else if(SpmpsensorValue<=100) {
flag= EEPROM.read(addr2);
if(flag==1) {
digitalWrite(BUZZER,HIGH);
digitalWrite(RELAYPIN, LOW);
digitalWrite(EXTRELAYPIN, HIGH);
delay(100);
digitalWrite(BUZZER,LOW);
delay(100);
}
}
}
