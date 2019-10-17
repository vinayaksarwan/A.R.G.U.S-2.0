/*
This sketch instructs the motor to go through 90 degrees.
Connect the TX pin coming out of the motor(orange wire) to pin 9 on Arduino.
Connect the RX pin coming out of the motor(yellow wire) to pin 10 on Arduino.
Remember to give common ground connection to the motor and the Arduino.
*/
#include <SoftwareSerial.h>
#include <Rhino.h>


Rhino motor1(9,10);	// RX( -> TX of motor), TX( -> RX of motor)

void setup()
{
  delay(2000);
  motor1.printOutput(1);	// enables Serial printing of function outputs
  motor1.init();	// initializes the motor and sets current position as origin
  	// instructs motor to rotate by 90 degrees
}

void loop()
{
  int pos;
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    motor1.gotoAngleDeg(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    motor1.gotoAngleDeg(pos);            // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  
}
