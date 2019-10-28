#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif


#include <ros.h>
#include <std_msgs/UInt16.h>
#include <geometry_msgs/Point.h>

#include <SoftwareSerial.h>
#include <Rhino.h>
#include <std_msgs/Char.h>
int x = 0;

ros::NodeHandle  nh;
Rhino motor1(9,10); 

int pwm1pin = 9, pwm2pin = 11, pwm3pin =12, dir1,dir2, dir3;
int dirpin1=6, dirpin2=7, dirpin3 = 8;
int xpotpin = A0, ypotpin = A1, zpotpin = A2; 

void Rhino_cb( const std_msgs::Char & grip_msg){
  if(grip_msg.data == 'U')
  {
      x+=5;
      if(x<180)
      
      motor1.gotoAngleDeg(x);
      
  }
  if(grip_msg.data == 'D')
  {
      x-=5;
      motor1.gotoAngleDeg(x);
  }
    
}

void set_length( const geometry_msgs::Point& cmd_msg)
{
  //Assigning the length values recieved from the ros node to x and y
  int x = cmd_msg.x;
  int y = cmd_msg.y; 

  //mapping the recieved lengths to their respective feedback reference
  int xmap = map(x, 20, 120, 25, 980);
  int ymap = map(y, 20, 120, 25, 980);  

  //taking feedback from actuators for reference
  int xval = analogRead(xpotpin);
  int yval = analogRead(ypotpin);
  
  //comparing the recieved and current reference value for x
  if(xval<xmap)
  {
    dir1 = 0;
  }
  else if(xval>xmap)
  {
    dir1 = 1;
  }

  //comparing the recieved and current reference value for y
  if(yval<ymap)
  {
    dir2 = 0;
  }
  else if(yval>ymap)
  {
    dir2 = 1;
  }

  //checking reference for loop condition
  while((!(xval<(xmap+30) && xval>(xmap-30))) || (!(yval<(ymap+30) && yval>(ymap-30)) ))
  {
    xval = analogRead(xpotpin);
    yval = analogRead(ypotpin);
    
    //comparing current reference with target reference +- 30 for x
    if(xval<(xmap+30) && xval>(xmap-30))
    {
      analogWrite(pwm1pin, 0); //stopping actuator 1
    }
    else
    {
      analogWrite(pwm1pin, 255);
      digitalWrite(dirpin1, dir1);
    }
   
   //comparing current reference with target reference +- 30 for y
   if(yval<(ymap+30) && yval>(ymap-30))
    {
      analogWrite(pwm2pin, 0); //stopping actuator 2
    }
    else
    {
      analogWrite(pwm2pin, 255);
      digitalWrite(dirpin2, dir2);
    }
  }
}

void move_arm( const geometry_msgs::Point& cmd_msg)
{
   set_length(cmd_msg);  
    
}


ros::Subscriber<geometry_msgs::Point> sub("robotic_arm", move_arm); //creating a subscriber that subscribes to the topic /robotic_arm
ros::Subscriber<std_msgs::Char> sub1("gripper_motion", Rhino_cb);

void setup(){
  //setting up pinModes
  pinMode(pwm1pin, OUTPUT);
  pinMode(dirpin1, OUTPUT);
  pinMode(pwm2pin, OUTPUT);
  pinMode(dirpin2, OUTPUT);
  pinMode(xpotpin, INPUT);
  pinMode(ypotpin, INPUT);
  pinMode(13, OUTPUT);
    
    delay(2000);
  
  motor1.printOutput(1);  // enables Serial printing of function outputs
  motor1.init();
  nh.initNode(); //initializing the node
  nh.subscribe(sub);
  nh.subscribe(sub1);
 
}

void loop(){
  nh.spinOnce();
  delay(1);
}
