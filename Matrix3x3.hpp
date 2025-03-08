/*****************************************************************************
**************
* Programmer: Conner Howard
* File: 
* Date: 
* Description:
******************************************************************************
*************/
#ifndef MATRIX_3x3_HPP
#define MATRIX_3x3_HPP

#include <array>

template<typename T>
struct Matrix3x3 : public std::array<std::array<T, 3>, 3>{
public:

    bool operator==(const Matrix3x3& lhs)
    {
        for(int y = 0; y < 3; y++)
        {
            for(int x = 0; x < 3; x++)
            {
                if(this->at(x).at(y) != lhs[x][y]) return false;
            }
        }
        return true;
    }

    Matrix3x3& operator=(const Matrix3x3& lhs)
    {
        for(int y = 0; y < 3; y++)
        {
            for(int x = 0; x < 3; x++)
            {
                this->at(x).at(y) = lhs[x][y];
            }
        }
        return *this;
    }
};

#endif