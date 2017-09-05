#include <ros/ros.h>
#include <ros/package.h>
#include <image_transport/image_transport.h>
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "talker");

    ros::NodeHandle n;
    image_transport::ImageTransport it(n);
    image_transport::Publisher pub_left = it.advertise("cv_camera/image_left", 1);
    image_transport::Publisher pub_right = it.advertise("cv_camera/image_right", 1);

    ros::Rate loop_rate(10);
    int count = 0;

    cv::Mat temp_img = cv::imread(ros::package::getPath("sample_publisher")+"/data/lena.jpg");

    while (ros::ok())
    {
        ros::Time ts = ros::Time::now();
        cv::Mat img_left = temp_img.clone();
        cv::Mat img_right = temp_img.clone();
        sensor_msgs::ImagePtr msg_left = cv_bridge::CvImage(std_msgs::Header(), "bgr8", img_left).toImageMsg();
        sensor_msgs::ImagePtr msg_right = cv_bridge::CvImage(std_msgs::Header(), "bgr8", img_right).toImageMsg();

        msg_left->header.stamp = msg_right->header.stamp = ts;
        msg_left->header.seq = msg_right->header.seq = count;

       // if(count%2==0){msg_right->header.stamp.nsec += 1;}
        std::cout<<count<<" "<<msg_left->header.stamp<<" "<<msg_right->header.stamp<<std::endl;

        pub_left.publish(msg_left);
        pub_right.publish(msg_right);

        ros::spinOnce();

        loop_rate.sleep();

        ++count;
    }


  return 0;
}
