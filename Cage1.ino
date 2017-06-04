/* 
 *  Mr. Cage – Random Music Machine 
 *  
 *  Ruben Philipp
 *  http://github.com/rubenphilipp/
 *  
 *  Terminology:
 *  ARD = Arduino (UNO) PIN ID
 *  BB = Breadboard coordinates
 *  
*/

// include libraries
#include <Servo.h>

// initialize pins
const int SERVO = 3; // servo motor for the mallet (PWM required) {ARD: 3; BB: a-e28}
const int dataPin = 10;     // DS [S1] on 74HC595 {ARD: 10; BB: d13}
const int latchPin = 11;      // ST_CP [RCK] on 74HC595 {ARD: 11; BB: d11}
const int clockPin = 12;      // SH_CP [SCK] on 74HC595 {ARD: 12; BB: d10}

// generate Servo object
Servo mallet; // mallet servo

// initialize further variables
byte registerData = 0; // shift register data


void setup() {
  mallet.attach(SERVO);  // attaches the servo on pin 9 to the mallet servo object
  // Reset mallet
  mallet.write(180);

  /* set up pins: */

  // shift register
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);

  updateShiftRegister(); //initial shift register update

}

void loop() {
  malletBeat();
  delay(500);

}


/* functions */

// perform mallet beat
void malletBeat() {
  mallet.write(160);
  delay(200);
  mallet.write(180);
}


//Update shift register using global registerData var
void updateShiftRegister()
{
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, MSBFIRST, registerData);
   digitalWrite(latchPin, HIGH);
}
