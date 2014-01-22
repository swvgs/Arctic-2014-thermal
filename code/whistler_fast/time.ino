void dataByTime(float interval) {
  currentMillis = millis();

  toggleSwitchState = digitalReadFast(4);
  if (toggleSwitchState == LOW) {
    digitalWriteFast(6, LOW); 
    if (collectState == LOW) {
      Serial.println("Data collection stopped.");
      collectState = HIGH;
    }
  }   
  else  {
    digitalWriteFast(6, HIGH);
    if (currentMillis - previousMillis > interval) {
      previousMillis = currentMillis;
      //read ir, read amb, read momentary, read hall
      celcius = mlx9600();
      voltage = getTMP(A0);
      degreesC = (voltage - 0.5) * 100.0;
      momentaryState = digitalReadFast(7);

/*      if (readMomentary == 0 && momentaryState == HIGH) {
        digitalWriteFast(momentaryLed, HIGH); 
        readMomentary = 1;
      }/**/


      if (momentaryState == HIGH) {
        Serial.print("*,");
        momentaryState = 0;
//        readMomentary = 0;
        digitalWriteFast(9, HIGH);
      } 
      else {
        Serial.print(",");
        digitalWriteFast(9, LOW);
      }
      Serial.print(currentMillis);
      Serial.print(",");
      Serial.print(degreesC);
      Serial.print(",");
      Serial.println(celcius);
      collectState = LOW;
    }
  }
}



