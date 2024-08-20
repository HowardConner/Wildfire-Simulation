/*
Simulation Presets
A collection of simulation test presets
*/
#ifndef FIRE_SIMULATION_PRESENTS_HPP
#define FIRE_SIMULATION_PRESENTS_HPP

#include <vector>

#include "TileComponent.hpp"
#include "lib/Vec2i.hpp"

struct SimulationPreset{
    Vec2i BOARD_DIMS = {0,0};
    std::vector<Foliage> enviromentData;
    //std::vector<int> elevationData;
    //std::vector<int> percentHumidityData;
    //std::vector<int> temperature;
    std::vector<BurnState> fireState;
    std::vector<Vec2i> ignitionPoints;

    SimulationPreset() {}
    SimulationPreset(const SimulationPreset& copy)
    {
        *this = copy;
    }
    SimulationPreset& operator=(const SimulationPreset& rhs)
    {
        this->BOARD_DIMS            = rhs.BOARD_DIMS;
        this->enviromentData        = rhs.enviromentData;
        //this->elevationData         = rhs.elevationData;
        //this->percentHumidityData   = rhs.percentHumidityData;
        this->ignitionPoints        = rhs.ignitionPoints;

        return *this;
    }
    ~SimulationPreset() {}
};

// // Define pre-defined preset functions
// static SimulationPreset load5x5SamplePreset()
// {
//     SimulationPreset newPreset;

//     newPreset.BOARD_DIMS.x = 5;
//     newPreset.BOARD_DIMS.y = 5;

//     newPreset.enviromentData = {
//         Foliage::WATER, Foliage::WATER, Foliage::WATER, Foliage::WATER, Foliage::WATER,
//         Foliage::WATER, Foliage::WATER, Foliage::WATER, Foliage::WATER, Foliage::WATER,
//         Foliage::WATER, Foliage::WATER, Foliage::GRASS, Foliage::WATER, Foliage::GRASS,
//         Foliage::WATER, Foliage::WATER, Foliage::WATER, Foliage::WATER, Foliage::WATER,
//         Foliage::WATER, Foliage::WATER, Foliage::GRASS, Foliage::FOREST, Foliage::FOREST,
//     };
//     newPreset.elevationData = {
//         0, 0, 0, 0, 0,
//         0, 0, 0, 0, 0,
//         0, 0, 1, 0, 0,
//         0, 0, 0, 0, 0,
//         0, 0, 0, 0, 0,
//     };
//     newPreset.percentHumidityData = {
//         50, 50, 50, 50, 50,
//         50, 50, 50, 50, 50,
//         50, 50, 50, 50, 50,
//         50, 50, 50, 50, 50,
//         50, 50, 50, 50, 50,
//     };
//     newPreset.temperature = {
//         25, 25, 25, 25, 25,
//         25, 25, 25, 25, 25,
//         25, 25, 25, 25, 25,
//         25, 25, 25, 25, 25,
//         25, 25, 25, 25, 25,
//     };
//     newPreset.fireState = {
//         BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT,
//         BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT,
//         BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT,
//         BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT,
//         BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT,
//     };
//     return newPreset;
// }

// Define pre-defined preset functions
inline SimulationPreset load3x3FlameSpreadMixed()
{
    SimulationPreset newPreset;

    newPreset.BOARD_DIMS.x = 3;
    newPreset.BOARD_DIMS.y = 3;

    newPreset.enviromentData = {
        Foliage::FOREST, Foliage::FOREST, Foliage::FOREST,
        Foliage::GRASS,  Foliage::FOREST, Foliage::FOREST,
        Foliage::GRASS,  Foliage::GRASS,  Foliage::FOREST, 

    };
    // newPreset.elevationData = {
    //     0, 0, 0,
    //     0, 0, 0,
    //     0, 0, 0,
    // };
    // newPreset.percentHumidityData = {
    //     50, 50, 50,
    //     50, 00, 50,
    //     50, 50, 50,
    // };
    // newPreset.temperature = {
    //     -25, 25, 25,
    //     25, 500, 25,
    //     25, 25, 25,
    // };
    newPreset.fireState = {
        BurnState::NOT, BurnState::NOT, BurnState::NOT,
        BurnState::NOT, BurnState::ON_FIRE, BurnState::NOT,
        BurnState::NOT, BurnState::NOT, BurnState::NOT,
    };
    newPreset.ignitionPoints.push_back({1,1});

    return newPreset;
}

