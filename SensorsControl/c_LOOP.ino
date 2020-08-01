//=======================================================================
//                    Main Program Loop
//=======================================================================
void loop() {
  
  //Check for change in sensors first:
  sensorValue = analogRead(sensorPin);  //Read Analog value of sensor
  sensorValue = map(sensorValue,0,1024,20,60); //Map to 20-60 value
  sensorValue = random(20,60); //Read Sensor
  if(sensorValue == oldValue)
    return; //Nothing changed
  oldValue = sensorValue;
  Serial.println(" Change! let's send it...");
  //==================================// 
  //           Connect to host
  //==================================// 
  WiFiClientSecure httpsClient;
  int client_error_code = connect_host(&httpsClient);
  if(client_error_code != 0) return;
  
  String response;
  String Link;

  //==================================// 
  //           Get Patient
  //==================================// 
  //if(!got_patient){
  //  Link = "/getConnectionDetails?arduinoID=a";
  //  response = req(httpsClient,Link);
  //  parse_ArduinoIDQuery(response); //Get the Patient ID
  //  got_patient = true;
  //}
  //==================================// 
  //           Sensors POST
  //==================================// 

  delay(30); //Pause for drama
  
  String BPM_value = String(sensorValue);   //String to interger conversion
  Serial.println(sensorValue);
  //Upload sensor data with GET:  to //https://us-central1-lifeline-aa56b.cloudfunctions.net/updateSensor?oxi=95&bpm=95&arduinoID=a
  Link = "/updateSensor?oxi=95&bpm="+BPM_value+"&arduinoID=a";  //Sensors
  response = req(httpsClient,Link);
  //Check if posted..
  Serial.println("Done!");
  Serial.print("Waiting for change ... ");
  delay(500);  
}
//=======================================================================
