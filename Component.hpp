/*
Component base class
Every component must inherit DIRECTLY form this base class. There will be no support for multi-layer
    components. Thus, if a component requires inheritence, consider how it could be composed instead
    from other, more basic components
*/

#ifndef COMPONENT_BASE_CLASS_CPP
#define COMPONENT_BASE_CLASS_CPP

#include <iostream>
#include <string>       // for string support
#include <functional>   // for std::hash


using EntityID = std::uint32_t;
using ComponentID = std::size_t;

// tag type for the Component
template <typename T>
struct ComponentTypeTag {
    static constexpr ComponentID value = std::hash<std::string>{}(T::typeName);
};

// template <typename T>
// static constexpr ComponentID getTypeTag()
// {
//     return std::hash<std::string>{}(T::typeName);
// }

struct Component
{
public:
    // vitural destructor
    virtual ~Component() = 0;

    // force each base class to redefine this or it gets lumped in as a default (blank) Key
    // tip: use hash for the string of the component name
    virtual inline const ComponentID getComponentID() = 0;
    
};


#endif   