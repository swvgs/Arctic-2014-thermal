

//Button
const int buttonPin2 = 7;     // the number of the pushbutton pin
const int ledPin2 =  9;      // the number of the LED pin

//Hall
const int buttonPin = 11;     // the number of the pushbutton pin
const int ledPin =  3;      // the number of the LED pin

int buttonState = 0;         // variable for reading the pushbutton status
int buttonState2 = 0;         // variable for reading the pushbutton status

void setup() {

  pinMode(ledPin, OUTPUT);      
  pinMode(buttonPin, INPUT);  
  pinMode(ledPin2, OUTPUT);      
  pinMode(buttonPin2, INPUT);   

}


void loop() {

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


