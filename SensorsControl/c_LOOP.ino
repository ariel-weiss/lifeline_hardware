//=======================================================================
//                    Main Program Loop
//=======================================================================
void loop() {
  //==================================// 
  //           Connect to host
  //==================================// 
  WiFiClientSecure httpsClient;
  int client_error_code = connect_host(&httpsClient);
  if(client_error_code != 0) return;

  String response;
  String Link, ADCData, getData;

  //==================================// 
  //           Get Patient
  //==================================// 
  //if(!got_patient){
  Link = "/getConnectionDetails?arduinoID=a" ;//+ ADCData;
  response = post_data(httpsClient,Link);
  //parse_ArduinoIDQuery(response); //Get the Patient ID

  //==================================// 
  //           Sensors Read
  //==================================// 
  int sensorValue = analogRead(sensorPin);  //Read Analog value of sensor
  delay(30); //Pause for drama
  ADCData = String(sensorValue);   //String to interger conversion
  Serial.println(sensorValue);
  //Upload sensor data with GET:
  //Link = "/getConnectionDetails?arduinoID=a" ;//+ ADCData;
  //response = post_data(httpsClient,Link);

  
 
  
  delay(3000);  //GET Data at every 3 seconds
}
//=======================================================================
