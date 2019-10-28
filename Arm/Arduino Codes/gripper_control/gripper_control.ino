/*
 * rosserial Servo Control Example
 *
 * This sketch demonstrates the control of hobby R/C servos
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

 
#include <ros.h>
#include <SoftwareSerial.h>
#include <Rhino.h>
#include <std_msgs/Char.h>
int x = 0;

ros::NodeHandle  nh;
Rhino motor1(9,10);  // RX( -> TX of motor), TX( -> RX of motor)


void Rhino_cb( const std_msgs::Char & cmd_msg){
  if(cmd_msg.data == 'U')
  {
      x+=5;
      if(x<180)
      
      motor1.gotoAngleDeg(x);
      
  }
  if(cmd_msg.data == 'D')
  {
      x-=5;
      motor1.gotoAngleDeg(x);
  }
    
}


ros::Subscriber<std_msgs::Char> sub("gripper_motion", Rhino_cb);

void setup(){
  pinMode(13, OUTPUT);
  delay(2000);
  motor1.printOutput(1);  // enables Serial printing of function outputs
  motor1.init();  // initializes the motor and sets current position as origin

  nh.initNode();
  nh.subscribe(sub);
  
  
}

void loop(){
  nh.spinOnce();
  delay(1);
}
