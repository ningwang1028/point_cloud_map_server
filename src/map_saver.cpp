#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl_conversions/pcl_conversions.h>
#include <dirent.h>

const int MAX_PATH_SIZE = 1000;
std::string file_name;
bool map_saved = false;

void pointCloudMapCallback(const sensor_msgs::PointCloud2::ConstPtr& point_cloud_msg)
{
    ROS_INFO("Start save map ...");
    pcl::PointCloud<pcl::PointXYZI> point_cloud;
    pcl::fromROSMsg(*point_cloud_msg, point_cloud);
    pcl::io::savePCDFileASCII(file_name, point_cloud);
    map_saved = true;
    ROS_INFO("Save map to %s", file_name.c_str());
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "map_saver");
    ros::console::set_logger_level(ROSCONSOLE_DEFAULT_NAME, ros::console::levels::Debug);

    ros::NodeHandle nh;
    ros::Subscriber map_sub = nh.subscribe("point_cloud_map", 1, &pointCloudMapCallback);

    char buffer[MAX_PATH_SIZE];
    if(!getcwd(buffer, MAX_PATH_SIZE)) {
        ROS_ERROR("Path is too long!");
    }

    file_name = buffer;

    if(argc == 1) {
        file_name += "/map.pcd";
    }
    else {
        file_name += "/";
        file_name += argv[1];
        file_name += ".pcd";
    }

    ROS_INFO("Waiting for map ...");

    while(!map_saved && ros::ok()) {
        ros::spinOnce();
    }

    return 0;
}
