/* 
 *  Mr. Cage – Random Music Machine 
 *  
 *  Ruben Philipp
 *  http://github.com/rubenphilipp/
 *  
 *  Terminology:
 *  ARD = Arduino (UNO) PIN ID
 *  BB = Breadboard coordinates
 *  STP = stepper motor driver (ULN2003)
 *  
*/

// include libraries
#include <Servo.h>
#include <Stepper.h>

// initialize pins
const int SERVO = 3; // servo motor for the mallet (PWM required) {ARD: 3; BB: a-e28}
const int dataPin = 2; // DS [S1] on 74HC595 {ARD: 2; BB: d13}
const int latchPin = 12; // ST_CP [RCK] on 74HC595 {ARD: 12; BB: d11}
const int clockPin = 13; // SH_CP [SCK] on 74HC595 {ARD: 13; BB: d10}
const int stepper1 = 8; // {ARD: 8; STP: 1}
const int stepper2 = 9; // {ARD: 9; STP: 2}
const int stepper3 = 10; // {ARD: 10; STP: 3}
const int stepper4 = 11; // {ARD: 11; STP: 4}


// initialize Servo object
Servo mallet; // mallet servo

// initialize Stepper object (for more info cf. https://arduino-info.wikispaces.com/SmallSteppers)
const int stepsPerMotorRevolution = 32; // Number of steps per revolution of INTERNAL motor in 4-step mode
const int stepsPerOutputRevolution = stepsPerMotorRevolution * 64; // Steps per OUTPUT SHAFT of gear reduction
Stepper stepper(stepsPerMotorRevolution, stepper1, stepper3, stepper2, stepper4);

// initialize further global variables
byte registerData = 0; // shift register data


void setup() {
  /* set up mallet */
  mallet.attach(SERVO);  // attach the mallet servo
  mallet.write(180); //Reset mallet

  /* set up stepper: */
  stepper.setSpeed(700); // speed (max: ~1200 rpm):

  /* set up pins: */

  // shift register
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);

  updateShiftRegister(); //initial shift register update

}

void loop() {
  //malletBeat();
  
  if(bitRead(registerData, 0) == 0){
    bitSet(registerData, 0);
  } else {
    bitClear(registerData, 0);
  }
  updateShiftRegister();

  /* buzzer */
  /*bitSet(registerData, 3);
  updateShiftRegister();
  delay(100);
  bitClear(registerData, 3);
  updateShiftRegister();*/
  
  /*stepper.setSpeed(1200);
  stepper.step(stepsPerOutputRevolution/8);*/
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
