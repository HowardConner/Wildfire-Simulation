#include "game.hpp"

void initFireSim(FireSimulationData& simData)
{
    TileComponent baseTile;  // use default values for stone
    WindComponent baseWindTile;         // use default (zero)
    SimulationPreset preset(load11x11FlameSpreadMixedCenterWind());

    // init the size of the vectors
    simData.boardDimesions = preset.BOARD_DIMS;
    simData.enviroLayer.setSize(preset.BOARD_DIMS.x, preset.BOARD_DIMS.y);
    simData.windLayer.setSize(preset.BOARD_DIMS.x, preset.BOARD_DIMS.y);
    simData.averageHeatMapC.setSize(preset.BOARD_DIMS.x, preset.BOARD_DIMS.y);
    
    simData.enviroLayer.fill(baseTile);
    simData.windLayer.fill(baseWindTile);
    simData.averageHeatMapC.fill(24);

    // load the presets:
    for(int i = 0; i < preset.BOARD_DIMS.y*preset.BOARD_DIMS.x; i++)
    {
        switch (preset.enviromentData.at(i))
        {
        // case Foliage::STONE :
        //     generateStonePrebuilt(simData.enviroLayer(i), preset.enviromentData.at(i), preset.percentHumidityData.at(i));
        //     break;
        
        case Foliage::WATER :
            generateWaterPrebuilt(simData.enviroLayer(i));
            break;

        case Foliage::GRASS :
            generateGrassPrebuilt(simData.enviroLayer(i));
            break;
        // case Foliage::BRUSH :
        //     generateBrushPrebuilt(simData.enviroLayer(i), preset.enviromentData.at(i), preset.percentHumidityData.at(i));
        //     break;
        // case Foliage::SPARSE_FOREST :
        //     generateLightForestPrebuilt(simData.enviroLayer(i), preset.enviromentData.at(i), preset.percentHumidityData.at(i));
        //     break;
        case Foliage::FOREST :
            generateDenseForestPrebuilt(simData.enviroLayer(i));
            break;

        default:
            std::cout<<"****FATAL ERROR: EviornmentType Preset not defined in TileComponent::generatePrebuilt()"<<std::endl;
            std::cout<<"         Default build set to STONE"<<std::endl;
            // default to build stone:
            generateWaterPrebuilt(simData.enviroLayer(i));

            break;
        }

        // set burn states
        simData.enviroLayer(i).burnState = preset.fireState.at(i);
        simData.windLayer(i).direction = Vec2f(1.f, 2.f);
        simData.windLayer(i).direction.normal();
        simData.windLayer(i).speed = 5;
    }

    // for all the ignition coords, light them on fire to highest heat
    for(int i = 0; i < preset.ignitionPoints.size(); i++)
    {
        Vec2i coord = preset.ignitionPoints.at(i);

        simData.enviroLayer.at(coord.x, coord.y).burnState = BurnState::ON_FIRE;
        simData.enviroLayer.at(coord.x, coord.y).heatLevel.setToMax();
    }
    
}

