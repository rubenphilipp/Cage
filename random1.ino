/*
 * Random mode 1
 */

void random1() {
  //Toggle both front LEDs
  toggleLED(ledClockRed);
  toggleLED(ledClockBlue);

  /* initialize settings */
  const int operationsAmount = 6; //how many randomizable operations do exist?
  const int maxOperationsPerSequence = 5; //maximum length of a sequence

  /* initialize random values for this iteration */
  int repeatTimes = 1; //amount of repetitions (by default 1)
  // repeat the sequence? if so, how many times?
  if(random(0, 101) < 10) {
    repeatTimes = random(2, 5);
  }
  
  int operationDuration[maxOperationsPerSequence]; //how fast should the action be performed resp. how long should it endure? 0 => very quick; 1 => quite quick; 2 => medium; 3 => longish; 4 => rather long; 5 => lengthy
  int sequenceSize = random(1, (maxOperationsPerSequence + 1)); //how many (random) operations should be performed in sequence during the operation loop?

  /* generate operation sequence array */
  int sequence[maxOperationsPerSequence];
  
  for(int i = 0; i < sequenceSize; i++) {
    operationDuration[i] = random(1,101); //duration of the operation; could be used as a factor
    sequence[i] = random(0, operationsAmount); //define operation
  }

  /* print basic values to Serial */

  Serial.println("|| --- START --- GENERATE SEQUENCE");
  Serial.println("sequenceSize:");
  Serial.println(sequenceSize);
  Serial.println("repeatTimes:");
  Serial.println(repeatTimes);
  Serial.println("---");
  
  /* perform the sequence: */
  if(random(0,101) < 45){
    //just delay?
    //long or short?
    if(random(1, 101) < 33)
    {
      Serial.println("OPERATION: just delay (long)");
      delay(random(7001, 20000));
    }else{
      Serial.println("OPERATION: just delay (short)");
      delay(random(1000, 7000));
    }
    
  } else {
    //SEQUENCE repetition loop (SEQUENCE wrapper)
    for(int i = 0; i < repeatTimes; i++) {
      //Serial.println("-SEQUENCE loop-");
      //OPERATIONS loop -> step through the individual operations for this sequence
      for(int j = 0; j < sequenceSize; j++) {
        //Serial.println("-OPERATIONS loop-");
        //perform operation for this step of the sequence
        switch(sequence[j]) {
          case 0:
            //Serial.println("just delay");
            //just hold on for a moment
            delay(operationDuration[j]*25);
            break;
          case 1:
            //Serial.println("mallet beat");
            //just perform a mallet beat
            malletBeat();
            break;
          case 2:
            //Serial.println("buzz");
            //mallet plus buzz
            malletBeat();
            shortBeep();
            break;
          case 3:
            //Serial.println("activate fan");
            //just activate the fan
            startDCMotor();
            break;
          case 4:
            //Serial.println("activate fan, then wait");
            //activate the fan for a specific amount of time
            startDCMotor();
            delay(operationDuration[j]*40);
            stopDCMotor();
            break;
          case 5:
            //Serial.println("move the clock finger");
            //move the clock finger
            
            //determine direction
            if(random(1,101) < 50) {
              moveStepper(1100, (operationDuration[j]*0.01));
            } else {
              moveStepper(1100, (-operationDuration[j]*0.01));
            }
            break;
        }

        //toggle LEDs?
        if(random(1,101) < 30){
          switch(random(0,3)){
            case 0:
              toggleLED(ledClockRed);
              break;
            case 1:
              toggleLED(ledClockBlue);
              break;
            case 2:
              toggleLED(ledClockRed);
              toggleLED(ledClockBlue);
              break;
          }
        }
      }

      //additional short beep?
      if(random(0,101) < 5)
      {
        shortBeep();
      }
    }
  }

  /* tidy up everything */
  stopDCMotor(); //in case it was left on

  Serial.println("--- END --- |||");
}

