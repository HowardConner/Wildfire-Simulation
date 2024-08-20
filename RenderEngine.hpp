/*



*/
#ifndef RENDER_ENGINE_HPP
#define RENDER_ENGINE_HPP

#include <iostream>
#include <map> 
#include <vector>
#include <algorithm>

#include "RenderInfoComponent.hpp"
#include "raygui.h"

//using RenderListBuffer = std::vector<RenderInfoComponent>;

// Define the Render Engine Insertion Comparator
struct RenderComparator{
    bool operator()(const RenderInfoComponent& lhs, const RenderInfoComponent& rhs) const
    {
        // first, compare zHeights. The one with greater zheight is greater
        if(lhs.zHeight != rhs.zHeight)
        {
            return lhs.zHeight > rhs.zHeight;
        }
        // if object have different y-values, the one with the greater y value is greater
        if(lhs.BoundingBox.y != rhs.BoundingBox.y)
        {
            return lhs.BoundingBox.y > rhs.BoundingBox.y;
        }
        // if then one has a greater x value, let that one be greater
        if(lhs.BoundingBox.x != rhs.BoundingBox.x)
        {
            return lhs.BoundingBox.x > rhs.BoundingBox.x;
        }
    }
};


// update the renderList from the map of RenderComponents
void updateRenderList(std::vector<RenderInfoComponent>& renderList, const std::map<EntityID, RenderInfoComponent>& entityList);

// Render Function for all render components.
void renderScene(const std::vector<RenderInfoComponent>& renderList);













// // Function that inserts a new component into an existing render list
// //      handles proper insertion to preserve ordering of 
// // returns true if added, false otherwise
// bool addToRenderList(const std::map<EntityID, RenderInfoComponent>& renderList, const EntityID& newEntity, const RenderInfoComponent& newRenderComponent);

// // funciton that removes a component with a supplied EntityID from the renderList
// bool removeFromRenderList(const std::map<EntityID, RenderInfoComponent>& renderList, const EntityID& entityToRemove);

// // function checks list for existence of input searchID
// bool isEntityInRenderList(const std::map<EntityID, RenderInfoComponent>& renderList, const EntityID& serachID);

// // function searches renderlist and returns an iterator to the component in the map
// std::map<EntityID, RenderInfoComponent>::iterator searchRenderList(const std::map<EntityID, RenderInfoComponent>& renderList, const EntityID& serachID);


#endif