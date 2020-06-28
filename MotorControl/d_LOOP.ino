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
  //Link = "/updatePatientParameters?id="+data_patientID+"&bpm="+BPM+"&oxi="+OXI;
  
  delay(3000);  //GET Data at every 3 seconds
}
//=======================================================================
