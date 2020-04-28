// this code makes the LEDs flash, stay on, or blink like knightrider depeding on the range that the ultrasonic sensor picks something up

void checkRange() { //combines the code down below to make the LEDs flash, stay on, or blink like knightrider depedning on the range of the object the ultrasonic sensor is set to
  
  key = mykeypad.getKey();
  
  distance = runUltrasound();
  checkPoundStar();

  if (distance >= 20) { 
    wholeRange();
  }

  else if (target < distance && distance < 20) {
    lessThan20();
  }
  else if (distance < target) {
    lessThanTarget();
  }
}

// This will blink simoultaneously
void wholeRange() {

  for (int i = 0; i < numLED; i++) {
    digitalWrite(ledPins[i], HIGH);
  }

  lastTime = millis();
  while ((millis() - lastTime) <=  1000 && distance >= 20) { // we use 1000 in the millis() interval to blink for one second

    distance = runUltrasound();
    key = mykeypad.getKey();
    checkPoundStar();
    
  }

  for (int i = 0; i < numLED; i++) {
    digitalWrite(ledPins[i], LOW);
  }

  lastTime = millis();
  while ((millis() - lastTime) <= 1000 && distance >= 20) {

    distance = runUltrasound();
    key = mykeypad.getKey();
    checkPoundStar();

  }

  checkRange();

}

//This will keep the LED's on
void lessThan20() {

  for (int i = 0; i < numLED; i++) {
    digitalWrite(ledPins[i], HIGH);
  }

  while (target < distance && distance < 20) {

    distance = runUltrasound();
    key = mykeypad.getKey();
    checkPoundStar();

  }

  checkRange();
}

//This will do the knight rider blinking
void lessThanTarget() {

  for (int i = 0; i < numLED; i++) {

    lastTime = millis();
    while (distance < target && (millis() - lastTime) <= 100) { // millis() interval is 100 because we want the LEDs to blink 0.1 seconds

      digitalWrite(ledPins[i], HIGH);

      distance = runUltrasound();
      key = mykeypad.getKey();
      checkPoundStar();

    }
    digitalWrite(ledPins[i], LOW);
  }

  for (int i = 4; i >= 1; i--) {

    lastTime = millis();
    while (distance < target && (millis() - lastTime) <= 100) {

      digitalWrite(ledPins[i], HIGH);

      distance = runUltrasound();
      key = mykeypad.getKey();
      checkPoundStar();
    }
    digitalWrite(ledPins[i], LOW);
  }

  checkRange();
}
