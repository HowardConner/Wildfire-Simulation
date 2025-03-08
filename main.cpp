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

const float SIM_STEPS_PER_SECOND = 4;
const float SIM_SECONDS_PER_SIM_STEP = 1.f / SIM_STEPS_PER_SECOND;    // Fraction of a second between simulation steps

#include <math.h>
#include "src/raymath.h"
#include <iostream>
#include <iomanip>

//#include "RenderEngine.hpp"
#include "game.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::string;


int main()
{
    // std::map<EntityID, RenderInfoComponent> renderComponents;
    // std::vector<RenderInfoComponent> renderListBuffer;
    float elapsedTime = 0.0;
    bool pause = true;
    Rectangle statusRec{1300, 700, 75,75};
    Vector2 statusRectCenter{float(1300+75/2), float(700+75/2)}; //{statusRec.x + statusRec.width/2, statusRec.y + statusRec.height/2};
    float statusRectAngle = 0.f;

    // InitWindow(1400, 800, "wildfire simulation");
    // SetTargetFPS(60);
    Vec2i SimSize = {10,10};

    Vector_Grid<int> heatMap(20, SimSize.x, SimSize.y);
    Vector_Grid<int> heatMap2(20, SimSize.x, SimSize.y);

    Vector_Grid<int> heatLevelChange(0, SimSize.x, SimSize.y);
    Vector_Grid<int> fuelMap(20, SimSize.x, SimSize.y);
    Vector_Grid<int> waterMap(5, SimSize.x, SimSize.y);
    Vector_Grid<Biome> biomeMap(Biome::GRASS, SimSize.x, SimSize.y);
    Vector_Grid<Condition> burnStatus(Condition::NORMAL, SimSize.x, SimSize.y);
    Vector_Grid<I3x3Matrix> diffMatrix({0,0,0}, SimSize.x, SimSize.y);

    for(int i = 0; i < heatMap2.getLength(); i++)
    {
        heatMap2(i) = std::max(20,i);
        // std::cout<<heatMap2(i)<<" ";
    }
    std::cout<<std::endl<<"HeatMap2"<<std::endl;
    printGrid<int>(heatMap2, " ", 4, std::cout);


    //printGrid<int>(heatMap, " ", 4, std::cout);

    // for(int y = 0; y < heatMap.size().y; y++)
    // {
    //     std::cout<<std::setw(4)<<heatMap.at(0,y);
    //     for(int x = 1; x < heatMap.size().x; x++)
    //     {
    //         std::cout<<" "<<std::setw(4)<<heatMap.at(x,y);
    //     }
    //     std::cout<<std::endl;
    // }


    diffMatrix = computeDifferenceMatricies(heatMap2);

    //std::cout<<"difference Matrix:"<<std::endl;
    //printGrid<I3x3Matrix>(diffMatrix, " ", 4, std::cout);

    //heatLevelChange = solveDeltaHeatLevel(diffMatrix);

    // sumMed
    // sumDampedMed
    // deltaDampedAvg
    // detlaMaxDampedAvg
    // Vector_Grid<float> sumMed(0, SimSize.x, SimSize.y),
    //     sumDampedMed(0, SimSize.x, SimSize.y),
    //     deltaDampedAvg(0, SimSize.x, SimSize.y),
    //     deltaMaxDampedAvg(0, SimSize.x, SimSize.y);


    // std::cout<<"Running test Suite"<<std::endl;
    // for (int i = 0; i < diffMatrix.getLength(); i++)
    // {
    //     sumMed(i) = deltaTempSumMedian(diffMatrix(i), 0.75, 0.25);
    //     sumDampedMed(i) = deltaTempSumDampenedMedian(diffMatrix(i), 0.75, 0.25);
    //     deltaDampedAvg(i) = deltaTempDampedAverage(diffMatrix(i), 0.75, 0.25);
    //     deltaMaxDampedAvg(i) = deltaTempMaxDampedAverage(diffMatrix(i), 0.75, 0.25);
    // }
    // std::cout<<"print test Suite"<<std::endl;
    // std::cout<<"Summed Median"<<std::endl;
    // printGrid<float>(sumMed, " ", 4, std::cout);

    // std::cout<<"Sum Dampened Median"<<std::endl;
    // printGrid<float>(sumDampedMed, " ", 4, std::cout);

    // std::cout<<"Dampened Average"<<std::endl;
    // printGrid<float>(deltaDampedAvg, " ", 4, std::cout);

    // std::cout<<"Max Dampened Average"<<std::endl;
    // printGrid<float>(deltaMaxDampedAvg, " ", 4, std::cout);




    // ==================================================================================================================
    //                         This is a multi-equation test of the simulation step by step
    //                                  Temperatures are being shown below.
    // ==================================================================================================================

    // init maps to heat map 2
    Vector_Grid<int> sumMed(heatMap2), sumDampedMed(heatMap2), deltaDampedAvg(heatMap2), deltaMaxDampedAvg(heatMap2);
    Vector_Grid<I3x3Matrix> diffMatrix1(diffMatrix), diffMatrix2(diffMatrix), diffMatrix3(diffMatrix), diffMatrix4(diffMatrix);
    const float HEAT_MUTLI = 0.85, COOL_MULTI = 0.20;

    std::string cmdline;

    printGrid<int>(heatMap2, " ", 4);

    do{
        diffMatrix1 = computeDifferenceMatricies(sumMed);
        diffMatrix2 = computeDifferenceMatricies(sumDampedMed);
        diffMatrix3 = computeDifferenceMatricies(deltaDampedAvg);
        diffMatrix4 = computeDifferenceMatricies(deltaMaxDampedAvg);


        for (int i = 0; i < diffMatrix1.getLength(); i++)
        {
            sumMed(i) += deltaTempSumMedian(diffMatrix1(i), HEAT_MUTLI, COOL_MULTI);
            sumDampedMed(i) += deltaTempSumDampenedMedian(diffMatrix2(i), HEAT_MUTLI, COOL_MULTI);
            deltaDampedAvg(i) += deltaTempDampedAverage(diffMatrix3(i), HEAT_MUTLI, COOL_MULTI);
            deltaMaxDampedAvg(i) += deltaTempMaxDampedAverage(diffMatrix4(i), HEAT_MUTLI, COOL_MULTI);
        }

        std::cout<<"   ================================================================================================"<<endl;
        std::cout<<"     Summed Median " << std::setw(72) << " Dampened Summed Median"<<std::endl;
        for(int y = 0; y < sumMed.size().y; y++)
        {
            for (int x = 0; x < sumMed.size().x; x++)
            {
                cout << std::setw(4) << sumMed.at(x,y);
            }
            cout<<"                   ";
            for (int x = 0; x < sumDampedMed.size().x; x++)
            {
                cout << std::setw(4) << sumDampedMed.at(x,y);
            }
            std::cout<<endl;
        }
        cout<<endl;
        std::cout<<"     Damped Average" << std::setw(72) << "  Max Damped Average"<<std::endl;
        for(int y = 0; y < deltaDampedAvg.size().y; y++)
        {
            for (int x = 0; x < deltaDampedAvg.size().x; x++)
            {
                cout << std::setw(4) << deltaDampedAvg.at(x,y);
            }
            cout<<"                   ";
            for (int x = 0; x < deltaMaxDampedAvg.size().x; x++)
            {
                cout << std::setw(4) << deltaMaxDampedAvg.at(x,y);
            }
            std::cout<<endl;
        }

        // loop until 'e' + `enter` is pressed
    }while(cin.get() != 'e');


    // while (!WindowShouldClose())
    // {
    //     // Update data memebers
    //     elapsedTime += GetFrameTime();
    //     //updateRenderList(renderListBuffer,f*maxFlameRadiusuelAvaliable renderComponents);
        
    //     // update the firesim after 0.5 of a second
    //     if(elapsedTime >= SIM_SECONDS_PER_SIM_STEP)
    //     {
    //         //std::cout<<"run firestep()"<<std::endl;
    //         elapsedTime = 0.f;

    //         statusRectAngle += 360.f * float(DEG2RAD) / float(SIM_STEPS_PER_SECOND);
    //     }
    //     // if(IsKeyPressed(KeyboardKey::KEY_SPACE))
    //     // {
    //     //     runFireSimStep(fireSimData);
    //     // }

    //     //renderScene(renderListBuffer);

    //     // begin the render
    //     ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
    //     BeginDrawing();

    //     //std::cout<<"run draw sim()"<<std::endl;
    //     drawFireSim(fireSimData, Rectangle{400,100, 600,600}, true, false);

    //     //DrawRectanglePro(statusRec, statusRectCenter, statusRectAngle, DARKBLUE);
    //     DrawRectangle(statusRec.x, statusRec.y, statusRec.width, statusRec.height, DARKBLUE);
    //     DrawCircle(statusRectCenter.x, statusRectCenter.y, 10, RED);

    //     EndDrawing();

    //     // render UI Elements
    // }

    //CloseWindow();
    return 0;
}

