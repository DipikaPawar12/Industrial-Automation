//This code is in continuation with previous code, we have
//assumed that the total number of bottles filled in a day is
//150.
#include <SoftwareSerial.h>
int count = 150;
SoftwareSerial mySerial(9, 10);

void setup() {
mySerial.begin(9600);
Serial.begin(9600);
delay(100);
}
void loop() {
if (Serial.available()>0) {
switch(Serial.read) {
case 's': SendMessage();
break;
case 'r’: ReceiveMessage();
break;
}
}
if (mySerial.available()>0) {
Serial.write(mySerial.read());
}
}
void SendMessage() {
mySerial.println("AT+CMGF=1");
delay(1000);
mySerial.println("AT+CMGS=\"+919979481706\"\r");
delay(1000);
mySerial.println("Total number of bottles filled today : " + count);
delay(100);
mySerial.println((char)26);
delay(1000);
}
void ReceiveMessage() {
mySerial.println("AT+CNMI=2,2,0,0,0");
delay(1000);
}
