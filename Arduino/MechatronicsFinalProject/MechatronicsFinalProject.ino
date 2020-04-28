/* 3/16/20 Mechatronics Final project
 * 
 * This code will run 2 servo motors which will pan and sweep an ultrasound sensor,
 * which will detect the minimum distance to a toilet behind the user
 * 
 * The code starts once the user is within 100 cm (which can be changed through hard coding),
 * then will read minimum distances in real time as the user baccks up towards the toilet.
 * 
 * Once the user gets within 20cm, the servos will stop their usual motion, go to the Z angle where the system detected the minimum distance,
 * and pans up until is no longer senses a bowl, and starts to sense the tank (ie distance sensed >= our limit)
 * */

#include <Adafruit_GFX.h> //https://github.com/adafruit/Adafruit-GFX-Library make sure and rename file to include properly
#include <Adafruit_SSD1306.h> //https://github.com/adafruit/Adafruit_SSD1306 make sure and rename file to include properly
#include <SPI.h>
#include <Servo.h>
#include <Wire.h>
#include "Common.h"

//Initialize servos
Servo servox;
Servo servoz;

//Initialize display
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire); //Configured to our board size, this always gives error for some reason


void setup() {
  //Define servo pins
  servox.attach(servoxpin);
  servoz.attach(servozpin);

  //Initialize display screen over i2c
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // begins display, displays arduino logo by default
  display.clearDisplay(); //This will clear the adafruit logo

  //Set text information
  display.setTextSize(1);
  display.setTextColor(1);
  display.setCursor(0, 0);

  //Print welcome message
  display.print("Backup to toilet to begin");
  display.display();

  //Sets ultrasound to point directly out from wheelchair (Angles were measured from in person testing using servoTest.ino)
  servox.write(30);
  servoz.write(105);
  delay(100);
}

void loop() {

  //Checks if within range or not
  if(inRange == false) {
    distance = ultrasound();
    delay(10);
    Serial.println(distance);
    if(distance <= startRange) {
      inRange = true;
    }
  }
  
  //Gets distance data from the servo motors once withing range
  if(inRange == true) {
    getDataCentered();
  }

}

// This will pan and tilt based on where the ultrasound sensor detects the shortest distance to the toilet. It saves time by only panning in a 
// specific area, and adjusting its 'center' based on the orientation of the servo motors where the gimbal sensed its minimimum distance
void getDataCentered() {

  //Define range to pan/sweep
  int zRange = 15;
  int xRange = 15;

  //Define start and end angles, ranges are added and subtracted based on physical setup of servo motors
  int xStart = minDistance[0] + xRange;
  int zStart = minDistance[1] - zRange;

  int xEnd = minDistance[0] - xRange;
  int zEnd = minDistance[1] + zRange;
  
  //Set to origin
  servox.write(xUpperAngleInitial);
  servoz.write(zLowerAngleInitial);
  delay(200);

  //X angles are reversed (decreasing xAngle moves servo up)
  for (xAngle = xStart; xAngle >= xEnd; xAngle = xAngle - xStep) {

    servox.write(xAngle);
    delay(50);

    for (zAngle = zStart; zAngle <= zEnd; zAngle += zStep) {

      servoz.write(zAngle);
      delay(waitTime);

      distance = ultrasound();

      Serial.println(distance);

      getMin(xAngle, zAngle);
    }
  }
}

//Compares current distance to minimum. If the new distance is shorter, it stores the angle and distance
void getMin(int xAngle, int zAngle) {

  //Compares minimum distance to current minimum distance
  if (distance < minDistance[2]) {

    minDistance[0] = xAngle;
    minDistance[1] = zAngle;
    minDistance[2] = distance;

    //Prints minimum distance everytime a new min distance is found
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(1);
    display.setCursor(0, 0);

    display.print("Distance :");
    display.print(minDistance[2]);
    display.println(" cm");
    display.display();
  }

  //Checks if wheelchair is within 20 cm
  if (minDistance[2] <= 20) {

    //Shows message telling people not to move while getting height
    display.clearDisplay();
    display.println("Stay still, getting height");
    display.display();

    //Runs getHeight function
    getHeight();
  }
}

//This will give us the height of the toilet. It starts sensing at the location is sensed 20cm at, then starts rotating upwards. It will stop
void getHeight() {

  //Set ultrasound sensor to point where minimum distance was found
  servoz.write(minDistance[1]);
  delay(100);
  servox.write(minDistance[0]);
  delay(100);

  //This will keep the gimbal on the same z rotational axis, and rotate up until it reaches what seems to be the upper lip of the toilet.
  //This while loop conditional breaks the loop when the distance it senses goes outside of a range we set. We're assuming when distance passes this range,
  //it's sensing the tank and not the bowl anymore
  while (distance <= distanceLimit && xAngle >= xLowerAngleInitial) {

    servox.write(xAngle);
    delay(waitTime);

    distance = ultrasound();

    xAngle = xAngle - xStepHeight;
  }

  //Calculate height using height of gimbal plus height found with pythagorean therom
  //Ultrasound is perpendicular to floor at 30 degrees
  //multiply by -1 to account for x error
  float height = gimbalHeight + (distance * -1 * sin((xAngle - 30) * radToDegrees));
  
  //Cast to int so we don't have a ton of decimals
  height = (int) height;
  
  //print height and exit message
  display.clearDisplay();
  display.println("Height is ");
  display.print(height);
  display.println(" cm");
  display.println(" ");
  display.println("press button to start again");
  display.display();

  //Give time to display message to screen. After exiting, code restarts, so pressing the button again will start the sequence again
  delay(2000);
  exit(0);


}
