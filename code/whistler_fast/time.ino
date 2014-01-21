void dataByTime(float interval) {
  currentMillis = millis();

  toggleSwitchState = digitalReadFast2(toggleSwitch);
  if (toggleSwitchState == LOW) {
    digitalWriteFast2(toggleLed, LOW); 
    if (collectState == LOW) {
      Serial.println("Data collection stopped.");
      collectState = HIGH;
    }
  }   
  else  {
    digitalWriteFast2(toggleLed, HIGH);
    if (currentMillis - previousMillis > interval) {
      previousMillis = currentMillis;
      //read ir, read amb, read momentary, read hall
      celcius = mlx9600();
      voltage = getTMP(ambTemp);
      degreesC = (voltage - 0.5) * 100.0;
      momentaryState = digitalReadFast2(momentary);

/*      if (readMomentary == 0 && momentaryState == HIGH) {
        digitalWriteFast2(momentaryLed, HIGH); 
        readMomentary = 1;
      }/**/


      if (momentaryState == HIGH) {
        Serial.print("*,");
        momentaryState = 0;
//        readMomentary = 0;
        digitalWriteFast2(momentaryLed, HIGH);
      } 
      else {
        Serial.print(",");
        digitalWriteFast2(momentaryLed, LOW);
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



