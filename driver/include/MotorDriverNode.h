// MotorDriverNode.hpp

#ifndef MOTOR_DRIVER_NODE_H
#define MOTOR_DRIVER_NODE_H

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "std_msgs/msg/int16.hpp"

class MotorDriverNode : public rclcpp::Node {
public:
    MotorDriverNode();
   
    void cmdVelCallback(const geometry_msgs::msg::Twist::SharedPtr msg);

private:
    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr subscriber_;
    rclcpp::Publisher<std_msgs::msg::Int16>::SharedPtr publisher0_;
    rclcpp::Publisher<std_msgs::msg::Int16>::SharedPtr publisher1_;
    rclcpp::Publisher<std_msgs::msg::Int16>::SharedPtr publisher2_;
    rclcpp::Publisher<std_msgs::msg::Int16>::SharedPtr publisher3_;
};

#endif // MOTOR_DRIVER_NODE_HPP
