/*
* File: Game Header File
* Desc: Main header file for the wildfire simulation game. All effects are contained within one wrapper class
*   to contain the codebase
*/
#ifndef WILDFIRE_GAME_HPP
#define WILDFIRE_GAME_HPP

#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <cassert>

#include "raylib.h"
#include "helperFunctions.hpp"
#include "TileComponent.hpp"
#include "WindComponent.hpp"
#include "BiomeAtlas.hpp"
#include "SimulationPresets.hpp"
#include "lib/Vector_Grid.hpp"
#include "lib/Vec2i.hpp"
#include "lib/Vec2f.hpp"
#include "GameSettingsConstants.hpp"

inline Vec2i index_to_xy(const int index, const int sizeX, const int sizeY)
{
    return {index % sizeX, index / sizeX};
}

struct FireSimulationData{
    Vector_Grid<TileComponent> enviroLayer;
    // std::vector<TileComponent> nextEnviroLayer;  // next frame buffer
    Vector_Grid<WindComponent> windLayer;
    // std::vector<WindComponent> nextWindLayer;    // next frame buffer
    Vector_Grid<int> averageHeatMapC;
    Vec2i boardDimesions = {0, 0};

    // default constructor
    FireSimulationData(): enviroLayer(TileComponent()), windLayer(WindComponent{0, 0, 0}), averageHeatMapC(24)
    {

    }
    FireSimulationData& operator=(const FireSimulationData& copy)
    {
        assert(this->boardDimesions == copy.boardDimesions);
        this->enviroLayer = copy.enviroLayer;
        this->windLayer   = copy.windLayer;
        this->averageHeatMapC = copy.averageHeatMapC;
        return *this;
    }
};

void initFireSim(FireSimulationData& simData);

void runFireSimStep(FireSimulationData& simData);

void drawFireSim(const FireSimulationData& simData, const Rectangle& bounds, const bool drawDetailedBoard, const bool drawWindVectors);

// prints the grid with optional spacers
template<class T>
void printGrid(const Vector_Grid<T>& src, const std::string& optionalSpacer = " ", std::ostream& dest = std::cout);

// generates a vector grid of size AOEWidth by AOEWidth centered on the centerCoord point. Each entry of the 
//      resulting vector grid is a coordinate relative to the center coord
// assumes that the resulting grid is an odd by odd lengthed shape
//      ie, 3x3, 5x5, 7x7, etc
Vector_Grid<Vec2i> generateRelativeCoordinates(const Vec2i& centerCoord, const int AOEWidth);

// generates a vector grid of weights between two upper and lower bounds centered on 
//      the centeral point. The dimensions of the Grid are AOEWidth by AOEWidth centered on the
//      true center of the rectangle
// assumes that the resulting grid is an odd by odd lengthed shape. Only supports the following ATM
//      ie, 3x3, 5x5
Vector_Grid<float> generateProximityWeightMatrix(const int AOEWidth); //const float lowerBound, const float upperBound, 

// generates a vector grid of weights between the wind direction and neighboring cells. Returns a Grid that determins how wind
//      modifies the heat spreading calculations (dampens or increases them). All ccalculations are done relative to one centerCoord
//      and basically return the effect of wind on that cell's ability to spread
// assumes that the resulting grid is an odd by odd lengthed shape
//      ie, 3x3, 5x5, 7x7, etc
Vector_Grid<float> generateWindWeightMatrix(const Vector_Grid<WindComponent>& windLayer, const Vec2i& centerCoord, const int AOEWidth);

#endif