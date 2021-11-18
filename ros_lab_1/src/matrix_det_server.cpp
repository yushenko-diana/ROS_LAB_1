#include "ros/ros.h"
#include "ros_lab_1/Matrix.h"
#include "std_msgs/Float32.h"

ros::ServiceServer service;
ros::Publisher eventh_pub;
ros::Subscriber eventh_sub;

bool calc_determinant(ros_lab_1::Matrix::Request  &req,
         ros_lab_1::Matrix::Response &res)
{
  res.det = req.a11 * req.a22 * req.a33 + 
  req.a12 * req.a23 * req.a31 + 
  req.a13 * req.a31 * req.a32 -
  req.a13 * req.a22 * req.a31 -
  req.a11 * req.a23 * req.a32 - 
  req.a12 * req.a21 * req.a33;
  ROS_INFO("sending back response: [%ld]", (long int)res.det);
  std_msgs::Float32 det;
  det.data = res.det;
  eventh_pub.publish(det);
  return true;
}

void eventh_callback(const std_msgs::Float32::ConstPtr& msg){
  float num = msg->data;
  if ((int)num % 2 == 0)
  {
    ROS_INFO("even");
    }
  else
  {
    ROS_INFO("odd");
  }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "matrix_det_server");
  ros::NodeHandle n;

  service = n.advertiseService("matrix_det", calc_determinant);
  eventh_pub = n.advertise<std_msgs::Float32>("eventh", 1000);
  eventh_sub = n.subscribe("eventh", 1000, eventh_callback);

  ROS_INFO("Ready to calc determinant.");
  ros::spin();

  return 0;
}