void runFireSimStep(FireSimulationData& simData)
{
    // define variables
    Vector_Grid<float> expectedDeltaHeat(0.f, simData.enviroLayer.size().x, simData.enviroLayer.size().y);


    // // process burning fuel consumption
    // for(int i = 0; i < simData.enviroLayer.getLength(); i++)
    // {
    //     TileComponent& curTile = simData.enviroLayer(i);

    // }

    // process cooling effects due to local moisture
    for(int i = 0; i < simData.enviroLayer.getLength(); i++)
    {
        TileComponent& curTile = simData.enviroLayer(i);
        int moistureModifier = 1;

        // if tile is very hot, make it better and removing moisture form itself
        if(curTile.heatLevel > 3*curTile.heatLevel.getMax()/4)
        {
            moistureModifier = 2;
        }

        if(curTile.heatLevel >= 1)
        {
            if(curTile.moistureLevel >= (0.75 * curTile.moistureLevel.getMax()))
            {
                expectedDeltaHeat(i) -= int(6 / std::min(1.0, moistureModifier / 2.0));
            }
            else if(curTile.moistureLevel >= (0.40 * curTile.moistureLevel.getMax()))
            {
                expectedDeltaHeat(i) -= int(4 / moistureModifier);
            }
            else if(curTile.moistureLevel >= (0.20 * curTile.moistureLevel.getMax()))
            {
                expectedDeltaHeat(i) -= int(1);
            }
            // else if(curTile.moistureLevel >= 1)
            // {
            //     curTile.heatLevel -= 1;
            // }
        }
    }
    
    // std::cout<<"end cooling:"<<std::endl;
    // std::cout<<"process local heating:"<<std::endl;

    // process local heating effects
    for(int i = 0; i < simData.enviroLayer.getLength(); i++)
    {
        TileComponent& curTile = simData.enviroLayer(i);

        if(curTile.heatLevel >= 1 && curTile.moistureLevel > 0)
        {
            if(curTile.heatLevel >= (0.90 * curTile.heatLevel.getMax()))
            {
                curTile.moistureLevel -= 5 + biomeAtlas.at(curTile.biomeTag).moistureRetentionBonus;
            }
            else if(curTile.heatLevel >= (0.70 * curTile.heatLevel.getMax()))
            {
                curTile.moistureLevel -= 4 + biomeAtlas.at(curTile.biomeTag).moistureRetentionBonus;
            }
            else if(curTile.heatLevel >= (0.40 * curTile.heatLevel.getMax()))
            {
                curTile.moistureLevel -= 2 + biomeAtlas.at(curTile.biomeTag).moistureRetentionBonus;
            }
        }
    }

    // process burning fuel consumption
    for(int i = 0; i < simData.enviroLayer.getLength(); i++)
    {
        TileComponent& curTile = simData.enviroLayer(i);

        if(curTile.burnState == BurnState::ON_FIRE)
        {
            // consume fuel based on current heat level
            if(curTile.heatLevel >= (0.90 * curTile.heatLevel.getMax()))
            {
                curTile.fuelLevel -= 1;
                expectedDeltaHeat(i) += 8 + biomeAtlas.at(curTile.biomeTag).tempIncreaseBonus;
            }
            else if(curTile.heatLevel >= (0.40 * curTile.heatLevel.getMax()))
            {
                curTile.fuelLevel -= 2;
                expectedDeltaHeat(i) += 6.75 + biomeAtlas.at(curTile.biomeTag).tempIncreaseBonus;
            }
            else
            {
                curTile.fuelLevel -= 1;
                expectedDeltaHeat(i) += 5.5 + biomeAtlas.at(curTile.biomeTag).tempIncreaseBonus;
            }
        }
    }

    // std::cout<<"end local heating:"<<std::endl;
    // std::cout<<"process dispersed heating:"<<std::endl;

    // calculated dispersed heading due to convection
    //  TODO: incorperate wind effect
    for(int i = 0; i < simData.enviroLayer.getLength(); i++)
    {
        Vec2i curCoords = index_to_xy(i, simData.boardDimesions.x, simData.boardDimesions.y);
        TileComponent& curTile = simData.enviroLayer(i);
        const int AREA_OF_EFFECT = 3;
        Vector_Grid<Vec2i> Coords = generateRelativeCoordinates(curCoords, AREA_OF_EFFECT);
        const Vector_Grid<float> proximityWeights = generateProximityWeightMatrix(AREA_OF_EFFECT),
                                windWeights = generateWindWeightMatrix(simData.windLayer, curCoords, AREA_OF_EFFECT);

        // for each cell in the AOE, apply heating based on the current cell's temp
        for(int j = 0; j < Coords.getLength(); j++)
        {
            int heatDiff = 0, temp = 0;
            float coolingDivisor = 1.0;

            
            if(simData.enviroLayer.isInGrid(Coords(j).x, Coords(j).y))
            {
                heatDiff = curTile.heatLevel.getValue() - simData.enviroLayer.at(Coords(j).x, Coords(j).y).heatLevel.getValue();

                if(heatDiff < 0) {coolingDivisor = 0.5; }

                expectedDeltaHeat.at(Coords(j).x, Coords(j).y) += temp = std::round((proximityWeights(j) + windWeights(j)) * coolingDivisor * heatDiff); //

                
                // if(temp != 0)
                // {
                //     std::cout<<"("<<Coords(j).x<<", "<<Coords(j).y<<") "<<temp<< "  |  "<<expectedDeltaHeat.at(Coords(j).x, Coords(j).y)<<std::endl;
                // }            
            }
        }
    }

    // for each cell above ambient (zero) apply a slight cooling effect
    for(int i = 0; i < simData.enviroLayer.getLength(); i++)
    {
        const float AMBIENT_COOLING_EFFECT = 1.65;
        if(simData.enviroLayer(i).burnState != BurnState::ON_FIRE && simData.enviroLayer(i).heatLevel > 0)
        {
            expectedDeltaHeat(i) -= AMBIENT_COOLING_EFFECT;
        }
    }

    // std::cout<<"end dispersed heating:"<<std::endl;
    // std::cout<<"print delta heat:"<<std::endl;

    // // print the resulting delta
    // std::cout<<"Delta Heat added: "<<std::endl;
    // for(int y = 0; y < simData.boardDimesions.y; y++)
    // {
    //     for(int x = 0; x < simData.boardDimesions.x; x++)
    //     {
    //         std::cout<<expectedDeltaHeat.at(x,y)<<"   ";
    //     }
    //     std::cout<<std::endl;
    // }
    // std::cout<<"===================="<<std::endl;

    // post process the local heating data (clamp)
    for(int i = 0; i < expectedDeltaHeat.getLength(); i++)
    {
        const float BUFFER_FACTOR = 0.75;
        // reduce the effectivness of cooling
        if(expectedDeltaHeat(i) < 0)
        {
            expectedDeltaHeat(i) = std::floor((expectedDeltaHeat(i) + BUFFER_FACTOR) / 11.f);
        }
        else
        {
            expectedDeltaHeat(i) = std::ceil((expectedDeltaHeat(i)- BUFFER_FACTOR) / 2.f);
        }
    }
    
    // // print the resulting delta
    // std::cout<<"Delta Heat added: "<<std::endl;
    // for(int y = 0; y < simData.boardDimesions.y; y++)
    // {
    //     for(int x = 0; x < simData.boardDimesions.x; x++)
    //     {
    //         std::cout<<expectedDeltaHeat.at(x,y)<<"   ";
    //     }
    //     std::cout<<std::endl;
    // }
    // std::cout<<"===================="<<std::endl;

    // apply neighboring effects to board
    for(int i = 0; i < simData.enviroLayer.getLength(); i++)
    {
        simData.enviroLayer(i).heatLevel += expectedDeltaHeat(i);
    }

    // std::cout<<"print delta heat:"<<std::endl;
    // std::cout<<"process ignition rules:"<<std::endl;

    // define ignition rules
    for(int i = 0; i < simData.enviroLayer.getLength(); i++)
    {
        TileComponent& curTile = simData.enviroLayer(i);

        if(curTile.biomeTag != Foliage::WATER && curTile.biomeTag != Foliage::NONE)
        {
            switch (curTile.burnState)
            {
            case BurnState::NOT:
                if(curTile.heatLevel >= IGNITION_LEVEL * biomeAtlas.at(curTile.biomeTag).ignitionResistanceFactor)
                {
                    curTile.burnState = BurnState::ON_FIRE;
                }
                break;
            
            case BurnState::ON_FIRE:
                if(curTile.fuelLevel <= 0)
                {
                    curTile.burnState = BurnState::BURNED;
                }
                else if( curTile.heatLevel < IGNITION_LEVEL)
                {
                    curTile.burnState = BurnState::NOT;
                }
                break;
            
            case BurnState::BURNED:
                
                break;
            
            default:
                break;
            }
        }

    }
    // std::cout<<"end ignition rules:"<<std::endl;
}

