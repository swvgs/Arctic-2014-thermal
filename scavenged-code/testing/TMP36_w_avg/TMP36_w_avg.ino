// We'll use analog input 0 to measure the temperature sensor's
// signal pin.

const int temperaturePin = 0;
float voltage, degreesC;
float temps = 0;
float avgtemp =0;

void setup() { 
  Serial.begin(9600);
}

void loop() {
  temps = 0;
  for (int i=0;i<60;i++) {
    voltage = getVoltage(temperaturePin);
    degreesC = (voltage - 0.5) * 100.0;  
    temps += degreesC;
  }
  avgtemp = temps/60;
  Serial.print("avg temp: ");
  Serial.println(avgtemp);
delay(100);
}

float getVoltage(int pin) {
  return (analogRead(pin) * 5.0 / 1024.0);
}





