#ifndef CALCULNODE_H
#define CALCULNODE_H

#include "rclcpp/rclcpp.hpp"
#include <iostream>
#include <cmath>
#include "std_msgs/msg/int16.hpp" // Remplacez std_msgs/msg/int32.hpp par le type de message approprié
#include "std_msgs/msg/int32.hpp" 

class calculNode : public rclcpp::Node
{

   
private:

    int fisrt_msg_0, msg_0;
     int fisrt_msg_1, msg_1;
      int fisrt_msg_2, msg_2;
       int fisrt_msg_3, msg_3;
    int last_msg_0, msg0;
     int last_msg_1, msg1;
      int last_msg_2, msg2;
       int last_msg_3, msg3;

    bool bool0, bool1, bool2, bool3;
    rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscription_;
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscriber0_ ;
     rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscriber1_ ;
      rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscriber2_ ;
       rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscriber3_ ;
    rclcpp::Publisher<std_msgs::msg::Int16>::SharedPtr publisher0_;
     rclcpp::Publisher<std_msgs::msg::Int16>::SharedPtr publisher1_;
      rclcpp::Publisher<std_msgs::msg::Int16>::SharedPtr publisher2_;
       rclcpp::Publisher<std_msgs::msg::Int16>::SharedPtr publisher3_;
    rclcpp::Time datelanecmentprogramme;
public:
    calculNode();
    
    void timer_callback();
    void DrivetrainMot0Callback(const std_msgs::msg::Int32::SharedPtr msg);
    void DrivetrainMot1Callback(const std_msgs::msg::Int32::SharedPtr msg);
    void DrivetrainMot2Callback(const std_msgs::msg::Int32::SharedPtr msg);
    void DrivetrainMot3Callback(const std_msgs::msg::Int32::SharedPtr msg);
    int calcul_driver(int lastmsg, int firstmsg);
    int delta;
    float speed_for_mot0_mot1;
    float speed_for_mot2_mot3;
    float rpm;
    float tick_per_round_encodors = 24;
    float gear_box = 61/1;
    // float tick_per_round_motors  = tick_per_round_encodors * gear_box;
    float time_conversion = 60/3;

    // int calbgeg1();
    // int calbgeg2();
    // int calbgeg3();


    // rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscriber0_ ;
    // rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscriber0_ ;
    // rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscriber0_ ;
//    int tic_initial = 316862; // Nombre de tic initial
// int tic_final = 318295; // Nombre de tic final

// const double nombre_tours_par_minute = 100.0; // Nombre de tours par minute
// const double duree_sec = 3.0; // Durée en secondes
};

#endif
