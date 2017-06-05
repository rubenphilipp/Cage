/* 
 *  Test performance without randomization
 */

void testDrive1() {
  malletBeat();

  toggleLED(ledClockRed);
  toggleLED(ledClockBlue);

  /* buzzer */
  buzzSeq(50);

  moveStepper(1000, 0.5);
  
  startDCMotor();
  delay(500);
  
  stopDCMotor();
  delay(2000);
}

