/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   Example originally created with raylib 1.0, last time updated with raylib 1.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2013-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/
#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#undef RAYGUI_IMPLEMENTATION

#include <math.h>
#include "src/raymath.h"

#include "RenderEngine.hpp"
#include "game.hpp"

int main()
{
    std::map<EntityID, RenderInfoComponent> renderComponents;
    std::vector<RenderInfoComponent> renderListBuffer;
    FireSimulationData fireSimData;
    float elapsedTime = 0.0;
    bool pause = true;
    Rectangle statusRec{1300, 700, 75,75};
    Vector2 statusRectCenter{float(1300+75/2), float(700+75/2)}; //{statusRec.x + statusRec.width/2, statusRec.y + statusRec.height/2};
    float statusRectAngle = 0.f;

    InitWindow(1400, 800, "raygui - controls test suite");
    SetTargetFPS(60);

    // make some render objects
    renderComponents.insert({1,RenderInfoComponent(120,20, 50,50, RenderLayer::MIDDLE, BLUE)});

    initFireSim(fireSimData);

    // Vec2i v1(1,1), v2(-1, 1), v3(-1, -1), v4();

    // return 0;

    while (!WindowShouldClose())
    {
        // Update data memebers
        elapsedTime += GetFrameTime();
        //updateRenderList(renderListBuffer,f*maxFlameRadiusuelAvaliable renderComponents);
        
        // update the firesim after 0.5 of a second
        if(elapsedTime >= SIM_SECONDS_PER_SIM_STEP)
        {
            //std::cout<<"run firestep()"<<std::endl;
            runFireSimStep(fireSimData);
            elapsedTime = 0.f;

            statusRectAngle += 360.f * float(DEG2RAD) / float(SIM_STEPS_PER_SECOND);
        }
        // if(IsKeyPressed(KeyboardKey::KEY_SPACE))
        // {
        //     runFireSimStep(fireSimData);
        // }

        //renderScene(renderListBuffer);

        // begin the render
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
        BeginDrawing();

        //std::cout<<"run draw sim()"<<std::endl;
        drawFireSim(fireSimData, Rectangle{400,100, 600,600}, true, false);

        //DrawRectanglePro(statusRec, statusRectCenter, statusRectAngle, DARKBLUE);
        DrawRectangle(statusRec.x, statusRec.y, statusRec.width, statusRec.height, DARKBLUE);
        DrawCircle(statusRectCenter.x, statusRectCenter.y, 10, RED);

        EndDrawing();

        // render UI Elements
    }

    CloseWindow();
    return 0;
}

