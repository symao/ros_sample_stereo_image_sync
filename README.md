##How to compile
cd ~/catkin_ws/src
git clone https://github.com/symao/ros_sample_stereo_image_sync.git
cd ..
catkin_make

##How to run
###1. run nodelet
roslaunch sample_subscriber sample_pubsub.launch

###2. run node
roscore
rosrun sample_publisher sample_publisher_node
rosrun sample_subscriber sample_subscriber_node
