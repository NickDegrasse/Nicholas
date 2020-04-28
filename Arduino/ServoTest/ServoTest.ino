/*  This code was used to test positions/angles of our servo motors for a servo controlled gimbal with an ultrasound attatched. This code will take in user input that selects
 *  which motor to control, then moves the selected motor to an angle specified by the user.
 */

#include <Servo.h>

Servo servox;
Servo servoz;

int xPin = 5;
int zPin = 6;

int xAngle;
int zAngle;

char userEntry;

void setup() {
  // put your setup code here, to run once:
  servox.attach(xPin);
  servoz.attach(zPin);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Press x for xservo, z for zservo");
  
  while(true) {
    if (Serial.available() >0) {
      userEntry = Serial.read();
      break;
    }
  }


  if (userEntry == 'x') {
    xservo('x');
  }
  else if (userEntry == 'z') {
    zservo('z');
  }
  else {
    Serial.println("error somewhere");
  }
  
}
void xservo(char userEntry) {
  Serial.println("Enter angle");
    while (true) {
      if (Serial.available() > 0) {
      xAngle = Serial.parseInt();
      break;
      }
    }
    Serial.print("Servo x, move to ");
    Serial.print(xAngle);
    Serial.println(" degrees");
    servox.write(xAngle);
    delay(25);
}
void zservo(char userEntry) {
  Serial.println("Enter angle");

    while(true) {
      if (Serial.available() > 0) {
        zAngle = Serial.parseInt();
        break;
      }
    }
    Serial.print("Servo z, move to ");
    Serial.print(zAngle);
    Serial.println(" degrees");
    servoz.write(zAngle);
    delay(25);
}
