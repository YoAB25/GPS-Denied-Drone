/*
    This node send number from 1 to 100 then stops
*/

#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using std::placeholders::_1;

class GetNumbersSub : public rclcpp::Node {
    public:
        GetNumbersSub() : Node("numbers_sub") {
            subscription_ = this->create_subscription<std_msgs::msg::String>("num_topic", 10, std::bind(&GetNumbersSub::received_nums_callback, this, _1));
        }

    private:
        void received_nums_callback(const std_msgs::msg::String::SharedPtr msg){
            if(msg){
                RCLCPP_WARN(this->get_logger(), "I've received '%s'", msg->data.c_str());
            }
            else if (msg->data.empty()) {
                RCLCPP_FATAL(this->get_logger(), "Bruh, not a single message coming, go cry ...");
                rclcpp::shutdown();
            }
        }
        rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;

};

int main(int argc, char* argv[]){
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<GetNumbersSub>());
    rclcpp::shutdown();
    return 0;
}