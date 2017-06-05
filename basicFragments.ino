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
  enableBuzzer();
  delay(50);
  disableBuzzer();
}

