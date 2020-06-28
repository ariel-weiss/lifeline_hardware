//=======================================================================
//                    Connect HTTPS client
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

//=======================================================================
//                    Https request
//=======================================================================
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

//=======================================================================
//                      Parsing
//=======================================================================
void parse_ArduinoIDQuery(String json){
  const size_t capacity = JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(5) + 100;
  DynamicJsonDocument doc(capacity);
  
  //const char* json = "{\"data\":{\"arduinoID\":\"a\",\"rpm\":12,\"manual\":true,\"patientID\":\"FZhRr6v5sEvZl9Ib77LJ\",\"emsID\":\"Tfmx0ibyeaC8hHDAsu4c\"}}";
  
  deserializeJson(doc, json);
  
  JsonObject data = doc["data"];
  //String data_arduinoID = data["arduinoID"]; // "a"
  data_rpm = data["rpm"]; // 12
  data_manual = data["manual"]; // true
  data_patientID = data["patientID"]; // "FZhRr6v5sEvZl9Ib77LJ"
  //String data_emsID = data["emsID"]; // "Tfmx0ibyeaC8hHDAsu4c"

  //Serial.println("data patientID:");
  //Serial.println(data_patientID);
  
}

void parse_PatientQuery(String json){

  
}