// Define pre-defined preset functions
inline SimulationPreset load3x3FlameSpreadGrass()
{
    SimulationPreset newPreset;

    newPreset.BOARD_DIMS.x = 3;
    newPreset.BOARD_DIMS.y = 3;

    newPreset.enviromentData = {
        Foliage::GRASS, Foliage::GRASS, Foliage::GRASS,
        Foliage::GRASS, Foliage::GRASS, Foliage::GRASS,
        Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, 

    };

    newPreset.fireState = {
        BurnState::NOT, BurnState::NOT, BurnState::NOT,
        BurnState::NOT, BurnState::ON_FIRE, BurnState::NOT,
        BurnState::NOT, BurnState::NOT, BurnState::NOT,
    };
    newPreset.ignitionPoints.push_back({1,1});

    return newPreset;
}

// Define pre-defined preset functions
inline SimulationPreset load5x5FlameSpreadGrass()
{
    SimulationPreset newPreset;

    newPreset.BOARD_DIMS.x = 5;
    newPreset.BOARD_DIMS.y = 5;

    newPreset.enviromentData = {
        Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS,
        Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS,
        Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS,
        Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS,
        Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS,
    };

    newPreset.fireState = {
        BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT,
        BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT,
        BurnState::NOT, BurnState::NOT, BurnState::ON_FIRE, BurnState::NOT, BurnState::NOT,
        BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT,
        BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT,
    };
    // newPreset.ignitionPoints.push_back({1,1});
    // newPreset.ignitionPoints.push_back({1,2});
    // newPreset.ignitionPoints.push_back({2,1});
    newPreset.ignitionPoints.push_back({2,2});

    return newPreset;
}

// Define pre-defined preset functions
inline SimulationPreset load5x5FlameSpreadMixedWind()
{
    SimulationPreset newPreset;

    newPreset.BOARD_DIMS.x = 5;
    newPreset.BOARD_DIMS.y = 5;

    newPreset.enviromentData = {
        Foliage::FOREST, Foliage::FOREST, Foliage::FOREST, Foliage::FOREST, Foliage::FOREST,
        Foliage::GRASS, Foliage::FOREST, Foliage::FOREST, Foliage::FOREST, Foliage::FOREST,
        Foliage::GRASS, Foliage::GRASS, Foliage::FOREST, Foliage::FOREST, Foliage::FOREST,
        Foliage::GRASS, Foliage::FOREST, Foliage::FOREST, Foliage::FOREST, Foliage::FOREST,
        Foliage::FOREST, Foliage::FOREST, Foliage::FOREST, Foliage::FOREST, Foliage::FOREST,
    };

    newPreset.fireState = {
        BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT,
        BurnState::ON_FIRE, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT,
        BurnState::ON_FIRE, BurnState::ON_FIRE, BurnState::NOT, BurnState::NOT, BurnState::NOT,
        BurnState::ON_FIRE, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT,
        BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT,
    };
    newPreset.ignitionPoints.push_back({0,1});
    newPreset.ignitionPoints.push_back({0,2});
    newPreset.ignitionPoints.push_back({1,2});
    newPreset.ignitionPoints.push_back({0,3});

    return newPreset;
}

// Define pre-defined preset functions
inline SimulationPreset load5x5FlameSpreadMixedCenterWind()
{
    SimulationPreset newPreset;

    newPreset.BOARD_DIMS.x = 5;
    newPreset.BOARD_DIMS.y = 5;

    newPreset.enviromentData = {
        Foliage::FOREST, Foliage::FOREST, Foliage::FOREST, Foliage::FOREST, Foliage::FOREST,
        Foliage::FOREST, Foliage::FOREST, Foliage::FOREST, Foliage::FOREST, Foliage::FOREST,
        Foliage::FOREST, Foliage::FOREST, Foliage::GRASS, Foliage::FOREST, Foliage::FOREST,
        Foliage::FOREST, Foliage::FOREST, Foliage::FOREST, Foliage::FOREST, Foliage::FOREST,
        Foliage::FOREST, Foliage::FOREST, Foliage::FOREST, Foliage::FOREST, Foliage::FOREST,
    };

    newPreset.fireState = {
        BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT,
        BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT,
        BurnState::NOT, BurnState::NOT, BurnState::ON_FIRE, BurnState::NOT, BurnState::NOT,
        BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT,
        BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT,
    };
    // newPreset.ignitionPoints.push_back({1,1});
    // newPreset.ignitionPoints.push_back({1,2});
    // newPreset.ignitionPoints.push_back({2,1});
    newPreset.ignitionPoints.push_back({2,2});

    return newPreset;
}

