#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
//==================================// 
//            Query Vars
//==================================//
int data_rpm=16;
bool data_manual=false;
const char* data_patientID;
int data_sensor_oxi;
int data_sensor_bpm=20;
//String data_emsID;
//==================================// 
//            WiFi Vars
//==================================// 
const char *ssid = "RedmiAW";  
const char *password = "arielweiss";
 
// 'https://us-central1-lifeline-aa56b.cloudfunctions.net/getConnectionDetails?arduinoId=a'
const char *host = "us-central1-lifeline-aa56b.cloudfunctions.net";
const int httpsPort = 443;  //HTTPS= 443 and HTTP = 80
 
//SHA1 finger print of certificate use web browser to view and copy
//const char fingerprint[] PROGMEM = "56 17 38 a4 11 9d f8 79 a4 91 c4 8a 2b 3a eb da 03 b5 5b 6e";
const char fingerprint[] PROGMEM = "b8 28 38 35 06 a4 f8 41 50 b5 b4 d0 6d ce 07 a5 0c 13 2e bd";

const int MAX_LINES = 3;
//==================================// 
//           Stepper Vars
//==================================// 
const int stepPin = 4; //D2
const int dirPin = 5;  //D1
const int full_rotation = 200/2;
const int cycles = 1;
int total_steps = full_rotation * cycles;
int push_speed = 1500;
int RESPIRATIONS_NUM = 10;
//==================================// 
//           Functions
//==================================// 
void makeSteps();

int connect_host(WiFiClientSecure* httpsClient);
String req(WiFiClientSecure httpsClient, String Link);
void parse_ArduinoIDQuery(String json);
