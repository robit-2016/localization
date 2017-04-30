#include <ros/ros.h> //ros标准库头文件  
#include <iostream> //C++标准输入输出库
#include"localization/Samples.h"

using namespace std;

class localizer
{
    private:
    ros::NodeHandle it; //定义句柄
    localization::Samples msg_input; //定义Sample消息
    ros::Subscriber sub;  //定义订阅器
    double robot_x, robot_y, robot_theta;  //机器人坐标，机器人朝向角
    float nearestx[25], nearesty[25];  //定义最近点的x,y坐标
    float sub_local_x[25], sub_local_y[25], sub_local_theta[25], sub_world_x[25], sub_world_y[25];  //订阅的数据
    float dx, dy, dtheta; //x,y,theta的微分变量
    float Sum;

    public:
    localizer();
    ~localizer();
    void set_robot_x(float x);
    void set_robot_y(float y);
    void set_robot_theta(float theta);
    void set_Sum(float sum);        // set_系列为变量赋值
    float get_robot_x();
    float get_robot_y();
    float get_robot_theta();
    float get_Sum();
    float get_dx();
    float get_dy();
    float get_dtheta();            // get_系列为变量调用
    void msg_subsribe();           // 消息订阅函数
    void convert_callback(const localization::Samples::ConstPtr& msg);  // 消息回调函数
    void gredient_desent();   // 微分计算
    void match_degree();
    void calculate();   //计算每次迭代
};