// Define pre-defined preset functions
inline SimulationPreset load11x11FlameSpreadMixedCenterWind()
{
    SimulationPreset newPreset;

    newPreset.BOARD_DIMS.x = 11;
    newPreset.BOARD_DIMS.y = 11;

    newPreset.enviromentData = {
        Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS,
        Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS,
        Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS,
        Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS,
        Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS,
        Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS,
        Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS,
        Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::FOREST, Foliage::FOREST, Foliage::FOREST, Foliage::FOREST, Foliage::FOREST,
        Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::FOREST, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS,
        Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::FOREST, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS,
        Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::FOREST, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS,
        Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::FOREST, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS,
    };

    newPreset.fireState = {
        BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT,
        BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT,
        BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT,
        BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT,
        BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT,
        BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT,
        BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT,
        BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT,
        BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT,
        BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT,
        BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT,
    };
    // newPreset.ignitionPoints.push_back({1,1});
    // newPreset.ignitionPoints.push_back({1,2});
    // newPreset.ignitionPoints.push_back({2,1});
    newPreset.ignitionPoints.push_back({5, 5});

    return newPreset;
}


// Define pre-defined preset functions
inline SimulationPreset load5x5FlameSpreadMixed()
{
    SimulationPreset newPreset;

    newPreset.BOARD_DIMS.x = 5;
    newPreset.BOARD_DIMS.y = 5;

    newPreset.enviromentData = {
        Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS,
        Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::FOREST, Foliage::GRASS,
        Foliage::GRASS, Foliage::GRASS, Foliage::FOREST, Foliage::FOREST, Foliage::FOREST,
        Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::FOREST, Foliage::FOREST,
        Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::FOREST,
    };

    newPreset.fireState = {
        BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT,
        BurnState::NOT, BurnState::ON_FIRE, BurnState::ON_FIRE, BurnState::NOT, BurnState::NOT,
        BurnState::NOT, BurnState::ON_FIRE, BurnState::ON_FIRE, BurnState::NOT, BurnState::NOT,
        BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT,
        BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT,
    };
    newPreset.ignitionPoints.push_back({1,1});
    newPreset.ignitionPoints.push_back({1,2});
    newPreset.ignitionPoints.push_back({2,1});
    newPreset.ignitionPoints.push_back({2,2});

    return newPreset;
}


// Define pre-defined preset functions
static SimulationPreset load10x5SamplePreset()
{
    SimulationPreset newPreset;

    newPreset.BOARD_DIMS.x = 10;
    newPreset.BOARD_DIMS.y = 5;

    newPreset.enviromentData = {
        Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::FOREST, Foliage::FOREST, Foliage::FOREST, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS,
        Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::FOREST, Foliage::FOREST, Foliage::FOREST, Foliage::FOREST, Foliage::GRASS, Foliage::GRASS,
        Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::FOREST, Foliage::GRASS, Foliage::WATER, Foliage::WATER, Foliage::FOREST, Foliage::FOREST, Foliage::GRASS,
        Foliage::GRASS, Foliage::GRASS, Foliage::FOREST, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::WATER, Foliage::FOREST, Foliage::FOREST, Foliage::GRASS,
        Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::GRASS, Foliage::WATER, Foliage::WATER, Foliage::FOREST, Foliage::FOREST,
    };
    // newPreset.elevationData = {
    //     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    //     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    //     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    //     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    //     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    // };
    // newPreset.percentHumidityData = {
    //     10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    //     10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    //     10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    //     10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    //     10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 
    // };
    // newPreset.temperature = {
    //     25, 25, 25, 25, 25, 25, 25, 25, 25, 25,
    //     25, 25, 25, 25, 25, 25, 25, 25, 25, 25,
    //     25, 25, 25, 25, 25, 25, 25, 25, 25, 25,
    //     25, 25, 25, 25, 25, 25, 25, 25, 25, 25,
    //     25, 25, 25, 25, 25, 25, 25, 25, 25, 25,
    // };
    newPreset.fireState = {
        BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT,
            BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT,
        BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT,
            BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT,
        BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT,
            BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT,
        BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT,
            BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT,
        BurnState::ON_FIRE, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT,
            BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT, BurnState::NOT,

    };
    newPreset.ignitionPoints.push_back({0,3});
    newPreset.ignitionPoints.push_back({0,4});
    newPreset.ignitionPoints.push_back({1,4});

    return newPreset;
}

#endif