/*
 * Core functions for controlling the hardware
 */


// Update shift register using global registerData var
void updateShiftRegister()
{
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, MSBFIRST, registerData);
   digitalWrite(latchPin, HIGH);
}

// toggle LED
void toggleLED(int ledID) {
  //check if ledID refers to one of the four register outputs used for LED lighting in order to avoid damaging the machine
  if(ledID <= 3) {
    //toggle LED
    if(bitRead(registerData, ledID) == 0){
      bitSet(registerData, ledID);
    } else {
      bitClear(registerData, ledID);
    }
    
    updateShiftRegister(); //push to shift register
  }
}


//move stepper (clock hand); parameters: stepperSpeed (max: ~1200 rpm), double fullRotations (amount of rotations, relative to one full rotation)
void moveStepper(int stepperSpeed, double fullRotations) {
  //check if speed is lower than max
  if(stepperSpeed <= 1200) {
    stepper.setSpeed(stepperSpeed);
    stepper.step(stepsPerOutputRevolution*fullRotations);
  }
}

//start/stop the DC motor
void startDCMotor(char dir = "a") {
  digitalWrite(DCENABLE, HIGH); // enable on
  if(dir == "a") {
    digitalWrite(DCDIRA, HIGH);
    digitalWrite(DCDIRB, LOW);
  } else {
    digitalWrite(DCDIRA, LOW);
    digitalWrite(DCDIRB, HIGH);
  }
}

void stopDCMotor() {
  digitalWrite(DCENABLE, LOW); // enable off
}


//enable/disable buzzer
void enableBuzzer() {
  bitSet(registerData, 7);
  updateShiftRegister();
}

void disableBuzzer() {
  bitClear(registerData, 7);
  updateShiftRegister();
}

