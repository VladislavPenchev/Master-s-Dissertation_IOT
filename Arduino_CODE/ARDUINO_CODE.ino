#include <SoftwareSerial.h>
#include <matlab.h>

#define LED_PIN 5
#define LDR_PIN A0

const int NUMBER_SIZE_ARRAY_SEND_TO_MCU = 10;
const int LOWER_LIMIT = 5;   //MIN ARDUINO 0
const int UPPER_LIMIT = 130; //MAX ARDUINO 1024

const int COMMAND_TURN_LED_ON = 200;
const int COMMAND_TURN_LED_OFF = 201;
const int COMMAND_READ_VALUES_FROM_ARDUINO = 202;
const int COMMAND_SEND_VALUES_FROM_MCU_TO_ARDUINO = 203;

MATLAB controller;

int STBY = 9; //standby

//Motor A
int PWMA = 3; //Speed control
int AIN1 = 8; //Direction   //TODO:
int AIN2 = 7; //Direction



// create a Software Serial instance for communications with the ESP8266
SoftwareSerial mySerial(10, 11); // RX, TX

//variable to store the value coming from LDR
int sensorValue = 0; 

// array with values from LDR case
int arrLDR[NUMBER_SIZE_ARRAY_SEND_TO_MCU];

//iteration to add LDR values
int iterLDR = 0;

//------------------------------------------------------------------------------

void setup() {
  
  mySerial.begin(115200); // init Software Serial
  Serial.begin(9600);   // init normal USB/Hardware Serial

  // initiate all the LED pins
  pinMode(LED_PIN, OUTPUT);
  
 //  initiate all the LDR pins
  pinMode(LDR_PIN, INPUT);
  
  digitalWrite(LED_PIN, LOW);

   digitalWrite(STBY, LOW);
}

void FillArrayWithValuesFromLDR (int lowerLimit, int upperLimit);

//------------------------------------------------------------------------------
void loop() {

//TODO:

//   //Listen for software Serial messages
//  if(mySerial.available()>0){
//    
//    unsigned char in = mySerial.read();
//    
//     //TURN ON LED FROM BUTTON "ON"
//    if (in == COMMAND_TURN_LED_ON){
//      digitalWrite(LDR_PIN, HIGH);
//      //Serial.println(COMMAND_TURN_LED_ON);    
//    }
//    
//    //TURN OFF LED FROM BUTTON "OFF"
//    if(in == COMMAND_TURN_LED_OFF){
//      digitalWrite(LDR_PIN, LOW);
//      //Serial.println(COMMAND_TURN_LED_OFF);
//    }
//    
//      //READ LINE WITH VALUES FROM MCU
//    if(in == COMMAND_SEND_VALUES_FROM_MCU_TO_ARDUINO){
//      mySerial.write(203);
//            Serial.println(in);
//      String arrr = "";
//      for(int index = 0; index < 9; index++){
//          Serial.println(index);
//          while(mySerial.available() == 0);
//          char ch = mySerial.read();
//          arrr += ch;
//      }
//        
////       }
////      while(mySerial.available() > 0){ 
////      arrr += mySerial.readString();
////      }
//      
//      mySerial.write(in);
//      mySerial.print(arrr);
//      Serial.println(in);
//      Serial.println(arrr);
//      }
//        
//  }

      //assign values from LDR pin
      sensorValue = analogRead(LDR_PIN);
      //TODO:
      //Serial.println(sensorValue);
      delay(100);

//-----

controller.setRef(1.0);
controller.setOsv(0.2);
controller.step();
Serial.println(controller.getLamp());
Serial.print("-------");
Serial.println(controller.getMotor());

move(1,255 - controller.getMotor(), 1); //motor 1, full speed, left  




delay(100);


      
//----
    FillArrayWithValuesFromLDR (LOWER_LIMIT, UPPER_LIMIT);

    //get elements
    if(iterLDR == NUMBER_SIZE_ARRAY_SEND_TO_MCU){
      
        // 202 send values to nmc
        mySerial.write(COMMAND_READ_VALUES_FROM_ARDUINO);
  
             
        for (int i = 0; i <10; i++) {
          
          //convert unsigned char to short
          short testNumber = arrLDR[i];
          char lo = testNumber & 0xFF;
          char hi = (testNumber >> 8) & 0xFF;
    
          mySerial.write(hi); 
          mySerial.write(lo);

          //Serial.println("OKKKKKKKKKKKK");
          
        }

        iterLDR = 0;

    }
    
}

//------------------------------------------------------------------------------
void FillArrayWithValuesFromLDR (int lowerLimit, int upperLimit){
  if(sensorValue >= lowerLimit && sensorValue <= upperLimit){ //Change
  //first iterLDR = 0 after increment reach size of array
    if(iterLDR != NUMBER_SIZE_ARRAY_SEND_TO_MCU){
      arrLDR[iterLDR] = sensorValue;
      //TODO:
      //Serial.println(iterLDR);
      iterLDR++;
    }
  }
}

//------------------------------------------------------------------------------
void move(int motor, int speed, int direction){
//Move specific motor at speed and direction
//motor: 0 for B 1 for A
//speed: 0 is off, and 255 is full speed
//direction: 0 clockwise, 1 counter-clockwise

digitalWrite(STBY, HIGH); //disable standby

boolean inPin1 = LOW;
boolean inPin2 = HIGH;

if(direction == 1){
inPin1 = HIGH;
inPin2 = LOW;
}

if(motor == 1){
digitalWrite(AIN1, inPin1);
digitalWrite(AIN2, inPin2);
analogWrite(PWMA, speed);
}

}
