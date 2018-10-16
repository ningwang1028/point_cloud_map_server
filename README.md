# point_cloud_map_server
## Details
point_cloud_map_server is a ROS package used to load or save point cloud map.
### Node
* map_loader  
load point cloud from pcd file and publish with sensor_msgs::PointCloud2 message on topic /point_cloud_map.  
* map_saver    
receive point cloud from topic /point_cloud_map and save to pcd pile.  
## Build
  ```shell 
  cd ${catkin_workspace}/src
  git clone https://github.com/ningwang1028/point_cloud_map_server.git
  cd ..
  catkin_make
  ```
## Run 
* save map
  ```shell  
  rosrun point_cloud_map_server map_loader file_name
  ```
* load map
    ```shell  
  rosrun point_cloud_map_server map_saver xxx.pcd 
  ```
