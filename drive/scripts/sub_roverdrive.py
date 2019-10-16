#!/usr/bin/env python
import rospy
from drive.msg import drive_msg
import serial  
import time

arduino = serial.Serial('/dev/ttyACM1', 9600, timeout=.1)


def callback(data):
    valL=data.lpwm
    if (valL == 0.0):
    	valL=str("000")
    else:    
	valL=str(int(valL))
    
    valR=data.rpwm
    if (valR == 0.0):
    	valR=str("000")
    else:  
        valR=str(int(valR))
    
    LvalD=data.ldir
    if (LvalD == 0):
    	LvalD=str("0")
    else:  
	LvalD=str("1")
    
    RvalD=data.rdir
    if (RvalD == 0):
    	RvalD=str("0")
    else:  
	RvalD=str("1")
    
    val= valL + " " + valR + " " + LvalD + " " + RvalD + '\0'
    
    rospy.loginfo("0123456789")
    rospy.loginfo(val)
    arduino.write(val)
    
def listener():
    #data.lpwm=0
    #data.rpwm=0
    #data.ldir=0
    #data.rdir=0
    rospy.init_node('pwmreciver', anonymous=True)

    rospy.Subscriber("rover_drive", drive_msg , callback)

    rospy.spin()

if __name__ == '__main__':
    listener()

