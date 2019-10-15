Arduino codes and ROS packages for the robotic arm made for the rover prototype.
The arm has 6 Degree of freedom.
Linear actuators are used for the shoulder and elbow joints.
For the base joint DC motor is used with worm gears.
For the wrist joint a Rhino Server motor is used.
The arm is controlled via joystick using the joy package for ROS. The data publishded on the joy_node is mapped to length(incremental) and it is subscribed by arduino which then controls the length of the linear actuators and position of the DC motor by continuously taking feedback.
Right now we are using arduino as a ROS node which subscribes to the topic robotic_arm.
