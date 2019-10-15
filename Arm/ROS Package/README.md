ROS nodes for the robotic arm.
For using this node for controlling the robotic arm you first need to install the joy ros package from 
"http://wiki.ros.org/joy"
These ros nodes are in a package named  "joystick_arm_control". So first create a package with this name with dependencies rospy std_msgs sensor_msgs geometry_msgs.
Then place these nodes inside the script directory inside the package.
The launch file will also launch the required joy node and set the parameter for the joystick as js0 by default. If your ls /dev/input command shows input other than js0 (like js1 or js2) change the value of the parameter in the launch file accordingly.

