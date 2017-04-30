#include "ros/ros.h"
#include <iostream>
#include <stdlib.h>
#include "localization/Samples.h"

using namespace std;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "talker");
    ros::NodeHandle n;
    ros::Publisher chatter_pub = n.advertise<localization::Samples>("samples", 1000);
    ros::Rate loop_rate(10);
    localization::Samples msg;
    int i=0,j=0;  
    for( i=0;i<25;i++)
    {
        msg.local_x[i]=i;
        msg.local_y[i]=i+1;
        msg.local_theta[i]=i+2;
        msg.world_x[i]=i+3;
	msg.world_y[i]=i+4;
    } 
    while (ros::ok())
    {
        //ROS_INFO("I heard: [%f]", msg.local_x[2]);
        chatter_pub.publish(msg);
        ros::spinOnce();
        loop_rate.sleep();
        i++;
    }
    return 0;
}
