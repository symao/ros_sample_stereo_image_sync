#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>

#include <pluginlib/class_list_macros.h>
#include <nodelet/nodelet.h>

namespace sample_subscriber
{
    class sample_subscriber_nodelet: public nodelet::Nodelet
    {
    public:
        sample_subscriber_nodelet():sync(NULL){}
        virtual ~sample_subscriber_nodelet()
        {
            if(!sync) {delete sync;}
        }
        virtual void onInit()
        {
            ros::NodeHandle& nh = getNodeHandle();
            sub_img_left.subscribe(nh, "/cv_camera/image_left", 1);
            sub_img_right.subscribe(nh, "/cv_camera/image_right", 1);
            sync = new message_filters::TimeSynchronizer<sensor_msgs::Image, sensor_msgs::Image>(sub_img_left, sub_img_right, 5);  //queue_size
            sync->registerCallback(boost::bind(&sample_subscriber_nodelet::callback, this, _1, _2));
        }
    private:
        message_filters::Subscriber<sensor_msgs::Image> sub_img_left,sub_img_right;
        message_filters::TimeSynchronizer<sensor_msgs::Image, sensor_msgs::Image>* sync;

        void callback(const sensor_msgs::ImageConstPtr& msg_image_left, const sensor_msgs::ImageConstPtr& msg_image_right)
        {
            auto img_left_ptr = cv_bridge::toCvCopy(msg_image_left, "bgr8");
            auto img_right_ptr = cv_bridge::toCvCopy(msg_image_right, "bgr8");
            std::cout<<"Sub "<<img_left_ptr->header.seq
                    <<img_left_ptr->header.stamp<<" == "
                    <<img_right_ptr->header.stamp<<" "
                    <<img_left_ptr->header.seq<<" == "
                    <<img_right_ptr->header.seq<<" "
                    <<"Time diff: "<<img_left_ptr->header.stamp - img_right_ptr->header.stamp<<std::endl;
            // ros::Duration(1).sleep();
        }
    };

    PLUGINLIB_DECLARE_CLASS(sample_subscriber, sample_subscriber_nodelet, sample_subscriber::sample_subscriber_nodelet, nodelet::Nodelet);

}
