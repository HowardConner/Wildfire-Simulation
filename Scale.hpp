#ifndef SCALE_RANGE_HPP
#define SCALE_RANGE_HPP

#include <iostream>
#include <algorithm>

template<int MIN, int MAX>
class Scale{
public:

// Constructor, destructor, copy constructor copy assignment operator
Scale()
{
    mCurrentValue = MIN;
}

Scale(const int initSetPoint)
{
    mCurrentValue = std::clamp(initSetPoint, MIN, MAX);
}

Scale(const Scale<MIN,MAX>& copy)
{
    this->mCurrentValue = copy.mCurrentValue;
}

Scale<MIN,MAX>& operator=(const Scale<MIN,MAX>& rhs)
{
    this->mCurrentValue = rhs.mCurrentValue;
    return *this;
}

~Scale()
{

}

// operator overloads
Scale<MIN,MAX>& operator+=(const int increment)
{
    this->mCurrentValue += increment;
    if(mCurrentValue > MAX)
    {
        mCurrentValue = MAX;
    }
    else if(mCurrentValue < MIN)
    {
        mCurrentValue = MIN;
    }
    return *this;
}

Scale<MIN,MAX>& operator-=(const int increment)
{
    this->mCurrentValue -= increment;
    if(mCurrentValue < MIN)
    {
        mCurrentValue = MIN;
    }
    else if(mCurrentValue > MAX)
    {
        mCurrentValue = MAX;
    }
    return *this;  
}

friend int operator+(const Scale<MIN,MAX>& scale, const int increment)
{
    return scale.getValue() + increment;
}

friend int operator+(const int increment, const Scale<MIN,MAX>& scale)
{
    return scale.getValue() + increment;
}

friend int operator-(const Scale<MIN,MAX>& scale, const int increment)
{
    return scale.getValue() - increment;
}

friend int operator-(const int increment, const Scale<MIN,MAX>& scale)
{
    return scale.getValue() - increment;
}

friend bool operator>(const Scale<MIN,MAX>& scale, const int value)
{
    return scale.getValue() > value;
}
friend bool operator<(const Scale<MIN,MAX>& scale, const int value)
{
    return scale.getValue() < value;
}
friend bool operator>=(const Scale<MIN,MAX>& scale, const int value)
{
    return scale.getValue() >= value;
}
friend bool operator<=(const Scale<MIN,MAX>& scale, const int value)
{
    return scale.getValue() <= value;
}
friend bool operator==(const Scale<MIN,MAX>& scale, const int value)
{
    return scale.getValue() == value;
}

Scale<MIN,MAX>& operator++()
{
    this->mCurrentValue += 1;
    if(mCurrentValue > MAX)
    {
        mCurrentValue = MAX;
    }
    return *this;
}

Scale<MIN,MAX>& operator--()
{
    this->mCurrentValue -= 1;
    if(mCurrentValue < MIN)
    {
        mCurrentValue = MIN;
    }
    return *this;
}

constexpr int getMin() const
{
    return MIN;
}

constexpr int getMax() const
{
    return MAX;
}

inline int getValue() const
{
    return this->mCurrentValue;
}

inline void setToMax()
{
    this->mCurrentValue = MAX;
}
inline void setToMin()
{
    this->mCurrentValue = MIN;
}

private:
    int mCurrentValue = 0;
};

#endif