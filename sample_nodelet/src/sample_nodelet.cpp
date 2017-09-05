#include <pluginlib/class_list_macros.h>
#include <ros/ros.h>
#include <sample_nodelet.h>

PLUGINLIB_EXPORT_CLASS(example_pkg::SampleNodelet, nodelet::Nodelet)

namespace example_pkg
{
    void SampleNodelet::onInit()
    {
        NODELET_DEBUG("Initializing nodelet...");
        ROS_INFO("Nodelet is Ok for test!!");
    }
}