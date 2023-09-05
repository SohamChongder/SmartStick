#include<Servo.h>

const int leftForward1 = 5;
const int leftBackward1 = 4;

const int leftForward2 = 10;
const int leftBackward2 = 9;
const int rightForward2 = 7;
const int rightBackward2 =8;

const int trigPinLeft=11;
const int echoPinFront=9;
const int echoPinRight=12;
const int echoPinLeft=13;
const int trigPinRight=3;
const int trigPinFront=2;



Servo turn;

void setup() 
{
  pinMode(leftForward1, OUTPUT);
  pinMode(leftBackward1, OUTPUT);
  pinMode(leftForward2,OUTPUT);
  pinMode(leftBackward2, OUTPUT);
  pinMode(rightForward2, OUTPUT);
  pinMode(rightBackward2, OUTPUT);
  pinMode(trigPinRight,OUTPUT);
  pinMode(trigPinLeft,OUTPUT);
  pinMode(trigPinFront,OUTPUT);
  pinMode(echoPinFront,INPUT);
  pinMode(echoPinLeft,INPUT);
  pinMode(echoPinRight,INPUT);
  turn.attach(6);
  turn.write(90);
  Serial.begin(9600);

}



void front()
{//to go in front
  digitalWrite(leftForward1, HIGH);
  digitalWrite(leftBackward1, LOW);
  digitalWrite(leftForward2, HIGH);
  digitalWrite(leftBackward2, LOW);
  digitalWrite(rightForward2, HIGH);
  digitalWrite(rightBackward2, LOW);
}

void back()
{// to go backwards
  digitalWrite(leftForward1, LOW);
  digitalWrite(leftBackward1, HIGH);
  digitalWrite(leftForward2, LOW);
  digitalWrite(leftBackward2, HIGH);
  digitalWrite(rightForward2, LOW);
  digitalWrite(rightBackward2, HIGH);
}


void right()
{//to turn right
  int i;
  turn.write(90);
  for(i=90;i<=120;i++)
  {
    turn.write(i);
    delay(100);    
  }
  
  for(i=120;i>=90;i--)
  {
    turn.write(i);
    delay(100);
  }
  
}

void left()
{//to turn left
  int i;
  turn.write(90);
  for(i=90;i>=60;i--)
  {
    turn.write(i);
    delay(100);    
  }
  
  for(i=60;i<=90;i++)
  {
    turn.write(i);
    delay(100);
  }
  
}

void stop()
{//to stop
  digitalWrite(leftForward1, LOW);
  digitalWrite(leftBackward1, LOW);
  digitalWrite(leftForward2, LOW);
  digitalWrite(leftBackward2, LOW);
  digitalWrite(rightForward2, LOW);
  digitalWrite(rightBackward2, LOW);
}

boolean isRight()
{
  float duration,distance;
  //to check if turning right is feasible
   digitalWrite(trigPinRight, LOW);
  delayMicroseconds(3);
  digitalWrite(trigPinRight, HIGH);
  delayMicroseconds(11);
  digitalWrite(trigPinRight, LOW);
  duration = pulseIn(echoPinRight,HIGH);
  distance = duration * 0.034 / 2; 
  Serial.println(distance);
  if(distance<100)
  return false;
  else
   return true;
   
  
}

boolean isLeft()
{
  float duration,distance;
  //to check if turning left is feasible
   digitalWrite(trigPinLeft, LOW);
  delayMicroseconds(3);
  digitalWrite(trigPinLeft, HIGH);
  delayMicroseconds(11);
  digitalWrite(trigPinLeft, LOW);
  duration = pulseIn(echoPinLeft,HIGH);
  distance = duration * 0.034 / 2; 
  Serial.println(distance);
  if(distance<100)
    return false;
  else
    return true;
}

boolean isFront()
{
  float duration,distance;
  //to check if turning right is feasible
   digitalWrite(trigPinFront, LOW);
  delayMicroseconds(3);
  digitalWrite(trigPinFront, HIGH);
  delayMicroseconds(11);
  digitalWrite(trigPinFront, LOW);
  duration = pulseIn(echoPinFront,HIGH);
  distance = duration * 0.034 / 2; 
  Serial.println(distance);
  if(distance<100)
  return false;
  else
  return true;
}


void loop()
{
 if(isFront())
 {
   front();
   
 }
 else
  {
  
   delay(500);
    if(isRight()&&isLeft())
    {
      int c = random(1,3);
      if(c==1)
      {
        front();
        left();
        delay(200);
      }
      if(c==2)
      {
        front();
        right();
        delay(200);
      }
    }
    else if(isRight()&&!(isLeft()))
    {
      front();
      right();
      delay(200);
    }
    else if(isLeft()&&!(isRight()))
    {
      front();
      left();
      delay(200);
    }
    else
    {
      while(!(isLeft()||isRight()))
      back();
    }
  }   
}
