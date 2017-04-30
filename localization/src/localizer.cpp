#include "localizer.h"

localizer::localizer()
{
    int i;
    Sum = 0;
    for( i = 0 ; i < 25 ; i++ )
    {
	nearestx[i] = 5;
        nearesty[i] = 5;
	sub_local_x[i] = 3;
    	sub_local_y[i] = 3;
    }
    robot_x = 1.0;
    robot_y = 2.0;
    robot_theta =3.0;
    dx = 0.0;
    dy = 0.0;
    dtheta = 0.0;
}

localizer::~localizer()
{
}

void localizer::set_robot_x(float x)
{
    robot_x = x ;
}

void localizer::set_robot_y(float y)
{
    robot_y = y ;
}

void localizer::set_robot_theta(float theta)
{
    robot_theta = theta ;
}

void localizer::set_Sum(float sum)
{
    Sum = sum;
}

float localizer::get_robot_x()
{
    return robot_x;
}

float localizer::get_robot_y()
{
    return robot_y;
}

float localizer::get_robot_theta()
{
    return robot_theta;
}

float localizer::get_Sum()
{
    return Sum;
}

float localizer::get_dx()
{
    return dx;
}

float localizer::get_dy()
{
    return dy;
}

float localizer::get_dtheta()
{
    return dtheta;
}

void localizer::msg_subsribe()
{
    sub = it.subscribe("samples", 1, &localizer::convert_callback, this);
}

void localizer::convert_callback(const localization::Samples::ConstPtr& msg)
{
    int i=0, j=0;
    for(i=0; i<25; i++)
    {
	sub_local_x[i] = msg->local_x[i];
	sub_local_y[i] = msg->local_y[i];
	sub_local_theta[i] = msg->local_theta[i];
	sub_world_x[i] = msg->world_x[i];
	sub_world_y[i] = msg->world_y[i];
  	calculate();
    }
}

void localizer::gredient_desent()
{
    int i, j;
    float max = 60000;
    for( i = 0 ; i < 25 ; i++ )
    {
	dx += 2 * ( nearestx[i] - sub_local_x[i] ) / max;
    }
    for( i = 0 ; i < 25 ; i++ )
    {
	dy += 2 * ( nearesty[i] - sub_local_y[i] ) / max;
    }
    for( i = 0 ; i < 25 ; i++ )
    {
	dtheta += 2 * ( ( nearestx[i] - sub_world_x[i] ) * ( - sin(robot_theta) * sub_local_x[i] - cos(robot_theta) * sub_local_y[i] ) + 
                        ( nearesty[i] - sub_world_x[i] ) * ( cos(robot_theta) * sub_local_x[i] - sin(robot_theta) * sub_local_y[i] ) ) / max;
    }
    cout << dx << " " << dy << " " << dtheta << endl;
}

void localizer::match_degree()
{
    int i,j;
    float max = 60000000;
    for ( i = 0 ; i < 25 ; i++ )
    {
        Sum += 1.0 - ( ( sub_world_x - nearestx ) * ( sub_world_x - nearestx ) + ( sub_world_y - nearesty ) * ( sub_world_y - nearesty ) ) / max;
    } 
}

void localizer::calculate()
{
   int i, j;
    float step_width = 0.01;
    float max_iterater = 5;
    float count = 0;
    while( count < 5 )
    {
        gredient_desent();
	robot_x += dx * step_width;
        robot_y += dy * step_width;
        robot_theta += dtheta * step_width;
	step_width = step_width / 2.0;
	count += 1;
    }
}




















