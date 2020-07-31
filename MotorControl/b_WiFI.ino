//=======================================================================
//                    Connect HTTPS client
//=======================================================================
int connect_host(WiFiClientSecure* httpsClient){
  Serial.print("Connecting to host ...");
  //Serial.println(host);
 
  //Serial.printf("Using fingerprint '%s'\n", fingerprint);
  (*httpsClient).setFingerprint(fingerprint);
  (*httpsClient).setTimeout(15000); // 15 Seconds
  delay(1000);
  
  //Serial.print("HTTPS Connecting");
  int r=0; //retry counter
  while((!(*httpsClient).connect(host, httpsPort)) && (r < 30)){
      delay(100);
      Serial.print(".");
      r++;
  }
  if(r==30) {
    Serial.println(" Connection failed!");
    return -1;
  }
  else {
    Serial.println(" Connected.");
  }
  return 0;
}

//=======================================================================
//                    Https request
//=======================================================================
String req(WiFiClientSecure httpsClient, String Link){
  Serial.print("Sending request ... ");
  //Serial.println(host+Link);
 
  httpsClient.print(String("GET ") + Link + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +               
               "Connection: close\r\n\r\n");
 
  Serial.println(" Sent!");
                  
  while (httpsClient.connected()) {
    String line = httpsClient.readStringUntil('\n');
    if (line == "\r") {
      Serial.println(">Headers received");
      break;
    }
  }
 
  Serial.println(">Reply was:");
  String line;
  String result="";
  while(httpsClient.available()){        
    line = httpsClient.readStringUntil('\n');  //Read Line by Line
    Serial.println(line); //Print response
    result += line;
  }
  Serial.println("==========");
  //Serial.println("closing connection");
  return result;
}

//=======================================================================
//                      Parsing
//=======================================================================
void parse_ArduinoIDQuery(String json){
  const size_t capacity = JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(6) + 130;
  DynamicJsonDocument doc(capacity);
  
  //const char* json = "{\"data\":{\"patientID\":\"FZhRr6v5sEvZl9Ib77LJ\",\"sensor\":{\"oxygenPercentage\":95,\"bpm\":95},\"emsID\":\"Tfmx0ibyeaC8hHDAsu4c\",\"manual\":true,\"arduinoID\":\"a\",\"rpm\":12}}";

  deserializeJson(doc, json);
   
  JsonObject data = doc["data"];
  data_rpm = data["rpm"]; // 12
  data_manual = data["manual"]; // true
  data_patientID = data["patientID"]; // "FZhRr6v5sEvZl9Ib77LJ"
  
  data_sensor_oxi = data["sensor"]["oxygenPercentage"]; // 95
  data_sensor_bpm = data["sensor"]["bpm"]; // 95
  Serial.println("|---------------|");
  Serial.println("Data: ");
  Serial.print("Manual?: ");
  Serial.println(data_manual);
  Serial.print("rpm: ");
  Serial.println(data_rpm);
  Serial.print("OXI: ");
  Serial.println(data_sensor_oxi);
  Serial.print("BPM: ");
  Serial.println(data_sensor_bpm);
  Serial.println("|---------------|");
  
}
