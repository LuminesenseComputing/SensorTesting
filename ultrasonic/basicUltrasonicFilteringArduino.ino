/* i2c components based off of sample code for i2c from Michael Ding and Tyler Gamvrelis
 */

///////INCLUDE STATEMENTS////////////
////////////////////////////////////
#include <Wire.h>
#include <Servo.h>
#include <Stepper.h>


//////PIN ASSIGNMENTS//////////////
////////////////////////////////////
//note that D3 is sketchy

const int trigPin = 3;
const int echoPin = 12;

///////GLOBALS/////////////////////
//////////////////////////////////

//ultrasonic distance constants

const long int minPoleHeight = 14ll;
const long int maxPoleHeight = 18ll;
const long int minGroundHeight = 24ll;
const long int maxGroundHeight = 28ll;

//moving ultrasonic avg
const int lengthAvg = 20; // note this used to be int const
long movingAvgArr[lengthAvg];
long movingAvgSum = 0;
int currentAvgArrayIndex = 0;
long movingAvg;

//////INIT AND SETUP FUNCTIONS////////////////
///////////////////////////////////
void initMovingAvg(){
  //initialize avg array
  for (int i = 0; i < lengthAvg; i++ ) {
    movingAvgArr[i] = 200; /* set element at location i to i + 100 */
  }
  movingAvg = 200;
  movingAvgSum = 200*lengthAvg;
  return;
}



void setup(){
  
    // Open serial port to PC (hardware UART)
    Serial.begin(9600);      

    //ultrasonic setup
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPin, INPUT); // Sets the echoPin as an Input
    
}



/////////HELPER FUNCTIONS///////////////
////////////////////////////////////////

//get the ultrasonic distance reading from the sensor
long ultrasonicDistance(){
    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    long duration = pulseIn(echoPin, HIGH, 4000);
    // Calculating the distance
    long distance= duration*0.034/2;
    // Prints the distance on the Serial Monitor

    return distance;
}

//change the movingAvg of the ultrasonic sensors value based on the current ultrasonic sensor reading
void changeUltrasonicMovingAvg(){
    long distance = 0;
    distance = ultrasonicDistance();

    //if the distance measured is an unrealistic number then do not change the moving average
    if (distance < minPoleHeight || (distance > maxPoleHeight && distance < minGroundHeight) || distance > maxGroundHeight){
      return;
    }

    //change the moving avg based on the distance measured
    movingAvgSum -= movingAvgArr[currentAvgArrayIndex];
    movingAvgSum += distance;
    movingAvgArr[currentAvgArrayIndex] = distance;
    movingAvg = movingAvgSum/lengthAvg;
    currentAvgArrayIndex ++;
    if (currentAvgArrayIndex == lengthAvg){
      currentAvgArrayIndex = 0;
    }
    return;
}


////////////////MAIN LOOP//////////////////
///////////////////////////////////////////



void loop(){
  
  
    initMovingAvg();
    while (true){
        changeUltrasonicMovingAvg();
        Serial.println(movingAvg);
    }  
}



/////////END////////////
////////////////////////
