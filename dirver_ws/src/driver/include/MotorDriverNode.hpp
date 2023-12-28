// MotorDriverNode.hpp

#ifndef MOTOR_DRIVER_NODE_HPP
#define MOTOR_DRIVER_NODE_HPP

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "std_msgs/msg/float64.hpp"

class MotorDriverNode : public rclcpp::Node {
public:
    MotorDriverNode();
    void cmdVelCallback(const geometry_msgs::msg::Twist::SharedPtr msg);

private:
    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr subscriber_;
    rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr publisher0_;
    rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr publisher1_;
    rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr publisher2_;
    rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr publisher3_;
};

#endif // MOTOR_DRIVER_NODE_HPP
