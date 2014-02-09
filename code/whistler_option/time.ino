void dataByTime(float interval) {
  currentMillis = millis();

  toggleSwitchState = digitalRead(toggleSwitch);
  if (toggleSwitchState == LOW) {
    digitalWrite(toggleLed, LOW); 
    if (collectState == LOW) {
      Serial.println("Data collection stopped.");
      collectState = HIGH;
    }
  }   
  else  {
    digitalWrite(toggleLed, HIGH);
    if (currentMillis - previousMillis > interval) {
      previousMillis = currentMillis;
      //read ir, read amb, read momentary, read hall
      celcius = mlx9600();
      voltage = getTMP(ambTemp);
      degreesC = (voltage - 0.5) * 100.0;
      momentaryState = digitalRead(momentary);

/*      if (readMomentary == 0 && momentaryState == HIGH) {
        digitalWrite(momentaryLed, HIGH); 
        readMomentary = 1;
      }/**/


      if (momentaryState == HIGH) {
        Serial.print("*;");
        momentaryState = 0;
//        readMomentary = 0;
        digitalWrite(momentaryLed, HIGH);
      } 
      else {
        Serial.print(";");
        digitalWrite(momentaryLed, LOW);
      }
      Serial.print(currentMillis);
      Serial.print(";");
      Serial.print(degreesC);
      Serial.print(";");
      Serial.println(celcius);
      collectState = LOW;
    }
  }
}



