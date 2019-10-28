#!/usr/bin/env python
import rospy
from geometry_msgs.msg import Point

def callback(data):
    lat=data.x
    lon=data.y
    rospy.loginfo("latitude"+lat)
    rospy.loginfo("longitude"+lon)
    
def listener():

    
    rospy.init_node('getGPSval', anonymous=True)

    rospy.Subscriber("gpsval", Point, callback)

    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()

if __name__ == '__main__':
    listener()