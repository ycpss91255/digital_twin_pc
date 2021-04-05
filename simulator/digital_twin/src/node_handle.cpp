#include "digital_twin/node_handle.h"

SimNodeHandle::SimNodeHandle(int argc, char **argv, std::string NodeName) {
  ros::init(argc, argv, NodeName);
  init();
}

SimNodeHandle::~SimNodeHandle() {
  ros::shutdown();

#ifdef DEBUG
  printf("~SimNodeHandle(DEBUG)\n");
#endif
}

void SimNodeHandle::init() {
  this->n = new ros::NodeHandle();

  MotorSpeed_sub = n->subscribe<motion::FourMotorStates>(
      wheel_pos_topic_name, 1000, &SimNodeHandle::MotorSpeedBack, this);

  WheelCmd1_pub = n->advertise<std_msgs::Float64>(wheel1_cmd_topic_name, 1000);
  WheelCmd2_pub = n->advertise<std_msgs::Float64>(wheel2_cmd_topic_name, 1000);
  WheelCmd3_pub = n->advertise<std_msgs::Float64>(wheel3_cmd_topic_name, 1000);
  WheelCmd4_pub = n->advertise<std_msgs::Float64>(wheel4_cmd_topic_name, 1000);

  MotorPos_sub = n->subscribe<sensor_msgs::JointState>(
      wheel_pos_topic_name, 1000, &SimNodeHandle::MotorPosBack, this);
  MotorPos_pub = n->advertise<motion::FourMotorStates>(wheel1_cmd_topic_name, 1000);

#ifdef DEBUG
  printf("Motion_nodeHandle(DEBUG)\n");
#endif
}

void SimNodeHandle::MotorSpeedBack(const motion::FourMotorStates::ConstPtr &msg) {
  MotorCmd.w1 = msg->w1;
  MotorCmd.w2 = msg->w2;
  MotorCmd.w3 = msg->w3;
  MotorCmd.w4 = msg->w4;
  pub_MotorSpeed(MotorCmd);

#ifdef DEBUG
  printf("MotorSpeedBack(DEBUG)\n");
  printf("w1 : %f\n", MotorCmd.w1);
  printf("w2 : %f\n", MotorCmd.w2);
  printf("w3 : %f\n", MotorCmd.w3);
  printf("w4 : %f\n", MotorCmd.w4);
#endif
}

void SimNodeHandle::pub_MotorSpeed(motion::FourMotorStates Cmd) {
  WheelCmd1_pub.publish(Cmd.w1);
  WheelCmd2_pub.publish(Cmd.w2);
  WheelCmd3_pub.publish(Cmd.w3);
  WheelCmd4_pub.publish(Cmd.w4);
}

void SimNodeHandle::MotorPosBack(const sensor_msgs::JointState::ConstPtr &msg) {
  // this->MotionCmd.x = msg->linear.x;
  // this->MotionCmd.y = msg->linear.y;
  // this->MotionCmd.yaw = msg->angular.z;

#ifdef DEBUG
  printf("CmdVelBack(DEBUG)\n");
  printf("x : %f\n", msg->linear.x);
  printf("y : %f\n", msg->linear.y);
  printf("z : %f\n", msg->angular.z);
#endif
}

// // void SimNodeHandle::Set
