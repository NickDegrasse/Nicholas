//Download library here https://learn.sparkfun.com/tutorials/tb6612fng-hookup-guide#library-and-example-code, manually import by copying library to User\Documents\Arduino\libraries
#include <SparkFun_TB6612.h>
#include "common.h"
#include "Timer.h"

using namespace defs; //inlcudes all definitions made in common.h

namespace //limits the scope of decalations inside namespace to this file.
{
Motor leftMotor = Motor(AIN1, AIN2, PWMA, offsetA, STBY); 
Motor rightMotor = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

Timer calibrationTimer = Timer(CALIBRATION_TIME);
Timer outputTimer = Timer(SECOND); // one second interval between outputs
int logIndex = 0;                  // used by calibrate method
int sensorLog[dataPoints][NUM_SENSORS];
int maxIR = 800;
int minIR = 180;
float Kp; //This will change using the potentiometer during testing
float Kd; //This will change using the potentiometer during testing
float Ki;
float P, I, D;
float direction;

float voltage;
float error;
float previousError;
float desiredCoefficient; //For testing
} //end namespace init



void setup()
//all actions that are only done once
{
  pinMode(13, OUTPUT); //only needed once so done in setup()
  Serial.begin(9600);
  Serial.println(F("Connected")); //quick check to make sure device is communicating
  //calibrate();

  delay(5000);
}

void loop()
{
  
  Kp = getCoefficient();        //For testing PID values, changes Kp or Kd based on potentiometer

  readSensor();                 //Collects data from sensors and stores in an array
  direction = calculatePID();   //Calculates direction based on PID output. Direction is from 0-1 with 0 being left, 1 being right. 0.5 means there is no error and the device is on the line
  propForward(direction);       //Drives motors proportionally based on the ratio from 0-1 we pass in
}

float getRatio()                //This will take the values from the IR sensors, add them up as a weighted average and return a ratio from 0-1 to be used in the PID calculation
{
  //Serial.print(F("getRatio"));
  int outputArr[NUM_SENSORS];   //Create temporary array to store values
  int sum = 0;                  //Initialize sum variable

  for (int i = 0; i < NUM_SENSORS; i++)
  {
    outputArr[i] = sensorDataRaw[i] * weightArray[i]; //stores weighted values
  }

  for (int i = 0; i < NUM_SENSORS; i++)
  {
    if (i != 2)
    {
      sum = sum + outputArr[i];
    }
  }

  //This will include the center sensor. We're assuming that the center sensor has a fairly small value
  //(handled by the turn threshold), however if the line is between the center and inner sensors, we want to still
  //consider the center sensor value

  if (sum > 0)
  {
    sum = sum + (CENTER_WEIGHT * outputArr[2]);
  }
  else if (sum < 0)
  {
    sum = sum - (CENTER_WEIGHT * outputArr[2]);
  }

  //This will constrain sum incase somehow it reaches values we wouldn't expect (likely to come up for very sharp turns).
  //May want to try and remove this
  sum = constrain(sum, (-OUTER_WEIGHT * maxIR), (OUTER_WEIGHT * maxIR));

  //maps from 0 to 1
  float temp = map(sum, (-OUTER_WEIGHT * maxIR), (OUTER_WEIGHT * maxIR), 0, 1000.00);
  return (temp / 1000.00);
}

float calculatePID()
{
  previousError = error;      //Store previous error here
  error = 0.5 - getRatio();   //Gets error, as 0.5 is our ideal value we always want to shoot for
 
  P = error;                  //Proportional error
  I = I + error;              //Integral error (not currently using
  D = error - previousError;  //Derivative error
  Serial.println(Kp);         //Can't print to Serial while robot is running, okay since potentiometer saves physical location the correct Kp/Kd should print when recconnected

  return (Kp * P) + (Ki * I) + (Kd * D); //Final PID value
}

void readSensor()           //Reads IR sensors (analog) and stores their information in an array
{
  //Serial.println("readSensor()");
  for (int x = 0; x < NUM_SENSORS; x++)
  {
    //Serial.println(analogRead(IRSensor[x]));
    sensorDataRaw[x] = analogRead(IRSensor[x]);
  }
}

void propForward(float PIDval) //Drives the motors
{
  // Add PID values
  int speed1 = SPEED + PIDval;
  int speed2 = SPEED - PIDval;

  //Prevents motor from reversing
  if(speed1 <= 0) {
    speed1 = 0;
  }
    if(speed2 <= 0) {
    speed2
     = 0;
  }

  //Drives motors
  leftMotor.drive(speed1);
  rightMotor.drive(speed2);
}

// For testing with a potentiometer
float getCoefficient() {

  voltage = analogRead(A3);
  //Serial.println(voltage);
  desiredCoefficient = map(voltage, 0, 1023, 0, 500); //Change range of Kp/Kd values here (Syntax: map(value, fromLow, fromHigh, toLow, toHigh))
  
  return desiredCoefficient;
}
