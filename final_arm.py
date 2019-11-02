#!/usr/bin/env python
import rospy
from sensor_msgs.msg import Joy
from pcl_msgs.msg import Vertices
arm = Vertices()
arm.vertices = [0, 0, 0, 0, 0, 0, 0]
actuator_x=0
actuator_y=0
base=0
wrist=0
gripper_rotation=0
gripper_jaw=0

def move_base(data):
        
        global base
        bl= data.buttons[4]
        br=data.buttons[5]

        if((br == 0 and bl == 0) or (br==1 and bl ==1)) :
                base = 0
        if(br == 1 and bl == 0) :
                base = 1
        if(br == 0 and bl == 1) :
                base = 2

        arm.vertices[2] = base



def move_gripper(data):

        global wrist
        global gripper_jaw
        global gripper_rotation

        wu = data.buttons[0]
        wd = data.buttons[2]

        wr = data.buttons[1]
        wl = data.buttons[3]

        jclose = data.buttons[7]
        jopen = data.buttons[6]

        if((wu == 0 and wd == 0) or (wu==1 and wd ==1)) :
                wrist = 0
        if(wu == 1 and wd == 0) :
                wrist = 1
        if(wu == 0 and wd == 1) :
                wrist = 2

        if((wl == 0 and wr == 0) or (wl==1 and wr ==1)) :
                gripper_rotation = 0
        if(wl == 1 and wr == 0) :
                gripper_rotation = 1
        if(wl == 0 and wr == 1) :
                gripper_rotation = 2

        if((jclose == 0 and jopen == 0) or (jclose==1 and jopen ==1)) :
                gripper_jaw = 0
        if(jclose == 1 and jopen == 0) :
                gripper_jaw = 1
        if(jclose == 0 and jopen == 1) :
                gripper_jaw = 2

        arm.vertices[3] = wrist
        arm.vertices[4] = gripper_rotation
        arm.vertices[5] = gripper_jaw
        
        
def move_actuators(data):

        global actuator_x
        global actuator_y
        x = data.axes[0]
        y = data.axes[1]

        if(x==0):
                actuator_x =0
        if(x==1):
                actuator_x=1
        if(x==-1):
                actuator_x=2
        
        if(y==0):
                actuator_y=0
        if(y==1):
                actuator_y=1
        if(y==-1):
                actuator_y=2
        
        arm.vertices[0] = actuator_x
        arm.vertices[1] = actuator_y


        
def move_arm(data):
    rate = rospy.Rate(10)
    move_actuators(data)
    move_gripper(data)
    move_base(data)
    pub = rospy.Publisher('move_arm', Vertices ,queue_size=1)  #sends the Vertices message to "robotic_arm" topic
    pub.publish(arm)
    rate.sleep()

def joy_to_arm(): #function to recieve values from joystick through joy_node of joy package
    rospy.init_node('joy_to_arm', anonymous=True)
    rate = rospy.Rate(10)
    rospy.Subscriber("joy_for_arm", Joy, move_arm, queue_size=1)
    rate.sleep()
    rospy.spin()
    
if __name__ == '__main__':
    joy_to_arm()
