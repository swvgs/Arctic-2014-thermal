#include <i2cmaster.h>

//Button
const int buttonPin2 = 7;     // the number of the pushbutton pin
const int ledPin2 =  9;      // the number of the LED pin
int buttonState2 = 0;         // variable for reading the pushbutton status

//Hall
const int buttonPin = 11;     // the number of the pushbutton pin
const int ledPin =  3;      // the number of the LED pin
int buttonState = 0;         // variable for reading the pushbutton status

//TMP36
const int temperaturePin = 0;
float voltage, degreesC;
float temps = 0;
float avgtemp =0;


void setup() {

  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);      
  pinMode(buttonPin, INPUT);  
  pinMode(ledPin2, OUTPUT);      
  pinMode(buttonPin2, INPUT);

  i2c_init(); //Initialise the i2c bus
  PORTC = (1 << PORTC4) | (1 << PORTC5);//enable pullups
  Serial.println("Whistler V2.0 (01-10-14)");

}


void loop() {

  unsigned long currentMillis = millis();
  float celcius = mlx9600();

  Serial.print("IR: ");
  Serial.print(celcius);


  temps = 0;
  for (int i=0;i<60;i++) {
    voltage = getVoltage(temperaturePin);
    degreesC = (voltage - 0.5) * 100.0;  
    temps += degreesC;
  }
  avgtemp = temps/60;
  Serial.print(", CON: ");
  Serial.println(avgtemp);


  buttonState = digitalRead(buttonPin);
  buttonState2 = digitalRead(buttonPin2);

  if (buttonState == HIGH) {     
    digitalWrite(ledPin, HIGH);  
  } 
  else {
    digitalWrite(ledPin, LOW); 
  }
  if (buttonState2 == HIGH) {     
    digitalWrite(ledPin2, HIGH);  
  } 
  else {
    digitalWrite(ledPin2, LOW); 
  }

}



float getVoltage(int pin) {
  return (analogRead(pin) * 5.0 / 1024.0);
}



