//=======================================================================
//                    HTTPS requests
//=======================================================================
int connect_host(WiFiClientSecure* httpsClient){
  
  Serial.println("Host: ");
  Serial.print(host);
 
  Serial.printf("Using fingerprint '%s'\n", fingerprint);
  (*httpsClient).setFingerprint(fingerprint);
  (*httpsClient).setTimeout(15000); // 15 Seconds
  delay(1000);
  
  Serial.println("HTTPS Connecting");
  int r=0; //retry counter
  while((!(*httpsClient).connect(host, httpsPort)) && (r < 30)){
      delay(100);
      Serial.print(".");
      r++;
  }
  if(r==30) {
    Serial.println("Connection failed!");
    return -1;
  }
  else {
    Serial.println("Connected to web");
  }
  return 0;
}
//=======================================================================
//                    POST data
//=======================================================================
String post_data(WiFiClientSecure httpsClient, String Link){
  Serial.print("Requesting URL: ");
  Serial.println(host+Link);
 
  httpsClient.print(String("GET ") + Link + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +               
               "Connection: close\r\n\r\n");
 
  Serial.println(">Request Sent...");
                  
  while (httpsClient.connected()) {
    String line = httpsClient.readStringUntil('\n');
    if (line == "\r") {
      Serial.println(">Headers Received.");
      break;
    }
  }
 
  Serial.println(">Reply Was:");
  Serial.println("==========");
  String line;
  String result="";
  while(httpsClient.available()){        
    line = httpsClient.readStringUntil('\n');  //Read Line by Line
    Serial.println(line); //Print response
    result += line;
  }
  Serial.println("==========");
  Serial.println("Done.");
  return result;
}
