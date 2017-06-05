/*
 * basic performance fragments
 */

// perform mallet beat
void malletBeat() {
  mallet.write(137);
  delay(200);
  mallet.write(malletPos);
}

// perform buzzer noise
void buzz() {
  bitSet(registerData, 7);
  updateShiftRegister();
  delay(50);
  bitClear(registerData, 7);
  updateShiftRegister();
}

