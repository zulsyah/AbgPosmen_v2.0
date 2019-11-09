#include <ros/ros.h>
#include <std_msgs/Float32MultiArray.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Empty.h>
#include <std_msgs/UInt8.h>

#define TAKEOFF 12
#define LANDING 11
#define FORWARD 17
#define BACKWARD 18
#define LEFT 19
#define RIGHT 20

int id = 0;
bool test = false;

ros::Publisher action_pub, takeoff_pub, land_pub, camera_pub;

geometry_msgs::Twist set_vel, set_cam;
std_msgs::Empty emptyMsg;

void objectCallback(const std_msgs::Float32MultiArrayPtr &object)
{
   if (object->data.size() > 0)
   {
      id = object->data[0];

      switch (id)
      {

      case TAKEOFF:

         takeoff_pub.publish(emptyMsg);
	 set_cam.angular.y = -50;
	 set_cam.angular.z = 0;
	 ROS_INFO("Drone taking off now!");
         break;

      case LANDING:
         //land_pub.publish(emptyMsg);
	 test = false;
	 set_cam.angular.y = 0;
	 set_cam.angular.z = 0;
	 ROS_INFO("Drone landing now!");
         break;

      case FORWARD:
	
	 ROS_INFO("Drone move forward");
	 test = true;
         set_vel.linear.x = 1*0.05;
         set_vel.angular.z = 0;
         break;

      case BACKWARD:
	
	 ROS_INFO("Drone move backward");
         set_vel.linear.x = -1;
         set_vel.angular.z = 0;
         break;

      case LEFT:
	
	 ROS_INFO("Drone move left");
         set_vel.linear.x = 0;
         set_vel.angular.z = 1;
         break;

      case RIGHT:
	
	 ROS_INFO("Drone move right");
         set_vel.linear.x = 0;
         set_vel.angular.z = -1;
         break;

      default: // other object
         set_vel.linear.x = 0;
         set_vel.angular.z = 0;
      }
      action_pub.publish(set_vel);
      camera_pub.publish(set_cam);
   }
   else
   {

      if (test == true){

	ROS_INFO("hey dah jumpa");
	
        set_vel.linear.x = 0.0;
        set_vel.angular.z = 0;
        action_pub.publish(set_vel);

	land_pub.publish(emptyMsg);
      }

	if (test == false){
	ROS_INFO("hey tgh jalan");
        set_vel.linear.x = 0.025;
        set_vel.angular.z = 0;
        action_pub.publish(set_vel);
      }

	
   }
}

int main(int argc, char **argv)
{

   ros::init(argc, argv, "AbgPosmen_bebop");
   ros::NodeHandle nh;
   ros::Rate loop_rate(50);
   ros::Subscriber sub = nh.subscribe("/objects", 1, objectCallback);
   action_pub = nh.advertise<geometry_msgs::Twist>("bebop/cmd_vel", 1);
   takeoff_pub = nh.advertise<std_msgs::Empty>("bebop/takeoff", 1);
   land_pub = nh.advertise<std_msgs::Empty>("bebop/land", 1);
   camera_pub = nh.advertise<geometry_msgs::Twist>("bebop/camera_control", 1);
   ROS_INFO("Scan your ID in front of drone camera!");
   while (ros::ok())
   {
      ros::spinOnce();
      loop_rate.sleep();
   }
}
