#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  ros::init(argc, argv, "simple_navigation_goals");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  //wait for the action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal1;
  move_base_msgs::MoveBaseGoal goal2;
  // move_base_msgs::MoveBaseGoal goal3;
  //move_base_msgs::MoveBaseGoal goal4;

  //First goal for the robot
  goal1.target_pose.header.frame_id = "base_link";
  goal1.target_pose.header.stamp = ros::Time::now();

  goal1.target_pose.pose.position.x = 1.0;
  goal1.target_pose.pose.orientation.w = 1.0;

  //Second goal for the robot
  goal2.target_pose.header.frame_id = "base_link";
  goal2.target_pose.header.stamp = ros::Time::now();

  goal2.target_pose.pose.position.x = -1.0;
  goal2.target_pose.pose.orientation.w = -1.0;
  
  //Seding the first goal
  while(true){
      ROS_INFO("Sending goal");
      ac.sendGoal(goal1);
      ac.waitForResult();
      if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
	//sending the second goal
	ac.sendGoal(goal2);
	ac.waitForResult();
	if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
	  ROS_INFO("GOT IT!");
	}
      }
      else
	ROS_INFO("The base failed to move forward 1 meter for some reason");

  }
  return 0;
}
