//=======================================================================
//                    Main Program Loop
//=======================================================================
void loop() {
  WiFiClientSecure httpsClient;
  int client_error_code = connect_host(&httpsClient);
  if(client_error_code != 0) return;

  String response;
  String Link;
  //GET Data:
  Link = "/getConnectionDetails?arduinoID=a" ;//+ ADCData;
  response = req(httpsClient,Link);
  parse_ArduinoIDQuery(response); //Get the RPM, Manual etc..

  //Move stepper:
  if(data_manual){//Control via App: use RPM
    push_speed = map(data_rpm,12,20,0,1000);
  }else{//Control via Sensors: use BPM (and OXI not)
    push_speed = map(data_sensor_bpm,20,60,0,1000);
  }
  Serial.print("Push before: ");
  Serial.println(push_speed);
  push_speed += 2000; //At least 2 seconds
  makeSteps();
  
  Serial.println("DONE");
  
  delay(3000);  //GET Data at every 3 seconds
}
//=======================================================================
