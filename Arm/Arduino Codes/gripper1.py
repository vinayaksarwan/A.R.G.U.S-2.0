#!/usr/bin/env python
import rospy
from sensor_msgs.msg import Joy
from geometry_msgs.msg import Point
from numpy import interp
from std_msgs.msg import Char
wr=0
wl=0
wu=0
wd=0
go=0
gc=0
c= 'S'
def gripper_motor_values(data)
    global wr
    global wl
    global wu
    global wd
    global go
    global gc
    wr=data.buttons[0]
    wl=data.buttons[1]
    wu=data.buttons[2]
    wd=data.buttons[3]
    go=data.buttons[10]
    gc=data.buttons[11]
    if(wr==1 and wl==0)
        c='R'
    if(wr==0 and wl==1)
        c='L'
    if(wu==1 and wd==0)
        c='U'
    if(wu==0 and wd==1)
        c='D'
    if(go==1 and gc==0)
        c='O'
    if(go==0 and gc==1)
        c='C'
    if(wr==0 and wl==0 and wu==0 and wd==0 and go==0 and gc==0)
        c='S'

def move_motor(data):
    rate = rospy.Rate(10)
    move_motor_values(data)
    pub = rospy.Publisher('gripper_motion', Char ,queue_size=1)  #sends the Point message to "robotic_arm" topic
    pub.publish(c)
    rate.sleep()

def gripper_joy(): #function to recieve values from joystick through joy_node of joy package
    rospy.init_node('gripper_joy', anonymous=True)
    rate = rospy.Rate(10)
    rospy.Subscriber("joy", Joy, move_motor, queue_size=1)
    rate.sleep()
    rospy.spin()
if __name__ == '__main__':
    gripper_joy()
