/*
File name:  Tile Component
Description: Component containing all data relating to a simulation a tile in the
    fire sim. This includes data such as tile type, local humidity, avaliable 
    fuel, fire intensity.
    Also contains all functions and prebuilds to support easy development of code loop
*/
#ifndef ENVIROMENT_TILE_COMPONENT_HPP
#define ENVIROMENT_TILE_COMPONENT_HPP

#include <iostream>
#include "GameSettingsConstants.hpp"
#include "Scale.hpp"

// #include "Component.hpp"

// Define the EnvironmentTypes enum
enum class Foliage{
    NONE = 0,
    WATER,
    GRASS,
    //BRUSH,
    FOREST
};

// enum class Scale<0,10>{
//     ZERO = 0,
//     ONE,
//     TWO,
//     THREE,
//     FOUR,
//     FIVE,
//     SIX,
//     SEVEN,
//     EIGHT,
//     NINE,
//     TEN,
//     SCALE_MAX   // maximum level of the scale. Allows for easy scaling up and down later
// };

enum class BurnState{
    NOT = 0,
    //SMOLDERING,
    ON_FIRE,
    BURNED
};

// defi

struct TileComponent{
public:
    Foliage biomeTag;
    BurnState burnState;
    Scale<0,20> heatLevel;
    Scale<0,25> fuelLevel;
    Scale<0,20> moistureLevel;

    // Default Constructor -- barren stone tile
    TileComponent()
    {

    }

    // copy constructor
    TileComponent(const TileComponent& copy)
    {
        this->biomeTag = copy.biomeTag;
        this->burnState = copy.burnState;
        this->heatLevel = copy.heatLevel;
        this->fuelLevel = copy.fuelLevel;
        this->moistureLevel = copy.moistureLevel;
    }

    // copy assignment operator
    TileComponent& operator=(const TileComponent& rhs)
    {
            this->biomeTag = rhs.biomeTag;
            this->burnState = rhs.burnState;
            this->heatLevel = rhs.heatLevel;
            this->fuelLevel = rhs.fuelLevel;
            this->moistureLevel = rhs.moistureLevel;


        return *this;
    }

    // destructor
    ~TileComponent()
    {
        // nothing to free
    }

    // =========================================================================================
    //                              Public Member Functions
    // =========================================================================================


};


#endif