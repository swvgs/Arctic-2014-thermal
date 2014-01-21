#include <i2cmaster.h>
#include <digitalWriteFast.h>

// Pin configurations
//const int DS18B20 = 2;        // DS18B20
const int toggleLed = 3;      // Toggle LED
const int toggleSwitch = 4;   // Toggle Switch
const int powerLed = 5;       // Power LED
const int toggle2Led = 6;     // Toggle 2 LED
const int momentary = 7;      // Momentary Switch
const int toggle2Switch = 8;  // Toggle 2 Switch
const int momentaryLed = 9;   // Momentary Switch LED
const int hall = 10;          // Hall Switch 1
const int hall2 = 11;         // Hall Switch 2
const int ambTemp = A0;       // Analog 0, TMP36



// Variable definitions
int toggleSwitchState = 0;
int momentaryState = 0;
int readMomentary = 0;
int toggle2SwitchState = 0;
int hallState = 0;
int hallStateOld = 0;
int hall2State = 0;
int collectState = 1;

float voltage, degreesC;  // vars for TMP36
float celcius;            // vars for MLX
int dataMode = 0;         // used to set if the data is taken time or distance based

//This is to keep the delay between readings the same (frequancy constant)
unsigned long currentMillis = 0;
unsigned long previousMillis = 0;
float interval = 0;

size_t ptr = 0;       // ptr in the array for dumping
#define arrSize 30         //size of the array

// setup arrays for storing data
unsigned long dataTime[arrSize];
float dataAmbient[arrSize];
float dataIR[arrSize];





void setup() {

  Serial.begin(9600);

  //aalog pins do not need to be set as input, there is no option to set them otherwise.

  pinModeFast(toggleLed, OUTPUT);
  pinModeFast(powerLed, OUTPUT);
  pinModeFast(toggle2Led, OUTPUT);
  pinModeFast(momentaryLed, OUTPUT);

  // switch things on so that you know we are booting.
  digitalWriteFast2(toggleLed, HIGH);
  digitalWriteFast2(toggle2Led, HIGH);
  digitalWriteFast2(momentaryLed, HIGH);

  pinModeFast(toggleSwitch, INPUT);
  pinModeFast(momentary, INPUT);
  pinModeFast(toggle2Switch, INPUT);
  pinModeFast(hall, INPUT);
  // pinModeFast(hall2, INPUT);

  i2c_init(); //Initialise the i2c bus
  PORTC = (1 << PORTC4) | (1 << PORTC5); //enable pullups
  Serial.println("Whistler V2.0 (01--14)");

  /**************************************************************
   * Put in code for toggle to so that you switch from taking
   * data based on the hall sensors, or just time. Not sure what
   * this would look like, but that would go here.
   * digitalReadFast2(toggle2Switch);
  /**************************************************************/

  delay(3000); //1 second delay to make sure everything is ready and happy.

  toggle2SwitchState = digitalReadFast2(toggle2Switch);

  if (toggle2SwitchState == HIGH) {
    dataMode = 1;
    for (int i=0;i<10;i++) {
      digitalWriteFast2(toggle2Led, HIGH);
      delay(150);
      digitalWriteFast2(toggle2Led, LOW);
      delay(150);
    }
    interval = 1000 * 1/50 - 1; //set the data recording to 50Hz; ~20ms delay
    digitalWriteFast2(toggle2Led, HIGH);
  } 
  else {
    dataMode = 0;
    interval = 1000 * 1/50 -1;
    digitalWriteFast2(toggle2Led, LOW);
  }

  // switch things off so that you know booting is done and we are ready
  digitalWriteFast2(toggleLed, LOW);
  digitalWriteFast2(momentaryLed, LOW);
  digitalWriteFast2(powerLed, HIGH);

}


void loop() {
  //  Serial.print(collectState);

  if (dataMode == LOW) {
    dataByDistance(interval);
  } 
  else {
    dataByTime(interval);
  }


}



// Get voltage from the analog pin that the sensor is connected to
float getTMP(int pin) {
  return (analogRead(pin) * 5.0 / 1024.0);
}

