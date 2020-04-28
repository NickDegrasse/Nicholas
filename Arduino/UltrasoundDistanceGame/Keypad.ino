// Checks if pound or star was pressed, and either goes to a function to take in target, or exits the code
void checkPoundStar() {
  switch(key) {
    case '#':
      poundPressed();
      break;
    case '*':
      Serial.println("Thank you for trying Lab 1. 안녕! 우리에게 좋은 성적을 줘! :)");
      delay(100);
      //setup();
      exit(0);
      break;
      case 'A':
      gameMode();
      break;
  }
}

//This will run code when pound is pressed to store the target
void poundPressed() {
  
  Serial.println("Please enter your target distance from 2 - 19 inches");
  
  byte tens; //Tens will store either a 0 or 1, depending on if the users target is 2-9 or 10-19

  byte singles; //Tens will store either a 0 or 1, depending on if the users target is 2-9 or 10-19

  key = mykeypad.getKey();

  //Waits for input
  while(key == NO_KEY) {
    
    key = mykeypad.getKey();
    
    if(key != NO_KEY) {
      checkNumber(key); //Checks if numbers was entered
      tens = convertKeypad(key); //Convert keypad uses switch case to change characters to numbers (ie '2' becomes byte 2)
    }
  }

  //Checks if they input 0 or 1, if not the target is between 2-9
  if(tens <= 1) {
    key = mykeypad.getKey();
    
    while(key == NO_KEY) {
    
      key = mykeypad.getKey();
    
      if(key != NO_KEY) {
        checkNumber(key);
        singles = convertKeypad(key);

     }
    }
    
    //The tens is multiplied by ten, then added to the singles section (ie entering '1' '9' will be (10*1)+9 = 19
    target = (10 * tens) + singles;
    Serial.println("************************");
    Serial.print("Your target is ");
    Serial.print(target);
    Serial.println(" inches");
    Serial.println("************************");
  }

  //This handles case where the tens position was > 1, meaning the target is from
  else {
    target = tens;
    Serial.println("************************");
    Serial.print("Your target is ");
    Serial.print(target);
    Serial.println(" inches");
    Serial.println("************************");
  }

  delay(2000);
  isTarget = true; //Is target tells the arduino if a target has been entered
}

//converts character numbers to integers
byte convertKeypad(char keynum) {
  switch(keynum) {
    case '1':
    return 1;
    case '2':
    return 2;
    case '3':
    return 3;
    case '4':
    return 4;
    case '5':
    return 5;
    case '6':
    return 6;
    case '7':
    return 7;
    case '8':
    return 8;
    case '9':
    return 9;
    case '0':
    return 0;
  }
}

//Checks to see if a number was entered
void checkNumber(char keylet) {
  switch(keylet) {
    case 'A':
    Serial.println("A number was not entered");
    poundPressed();
    case 'B':
    Serial.println("A number was not entered");
    poundPressed();
    case 'C':
    Serial.println("A number was not entered");
    poundPressed();
    case 'D':
    Serial.println("A number was not entered");
    poundPressed();
    case '#':
    Serial.println("A number was not entered");
    poundPressed();
    case '*':
    Serial.println("A number was not entered");
    poundPressed();
  }
}
