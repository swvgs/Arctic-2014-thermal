/*
  Blink
 Turns on an LED on for one second, then off for one second, repeatedly.
 
 This example code is in the public domain.
 */

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led3 = 3;
int led5 = 5;
int led6 = 6;
int led9 = 9;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led3, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  pinMode(led9, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(led3, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(led5, HIGH);
  digitalWrite(led6, HIGH);
  digitalWrite(led9, HIGH);
  delay(1000);               // wait for a second
  digitalWrite(led3, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(led5, LOW);
  digitalWrite(led6, LOW);
  digitalWrite(led9, LOW);
  delay(1000);               // wait for a second
}

