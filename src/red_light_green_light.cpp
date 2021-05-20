#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

#include <ctime>
#include <chrono>
#include <thread>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "red_light_green_light");
    ros::NodeHandle nh;
    ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1);

    geometry_msgs::Twist red_light_twist;
    geometry_msgs::Twist green_light_twist;
    green_light_twist.linear.x = 0.5;

    int driving_forward = 0;
    auto light_change_time = std::chrono::high_resolution_clock::now();
    ros::Rate rate(10);

    while (ros::ok())
    {
        if (driving_forward)
            pub.publish(green_light_twist);
        else
            pub.publish(red_light_twist);
        if (light_change_time < std::chrono::high_resolution_clock::now())
        {
            driving_forward = 1 - driving_forward;
            light_change_time +=  std::chrono::seconds(3);
        }
        rate.sleep();
    }
}
