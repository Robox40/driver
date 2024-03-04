#include "calculNode.h"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"
#include "std_msgs/msg/int16.hpp"

calculNode::calculNode() : Node("calculNode") 
{
    this->declare_parameter<float>("tick_per_round_encodors", 24);
    this->declare_parameter<float>("gear_box", 61/1);
    this->declare_parameter<float>("time_conversion", 60/3);
    this->declare_parameter<float>("speed_for_mot0_mot1", -100);
    this->declare_parameter<float>("speed_for_mot2_mot3", 100);
    this->get_parameter("tick_per_round_encodors", tick_per_round_encodors);
    this->get_parameter("gear_box", gear_box);
    this->get_parameter("time_conversion", time_conversion);
    this->get_parameter("speed_for_mot0_mot1", speed_for_mot0_mot1);
    this->get_parameter("speed_for_mot2_mot3", speed_for_mot2_mot3);


        subscriber0_ = create_subscription<std_msgs::msg::Int32>(
        "/drivetrain/encoder_0", 10, std::bind(&calculNode::DrivetrainMot0Callback, this, std::placeholders::_1));
         subscriber1_ = create_subscription<std_msgs::msg::Int32>(
        "/drivetrain/encoder_1", 10, std::bind(&calculNode::DrivetrainMot1Callback, this, std::placeholders::_1));
         subscriber2_ = create_subscription<std_msgs::msg::Int32>(
        "/drivetrain/encoder_2", 10, std::bind(&calculNode::DrivetrainMot2Callback, this, std::placeholders::_1));
         subscriber3_ = create_subscription<std_msgs::msg::Int32>(
        "/drivetrain/encoder_3", 10, std::bind(&calculNode::DrivetrainMot3Callback, this, std::placeholders::_1));

    timer_ = create_wall_timer(std::chrono::seconds(3), std::bind(&calculNode::timer_callback, this));

    publisher0_ = create_publisher<std_msgs::msg::Int16>("/drivetrain/cmd_mot0", 10);
    publisher1_ = create_publisher<std_msgs::msg::Int16>("/drivetrain/cmd_mot1", 10);
    publisher2_ = create_publisher<std_msgs::msg::Int16>("/drivetrain/cmd_mot2", 10);
    publisher3_ = create_publisher<std_msgs::msg::Int16>("/drivetrain/cmd_mot3", 10);

    datelanecmentprogramme = this->get_clock()->now();
  

}

void calculNode::DrivetrainMot0Callback(const std_msgs::msg::Int32::SharedPtr msg)
{
    if(bool0 == false)
    {
        fisrt_msg_0 = msg->data;
        bool0 = true;
    }last_msg_0 = msg->data;
}

void calculNode::DrivetrainMot1Callback(const std_msgs::msg::Int32::SharedPtr msg)
{
    if(bool1 == false)
    {
        fisrt_msg_1 = msg->data;
        bool1 = true;
    }
    last_msg_1 = msg->data;
}

void calculNode::DrivetrainMot2Callback(const std_msgs::msg::Int32::SharedPtr msg)
{
if(bool2 == false)
    {
        fisrt_msg_2 = msg->data;
        bool2 = true;
    }     last_msg_2 = msg->data;
}

void calculNode::DrivetrainMot3Callback(const std_msgs::msg::Int32::SharedPtr msg)
{
if(bool3 == false)
    {
        fisrt_msg_3 = msg->data;
        bool3 = true;
    }    last_msg_3 = msg->data;
}


