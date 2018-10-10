#include <ros/ros.h>
#include "geometry_msgs/Twist.h"
#include "std_msgs/Float32MultiArray.h"


#define NODE_NAME "vw_generator"
#define SUBSCRIBE_WHEEL_VEL "wheel_velocity"
#define ADVERTISE_VW_ESTIMATE "vw_estimate"
#define BUFFER_SIZE 5
#define MESSAGE_FREQUENCY 20
#define LOOP_FREQ 20

#define AXEL_WIDTH 0.285 //meters


ros::Publisher vw_estimator;
ros::Subscriber wheel_vel_sub;

std_msgs::Float32MultiArray vw_estimate_msg;

float current_L_vel = 0;
float current_R_vel = 0;

float vhat = 0;
float what = 0;


void encoderCallback(const std_msgs::Float32MultiArray::ConstPtr& array)
{
    current_L_vel = array->data[0];
    current_R_vel = array->data[1];

    vhat = 0.5*(current_R_vel+current_L_vel);
    what = (current_R_vel-current_L_vel)/AXEL_WIDTH;

	vw_estimate_msg.data.push_back(vhat);   // add info to message (arra$
	vw_estimate_msg.data.push_back(what);

	vw_estimator.publish(vw_estimate_msg);    // publish data
	vw_estimate_msg.data.clear();
}


int main(int argc, char** argv)
{
	ros::init(argc, argv, NODE_NAME);
	ros::NodeHandle nh;
	
	vw_estimator = nh.advertise<std_msgs::Float32MultiArray>(ADVERTISE_VW_ESTIMATE, BUFFER_SIZE);
	wheel_vel_sub = nh.subscribe<std_msgs::Float32MultiArray>(SUBSCRIBE_WHEEL_VEL, BUFFER_SIZE, encoderCallback);

	ros::spin();
	return 0;
}