void drawFireSim(const FireSimulationData& simData, const Rectangle& bounds, const bool drawDetailedBoard, const bool drawWindVectors)
{
    // define variables
    const float reductionFactor = 0.75;
    Vector2 origin = {bounds.x, bounds.y};
    int tileWidth  = int(bounds.width /simData.boardDimesions.x);
    int tileHeight = int(bounds.height/simData.boardDimesions.y);
    const float maxFlameRadius = 0.5*reductionFactor*tileWidth;
    float flameRadiusMult = 1.0;

    Vec2f burntDim = {float(tileWidth), float(tileHeight)};    // init
    Vec2f burntOffset = {float(tileWidth), float(tileHeight)};

    // precompute fire characteristics
    burntDim *= reductionFactor;
    burntOffset *= (1.f-reductionFactor) / 2;

    // draw based on the location in the array of each tile
    for(int yIndex = 0; yIndex < simData.boardDimesions.y; yIndex++)
    {
        for(int xIndex = 0; xIndex < simData.boardDimesions.x; xIndex++)
        {
            const TileComponent& curTile = simData.enviroLayer.at(xIndex, yIndex);
            Vec2i shapeOrigin = {origin.x+xIndex*tileWidth, origin.y+yIndex*tileHeight};
            Vec2i center = {shapeOrigin.x+(0.5* tileWidth), shapeOrigin.y+(0.5*tileHeight)};


            switch (curTile.biomeTag)
            {
            // case Foliage::STONE :
            //     DrawRectangle(shapeOrigin.x, shapeOrigin.y, tileWidth, tileHeight, DARKGRAY);
            //     break;
            
            case Foliage::WATER :
                DrawRectangle(shapeOrigin.x, shapeOrigin.y, tileWidth, tileHeight, DARKBLUE);
                break;

            case Foliage::GRASS :
                DrawRectangle(shapeOrigin.x, shapeOrigin.y, tileWidth, tileHeight, YELLOW);
                break;
            // case Foliage::BRUSH :
            //     DrawRectangle(shapeOrigin.x, shapeOrigin.y, tileWidth, tileHeight, BROWN);
            //     break;
            // case Foliage::SPARSE_FOREST :
            //     DrawRectangle(shapeOrigin.x, shapeOrigin.y, tileWidth, tileHeight, GREEN);
            //     break;
            case Foliage::FOREST :
                DrawRectangle(shapeOrigin.x, shapeOrigin.y, tileWidth, tileHeight, DARKGREEN);
                break;

            default:
                std::cout<<"****FATAL ERROR: EviornmentType Preset not defined in Game::DrawFireSim() "<< static_cast<int>(curTile.biomeTag)<<std::endl;
                DrawRectangle(shapeOrigin.x, shapeOrigin.y, tileWidth, tileHeight, GRAY);
                break;
            }

            // if tile has been burned, then set a black square
            if(curTile.burnState == BurnState::BURNED)
            {
                DrawRectangle(shapeOrigin.x+burntOffset.x, shapeOrigin.y+burntOffset.y, burntDim.x, burntDim.y, BLACK);
            }
            // if the tile is on fire, draw a red circle over it
            else if(curTile.burnState == BurnState::ON_FIRE)
            {
                // compute flame radius multiplier
                flameRadiusMult = mapValuef(curTile.heatLevel.getValue(), curTile.heatLevel.getMin(), curTile.heatLevel.getMax(), 0.25, 1.0);
                DrawCircle(center.x, center.y, (maxFlameRadius*flameRadiusMult), RED);
            }

            // print the tempurature of the tile
            // DrawText(std::to_string(curTile.temperatureC).c_str(), center.x-(maxFlameRadius*0.5), center.y-(maxFlameRadius*0.5), maxFlameRadius, WHITE);


            if(drawDetailedBoard == true)
            {
                Color textColor{BLACK};
                std::string topText = "H:",
                            middleText = "M:",
                            bottomText = "F:";

                topText.append(std::to_string(curTile.heatLevel.getValue()).c_str());
                middleText.append(std::to_string(curTile.moistureLevel.getValue()));
                bottomText.append(std::to_string(curTile.fuelLevel.getValue()));

                if(curTile.burnState == BurnState::BURNED)
                {
                    textColor = WHITE;
                }

                // draw temperature
                DrawText(topText.c_str(), center.x-(maxFlameRadius*0.5), center.y-(maxFlameRadius*0.5), maxFlameRadius*0.5, textColor);

                // draw middle text
                DrawText(middleText.c_str(), center.x-(maxFlameRadius*0.5), center.y, maxFlameRadius*0.5, textColor);

                // draw remaining fuel
                DrawText(bottomText.c_str(), center.x-(maxFlameRadius*0.5), center.y+(maxFlameRadius*0.5), maxFlameRadius*0.5, textColor);

                // // draw average heat map values
                // DrawText(std::to_string(simData.averageHeatMapC.at(xIndex, yIndex)).c_str(), center.x-(maxFlameRadius*0.5), center.y+(maxFlameRadius*0.25), maxFlameRadius*0.5, WHITE);

            }

            // draw the wind arrow
            DrawLine(center.x, center.y, (center.x+simData.windLayer.at(xIndex,yIndex).direction.x*maxFlameRadius), (center.y+simData.windLayer.at(xIndex,yIndex).direction.y*maxFlameRadius), ORANGE);
        }
    }


    // now draw all horizontal lines
    for(int y = 0; y <= simData.boardDimesions.y; y++)
    {
        DrawLine(int(origin.x), int(origin.y+tileHeight*y), int(origin.x+simData.boardDimesions.x*tileWidth), int(origin.y+tileHeight*y), BLACK);
    }

    // draw all vertical lines
    for(int x = 0; x <= simData.boardDimesions.x; x++)
    {
        DrawLine(int(origin.x+tileWidth*x), int(origin.y), int(origin.x+tileWidth*x), int(origin.y+simData.boardDimesions.y*tileHeight), BLACK);
    }
}













    // // for each tile, loop through and compute the expected increase in temperature
    // for(int i = 0; i < simData.enviroLayer.getLength(); i++)
    // {
    //     // define variables
    //     TileComponent &curTile = simData.enviroLayer(i);
    //     const Biome &biome = biomeAtlas.at(curTile.fuelTag);
    //     int tempDiff = 0;





    //     // apply natural cooling effects
    //     tempDiff = curTile.temperatureC - AMBIENT_TEMPERATURE;
    //     std::cout<<tempDiff<<"   ";
    //     if(std::abs(tempDiff) > 5)
    //     {
    //         curTile.deltaTempC = curTile.deltaTempC - int(0.02 * tempDiff);
    //         std::cout<<curTile.deltaTempC<<" | ";
    //     }
    //     else if (std::abs(tempDiff) > 1)
    //     {
    //         int fixedReductionAmount = 1;
    //         if(tempDiff < 0) 
    //         {
    //             fixedReductionAmount *= -1;
    //         }

    //         curTile.deltaTempC = curTile.deltaTempC - fixedReductionAmount;
    //     }
    //     else
    //     {
    //         curTile.deltaTempC = curTile.deltaTempC - tempDiff;
    //     }

    // }
    // std::cout<<std::endl;

    // // perform state change effects -- includes applying and resetting delta T
    // for(int i = 0; i < simData.enviroLayer.getLength(); i++)
    // {
    //     // define variables
    //     TileComponent &curTile = simData.enviroLayer(i);
    //     const Biome &biome = biomeAtlas.at(curTile.fuelTag);

    //     // apply and reset delta t
    //     curTile.temperatureC = std::clamp(curTile.temperatureC + curTile.deltaTempC, -100, biome.maxBurnTemperature);
    //     curTile.deltaTempC = 0;

    //     switch (curTile.burnState)
    //     {
    //     case BurnState::NOT:
    //         if(curTile.temperatureC > biome.ignitionTemperature)
    //         {
    //             curTile.burnState = BurnState::ON_FIRE;
    //         }
    //         break;
    //     case BurnState::ON_FIRE:
    //         if(curTile.temperatureC <= biome.ignitionTemperature)
    //         {
    //             curTile.burnState = BurnState::NOT;
    //         }
    //         else if(curTile.percentFuelAvaliable <= 0)
    //         {
    //             curTile.burnState = BurnState::BURNED;
    //         }
    //         break;
    //     case BurnState::BURNED:
            
    //         break;
        
    //     default:
    //         break;
    //     }
    // }