void calculNode::timer_callback()
{
    rclcpp::Time now = this->get_clock()->now(); // Récupérer la date actuelle
    rclcpp::Duration diff = now - datelanecmentprogramme;
    double diffInSeconds = diff.seconds();
    RCLCPP_INFO(this->get_logger(), "La différence de temps est de %f secondes", diffInSeconds);

    std_msgs::msg::Int16 cmd;
    if (diffInSeconds > 3)
    {
        RCLCPP_INFO(this->get_logger(), "Dernier message reçu mot0: '%d'", last_msg_0);
        RCLCPP_INFO(this->get_logger(), "Dernier message reçu mot1: '%d'", last_msg_1);
        RCLCPP_INFO(this->get_logger(), "Dernier message reçu mot2: '%d'", last_msg_2);
        RCLCPP_INFO(this->get_logger(), "Dernier message reçu mot3: '%d'", last_msg_3);

        // Commandes à exécuter après 3 secondes

        // Arrêter le timer
        timer_->cancel();
         cmd.data = 0;
        publisher0_->publish(cmd);
        publisher1_->publish(cmd);
        publisher2_->publish(cmd);
        publisher3_->publish(cmd);

        int delta0, rpm0 = calcul_driver(last_msg_0, fisrt_msg_0);
        int delta1, rmp1 = calcul_driver(last_msg_1, fisrt_msg_1);
        int delta2, rpm2 = calcul_driver(last_msg_2, fisrt_msg_2);
        int delta3, rpm3 = calcul_driver(last_msg_3, fisrt_msg_3);
        
    }
    else
    {
        // Commandes à exécuter avant 3 secondes
        RCLCPP_INFO(this->get_logger(), "Premier message reçu mot0: '%d'", fisrt_msg_0);
        RCLCPP_INFO(this->get_logger(), "Premier message reçu mot1: '%d'", fisrt_msg_1);
        RCLCPP_INFO(this->get_logger(), "Premier message reçu mot2: '%d'", fisrt_msg_2);
        RCLCPP_INFO(this->get_logger(), "Premier message reçu mot3: '%d'", fisrt_msg_3);
        // Exemple :
        cmd.data = speed_for_mot0_mot1;
        publisher0_->publish(cmd);
        publisher1_->publish(cmd);
        cmd.data = speed_for_mot2_mot3;
        publisher2_->publish(cmd);
        publisher3_->publish(cmd);

    }
}
// int calculNode::calbgeg0()
// {
//     int delta0 = last_msg_0 - fisrt_msg_0;
//     RCLCPP_INFO(this->get_logger(), "delta0 '%d", delta0);
//     float rpm0 = (delta0/1464.0)*20.0;
//     RCLCPP_INFO(this->get_logger(), "rmp3 '%f", rpm0);
//     return delta0, rpm0;
// }
// int calculNode::calbgeg1()
// {
//     int delta1 = last_msg_1 - fisrt_msg_1;
//     RCLCPP_INFO(this->get_logger(), "delta1 '%d", delta1);
//     float rpm1 = (delta1/1464.0)*20.0;
//     RCLCPP_INFO(this->get_logger(), "rmp3 '%f", rpm1);
//     return delta1, rpm1;
// }
// int calculNode::calbgeg2()
// {
//     int delta2 = last_msg_2 - fisrt_msg_2;
//     RCLCPP_INFO(this->get_logger(), "delta2 '%d", delta2);
//     float rpm2 = (delta2/1464.0)*20.0;
//     RCLCPP_INFO(this->get_logger(), "rmp3 '%f", rpm2);
//     return delta2, rpm2;
// }
// int calculNode::calbgeg3()
// {
//     int delta3 = last_msg_3 - fisrt_msg_3;
//     RCLCPP_INFO(this->get_logger(), "delta3 '%d", delta3);
//     float rpm3 = (delta3/1464.0)*20.0;
//     RCLCPP_INFO(this->get_logger(), "rmp3 '%f", rpm3);
//     return delta3, rpm3;
// }

int calculNode::calcul_driver(int lastmsg, int firstmsg)
{
float tick_per_round_motors  = tick_per_round_encodors * gear_box;
delta = lastmsg - firstmsg;
RCLCPP_INFO(this->get_logger(), "delta '%d", delta);
rpm = (delta/tick_per_round_motors)*time_conversion;
RCLCPP_INFO(this->get_logger(), "rmp '%f", rpm);
return delta, rpm;
}



    
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<calculNode>());
    rclcpp::shutdown();
    return 0;
}
