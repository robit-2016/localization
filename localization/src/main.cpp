#include "localizer.h"

int main(int argc, char** argv)
{
    ros::init(argc, argv, "localizer");
    int i, j;
    float main_x = 0, main_y = 0, main_theta = 0;
    localizer sample1;
    sample1.msg_subsribe();
    //sample1.calculate();
    ros::spin();
    return 0;  
}
