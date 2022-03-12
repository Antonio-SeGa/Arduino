//ARDUINO OBSTACLE AVOIDING CAR Video - https://youtu.be/h-B42_HXL00//
// Before uploading the code you have to install the necessary library//
//AFMotor Library https://learn.adafruit.com/adafruit-motor-shield/library-install //
//NewPing Library https://github.com/eliteio/Arduino_New_Ping.git // 
//Servo Library https://github.com/arduino-libraries/Servo.git //

#include <AFMotor.h>  
#include <NewPing.h>
#include <Servo.h> 

#define TRIG_PIN A0 
#define ECHO_PIN A1
#define MAX_DISTANCE 150 
#define MAX_SPEED 200 // sets speed of DC  motors
#define MAX_SPEED_OFFSET 20


NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 

AF_DCMotor motor1(1, MOTOR12_64KHZ); 
AF_DCMotor motor2(2, MOTOR12_64KHZ);
AF_DCMotor motor3(3, MOTOR34_64KHZ);
AF_DCMotor motor4(4, MOTOR34_64KHZ);
Servo myservo;   

boolean goesForward=false;
int distance = 100;
int speedSet = 0;

int LED_LEFT = 15;
int LED_RIGHT = 19;
int LED_STOP = 24;
int LED_BACK = 32;

void setup() {

  myservo.attach(10);  
  myservo.write(115); 
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);

  pinMode(LED_LEFT,OUTPUT);
  pinMode(LED_RIGHT,OUTPUT);
  pinMode(LED_STOP,OUTPUT);
  pinMode(LED_BACK,OUTPUT);
}

void loop() {
 int distanceR = 0;
 int distanceL = 0;
 delay(40);
 
 if(distance<=25)
 {
  moveStop();
  digitalWrite(LED_STOP, HIGH);
  delay(3000);
  digitalWrite(LED_STOP, LOW);
  moveBackward();
  delay(200);
  moveStop();
  delay(200);
  distanceR = lookRight();
  delay(200);
  distanceL = lookLeft();
  delay(200);

  if(distanceR>=distanceL)
  {
    turnRight();
    moveStop();
  } 
  
  else
  
  {
    turnLeft();
    moveStop();
  }
 } 
 
 else
 {
  moveForward();
 }
 distance = readPing();
}

int lookRight()
{
    myservo.write(50); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(115); 
    return distance;
}

int lookLeft()
{
    myservo.write(170); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(115); 
    return distance;
    delay(100);
}

int readPing() { 
  delay(100);
  int cm = sonar.ping_cm();
  if(cm==0)
  {
    cm = 250;
  }
  return cm;
}

void moveStop() {
  motor1.run(RELEASE); 
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  } 
  
void moveForward() {

 if(!goesForward)
  {
    goesForward=true;
    motor1.run(FORWARD);      
    motor2.run(FORWARD);
    motor3.run(FORWARD); 
    motor4.run(FORWARD);     
    // slowly bring the speed up to avoid loading down the batteries too quickly
   for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) 
   {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    motor3.setSpeed(speedSet);
    motor4.setSpeed(speedSet);
    delay(5);
   }
  }
}

void moveBackward() {
    goesForward=false;
    motor1.run(BACKWARD);      
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);  
    // slowly bring the speed up to avoid loading down the batteries too quickly
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) 
  {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    motor3.setSpeed(speedSet);
    motor4.setSpeed(speedSet);
    delay(5);
  }
  digitalWrite(LED_BACK, HIGH);
  delay(500);
  digitalWrite(LED_BACK, LOW);
}  

void turnRight() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);     
  delay(500);
  motor1.run(FORWARD);      
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  digitalWrite(LED_RIGHT, HIGH);
  delay(500);
  digitalWrite(LED_RIGHT, LOW);      
} 
 
void turnLeft() {
  motor1.run(BACKWARD);     
  motor2.run(BACKWARD);  
  motor3.run(FORWARD);
  motor4.run(FORWARD);   
  delay(500);
  motor1.run(FORWARD);     
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  
  digitalWrite(LED_LEFT, HIGH);
  delay(500);
  digitalWrite(LED_LEFT, LOW);
  
}
