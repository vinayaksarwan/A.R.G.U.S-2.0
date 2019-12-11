# A.R.G.U.S 2.0
The second version of the Mars rover prototype A.R.G.U.S (Autonomous Robotic Grounded Unmanned Surveillant made by Team Inferno D.T.U (Delhi Technological University).


See the arm folder for Arm


See the drive folder for Drive


copy the two_arduino.launch file in any already built package on jetson. Use this to run rossserial node for two arduinos (for drive and arm) simultaneously.


For cameras. use "sudo apt-get install ros-melodic-usb-cam"


then "roscd usb_cam/launch"


"sudo gedit usb_cam-test.launch"


change /video0 to /video1


then use the command roslaunch usb_cam usb_cam-test.launch on jetson's terminal after exporting ros master uri and ip


then on pc after exportinng ros master uri and ip use command "rosrun rqt_image_view rqt_image_view"


and select the topic usb_cam/image_raw/compressed.
