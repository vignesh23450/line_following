#include <NewPing.h> 
#define IR_SENSOR_RIGHT 11
#define IR_SENSOR_LEFT 12
#define MOTOR_SPEED 180
#define trigPin1 8
#define echoPin1 9

const int LeftMotorForward = 6;
const int LeftMotorBackward = 7;
const int RightMotorForward = 5;
const int RightMotorBackward = 4;
long duration, distance, RightSensor,BackSensor,FrontSensor,LeftSensor;


void setup() {
 Serial.begin (9600);
pinMode(trigPin1, OUTPUT);
pinMode(echoPin1, INPUT);
pinMode(RightMotorForward, OUTPUT);
pinMode(LeftMotorForward, OUTPUT);
pinMode(LeftMotorBackward, OUTPUT);
pinMode(RightMotorBackward, OUTPUT);
 pinMode(IR_SENSOR_RIGHT, INPUT);
pinMode(IR_SENSOR_LEFT, INPUT);
rotateMotor(0,0);   
  delay(2000);

}

void loop() {
  SonarSensor(trigPin1, echoPin1);
RightSensor = distance;
if (FrontSensor <= 20) {
    moveStop();
    delay(300);
    moveBackward();
    delay(400);
    moveStop();
    delay(300);
    }
else{

  int rightIRSensorValue = digitalRead(IR_SENSOR_RIGHT);
  int leftIRSensorValue = digitalRead(IR_SENSOR_LEFT);

  //If none of the sensors detects black line, then go straight
  if (rightIRSensorValue == LOW && leftIRSensorValue == LOW)
  {
    rotateMotor(MOTOR_SPEED, MOTOR_SPEED);
  }
  //If right sensor detects black line, then turn right
  else if (rightIRSensorValue == HIGH && leftIRSensorValue == LOW )
  {
      rotateMotor(-MOTOR_SPEED, MOTOR_SPEED); 
  }
  //If left sensor detects black line, then turn left  
  else if (rightIRSensorValue == LOW && leftIRSensorValue == HIGH )
  {
      rotateMotor(MOTOR_SPEED, -MOTOR_SPEED); 
  } 
  //If both the sensors detect black line, then stop 
  else 
  {
    rotateMotor(0, 0);
  }
}

}
void SonarSensor(int trigPin,int echoPin)
{
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = ((duration/2) / 29.1);

}

void moveStop() {

  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
}
void moveForward() 
{
  //goesForward = true;
  //if (!goesForward) 
  {

    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(RightMotorForward, HIGH);
    digitalWrite(LeftMotorBackward, LOW);
    digitalWrite(RightMotorBackward, LOW);
  }
}

void moveBackward() 
{
  //goesForward = false;
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);

  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
}

void turnRight() {

  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);

  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);

  delay(500);

  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);

  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
}

void turnLeft() {

  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorForward, HIGH);

  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);

  delay(500);

  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);

  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
}
void rotateMotor(int rightMotorSpeed, int leftMotorSpeed)
{
  
  if (rightMotorSpeed < 0)
  {
          turnRight();
 
  }
  else if (rightMotorSpeed > 0)
  {
     turnLeft();      
  }
  else
  {
     moveStop();      
  }

  if (leftMotorSpeed < 0)
  {
     turnLeft();   
  }
  else if (leftMotorSpeed > 0)
  {
    turnRight();     
  }
  else 
  {
    moveStop();     
  }   
}
