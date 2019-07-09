#include <SoftwareSerial.h>
#include <matlab.h>

#define LED_PIN 5
#define LDR_PIN A0

const int NUMBER_SIZE_ARRAY_SEND_TO_MCU = 10;
const int LOWER_LIMIT = 0;   //MIN ARDUINO 0
const int UPPER_LIMIT = 1023; //MAX ARDUINO 1024

//Matlab regulator
MATLAB controller;

//Motor
int STBY = 9; //standby
int PWMA = 3; //Speed control
int AIN1 = 8; //Direction   //TODO:
int AIN2 = 7; //Direction

//COMUNICATION COMMAND ARDUINO - NODEMCU
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

double pos = 0;

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

void ReceveCommands();

void RunMotor();

void SendCommand();

//------------------------------------------------------------------------------
void loop() {

  //ReceveCommands();
  
//test
//    sensorValue = analogRead(LDR_PIN);
//    digitalWrite(LED_PIN,HIGH);
//    Serial.print(sensorValue);
//    Serial.println("------");
//    double sensorValueInDiaposon = sensorValue;
//    sensorValueInDiaposon = sensorValueInDiaposon / 160;
//    Serial.println(sensorValueInDiaposon);


//


 //move(100, 1); // full speed, left  
  RunMotor(); 
  

  //FillArrayWithValuesFromLDR (LOWER_LIMIT, UPPER_LIMIT);

  //SendCommand();

}



//------------------------------------------------------------------------------
void ReceveCommands (){
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
            Serial.println(in);
      String arrr = "";
      for(int index = 0; index < 9; index++){
          Serial.println(index);
          while(mySerial.available() == 0);
          char ch = mySerial.read();
          arrr += ch;
      }
              
      mySerial.write(in);
      mySerial.print(arrr);
      Serial.println(in);
      Serial.println(arrr);
      }
        
  }
}
//------------------------------------------------------------------------------
//when LDR array is full , Arduino send command to NodceMCU
void SendCommand(){
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
        iterLDR = 0;
    }    
  
}
//------------------------------------------------------------------------------
void RunMotor(){
  //assign values from LDR pin
  sensorValue = analogRead(LDR_PIN);


//pri zatvoreni nachlani usloviq
  //double pos = 0;
  //double x = 80;

//-----
  double sensorValueInDiaposon = sensorValue;
  sensorValueInDiaposon = sensorValueInDiaposon / 200.0; //90
  //Serial.print("LDR = ");
  //Serial.println(sensorValueInDiaposon);

  controller.setRef(0.);
  controller.setOsv(sensorValueInDiaposon); 
  controller.step();

  double lampFromMATLAB = controller.getLamp();
  lampFromMATLAB = lampFromMATLAB * 255.0;
  double motorFromMATLAB = controller.getMotor();
  motorFromMATLAB = motorFromMATLAB * 50.0;


  if(lampFromMATLAB > 255){
    lampFromMATLAB = 255.0;
  }else if (lampFromMATLAB < 0){
    lampFromMATLAB = 0.0;
  }

  if(motorFromMATLAB > 100){
    motorFromMATLAB = 100.0;
  }else if (motorFromMATLAB < -100){
    motorFromMATLAB = -100.0;
  }


//
//  if(pos > x && motorFromMATLAB > 0){
//    motorFromMATLAB = 0;
//  }else if (pos < 0 && motorFromMATLAB < 0){
//    motorFromMATLAB = 0;
//  }

  //pos = pos + motorFromMATLAB * 0.1; // 0.1 Ts  
  //test print
  Serial.print("LDR = ");
  Serial.print(sensorValueInDiaposon);
  Serial.print("    Lamp = ");
  Serial.print(lampFromMATLAB);
  Serial.print("    Motor = ");
  Serial.print(motorFromMATLAB);
//    Serial.print("    pos = ");
//  Serial.print(pos);
  Serial.println();


  if(motorFromMATLAB > 0){
    move(motorFromMATLAB, 1); //motor 1, full speed, left  
  }else if(motorFromMATLAB < 0){
    move(motorFromMATLAB, 0); //motor 1, full speed, left  
  }
//  else{
//    move(0,0);
//  }

  analogWrite(LED_PIN,lampFromMATLAB);

  delay(125);
}

//------------------------------------------------------------------------------
void move(int speed, int direction){
//Move specific motor at speed and direction
//speed: 0 is off, and 255 is full speed
//direction: 0 clockwise, 1 counter-clockwise

  digitalWrite(STBY, HIGH); //disable standby

  boolean inPin1 = LOW;
  boolean inPin2 = HIGH;
  
  if(direction == 1){
    inPin1 = HIGH;
    inPin2 = LOW;
  }

  digitalWrite(AIN1, inPin1);
  digitalWrite(AIN2, inPin2);
  analogWrite(PWMA, speed);  
}

//------------------------------------------------------------------------------
//get N number and add all in array
void FillArrayWithValuesFromLDR (int lowerLimit, int upperLimit){
  if(sensorValue >= lowerLimit && sensorValue <= upperLimit){ 
  //first iterLDR = 0 after increment reach size of array
    if(iterLDR != NUMBER_SIZE_ARRAY_SEND_TO_MCU){
      arrLDR[iterLDR] = sensorValue;
      //TODO:
      //Serial.println(iterLDR);
      iterLDR++;
    }
  }
}
