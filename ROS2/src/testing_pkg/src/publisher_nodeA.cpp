/*
    This node send number from 1 to 100 then stops
*/

#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

class SendNumbersPub : public rclcpp::Node {
    public:
        SendNumbersPub() : Node("numbers_pub") {
            publisher_ = this->create_publisher<std_msgs::msg::String>("num_topic", 10);
            timer_ = this->create_wall_timer(std::chrono::milliseconds(500), std::bind(&SendNumbersPub::timer_callback, this));
        }

    private:
        void timer_callback(){
            if(this->val <= 100){
                auto message = std_msgs::msg::String();
                message.data = "I'm sending " + std::to_string(this->val);
                RCLCPP_WARN(this->get_logger(), "Sending '%s'", message.data.c_str());
                publisher_->publish(message);
                this->val += 2;
                // int val = 0;
            }
            
            else{
                timer_->cancel();
                RCLCPP_FATAL(this->get_logger(), "Enough, you've reached the maximum allowed ...");

            }
        }

        rclcpp::TimerBase::SharedPtr timer_;
        rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
        int val{0};
       
};

int main(int argc, char* argv[]){
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SendNumbersPub>());
    rclcpp::shutdown();
    return 0;
}