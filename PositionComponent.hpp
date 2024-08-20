/*
Position Component
    Responsible for holding positioning and sizing data
*/

#ifndef POSITION_COMPONENT_CPP
#define POSITION_COMPONENT_CPP

#include <string>       // for string support and for std::hash
#include <functional>   // for std::hash

#include "Component.hpp"
#include "raylib.h"

struct PositionComponent : public Component
{
public:
    Rectangle BoundingBox;

    // constructor
    PositionComponent(const float x, const float y, const float width, const float height) : 
            BoundingBox{x, y, width, height}
    {
        
    }

    // copy constructor
    PositionComponent(const PositionComponent& copy)
    {
        this->BoundingBox = copy.BoundingBox;
    }

    // copy assignment operator
    PositionComponent& operator=(const PositionComponent& rhs)
    {
        this->BoundingBox = rhs.BoundingBox;
    }

    // destructor
    ~PositionComponent()
    {

    }

    // force each base class to redefine this or it gets lumped in as a default (blank) Key
    // tip: use hash for the string of the component name
    inline const ComponentID getComponentID()
    {
        //getTypeTag<PositionComponent>();
        return 0;
    }
    
};


#endif   