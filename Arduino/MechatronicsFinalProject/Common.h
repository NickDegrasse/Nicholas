//Pin definitions and wait time
const byte trigger = 11;
const byte echo = 10;
const byte servoxpin = 5;
const byte servozpin = 6;
const byte waitTime = 50;
const byte buttonPin= 8;
bool inRange= false;
int startRange = 100; //in cm


//Gimbal settings, these are hard coded and can be adjusted based on the setup
//The 'intial' variables just make it so the distanceMap works. Make sure to change values for

//                                      check implementation of initial variables

const int xLowerAngleInitial = 15;
const int xUpperAngleInitial = 50;
const int xStep = 2;
int xAngle;

const int zLowerAngleInitial = 95;
const int zUpperAngleInitial = 115;
const int zStep = 2;
int zAngle;

//Gimbal settings for height
int xStepHeight = 1;
long gimbalHeight = 53.5; //in cm
int distanceLimit = 45; //This is a limiter that helps choose between the tank of the toilet and the bowl
float radToDegrees = (3.141592653589793238 / 180.00);



//ultrasound stuff
long distance;
long duration, cm;


//Arrays to store data
long minDistance[3] = {0,0,2000}; //stores xangle,zangle, and min distance. set to 2000 as that's way more than we would expect. So index = 0 is xangle, index = 1 is zangle, and index = 2 is distance

//Initialize functions
long ultrasound();
void getData();
void getMin(int xAngle, int zAngle);
void getHeight();
