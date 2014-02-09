void dataByDistance(float interval) {
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

      hallState = digitalRead(hall);
      if (readMomentary == LOW) {
        momentaryState = digitalRead(momentary);
      }

      dataTime[ptr % arrSize] = currentMillis;
      dataAmbient[ptr % arrSize] = degreesC;
      dataIR[ptr % arrSize] = celcius;
      ptr++;

      if (readMomentary == 0 && momentaryState == HIGH) {
        digitalWrite(momentaryLed, HIGH); 
        readMomentary = 1;
      }

      if (hallState != hallStateOld) {
        if (momentaryState == HIGH) {
          Serial.print("*;");
          momentaryState = 0;
          readMomentary = 0;
          digitalWrite(momentaryLed, LOW);
        } 
        else {
          Serial.print(",");
        }

        size_t idx = 0;
        Serial.print("");
        for (; idx < arrSize; idx++) {
          Serial.print(dataTime[idx]);
          if (idx != arrSize-1) 
            Serial.print(",");
        }
        Serial.print(";");
        for(idx = 0; idx < arrSize; idx++) {
          Serial.print(dataAmbient[idx]);
          if (idx != arrSize-1) 
            Serial.print(",");
        }
        Serial.print(";");
        for(idx = 0; idx < arrSize; idx++) {
          Serial.print(dataIR[idx]);
          if (idx != arrSize-1) 
            Serial.print(",");
        }
        Serial.println("");
        hallStateOld = hallState;
      }
      collectState = LOW;
    }

  }
}


