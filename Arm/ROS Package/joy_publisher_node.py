#!/usr/bin/env python
import rospy
from sensor_msgs.msg import Joy
from geometry_msgs.msg import Point
from numpy import interp

x=0
y=0
z=0

point = Point()

def limit_values(data) :
    
    if data.x > 100 :
        point.x=100
    if data.x < 40 :
        point.x=40

    if data.y > 100:
        point.y=100
    if data.y < 40 :
        point.y=40

    if data.z > 180:
        point.z=180
    if data.z < 0 :
        point.z=0


def find_values(data):
    global x
    global y
    global z
    #scaling the values of lenghts and angle with respect to joystick movement
   #incx =  interp(data.axes[1], [-1, 1], [0, 1]) #length1
    #incy = interp(data.axes[3], [-1, 1], [0, 1])  #length2
    #incz = interp(data.axes[0], [-1, 1], [0, 180])  #Angle
    if(data.buttons[6] == 1):
        incx =  data.axes[0]*5
        incy = data.axes[1]*5
        incz =  data.axes[3]*2
        x = x+ incx
        y = y+ incy
        z = z + incz
        if (data.buttons[4] == 1 and data.buttons[5] == 1) :
            x=40
            y=40
            z=0
    
        point.x = x
        point.y = y
        point.z = z
        limit_values(point)
        rospy.loginfo(point)

def pub_values(data): #publishes the values of length1, length2 and angle to the robotic_arm topic
    rate = rospy.Rate(10) #100 values per second
    find_values(data) #to find the values of lengths and angle 
   # print "x-axis = " , point.x
    #print "y-axis = " , point.y
    #print "z-axis = " , point.z
    pub = rospy.Publisher('robotic_arm', Point ,queue_size=1)  #sends the Point message to "robotic_arm" topic
    if(data.buttons[6] == 1):
        pub.publish(point)
    rate.sleep()

def show_hello(data):
    pub_values(data)

def reciever_joy(): #function to recieve values from joystick through joy_node of joy package
    rospy.init_node('reciever_joy', anonymous=True)
    rate = rospy.Rate(10)
    rospy.Subscriber("joy", Joy, show_hello, queue_size=1)
    rate.sleep()
    rospy.spin()
    
if __name__ == '__main__':
    reciever_joy()
