//This is an alternate mode, which will give the player 7 seconds to guess a random distance the code will make. The LED lights will guide them,
//with left LEDs (pins 3 and 4) corresponding to too close, and pins 6 and 7 meaning too far. The middle LED (pin 5) means they're on the target
// This code is not meant to be realtime in any way

//Initiates game
void gameMode() {

  Serial.println("Hello, This is a game mode which will generate a random number from 2-20.");
  Serial.println("You will have 5 seconds to get to the randomly generated distance.");
  Serial.println("The led lights will tell you if you are getting further or closer");
  Serial.println("(left means youre less than target, right means youre above the target).");

  delay(7000);

  Serial.println(" ");
  Serial.println("Game will be begin in:");

  //Prints countdown
  for (int i = 5; i >= 1; i--) {
    Serial.println(i);
    delay(1000);
  }

  gameTarget = random(3, 12); //Generates random distance from 3 to 12
  beginGame(); //Begins game
}

void beginGame() {

  //Turns off LEDs if any are on
  for (int i = 0; i < numLED; i++) {
    digitalWrite(ledPins[i], LOW);
  }

  //Variables to save distance and
  //int D;

  //Stores time game is started
  lastTime = millis();


  //Runs game for 7 seconds
  while ((millis() - lastTime) <= 7000) {

    //Gets distance
    distance = runUltrasound2();

    //D = (int) distance;

    //Gets difference between distance and gameTarget
    difference = distance - gameTarget;


    //Conditionals to turn on specific LEDs based on how far player is from the gameTarget
    if (difference > 3) {
      digitalWrite(ledPins[4], HIGH);

      digitalWrite(ledPins[0], LOW);
      digitalWrite(ledPins[1], LOW);
      digitalWrite(ledPins[2], LOW);
      digitalWrite(ledPins[3], LOW);
    }
    else if (difference <= 3 && difference > 0) {
      digitalWrite(ledPins[3], HIGH);

      digitalWrite(ledPins[0], LOW);
      digitalWrite(ledPins[1], LOW);
      digitalWrite(ledPins[2], LOW);
      digitalWrite(ledPins[4], LOW);
    }
    else if (difference == 0) {
      digitalWrite(ledPins[2], HIGH);

      digitalWrite(ledPins[0], LOW);
      digitalWrite(ledPins[1], LOW);
      digitalWrite(ledPins[4], LOW);
      digitalWrite(ledPins[3], LOW);
    }
    else if (difference >= -3 && difference < 0) {
      digitalWrite(ledPins[1], HIGH);

      digitalWrite(ledPins[0], LOW);
      digitalWrite(ledPins[4], LOW);
      digitalWrite(ledPins[2], LOW);
      digitalWrite(ledPins[3], LOW);
    }
    else if (difference < -3) {
      digitalWrite(ledPins[0], HIGH);
      digitalWrite(ledPins[4], LOW);
      digitalWrite(ledPins[1], LOW);
      digitalWrite(ledPins[2], LOW);
      digitalWrite(ledPins[3], LOW);
    }

  }


  //Prints message for a win or loss
  if (difference == 0) {
    Serial.println("YOU WIN");

    //Knight rider code

    for (int y = 0; y < 5; y++) { //This will do the knight rider sequence 5 times

      for (int x = 0; x < 6; x++) {
        digitalWrite(ledPins[x], HIGH);
        delay(100);
        digitalWrite(ledPins[x], LOW);
      }

      for (int x = 4; x >= 1; x--) {
        digitalWrite(ledPins[x], HIGH);
        delay(100);
        digitalWrite(ledPins[x], LOW);
      }
    }

  }
  
  else if (difference != 0) {
    Serial.println("YOU LOSE");

    //Code to flash simoultaneously at user
    for (int y = 0; y < 5; y++) { //Flashes at user 5 times
      for (int x = 0; x < numLED; x++) {
        digitalWrite(ledPins[x], HIGH);
      }

      delay(100);

      for (int x = 0; x < numLED; x++) {
        digitalWrite(ledPins[x], LOW);
      }
      delay(100);
    }
  }

  //Returns to beginning
  setup();

}
