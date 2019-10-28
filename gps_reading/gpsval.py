#!/usr/bin/env python
import rospy
import time
from geometry_msgs.msg import Point
import serial

point = Point()

arduino = serial.Serial('/dev/ttyUSB0',9600)


def talker():
        pub = rospy.Publisher('gpsval', Point, queue_size=100)
        rospy.init_node('gps_sender', anonymous=True)
        rate = rospy.Rate(100)
        
        # 10hz
        while not rospy.is_shutdown():
            rawdata=[]
            rawdata=str(arduino.readline())
        #rospy.loginfo(point)
            if rawdata[0] == 'L':
                lat=float(rawdata[4:14])
                lon=float(rawdata[18:29])
                point.x= lat
                point.y= lon
                point.z= 0
                print(lat)
                print(lon)
                pub.publish(point)
                rate.sleep()
        #rospy.spin()

if __name__ == '__main__':
    talker()
    