#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
//==================================// 
//            Query Vars
//==================================//
const char* data_patientID;
bool got_patient = false;
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
//           Sensors Vars
//==================================// 
int sensorPin = 0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor
int oldValue = 0;
//==================================// 
//           Functions
//==================================//

int connect_host(WiFiClientSecure* httpsClient);
String req(WiFiClientSecure httpsClient, String Link);
void parse_ArduinoIDQuery(String json);
