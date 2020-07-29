#include <dht.h>
#include <LiquidCrystal.h>
dht.DHT;
#define DHT11 PIN 7
void setup() {
serial.begin(9600);

lcd.begin(16, 2);
lcd.print("hello, world!");
pinMode(buz,OUTPUT);
}
void loop() {
float h=dht.readHumidity();
float t= dht.readTemperature();
int buz=8;
int chk.DHT.Read11(DHT11_PIN);
lcd.setCursor(0, 0);
lcd.print("Temperature =");
lcd.print(t);
lcd.setCursor(0,1);
lcd.print("Humidity =");
lcd.print(h);
delay(1000);
if (t>25) {
tone(buz,1000);
delay(1000);
}
else {
noTone(buz);
}
}