// prints the grid with optional spacers
template<class T>
void printGrid(const Vector_Grid<T>& src, const std::string& optionalSpacer, std::ostream& dest)
{
    for(int y = 0; y < src.size().y; y++)
    {
        for(int x = 0; x < src.size().x; x++)
        {
            dest<<src.at(x,y)<<optionalSpacer;
        }
        dest<<std::endl;
    }
    dest<<std::endl;
}

// generates a vector grid of size AOEWidth by AOEWidth centered on the centerCoord point. Each entry of the 
//      resulting vector grid is a coordinate relative to the center coord
// assumes that the resulting grid is an odd by odd lengthed shape
//      ie, 3x3, 5x5, 7x7, etc
Vector_Grid<Vec2i> generateRelativeCoordinates(const Vec2i& centerCoord, const int AOEWidth)
{
    // preprocessor assert
    assert(AOEWidth % 2 == 1 && "AOEWidth was NOT an odd number; behavior undefined");

    // define variables
    Vector_Grid<Vec2i> result(centerCoord, AOEWidth,AOEWidth);
    int offset = (AOEWidth / 2);

    for(int y = 0; y < AOEWidth; y++)
    {
        for(int x = 0; x < AOEWidth; x++)
        {
            result.at(x,y) = {centerCoord.x + x - offset, centerCoord.y + y - offset};
            //std::cout<<result.at(x,y).x<<", "<<result.at(x,y).y<<"    ";
        }
        //std::cout<<std::endl;
    }

    return result;
}

