// MotorDriverNode.cpp

#include "MotorDriverNode.hpp"
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "std_msgs/msg/float64.hpp"

MotorDriverNode::MotorDriverNode() : Node("motor_driver_node") {
    // Abonnement au topic "cmd_vel"
    subscriber_ = create_subscription<geometry_msgs::msg::Twist>(
        "cmd_vel", 10, std::bind(&MotorDriverNode::cmdVelCallback, this, std::placeholders::_1));

    // Publication sur les topics cmd_mot0, cmd_mot1, cmd_mot2, cmd_mot3
    publisher0_ = create_publisher<std_msgs::msg::Float64>("cmd_mot0", 10);
    publisher1_ = create_publisher<std_msgs::msg::Float64>("cmd_mot1", 10);
    publisher2_ = create_publisher<std_msgs::msg::Float64>("cmd_mot2", 10);
    publisher3_ = create_publisher<std_msgs::msg::Float64>("cmd_mot3", 10);
}

void MotorDriverNode::cmdVelCallback(const geometry_msgs::msg::Twist::SharedPtr msg) {
    // Traitement des commandes de vitesse
    double linearVel = msg->linear.x;
    double angularVel = msg->angular.z;

    // Calcul des vitesses des moteurs (à adapter selon votre logique)
    double velMotor0 = linearVel + angularVel;
    double velMotor1 = linearVel - angularVel;
    double velMotor2 = linearVel + angularVel;
    double velMotor3 = linearVel - angularVel;

    // Publication sur les topics cmd_mot0, cmd_mot1, cmd_mot2, cmd_mot3
    auto message0 = std_msgs::msg::Float64();
    message0.data = velMotor0;
    publisher0_->publish(message0);

    auto message1 = std_msgs::msg::Float64();
    message1.data = velMotor1;
    publisher1_->publish(message1);

    auto message2 = std_msgs::msg::Float64();
    message2.data = velMotor2;
    publisher2_->publish(message2);

    auto message3 = std_msgs::msg::Float64();
    message3.data = velMotor3;
    publisher3_->publish(message3);
}
