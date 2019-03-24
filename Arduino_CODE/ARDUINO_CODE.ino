#include <SoftwareSerial.h>

#define LED_PIN 5
#define LDR_PIN A0

const int NUMBER_SIZE_ARRAY_SEND_TO_MCU = 10;
const int LOWER_LIMIT = 980;   //MIN ARDUINO 0
const int UPPER_LIMIT = 1020; //MAX ARDUINO 1024

const int COMMAND_TURN_LED_ON = 200;
const int COMMAND_TURN_LED_OFF = 201;
const int COMMAND_READ_VALUES_FROM_ARDUINO = 202;
const int COMMAND_SEND_VALUES_FROM_MCU_TO_ARDUINO = 203;



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
}

void FillArrayWithValuesFromLDR (int lowerLimit, int upperLimit);

//------------------------------------------------------------------------------
void loop() {

  //1.Only LED

   //Listen for software Serial messages
  if(mySerial.available()>0){
    
    unsigned char in = mySerial.read();
    
     //TURN ON LED FROM BUTTON "ON"
    if (in == COMMAND_TURN_LED_ON){
      digitalWrite(LDR_PIN, HIGH);
      //Serial.println(COMMAND_TURN_LED_ON);    
    }
    
    //TURN OFF LED FROM BUTTON "OFF"
    if(in == COMMAND_TURN_LED_OFF){
      digitalWrite(LDR_PIN, LOW);
      //Serial.println(COMMAND_TURN_LED_OFF);
    }
    
      //READ LINE WITH VALUES FROM MCU
    if(in == COMMAND_SEND_VALUES_FROM_MCU_TO_ARDUINO){
      mySerial.write(203);
      mySerial.write(in);
      }
        
  }

      //assign values from LDR pin
      sensorValue = analogRead(LDR_PIN);
      
      Serial.println(sensorValue);
      delay(100);

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
        }

    }
    
}

//------------------------------------------------------------------------------
void FillArrayWithValuesFromLDR (int lowerLimit, int upperLimit){
  if(sensorValue >= lowerLimit && sensorValue <= upperLimit){ //Change
  //first iterLDR = 0 after increment reach size of array
    if(iterLDR != NUMBER_SIZE_ARRAY_SEND_TO_MCU){
      arrLDR[iterLDR] = sensorValue;
      Serial.println(iterLDR);
      iterLDR++;
    }
  }
}