// generates a vector grid of weights between two upper and lower bounds centered on 
//      the centeral point. The dimensions of the Grid are AOEWidth by AOEWidth centered on the
//      true center of the rectangle
// assumes that the resulting grid is an odd by odd lengthed shape. Only supports the following ATM
//      ie, 3x3, 5x5
Vector_Grid<float> generateProximityWeightMatrix(const int AOEWidth) //const float lowerBound, const float upperBound, 
{
    // preprocess asserts
    assert(AOEWidth % 2 == 1 && "AOEWidth was NOT an odd number; behavior undefined");
    assert((AOEWidth == 3 || AOEWidth == 5) && "Other AOEWidth options NOT supported");

    // define variables
    Vector_Grid<float> result(0.0, AOEWidth, AOEWidth);

    if(AOEWidth == 3)
    {
        result = {
            0.25, 0.5, 0.25,
            0.5 , 0.f,  0.5,
            0.25, 0.5, 0.25
        };
    }
    else if(AOEWidth == 5)
    {
        result = {
            0.125, 0.25, 0.25, 0.25, 0.125,
            0.25,  0.35, 0.50, 0.35, 0.25,
            0.25,  0.50, 0.f,  0.5,  0.25,
            0.25,  0.35, 0.50, 0.35, 0.25,
            0.125, 0.25, 0.25, 0.25, 0.125,
        };
    }

    return result;
}

