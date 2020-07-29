#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int count;
int relay=7;
int ir = 3;
const int motorPin1 = 9;
const int motorPin2 = 10;
int prev = 1;
int curr = 1;
int counter = 0;
boolean solenoid_on = false;
void setup() {
lcd.begin(16, 2);
Serial.begin(9600);
pinMode(ir, INPUT);
pinMode(relay,OUTPUT);
pinMode(motorPin1, OUTPUT);
pinMode(motorPin2, OUTPUT);

pinMode(4,OUTPUT);
pinMode(2,OUTPUT);
lcd.print(“Bottles filled : “);
}
void loop() {
lcd.setCursor(0, 1);
int curr = digitalRead(ir);
if (curr != prev) {
if (curr == 0) {
counter++;
Serial.println("Obstacle Detected...!");
Serial.println(counter);
lcd.print(counter);
}
prev_state = curr_state;
}
delay(100);
if (solenoid_on) {
delay(6000);
analogWrite(motorPin1, 0);
analogWrite(motorPin2, 0);
solenoid_on = false;
}
digitalWrite(relay,LOW);
analogWrite(motorPin1, 180);
analogWrite(motorPin2, 0)
}
