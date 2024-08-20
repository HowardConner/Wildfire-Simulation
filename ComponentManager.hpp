/*
Component Manager Class
Class designed to assisted in the entity-component-system paradigm. Works with any
    struct class defined from the [Component] base class struct.
*/
#ifndef COMPONENT_MANAGER_HPP
#define COMPONENT_MANAGER_HPP

#include <map>
#include <unordered_map>

#include "Component.hpp"    // for base component and EntityID


class ComponentManager{
public:
    // constructor
    ComponentManager()
    {

    }

    // destructor
    ~ComponentManager()
    {

    }

private:
    std::unordered_map<ComponentID, std::map<EntityID, Component>> componentAtlas;

    // virtual copy constructor
    ComponentManager(const ComponentManager& copy) {}

    // virtual copy assignment operator
    ComponentManager& operator=(const ComponentManager& rhs);
};


#endif