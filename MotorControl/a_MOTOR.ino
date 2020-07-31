//=======================================================================
//                    Stepping the Stepper
//=======================================================================
void makeSteps(){
  int counter = RESPIRATIONS_NUM;
  while(counter > 0){
    digitalWrite(dirPin,LOW); // Enables the motor to move in a particular direction
    // Makes 200 pulses for making one full cycle rotation
    for(int x = 0; x < total_steps; x++) {
      digitalWrite(stepPin,HIGH); 
      delayMicroseconds(2000); 
      digitalWrite(stepPin,LOW); 
      delayMicroseconds(2000); 
      yield();
    }
    Serial.print("Speed: ");
    Serial.println(push_speed);
    delay(push_speed); // Delay by push_speed
    
    digitalWrite(dirPin,HIGH); //Changes the rotations direction
    // Makes 400 pulses for making two full cycle rotation
    for(int x = 0; x < total_steps ; x++) {
      digitalWrite(stepPin,HIGH);
      delayMicroseconds(1000);
      digitalWrite(stepPin,LOW);
      delayMicroseconds(1000);
      yield();
    }
    
    delay(push_speed); // Delay by push_speed
    counter--;
  }
}
