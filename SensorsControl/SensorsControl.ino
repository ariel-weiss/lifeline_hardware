#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
//==================================// 
//            WiFi Vars
//==================================// 
const char *ssid = "RedmiAW";  
const char *password = "arielweiss";
 
// 'https://us-central1-lifeline-aa56b.cloudfunctions.net/getConnectionDetails?arduinoId=a'
const char *host = "us-central1-lifeline-aa56b.cloudfunctions.net";
const int httpsPort = 443;  //HTTPS= 443 and HTTP = 80
 
//SHA1 finger print of certificate use web browser to view and copy
const char fingerprint[] PROGMEM = "56 17 38 a4 11 9d f8 79 a4 91 c4 8a 2b 3a eb da 03 b5 5b 6e";

const int MAX_LINES = 3;
//==================================// 
//           Stepper Vars
//==================================// 
const int stepPin = 3; 
const int dirPin = 4; 

const int full_rotation = 200;
const int cycles = 10;
int total_steps;
int total_steps_other_way;
//==================================// 
//=======================================================================
//                    HttpS requests
//=======================================================================
int connect_host(WiFiClientSecure* httpsClient){
  Serial.println(host);
 
  Serial.printf("Using fingerprint '%s'\n", fingerprint);
  (*httpsClient).setFingerprint(fingerprint);
  (*httpsClient).setTimeout(15000); // 15 Seconds
  delay(1000);
  
  Serial.print("HTTPS Connecting");
  int r=0; //retry counter
  while((!(*httpsClient).connect(host, httpsPort)) && (r < 30)){
      delay(100);
      Serial.print(".");
      r++;
  }
  if(r==30) {
    Serial.println("Connection failed");
    return -1;
  }
  else {
    Serial.println("Connected to web");
  }
  return 0;
}

String req(WiFiClientSecure httpsClient, String Link){
  Serial.print("requesting URL: ");
  Serial.println(host+Link);
 
  httpsClient.print(String("GET ") + Link + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +               
               "Connection: close\r\n\r\n");
 
  Serial.println("request sent");
                  
  while (httpsClient.connected()) {
    String line = httpsClient.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }
 
  Serial.println("reply was:");
  Serial.println("==========");
  String line;
  String result="";
  while(httpsClient.available()){        
    line = httpsClient.readStringUntil('\n');  //Read Line by Line
    Serial.println(line); //Print response
    result += line;
  }
  Serial.println("==========");
  Serial.println("closing connection");
  return result;
}

void parse_ArduinoIDQuery(String json){
  const size_t capacity = JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(5) + 100;
  DynamicJsonDocument doc(capacity);
  
  //const char* json = "{\"data\":{\"arduinoID\":\"a\",\"rpm\":12,\"manual\":true,\"patientID\":\"FZhRr6v5sEvZl9Ib77LJ\",\"emsID\":\"Tfmx0ibyeaC8hHDAsu4c\"}}";
  
  deserializeJson(doc, json);
  
  JsonObject data = doc["data"];
  const char* data_arduinoID = data["arduinoID"]; // "a"
  int data_rpm = data["rpm"]; // 12
  bool data_manual = data["manual"]; // true
  const char* data_patientID = data["patientID"]; // "FZhRr6v5sEvZl9Ib77LJ"
  const char* data_emsID = data["emsID"]; // "Tfmx0ibyeaC8hHDAsu4c"

  Serial.println("data patientID:");
  Serial.println(data_patientID);
  
}
//=======================================================================
//                    Power on setup
//=======================================================================
 
void setup() {
  delay(1000);
  Serial.begin(115200);
  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);        //Only Station No AP, This line hides the viewing of ESP as wifi hotspot
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");
 
  Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP

  //Stepper init
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);

  total_steps = full_rotation * cycles;
}
 
//=======================================================================
//                    Main Program Loop
//=======================================================================
void loop() {
  WiFiClientSecure httpsClient;
  int client_error_code = connect_host(&httpsClient);
  if(client_error_code != 0) return;

  String response;
  String Link;//, ADCData, getData;
  //int adcvalue=analogRead(A0);  //Read Analog value of LDR
  //ADCData = String(adcvalue);   //String to interger conversion
  //GET Data:
  Link = "/getConnectionDetails?arduinoID=a" ;//+ ADCData;
  
  response = req(httpsClient,Link);
  parse_ArduinoIDQuery(response);
  Serial.println("DONE");
  //Link = "/getPatient";
  
  delay(3000);  //GET Data at every 3 seconds
}
//=======================================================================
