// Load Wi-Fi library
#include <ESP8266WiFi.h>

const char* SSID = "VIVACOM_604044";              //"arduino_test";  //"King";         //FAVICEDEAN //M-Tel_9BCC VIVACOM_604044
const char* PASSWORD = "Na_Pen4o_neta";       //"12345678";      //"";     //veselavesela  //48575443929BCC83
const int NUMBER_SIZE_ARRAY_READ_FROM_ARDUINO = 10;
const int COMMAND_TURN_LED_ON = 200;
const int COMMAND_TURN_LED_OFF = 201;
const int COMMAND_READ_VALUES_FROM_ARDUINO = 202;
const int COMMAND_SEND_VALUES_FROM_MCU_TO_ARDUINO = 203;


// Replace with your network credentials
const char* ssid     = SSID;            
const char* password = PASSWORD;     

WiFiClient client;


// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String output5State = "off";

// Assign output variables to GPIO pins
const int output5 = 5;

//Array with received values from Arduino
short arrLDR[NUMBER_SIZE_ARRAY_READ_FROM_ARDUINO];

//iterator for arrLDR
int iterLDR = 0;


String stringJoinLdrArr = String(" ");

//for name in GET/Post query 
String submitButton = "SUBMIT";

bool flagREAD202COMPLETE = false;







void setup() {
  Serial.begin(115200);
  
  // Initialize the output variables as outputs
  pinMode(output5, OUTPUT);
  
  // Set outputs to LOW
  digitalWrite(output5, LOW);

  // Connect to Wi-Fi network with SSID and password
 
  //Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
   
  server.begin();
}

//declare methods
void ConvertRecivedNumberFromArduinoAndAddInArray(unsigned char in, int iterLDR, short arrLDR[]);
void SplitNumbersFromIterLDRInline();


void loop(){
  client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    //Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      while (client.available() == 0);
      while (client.available()) {             // if there's bytes to read from the client,
        delay(1);
        char c = client.read();             // read a byte, then     
        //Serial.write(c);                    // print it out the serial monitor
        header += c;}        
        //if (c == '\n') {                    // if the byte is a newline character
        
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
         // if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

//-------------------------------------------------------------------------------

            
            
            // turns the LED on and off
            if (header.indexOf("GET /5/on") >= 0) {              
              output5State = "on";            
              Serial.write(COMMAND_TURN_LED_ON);
            } else if (header.indexOf("GET /5/off") >= 0) {             
              output5State = "off";
              Serial.write(COMMAND_TURN_LED_OFF);
            } else if (header.indexOf("GET /SUBMIT") >= 0) {
              submitButton = "SUBMIT";
              //Serial.write(COMMAND_SEND_VALUES_FROM_MCU_TO_ARDUINO);
              //Serial.print(submitButton);
            }

            if (header.indexOf("ValuesForArduino") >= 0) {
              
              //example ValuesForArduino=%26cl&clk_action=accept //goal(before) -> ValuesForArduino=
              int startIndexOfValueBeforArray = header.indexOf("ValuesForArduino");
              
              //example ValuesForArduino=%26cl&clk_action=accept //goal(after) -> &clk_action=accept
              int startIndexOfValueAfterArray =  header.indexOf("&clk_action=accept");

              //TODO: make 17(ValuesForArduino) CONSTANT 
              String result = header.substring(startIndexOfValueBeforArray + 17, startIndexOfValueAfterArray);

              //TODO: create decompiler in class or method

              String delimiter = "%2C";

              result.replace(delimiter,",");
               submitButton = result;
              //submitButton = "ValuesForArduino";
              Serial.write(COMMAND_SEND_VALUES_FROM_MCU_TO_ARDUINO);
              Serial.print(result);
            }
            //submitButton = header;

//-------------------------------------------------------------------------------          
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
           
            //ARDUINO 
            
            // If the output5State is off, it displays the ON button       
            if (output5State=="off") {
              client.println("<p><a href=\"/5/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/5/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 

            //SEND VALUES TO ARDUINO
                       
            //client.println("<input type=\"text\" name=\"ValuesForArduino\" value=\"\" class=\"ValuesForArduino\">");

            String testPost = "<form method=\"post\" action=\"/SUBMIT\" >";
            testPost += "<input type=\"text\" name=\"ValuesForArduino\" value=\""+submitButton+"\" class=\"ValuesForArduino\">";
            testPost +="<input type=\"submit\" name=\"clk_action\" value=\"accept\">";
            testPost +="</form>";
            client.println(header);
            client.println(testPost);
            client.println(submitButton);
            client.println("<p> "+ submitButton + "</p>");
            
//            if(submitButton=="SUBMIT"){
//              //client.println("<a href=\"/SUBMIT\"><button class=\"button\">SUBMIT</button></a>");
//              client.println(testPost);
//            }else{
//              //client.println("<p><a href=\"/5/off\"><button class=\"button\">SUBMIT</button></a></p>");
//            }  


            

 




//-------------------------------------------------------------------------------
            
            if(Serial.available() > 0){
              
              unsigned char in = Serial.read();

              client.println("IN1");

              ConvertRecivedNumberFromArduinoAndAddInArray(in,iterLDR,arrLDR);
              
              SplitNumbersFromIterLDRInline();

             //TODO:
              //client.println(in);
              
              //203 
              if(in == 203){
                String test = "<p>";
                test+= in;
                test+="</p>";
                client.println(test);

                String arrr = "";
                delay(10);
                while(Serial.available() > 0){ 
                  delay(10);
                char ch = Serial.read();
                  
                arrr += ch;
                }

                String test2 = "<p>";
                test2+= arrr;
                test2+="</p>";
                client.println(test2);
                
                
              }
                
              }

            //}

             

            
//-------------------------------------------------------------------------------
               
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
       /* } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }*/
      //}
    }
    header = "";
    client.stop();
  }
}



void ConvertRecivedNumberFromArduinoAndAddInArray(unsigned char in, int iterLDR, short arrLDR[]){

  client.println("IN2");
  //202 Read from arduino
  if(in == COMMAND_READ_VALUES_FROM_ARDUINO){        

           client.println("IN3");
            
    for(iterLDR = 0; iterLDR < NUMBER_SIZE_ARRAY_READ_FROM_ARDUINO; iterLDR++){
      client.println(iterLDR);

    //first bits
    unsigned char hi = Serial.read();
    //second bits
    unsigned char lo = Serial.read();
                
    //concatination bits => number
    short y = (hi << 8) | lo;
                
    arrLDR[iterLDR] = y;                
    }
    flagREAD202COMPLETE = true;
    client.println(iterLDR);
  }
}

void SplitNumbersFromIterLDRInline(){

  client.println("IN4");
  client.println(flagREAD202COMPLETE);
  
    //loop arrLDR and assign values in text line
    if(flagREAD202COMPLETE){
      for (int i = 0; i < NUMBER_SIZE_ARRAY_READ_FROM_ARDUINO; i++) {
        stringJoinLdrArr+=arrLDR[i];
        stringJoinLdrArr+= " ";
        client.println(stringJoinLdrArr);
      }
      
    //create HTML(input) and fill values from Arduino LDR array
    String printArrInInput = "";
    printArrInInput+= "<p><input type=\"text\" value=\"";
    printArrInInput+= stringJoinLdrArr;
    printArrInInput+= "\" class=\"DataFromArduino\"></p>";
                  
    client.println(printArrInInput);
    }
}
