/*Lab 1, 
  2/10/2020
  The setup for this lab, is an Arduino Uno attached to an ultrasound sensor, as well as 5 LED's. The user enters a distance on a keypad, then the LED's flash based on
  what range the user selects. I also added an alternate game mode, where a random distance is generated, and the lights prompt the user to hold an object/their hand at that
  random distance within 5 seconds, with the LED's prompting them
  
   This code will do the following:
    Greet the user and explain what the code will do
    * will start accepting the users number input distance(x) using a keypad
    * will start measuring distance using an ultrasound
    read out distances to the user
    flash 5 LED's simultaneously when distance is 20-118 inches
    within pre target range (target < x < 20) led's continuously on
    then the distance is within target (x < target) all 5 LED's will blink like knight rider with 0.1 sec for LED

    Alternatively, there is a game mode which I added which will have the
  */

#include <Keypad.h>

//                                  Initiate keypad variables
const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};


byte rowPins[ROWS] = {12, 11, A0, A1}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {A2, A3, A4, A5}; //connect to the column pinouts of the keypad


//create a new Keypad object
Keypad mykeypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

//                        Initiate LED variables
const byte numLED = 5;
const byte ledPins[numLED] = {3,4,5,6,7}; //Initiate pins

//                        Initialize ultrasound code
const byte trigger = 2;
const byte echo = 8;
long duration;
byte inches;
byte distance;

//                       Initialize extra variables
byte target;
char key;
bool isTarget = false;
long lastTime = 0;
int gameTarget;
int difference;

void setup() {
  
    Serial.begin(9600);
    Serial.println("***************************************************");
    Serial.println("We are Lil Jon and the Eastside boys! Enjoy Lab #1"); //Welcome message
    Serial.println("Press # button to enter target distance measurement");
    Serial.println("Press * to end measurement");
    Serial.println("Press A for game mode (only available on startup");
    Serial.println("***************************************************");

    
    for(int i = 0; i < numLED; i++) { //Initialize ledPins as output
      digitalWrite(ledPins[i], OUTPUT);
      pinMode(ledPins[i], LOW);
    }
    
    //Initialize keypad pins, assuming ROWS = COLS
    for(int i = 0; i < ROWS; i++) { //Initialize rows and columns as input, assumes ROWS = COLS
      digitalWrite(rowPins[i], INPUT);
      digitalWrite(colPins[i], INPUT);
    }

    //Initialize ultrasound pins
      pinMode(trigger, OUTPUT);
      pinMode(echo, INPUT);
  
}

void loop() {

  key = mykeypad.getKey(); //This looks for input from the user

  checkPoundStar(); //This checks if the key that was pressed was a * or # sign, if either was pressed, isTarget is set equal to true

  if(isTarget == true) {
    distance = runUltrasound(); //gets distance from ultrasound sensor
    checkRange(); //Checks the distance to see what range its in
  }
  
}
