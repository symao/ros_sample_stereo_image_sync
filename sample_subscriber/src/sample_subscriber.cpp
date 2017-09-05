#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>


void callback(const sensor_msgs::ImageConstPtr& msg_image_left, const sensor_msgs::ImageConstPtr& msg_image_right)
{
    auto img_left_ptr = cv_bridge::toCvCopy(msg_image_left, "bgr8");
    auto img_right_ptr = cv_bridge::toCvCopy(msg_image_right, "bgr8");

    std::cout<<img_left_ptr->header.stamp<<" == "
            <<img_right_ptr->header.stamp<<" "
            <<img_left_ptr->header.seq<<" == "
            <<img_right_ptr->header.seq<<" "
            <<"Time diff: "<<img_left_ptr->header.stamp - img_right_ptr->header.stamp<<std::endl;

    ros::Duration(1).sleep();
}

int main(int argc, char**argv)
{ 
    ros::init(argc, argv, "landmark_detect_node");
    ros::NodeHandle nh;
    message_filters::Subscriber<sensor_msgs::Image> sub_img_left(nh, "/cv_camera/image_left", 1);
    message_filters::Subscriber<sensor_msgs::Image> sub_img_right(nh, "/cv_camera/image_right", 1);
    message_filters::TimeSynchronizer<sensor_msgs::Image, sensor_msgs::Image> sync(sub_img_left, sub_img_right, 5);  //queue_size
    sync.registerCallback(boost::bind(&callback, _1, _2));
    ros::spin();
    return 0;
}
