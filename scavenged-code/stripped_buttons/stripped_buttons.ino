
//define some pins
#define toggleLED   6
#define toggle      7
#define toggle2LED  9 
#define toggle2    11
#define momentary  10
#define momentaryLED    12
#define pwrLED      8

int momentaryState = 0;
unsigned long waituntil = 0;
long looppause = 5000; //time to delaybetween loops in miliseconds, 30000 = 30seconds


void setup() {

  pinMode(toggle, INPUT);
  digitalWrite(toggle, HIGH);
  pinMode(toggle2, INPUT);
  digitalWrite(toggle2, HIGH);
  digitalWrite(pwrLED, HIGH); //turn power on LED on

}

void loop() {


  while (digitalRead(toggle) == LOW) //when pin is low execute code
  {
    digitalWrite(toggleLED, HIGH); //turn on LED so you know you are taking data
    momentaryState = digitalRead(momentary);
    if (momentaryState == HIGH) {
      digitalWrite(momentaryLED, HIGH);
      //put a mark in the data
    } else {
      digitalWrite(momentaryLED, LOW);
    }

  }


}