// generates a vector grid of weights between the wind direction and neighboring cells. Returns a Grid that determins how wind
//      modifies the heat spreading calculations (dampens or increases them). All ccalculations are done relative to one centerCoord
//      and basically return the effect of wind on that cell's ability to spread
// assumes that the resulting grid is an odd by odd lengthed shape
//      ie, 3x3, 5x5, 7x7, etc
Vector_Grid<float> generateWindWeightMatrix(const Vector_Grid<WindComponent>& windLayer, const Vec2i& centerCoord, const int AOEWidth)
{
    // define variables
    Vector_Grid<float> result(0.0, AOEWidth, AOEWidth);
    const float CUTOFF_ANGLE = 0.5;
    int offset = (AOEWidth / 2);

    for(int y = 0; y < AOEWidth; y++)
    {
        for(int x = 0; x < AOEWidth; x++)
        {
            //CUTOFF_ANGLE = (1 / windLayer.at(x,y).speed);
            float dotProd = windLayer.at(x,y).direction.dot({x - offset, y - offset});
            //std::cout<<dotProd<<std::endl;

            // if dot product is positive (at least almost in the direction of the wind flow)
            if(dotProd == 0 && Vec2i(x,y) == centerCoord)
            {
                // wind effect due to self
                result.at(x,y) = 0.35;
            }
            else if(dotProd > CUTOFF_ANGLE)
            {
                // higher winds
                result.at(x,y) = mapValuef(dotProd, CUTOFF_ANGLE, 1.0, 0.25, 1.05);
            }
            else
            {
                // faster wind makes back flow much less effective
                result.at(x,y) = mapValuef(dotProd, -1.0, CUTOFF_ANGLE, -0.12, 0);
            }
        }
    }


    if(Vec2i{5,5} == centerCoord){printGrid<float>(result, "   ", std::cout);}

    return result;
}