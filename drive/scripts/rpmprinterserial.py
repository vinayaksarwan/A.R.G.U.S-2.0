#!/usr/bin/env python
import rospy
import time
import serial



arduino = serial.Serial('/dev/ttyACM1',9600)


def gpsvalprinter():
        #pub = rospy.Publisher('gpsval', Point, queue_size=100)
        #rospy.init_node('gps_sender', anonymous=True)
        #rate = rospy.Rate(100)
        
        # 10hz
        #while not rospy.is_shutdown():
        i=0
        rawdata=[]
        rawdata=str(arduino.readline())
        n=len(rawdata)
        print(rawdata)
        #rospy.loginfo(point)
        while(rawdata[i]!=','):
            i=i+1
        s=i
        lat=float(rawdata[0:s-1])
        lon=float(rawdata[s+1:n])
        print("lat:"+str(lat))
        print("lon:"+str(lon))
        #pub.publish(point)
        #rate.sleep()
        #rospy.spin()

while True:
    gpsvalprinter()
    