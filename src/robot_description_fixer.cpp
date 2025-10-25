#include"yasarobo2025_26_rviz2_tools/robot_description_fixer.hpp"

RobotDescriptionFixer::RobotDescriptionFixer(const rclcpp::NodeOptions & options)
    : Node("robot_description_fixer", options)
{
    const char* home_env = std::getenv("HOME");
    if (!home_env) {
        RCLCPP_ERROR(this->get_logger(), "HOME env not set");
        throw std::runtime_error("HOME env not set");
    }
    this->home_path_ = std::string(home_env);

    rclcpp::QoS sub_qos = rclcpp::QoS(rclcpp::KeepLast(1))
        .reliable()
        .transient_local();
    this->sub_ = this->create_subscription<std_msgs::msg::String>(
        "/robot_description",
        sub_qos,
        std::bind(&RobotDescriptionFixer::callback, this, std::placeholders::_1)
    );

    rclcpp::QoS pub_qos = rclcpp::QoS(rclcpp::KeepLast(1))
        .reliable()
        .transient_local();
    this->pub_ = this->create_publisher<std_msgs::msg::String>(this->home_path_ + "/robot_description", pub_qos);
}

void RobotDescriptionFixer::callback(const std_msgs::msg::String::SharedPtr msg) {
    RCLCPP_INFO(this->get_logger(), "fkerpofikprekfopkare");
    std::string data = msg->data;
    
    std::regex home_pattern("/home/[^/]+/ros_ws/install/[^/]+/share/[^/]+/");
    data = std::regex_replace(data, home_pattern, this->home_path_+"/ros_ws/src/yasarobo2025_26/");

    std_msgs::msg::String out = std_msgs::msg::String();
    out.data = data;
    pub_->publish(out);

    RCLCPP_INFO(this->get_logger(), "Replaced install path with %s", this->home_path_.c_str());
}

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<RobotDescriptionFixer>());
    rclcpp::shutdown();
    return 0;
}