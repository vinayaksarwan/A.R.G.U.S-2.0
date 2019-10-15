/*
 * rosserial Servo Control Example
 *
 * This sketch dmonstrates the control of hobby R/C servos
 * using ROS and the arduiono
 * 
 * For the full tutorial write up, visit
 * www.ros.org/wiki/rosserial_arduino_demos
 *
 * For more information on the Arduino Servo Library
 * Checkout :
 * http://www.arduino.cc/en/Reference/Servo
 */

#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif

int pwmpin1=9;
int dirpin1 = 6;
int pwmpin2=11;
int dirpin2= 7;
#include <Servo.h> 
#include <ros.h>
#include <std_msgs/UInt16.h>
#include <geometry_msgs/Point.h>

ros::NodeHandle  nh;

void set_length1(int l)
{
  int x = map(l, 20, 120, 993, 55);
  int dir;
  int val = analogRead(A0);
  Serial.print("Sensor reading :");
  Serial.print(val);
  Serial.println("\n");
  if(val>x)
  {
    dir =0;
  }
  else
  {
    dir = 1;
  }
  while(val!=x)
  {
    val=analogRead(A0);
    analogWrite(pwmpin1, 255);
    digitalWrite(dirpin1, dir); 
  }
    analogWrite(pwmpin1, 0);
    digitalWrite(dirpin1 , 0);
}
void set_length2(int l)
{
  int y = map(l, 20, 120, 993, 55);
  int dir;
  int val = analogRead(A1);
  Serial.print("Sensor reading :");
  Serial.print(val);
  Serial.println("\n");
  if(val>y)
  {
    dir =0;
  }
  else
  {
    dir = 1;
  }
  while(val!=y)
  {
    val=analogRead(A1);
    analogWrite(pwmpin2, 255);
    digitalWrite(dirpin2, dir); 
  }
    analogWrite(pwmpin2, 0);
    digitalWrite(dirpin2 , 0);
}



void servo_cb( const geometry_msgs::Point& cmd_msg){
   set_length1(cmd_msg.x); 
   set_length2(cmd_msg.y);  
  digitalWrite(13, HIGH-digitalRead(13));  //toggle led  
}


ros::Subscriber<geometry_msgs::Point> sub("robotic_arm", servo_cb);

void setup(){
  pinMode(13, OUTPUT);
  pinMode(pwmpin1, OUTPUT);
  pinMode(dirpin1, OUTPUT);
  pinMode(pwmpin2, OUTPUT);
  pinMode(dirpin2, OUTPUT);
  nh.initNode();
  nh.subscribe(sub);
  
   //attach it to pin 9
}

void loop(){
  nh.spinOnce();
  delay(1);
}
