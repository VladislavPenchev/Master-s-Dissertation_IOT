
#include <SoftwareSerial.h>

#define YELLOW_PIN 5

// create a Software Serial instance for communications with the ESP8266
SoftwareSerial mySerial(10, 11); // RX, TX

void setup() {
  
  mySerial.begin(115200); // init Software Serial
  Serial.begin(9600);   // init normal USB/Hardware Serial

  // initiate all the LED pins
  pinMode(YELLOW_PIN, OUTPUT);
  digitalWrite(YELLOW_PIN, LOW);
}

void loop() {
  // Listen for software Serial messages
  if(mySerial.available()>0){
    unsigned char in = mySerial.read();

    if (in == 100){
      digitalWrite(YELLOW_PIN, HIGH);
      Serial.println(in);
    Serial.println("100");
    }
    
    if(in == 200){
      digitalWrite(YELLOW_PIN, LOW);
      Serial.println(in);
    Serial.println("200");
    }
        
    
  }
}
