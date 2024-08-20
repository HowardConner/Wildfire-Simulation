#include "RenderEngine.hpp"


// update the renderList from the map of RenderComponents
void updateRenderList(std::vector<RenderInfoComponent>& renderList, const std::map<EntityID, RenderInfoComponent>& entityList)
{
    // define variables
    std::map<EntityID, RenderInfoComponent>::const_iterator curComponent = entityList.begin();

    // prep the renderlist vector
    renderList.clear();
    renderList.reserve(entityList.size());

    // copy the contents of the map to the vector
    while(curComponent != entityList.end())
    {
        // TODO: add off-screen culling

        // perform the insert according to the comparator
        renderList.push_back(curComponent->second);

        // increment the iterator
        curComponent++;
    }

    //std::cout<<renderList.size()<<" componenets added to render list"<<std::endl;
    
    // now post-sort
    std::sort(renderList.begin(), renderList.end(), RenderComparator());
}



// Render Function for all render components.
void renderScene(const std::vector<RenderInfoComponent>& renderList)
{
    // define variables
    size_t renderCount = 0;
    auto renderIterator = renderList.begin();

    // begin the render
    ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
    BeginDrawing();

    while(renderIterator != renderList.end())
    {


        // draw a box with the appropriat texture
        DrawRectangle(renderIterator->BoundingBox.x, renderIterator->BoundingBox.y, 
            renderIterator->BoundingBox.width, renderIterator->BoundingBox.height,
            renderIterator->renderColor);
            //BLUE);
        
        // // if boarder is on, draw it
        // if(renderIterator->showBorder)
        // {
        //     DrawRectangleLines(renderIterator->BoundingBox.x, renderIterator->BoundingBox.y, 
        //     renderIterator->BoundingBox.width, renderIterator->BoundingBox.height,
        //     renderIterator->borderColor);
        // }

        // incrament things
        renderIterator++;
        renderCount++;
    }

    EndDrawing();

}