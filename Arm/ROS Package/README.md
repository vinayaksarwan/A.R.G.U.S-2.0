ROS nodes for the robotic arm.
For using this node for controlling the robotic arm you first need to install the joy ros package from 
"http://wiki.ros.org/joy"
These ros nodes are in a package named  "joystick_arm_control". So first create a package with this name with dependencies rospy std_msgs sensor_msgs geometry_msgs.
Then place these nodes inside the script directory inside the package.
To run the nodes use the launch file robotic_arm_final.launch. It will also run the joy nodes. for the serial nodes run the two_arduino.launch file on jetson.
(First run the drive launch file as the joystick js0 is by default for drive and js1 is by default for arm.).



