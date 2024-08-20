/*
Position Component
    Responsible for holding positioning and sizing data
*/

#ifndef RENDER_INFO_COMPONENT_CPP
#define RENDER_INFO_COMPONENT_CPP

#include <string>       // for string support and for std::hash
#include <functional>   // for std::hash

#include "Component.hpp"
#include "raylib.h"

enum RenderLayer{
    BACK = 0,
    MIDDLE,
    FRONT,
    UI
};

struct RenderInfoComponent// : public Component
{
public:
    Rectangle BoundingBox;
    Color renderColor;      // TODO: swap this with some sort of pointer or ID-reference to a sprite sheet
    RenderLayer layer;
    size_t zHeight = 0;     // default to set render height to the bottom

    bool showBorder = false;
    Color borderColor = BLACK;  // default color
    float borderWidth = 0.1;    // default color width

    // constructor
    RenderInfoComponent(const float x, const float y, const float width, const float height, const RenderLayer& drawLayer, const Color& initColor, const size_t initZHeight = 0) : 
            BoundingBox{x, y, width, height}, 
            layer(drawLayer), 
            // renderColor{initColor},
            zHeight(initZHeight)
    {
        renderColor = initColor;
    }

    // copy constructor
    RenderInfoComponent(const RenderInfoComponent& copy)
    {
        this->BoundingBox = copy.BoundingBox;
        this->renderColor = copy.renderColor;
        this->layer = copy.layer;
        this->zHeight = copy.zHeight;

        this->showBorder = copy.showBorder;
        this->borderColor = copy.borderColor;
        this->borderWidth = copy.borderWidth;
    }

    // copy assignment operator
    RenderInfoComponent& operator=(const RenderInfoComponent& rhs)
    {
        this->BoundingBox = rhs.BoundingBox;
        this->renderColor = rhs.renderColor;
        this->layer = rhs.layer;
        this->zHeight = rhs.zHeight;

        this->showBorder = rhs.showBorder;
        this->borderColor = rhs.borderColor;
        this->borderWidth = rhs.borderWidth;

        return *this;
    }

    // destructor
    ~RenderInfoComponent()
    {

    }

    // force each base class to redefine this or it gets lumped in as a default (blank) Key
    // tip: use hash for the string of the component name
    inline const ComponentID getComponentID()
    {
        //getTypeTag<RenderInfoComponent>();
        return 0;
    }
    
};


#endif   