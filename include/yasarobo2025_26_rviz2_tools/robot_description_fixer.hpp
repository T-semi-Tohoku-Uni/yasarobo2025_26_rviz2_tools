#pragma once
#include<rclcpp/rclcpp.hpp>
#include<std_msgs/msg/string.hpp>
#include<regex>

class RobotDescriptionFixer: public rclcpp::Node {
    public:
        explicit RobotDescriptionFixer(const rclcpp::NodeOptions & options = rclcpp::NodeOptions());

    private:
        void callback(const std_msgs::msg::String::SharedPtr msg);

        std::string home_path_;
        rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub_;
        rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_;
};