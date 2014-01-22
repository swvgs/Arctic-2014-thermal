void dataByDistance(float interval) {
  currentMillis = millis();

  toggleSwitchState = digitalReadFast(4);
  if (toggleSwitchState == LOW) {
    digitalWriteFast(3, LOW); 
    if (collectState == LOW) {
      Serial.println("Data collection stopped.");
      collectState = HIGH;
    }
  }   
  else  {
    digitalWriteFast(3, HIGH);
    if (currentMillis - previousMillis > 1) {
      previousMillis = currentMillis;

      //read ir, read amb, read momentary, read hall
      celcius = mlx9600();
      voltage = getTMP(A0);
      degreesC = (voltage - 0.5) * 100.0;  

      hallState = digitalReadFast(10);
      if (readMomentary == LOW) {
        momentaryState = digitalReadFast(7);
      }

      dataTime[ptr % arrSize] = currentMillis;
      dataAmbient[ptr % arrSize] = degreesC;
      dataIR[ptr % arrSize] = celcius;
      ptr++;

      if (readMomentary == 0 && momentaryState == HIGH) {
        digitalWriteFast(9, HIGH); 
        readMomentary = 1;
      }

      if (hallState != hallStateOld) {
        if (momentaryState == HIGH) {
          Serial.print("*,");
          momentaryState = 0;
          readMomentary = 0;
          digitalWriteFast(9, LOW);
        } 
        else {
          Serial.print(",");
        }

        size_t idx = 0;
        Serial.print("[");
        for (; idx < arrSize; idx++) {
          Serial.print(dataTime[idx]);
          if (idx != arrSize-1) 
            Serial.print(",");
        }
        Serial.print("],[");
        for(idx = 0; idx < arrSize; idx++) {
          Serial.print(dataAmbient[idx]);
          if (idx != arrSize-1) 
            Serial.print(",");
        }
        Serial.print("],[");
        for(idx = 0; idx < arrSize; idx++) {
          Serial.print(dataIR[idx]);
          if (idx != arrSize-1) 
            Serial.print(",");
        }
        Serial.println("]");
        hallStateOld = hallState;
      }
      collectState = LOW;
    }

  }
}


