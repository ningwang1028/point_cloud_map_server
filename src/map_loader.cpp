#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl_conversions/pcl_conversions.h>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "map_loader");
    ros::console::set_logger_level(ROSCONSOLE_DEFAULT_NAME, ros::console::levels::Debug);

    ros::NodeHandle nh;
    ros::Publisher map_pub = nh.advertise<sensor_msgs::PointCloud2>("point_cloud_map", 1, true);

    if (argc != 2) {
        ROS_ERROR("Error command!");
        return 1;
    }

    std::string file_name(argv[1]);

    pcl::PointCloud<pcl::PointXYZI> point_cloud;

    ROS_INFO("Start load map ...");
    if (pcl::io::loadPCDFile<pcl::PointXYZI> (file_name, point_cloud) == -1) {
        ROS_ERROR("Couldn't read file %s \n", file_name.c_str());
        return 1;
    }

    ROS_INFO("Load map successful.");

    sensor_msgs::PointCloud2 point_cloud_msg;
    pcl::toROSMsg(point_cloud, point_cloud_msg);
    point_cloud_msg.header.stamp = ros::Time::now();
    point_cloud_msg.header.frame_id = "map";
    map_pub.publish(point_cloud_msg);

    ros::spin();

    return 0;
}
