/*
File: Wind Component Header file
Description: Struct of wind components. Should be paired with Environmental Tile Components
    to model the air flow. This header contains data mostly pertaining to the speed and
    direction of the airflow, with more to come.

*/
#ifndef WIND_COMPONENT_HPP
#define WIND_COMPONENT_HPP

//#include "raylib.h" // for vector2
#include "lib/Vec2f.hpp"

struct WindComponent
{
    int speed;          // speed of wind in m/s; length of the vector
    Vec2f direction;  // direction of the wind movement in a unit circle
    // int temperatureC;   // temperature, in Celsius, of the wind

    WindComponent(const int initSpeed, const float initWindDirX, const float initWindDirY)
    {
        this->speed = initSpeed;
        this->direction = {initWindDirX, initWindDirY};
    }
    WindComponent()
    {
        this->speed = 0;
        this->direction = {0, 0};
    }
    WindComponent(const WindComponent& copy)
    {
        this->speed = copy.speed;
        this->direction = copy.direction;
    }
    WindComponent& operator=(const WindComponent& rhs)
    {
        this->speed = rhs.speed;
        this->direction = rhs.direction;
        return *this;
    }
    ~WindComponent()
    {
        
    }
};


#endif