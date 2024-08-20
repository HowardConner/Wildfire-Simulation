/*
Environment Types Header File
Contains a list of all supported Environment types as well as prebuild constructors for each of
    those types. These prebuilds load a pre-defined set of variables for each enviornment type
*/
#ifndef BIOME_ATLAS_HPP
#define BIOME_ATLAS_HPP

#include <unordered_map>
#include "GameSettingsConstants.hpp"
#include "TileComponent.hpp" // to support the forward-definition

// forward delcaire types
// enum Foliage;
// enum Scale;
// enum HeatLevel;
// struct TileComponent;


enum class FuelDensity{
    NONE        = 0,
    SPARSE      = 1,
    MODERATE    = 2,
    DENSE       = 4
};

enum class VegetationType{
    NONE        = 0,
    HERBACEOUS  = 1,
    MIXED       = 2,
    WOODY       = 3
};

enum class Age{
    NONE        = 0,
    YOUNG       = 1,
    MATURE      = 2,
    OLD_GROWTH  = 3
};

struct Biome{
    float fuelEfficiencyBonus;    // - means uses fuel slower, + means consumes faster
    float tempIncreaseBonus;      // how a (on fire) tile has bonus temp increase due to combustion
    float ignitionResistanceFactor; // additional damping factor applied to the igntion level to increase (>1.0) or decrease (<1.0) igntion level
    float moistureRetentionBonus;   // bonus on the moisture that a cell contains (- reduces effects of evaporation)

//     FuelDensity fuelDensity;
//     VegetationType vegetationType;
//     Age age;
//     float fuelBurnRate;
//     float fuelHeatFactor;   // factor of heat (in temperature) generated by fuel
//     int ignitionTemperature;
//     int maxBurnTemperature;
};

// define const biome references
const Biome BiomeWater{0, -2, 2.0, -50.f};
const Biome BiomeStone{0, 0, 100.f, 0.f};

const Biome BiomeGrass{    0, 3, 0.75, 0.f};
const Biome BiomeBrush{    0, 1, 1.f , 0.f};
const Biome BiomeForest{  -2, 3, 2.f, -6.f};
// const Biome BiomeOldForest{     FuelDensity::DENSE,     VegetationType::WOODY,      Age::OLD_GROWTH, 0.4f, 1.0, 360, 1000};

const std::unordered_map<Foliage, Biome> biomeAtlas{
    {Foliage::WATER, BiomeWater},
    //{Foliage::STONE, BiomeStone},
    {Foliage::GRASS, BiomeGrass},
    //{Foliage::BRUSH, BiomeBrush},
    //{Foliage::SPARSE_FOREST, BiomeSparseForest},
    {Foliage::FOREST, BiomeForest},
};

// Define the prebuilt functions list

// water Environment
inline void generateWaterPrebuilt(TileComponent& component)//, const int initTileElevation, const int initLocalHumidityPercent)
{
    component.biomeTag = Foliage::WATER;
    component.burnState = BurnState::NOT;
    component.fuelLevel.setToMin();
    component.heatLevel.setToMin();
    component.moistureLevel = int( 0.75* component.moistureLevel.getMax());
}
// grass Environment
inline void generateGrassPrebuilt(TileComponent& component)//, const int initTileElevation, const int initLocalHumidityPercent)
{
    component.biomeTag = Foliage::GRASS;
    component.burnState = BurnState::NOT;
    component.fuelLevel.setToMax();
    component.heatLevel.setToMin();
    component.moistureLevel = int( 0.50* component.moistureLevel.getMax());
}
// heavy forest Environment
inline void generateDenseForestPrebuilt(TileComponent& component)//, const int initTileElevation, const int initLocalHumidityPercent)
{
    component.biomeTag = Foliage::FOREST;
    component.burnState = BurnState::NOT;
    component.fuelLevel.setToMax();
    component.heatLevel.setToMin();
    component.moistureLevel = int( 0.75* component.moistureLevel.getMax());
}


// // stone Environment
// inline void generateStonePrebuilt(TileComponent& component, const int initTileElevation, const int initLocalHumidityPercent)
// {
//     component.fuelTag          = Foliage::STONE;
//     component.percentFuelAvaliable     = 0;
//     component.percentMoisture      = 0;
//     component.temperatureC      = 25;
//     component.fireState         = BurnState::NOT;
// }

// // heavy shrub Environment
// inline void generateBrushPrebuilt(TileComponent& component, const int initTileElevation, const int initLocalHumidityPercent)
// {
//     component.fuelTag          = Foliage::BRUSH;
//     component.percentFuelAvaliable     = 30;
//     component.percentMoisture      = 10;
//     component.temperatureC      = 25;
//     component.fireState         = BurnState::NOT;
// }
// // Light forest Environment
// inline void generateLightForestPrebuilt(TileComponent& component, const int initTileElevation, const int initLocalHumidityPercent)
// {
//     component.fuelTag          = Foliage::SPARSE_FOREST;
//     component.percentFuelAvaliable     = 1000;
//     component.percentMoisture      = 50;
//     component.temperatureC      = 25;
//     component.fireState         = BurnState::NOT;
// }


#endif