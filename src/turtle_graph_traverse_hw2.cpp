#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Int32.h"

#include "geometry_msgs/Twist.h"

#include "turtlesim/Pose.h"

#include <stdlib.h>
#include <time.h>

//the constants contain the x and y coordinates that the turtle needs to visit
#include <cs309_turtlesim/turtle_constants.h>

//global publisher for velocity
ros::Publisher velocity_pub;

//the turtle's current pose gets stored here
turtlesim::Pose current_pose;

void pose_cb(const turtlesim::Pose::ConstPtr& msg){
    current_pose = *msg;
}

int main(int argc, char **argv){
    
    //initialize the node
    ros::init(argc, argv, "traveling_salesturtle");
    
    //instantiate the node handle which is used for creating publishers and subscribers
    ros::NodeHandle n;
    
    //publisher for velocity commands
    velocity_pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1);

    //subscriber for the turtle's pose
    ros::Subscriber sub_pose = n.subscribe("/turtle1/pose", 1, pose_cb );

    ros::Publisher pub = n.advertise<std_msgs::Int32>("/rand", 1000);
    srand(time(NULL));
   
    //your code for solving the traveling salesmane problem goes here (of course you can define helper functions above the main function)
    ros::Rate r(10);
    while(ros::ok()) {
        ROS_INFO("This is an annoying message!");
        std_msgs::Int32 msg;
        msg.data = rand() * RAND_MAX;
        pub.publish(msg);
        r.sleep();
        ros::spinOnce();
    }
    
    return 0;
}
