#include "game.hpp"

inline Vec2i dir_to_Vec2i(const Direction dir)
{
    static Vec2i directionUnitVectors[int(Direction::COUNT)] =
    {{-1, 1}, { 0, 1}, { 1, 1},
     {-1, 0}, { 0, 0}, { 1, 0},
     {-1,-1}, { 0,-1}, { 1,-1}};
    return directionUnitVectors[(int)dir];
}


inline Vec2i dir_to_coord(const Vec2i center, const Direction dir)
{
    return center + dir_to_Vec2i(dir);
}

inline Vec2i dir_to_coord(const size_t centerX, const size_t centerY, const Direction dir)
{
    return Vec2i(centerX, centerY) - dir_to_Vec2i(dir);
}

inline size_t dir_to_coord_x(const Vec2i center, const Direction dir)
{
    return center.x - dir_to_Vec2i(dir).x;
}

inline size_t dir_to_coord_x(const size_t x, const Direction dir)
{
    return x - dir_to_Vec2i(dir).x;
}

inline size_t dir_to_coord_y(const Vec2i center, const Direction dir)
{
    return center.x - dir_to_Vec2i(dir).y;
}

inline size_t dir_to_coord_y(const size_t y, const Direction dir)
{
    return y - dir_to_Vec2i(dir).y;
}







#ifdef GRAPHICS_ENABLED
void drawFireSim(const Vector_Grid<Tile>& simData, const Rectangle& bounds, const bool drawDetailedBoard, const bool drawWindVectors)
{
    // define variables
    const float reductionFactor = 0.75;
    Vector2 origin = {bounds.x, bounds.y};
    int tileWidth  = int(bounds.width /simData.size().x);
    int tileHeight = int(bounds.height/simData.size().y);
    const float maxFlameRadius = 0.5*reductionFactor*tileWidth;
    float flameRadiusMult = 1.0;

    Vec2f burntDim = {float(tileWidth), float(tileHeight)};    // init
    Vec2f burntOffset = {float(tileWidth), float(tileHeight)};

    // precompute fire characteristics
    burntDim *= reductionFactor;
    burntOffset *= (1.f-reductionFactor) / 2;

    // draw based on the location in the array of each tile
    for(int yIndex = 0; yIndex < simData.size().y; yIndex++)
    {
        for(int xIndex = 0; xIndex < simData.size().x; xIndex++)
        {
            const Tile& curTile = simData.at(xIndex, yIndex);
            Vec2i shapeOrigin = {origin.x+xIndex*tileWidth, origin.y+yIndex*tileHeight};
            Vec2i center = {shapeOrigin.x+(0.5* tileWidth), shapeOrigin.y+(0.5*tileHeight)};


            switch (curTile.biome)
            {
            // case Foliage::STONE :
            //     DrawRectangle(shapeOrigin.x, shapeOrigin.y, tileWidth, tileHeight, DARKGRAY);
            //     break;
            
            case Biome::WATER :
                DrawRectangle(shapeOrigin.x, shapeOrigin.y, tileWidth, tileHeight, DARKBLUE);
                break;
            case Biome::STONE :
                DrawRectangle(shapeOrigin.x, shapeOrigin.y, tileWidth, tileHeight, LIGHTGRAY);
                break;

            case Biome::GRASS :
                DrawRectangle(shapeOrigin.x, shapeOrigin.y, tileWidth, tileHeight, YELLOW);
                break;
            // case Foliage::BRUSH :
            //     DrawRectangle(shapeOrigin.x, shapeOrigin.y, tileWidth, tileHeight, BROWN);
            //     break;
            // case Foliage::SPARSE_FOREST :
            //     DrawRectangle(shapeOrigin.x, shapeOrigin.y, tileWidth, tileHeight, GREEN);
            //     break;
            case Biome::FOREST :
                DrawRectangle(shapeOrigin.x, shapeOrigin.y, tileWidth, tileHeight, DARKGREEN);
                break;

            default:
                std::cout<<"****FATAL ERROR: EviornmentType Preset not defined in Game::DrawFireSim() "<< static_cast<int>(curTile.biome)<<std::endl;
                DrawRectangle(shapeOrigin.x, shapeOrigin.y, tileWidth, tileHeight, GRAY);
                break;
            }

            // if tile has been burned, then set a black square
            if(curTile.cond == Condition::BURNT)
            {
                DrawRectangle(shapeOrigin.x+burntOffset.x, shapeOrigin.y+burntOffset.y, burntDim.x, burntDim.y, BLACK);
            }
            // if the tile is on fire, draw a red circle over it
            else if(curTile.cond == Condition::BURNING)
            {
                // compute flame radius multiplier
                // let 200 be initial ignition temp and 1000 be the simulation cap
                flameRadiusMult = mapValuef(curTile.temp, 200, 1000, 0.25, 1.0);
                DrawCircle(center.x, center.y, (maxFlameRadius*flameRadiusMult), RED);
            }

            // print the tempurature of the tile
            // DrawText(std::to_string(curTile.temperatureC).c_str(), center.x-(maxFlameRadius*0.5), center.y-(maxFlameRadius*0.5), maxFlameRadius, WHITE);


            if(drawDetailedBoard == true)
            {
                Color textColor{BLACK};
                std::string topText = "H:";
                            // middleText = "M:",
                            // bottomText = "F:";

                topText.append(std::to_string(curTile.temp).c_str());
                // middleText.append(std::to_string(curTile.moistureLevel.getValue()));
                // bottomText.append(std::to_string(curTile.fuelLevel.getValue()));

                if(curTile.cond == Condition::BURNT)
                {
                    textColor = WHITE;
                }

                // draw temperature
                DrawText(topText.c_str(), center.x-(maxFlameRadius*0.5), center.y-(maxFlameRadius*0.5), maxFlameRadius*0.5, textColor);

                // // draw middle text
                // DrawText(middleText.c_str(), center.x-(maxFlameRadius*0.5), center.y, maxFlameRadius*0.5, textColor);

                // // draw remaining fuel
                // DrawText(bottomText.c_str(), center.x-(maxFlameRadius*0.5), center.y+(maxFlameRadius*0.5), maxFlameRadius*0.5, textColor);

                // // draw average heat map values
                // DrawText(std::to_string(simData.averageHeatMapC.at(xIndex, yIndex)).c_str(), center.x-(maxFlameRadius*0.5), center.y+(maxFlameRadius*0.25), maxFlameRadius*0.5, WHITE);

            }

            // draw the wind arrow
            //DrawLine(center.x, center.y, (center.x+simData.windLayer.at(xIndex,yIndex).direction.x*maxFlameRadius), (center.y+simData.windLayer.at(xIndex,yIndex).direction.y*maxFlameRadius), ORANGE);
        }
    }


    // now draw all horizontal lines
    for(int y = 0; y <= simData.size().y; y++)
    {
        DrawLine(int(origin.x), int(origin.y+tileHeight*y), int(origin.x+simData.size().x*tileWidth), int(origin.y+tileHeight*y), BLACK);
    }

    // draw all vertical lines
    for(int x = 0; x <= simData.size().x; x++)
    {
        DrawLine(int(origin.x+tileWidth*x), int(origin.y), int(origin.x+tileWidth*x), int(origin.y+simData.size().y*tileHeight), BLACK);
    }
}
#endif


/* Function Name: Compute Differnce Matricies
* Description: Assess the HeatMap and Computes a Difference Map for each cell in the heatmap. The difference matrix
*   is the differnce in temperatures between a central cell and all if it's neighbors
* Inputs: Vector_Grid of the heatmap, where each cell is the temperature value at that location
* Preconditions:
* Outputs: Vector_Grid of 3x3 Integer Matricies which have the complete temperature difference for each corrdinate direction
*       Center will always be set to 0
* Returns: Vector_Grid of 3x3 Integer Matricies which have the complete temperature difference for each corrdinate direction
*       Center will always be set to 0
* Postconditions:
*/
Vector_Grid<I3x3Matrix> computeDifferenceMatricies(const Vector_Grid<int>& heatMap)
{
    // define Variables
    Vector_Grid<I3x3Matrix> diffM(I3x3Matrix{{0, 0, 0}}, heatMap.size().x, heatMap.size().y);
    Vec2i gridSize = {heatMap.size().x, heatMap.size().y};
    //int curTemp = 0;
    //Vec2i curLoc = {0,0};

    //std::cout<<"computing difference matrix for len: "<<diffM.getLength()<<std::endl;
    // loop through all cells
    for(int i = 0; i < heatMap.getLength(); i++)
    {
        // Update Variables
        int curTemp = heatMap(i);
        Vec2i curLoc = index_to_xy(i, gridSize.x, gridSize.y);
        
        // printf("Error in computerDifferenceMatricies() --> Vector_Grid will not work, will thow Out Of Bounds Error. Need structure with border boundary\n Exiting\n");
        // exit(1);
        
        // // for all of the coordinate directions, compute the difference
        // diffM(i)[0][0] = curTemp - heatMap.at(dir_to_coord_x(curLoc.x, Direction::NW), dir_to_coord_y(curLoc.y, Direction::NW));
        // diffM(i)[1][0] = curTemp - heatMap.at(dir_to_coord_x(curLoc.x, Direction::N),  dir_to_coord_y(curLoc.y, Direction::N));
        // diffM(i)[2][0] = curTemp - heatMap.at(dir_to_coord_x(curLoc.x, Direction::NE), dir_to_coord_y(curLoc.y, Direction::NE));

        // diffM(i)[0][1] = curTemp - heatMap.at(dir_to_coord_x(curLoc.x, Direction::W), dir_to_coord_y(curLoc.y, Direction::W));
        // //diffM(i)[1][1] = curTemp - heatMap.at(dir_to_coord_x(curLoc.x, Direction::CENTER), dir_to_coord_y(curLoc.y, Direction::CENTER));
        // diffM(i)[2][1] = curTemp - heatMap.at(dir_to_coord_x(curLoc.x, Direction::E), dir_to_coord_y(curLoc.y, Direction::E));

        // diffM(i)[0][2] = curTemp - heatMap.at(dir_to_coord_x(curLoc.x, Direction::SW), dir_to_coord_y(curLoc.y, Direction::SW));
        // diffM(i)[1][2] = curTemp - heatMap.at(dir_to_coord_x(curLoc.x, Direction::S),  dir_to_coord_y(curLoc.y, Direction::S));
        // diffM(i)[2][2] = curTemp - heatMap.at(dir_to_coord_x(curLoc.x, Direction::SE), dir_to_coord_y(curLoc.y, Direction::SE));

        cellHeatDifference(diffM(i), curTemp, curLoc, heatMap, Direction::NW);
        cellHeatDifference(diffM(i), curTemp, curLoc, heatMap, Direction::N);
        cellHeatDifference(diffM(i), curTemp, curLoc, heatMap, Direction::NE);

        cellHeatDifference(diffM(i), curTemp, curLoc, heatMap, Direction::W);
        // cellHeatDifference(diffM(i), curTemp, curLoc, heatMap, Direction::CENTER);
        cellHeatDifference(diffM(i), curTemp, curLoc, heatMap, Direction::E);

        cellHeatDifference(diffM(i), curTemp, curLoc, heatMap, Direction::SW);
        cellHeatDifference(diffM(i), curTemp, curLoc, heatMap, Direction::S);
        cellHeatDifference(diffM(i), curTemp, curLoc, heatMap, Direction::SE);
    }

    // end of loop, print sample heat map
    return diffM;
}

/* Function Name: Cell Heat Difference Calculator
* Description: A helper function for computerDifferenceMatricies() which computes the single step of a difference between one cell
*       and one of its neighbors (using DIRECTION input)
* Inputs: Ouput Matrix, Current center cell temp, current cell coordinate in the heatmap/map, and the direction from that cell
* Preconditions:
* Outputs: So long as adjacent point (from DIR variable) is in the heatmap grid, will compute the difference of heats, equates to:ADJ_OFFSET_SINGLESHOT
*       adjacent temp - curTemp
* Returns: none
* Postconditions:
*/
void cellHeatDifference(I3x3Matrix& diffMatrix, const int curTemp, const Vec2i& curCell, const Vector_Grid<int>& heatMap, const Direction& Dir)
{
    // Define variables
    Vec2i index = Vec2i(1,1) + dir_to_Vec2i(Dir);
    Vec2i loc = dir_to_coord(curCell, Dir);

    if(heatMap.isInGrid(loc.x, loc.y))
    {
        diffMatrix[index.y][index.x] = heatMap.at(loc.x, loc.y) - curTemp;

        //printf("DiffMatrix[%d][%d] = %d\n", index.x, index.y, diffMatrix[index.x][index.y]);
    }
}

/* Function Name: Compute Matrix Median Values
* Description: Finds the median positive and negative values in the matrix, respectfully. Ignores zeros
* Inputs: I3x3Matrix
* Preconditions:
* Outputs: Pair of ints, First = Positive Median Value,
                        Second = Negative Median Value
* Returns: Pair of ints, First = Positive Median Value,
                        Second = Negative Median Value
* Postconditions:
*/
inline std::pair<int,int> computeMatrixMedian(const I3x3Matrix& diffMatrix)
{
    // define variables
    int posMed = 0, negMed = 0;
    std::vector<int> positives, negatives;

    // reserve size
    positives.reserve(8);
    negatives.reserve(8);

    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
                 if(diffMatrix[x][y] > 0) {positives.push_back(diffMatrix[x][y]);}
            else if(diffMatrix[x][y] < 0) {negatives.push_back(diffMatrix[x][y]);}
        }
    }

    // sort lists if elements present
    if (positives.size() > 0) 
    {
        std::sort(positives.begin(), positives.end());
        posMed = positives.at(static_cast<int>(positives.size() / 2));
    }
    if (negatives.size() > 0)
    {
        std::sort(negatives.begin(), negatives.end());
        negMed = negatives.at(static_cast<int>(negatives.size() / 2));
    } 

    return std::pair<int,int>(posMed, negMed);
}

/* Function Name: Compute Matrix Average Values
* Description: Finds the average positive and negative value in the matrix, respectfully. Ignores zeros
* Inputs:
* Preconditions:
* Outputs: Pair of floats, First = Positive Median Value,
                          Second = Negative Median Value
* Returns: Pair of floats, First = Positive Median Value,
                          Second = Negative Median Value
* Postconditions:
*/
inline std::pair<float,float> computeMatrixAverage(const I3x3Matrix& diffMatrix)
{
    // define variables
    std::pair<float, int> positive, negative;

    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            if(diffMatrix[x][y] > 0) 
            {
                positive.first += diffMatrix[x][y];
                positive.second++;
            }
            else if(diffMatrix[x][y] < 0) 
            {
                negative.first += diffMatrix[x][y];
                negative.second++;
            }
        }
    }

    // compute the averages and return
    if (positive.second > 0) positive.first = static_cast<float>(positive.first / positive.second);
    if (negative.second > 0) negative.first = static_cast<float>(negative.first / negative.second);

    return std::pair<float, float>(positive.first, negative.first);
}


/* Function Name: Solve Detla Heat Level Map
* Description: Converts results of difference matrix into a single intermediate heat value which will 
*       map to a temperature increase/decrease value for the final simulation. Function takes heat differnce
*       matrix grid and computes the intermediate heat level value from the non-zero results
* Inputs: Heat Map Neighbor Difference Matrix Grid
* Preconditions:
* Outputs: integer vector grid of intermediate delta heat values
* Returns: integer vector grid of intermediate delta heat values
* Postconditions: intermediate delta heat values must be interpreted before being applied to heat map
*/
Vector_Grid<int> solveDeltaHeatLevel(const Vector_Grid<I3x3Matrix>& diffMatrix)
{
    // define variables
    Vector_Grid<int> deltaHeatLevels(0, diffMatrix.size().x, diffMatrix.size().y);

    for(int i = 0; i < diffMatrix.getLength(); i++)
    {
        deltaHeatLevels(i) = deltaHeatLevelFromMatrix(diffMatrix(i));
    }

    return deltaHeatLevels;
}

/* Function Name: Compute Matrix Delta Heat Level
* Description: Helper function for `solveDeltaHeatLevel()` which solves for a single 3x3 Matrix
*       Generates a single intermediate delta heat level value.
* Inputs: a single I3x3Matrix object of adjacent temperature differences
* Preconditions:
* Outputs: computes an intermediate delta heat level value for matrix
* Returns: computes an intermediate delta heat level value for matrix
* Postconditions: intermediate delta heat value must be interpreted before being applied to heat map
*/
int deltaHeatLevelFromMatrix(const I3x3Matrix& diffMatrix)
{
    // define variables
    int posHeat = 0, posCount = 0;
    int negHeat = 0, negCount = 0;

}



/* Function Name: Calculate Temperature Delta using Sum Median Method
* Description: Assesses difference matrix and computes a delta temperature from formula:
*       deltaTemperature = (median positive temp difference) + (median negative temp difference)
* Inputs: A grid cell's difference matrix, cooling and heating damper multipliers as decimals (recommended ex 0.25 and 0.75)
* Preconditions:
* Outputs: a cell's calculated temperature increase/decrease in standard units
* Returns: a cell's calculated temperature increase/decrease in standard units
* Postconditions:
*/
float deltaTempSumMedian(const I3x3Matrix& diffMatrix, const float coolingDamperMultiplier, const float heatingDamperMultiplier)
{
    // Define Variables
    std::pair<int,int> medians = computeMatrixMedian(diffMatrix);
    medians.first = std::min(medians.first, TEMP_DELTA_MAX_HEAT);
    medians.second = std::max(medians.second, TEMP_DELTS_MIN_COOL);

    // firest is positve median, second is negative median
    return medians.first + medians.second;
}

/* Function Name: Calculate Temperature Delta using Sum Damped Median Method
* Description: Assesses difference matrix and computes a delta temperature from formula:
*   if pos med temp + neg med temp is positive
*       deltaTemperature = heatingDamperMultiplier * ((median positive temp difference) + (median negative temp difference))
*   otherwise
*       deltaTemperature = coolingDamperMultiplier * ((median positive temp difference) + (median negative temp difference))
* Inputs: A grid cell's difference matrix, cooling and heating damper multipliers as decimals (recommended ex 0.25 and 0.75)
* Preconditions:
* Outputs: a cell's calculated temperature increase/decrease in standard units
* Returns: a cell's calculated temperature increase/decrease in standard units
* Postconditions:
*/
float deltaTempSumDampenedMedian(const I3x3Matrix& diffMatrix, const float coolingDamperMultiplier, const float heatingDamperMultiplier)
{
    // Define Variables
    std::pair<int,int> medians = computeMatrixMedian(diffMatrix); // First = PosMed, second = NegMed
    medians.first = std::min(medians.first, TEMP_DELTA_MAX_HEAT);
    medians.second = std::max(medians.second, TEMP_DELTS_MIN_COOL);

    int summedMedian = medians.first + medians.second;

    // if positive, apply heating damper
    if(summedMedian > 0) heatingDamperMultiplier * summedMedian;
    // else cooling damper
    else summedMedian = coolingDamperMultiplier * summedMedian;

    return summedMedian;
}


/* Function Name: Calculate Temperature Delta using Damped Average Method
* Description:  Assesses difference matrix and computes a delta temperature from formula:
*       deltaTemperature = (heatingDamperMultiplier * AVG Pos Diff) + (coolingDamperMultiplier * AVG Neg Diff)
* Inputs: A grid cell's difference matrix, cooling and heating damper multipliers as decimals (recommended ex 0.25 and 0.75)
* Preconditions:
* Outputs: a cell's calculated temperature increase/decrease in standard units
* Returns: a cell's calculated temperature increase/decrease in standard units
* Postconditions:
*/
float deltaTempDampedAverage(const I3x3Matrix& diffMatrix, const float coolingDamperMultiplier, const float heatingDamperMultiplier)
{
    // define variables
    std::pair<float, float> averages = computeMatrixAverage(diffMatrix);
    averages.first = std::min(averages.first, (float)TEMP_DELTA_MAX_HEAT);
    averages.second = std::max(averages.second, (float)TEMP_DELTS_MIN_COOL);

    return (heatingDamperMultiplier*averages.first) + (coolingDamperMultiplier*averages.second);
}

/* Function Name: Calculate Temperature Delta using Max Damped Average Method
* Description:  Assesses difference matrix and computes a delta temperature from formula:
*   if DampendAverage < 0
*       deltaTemperature = MAXIMUM(Average Negative, (coolingDamperMultiplier * Dampened AVG))
*   otherwise
*       deltaTemperature = MINIMUM(Average Positive, (HeatingDamperMultiplier * Dampened AVG))
* Inputs: A grid cell's difference matrix, cooling and heating damper multipliers as decimals (recommended ex 0.25 and 0.75)
* Preconditions:
* Outputs: a cell's calculated temperature increase/decrease in standard units
* Returns: a cell's calculated temperature increase/decrease in standard units
* Postconditions:
*/
float deltaTempMaxDampedAverage(const I3x3Matrix& diffMatrix, const float coolingDamperMultiplier, const float heatingDamperMultiplier)
{
    // define variables
    std::pair<float, float> averages = computeMatrixAverage(diffMatrix);
    averages.first = std::min(averages.first, (float)TEMP_DELTA_MAX_HEAT);
    averages.second = std::max(averages.second, (float)TEMP_DELTS_MIN_COOL);
    // int dampedAvg = (heatingDamperMultiplier*averages.first) + (coolingDamperMultiplier*averages.second);
    int dampedAvg = (averages.first) + (averages.second);


    // if damped average is positive
    if(dampedAvg > 0)
    {
        return std::min(averages.first, (heatingDamperMultiplier * dampedAvg));
    }
    else if (dampedAvg < 0)
    {
        return std::max(averages.second, (coolingDamperMultiplier * dampedAvg));
    }
    else return 0;
    
}

/* Function Name:
* Description: Uses "direct-solve" Methods to compute the change in the heat map temperature for the next simulation step. "direct-
*       solve" differes from the intermediate method since it directly computes the delte temperature value from convection events
*   Mode <SUM_MEDIAN> applies the deltaTempSumMedian() function to each matrix
*   Mode <SUM_DAMPENED_MEDIAN> Applies deltaTempSumDampenedMedian()
*   Mode <DAMPENED_AVERAGE> Applies deltaTempDampenedAverage()
*   Mode <MAX_DAMPEDED_AVERAGE> Applies deltaTempMaxDampenedAverage()
* Inputs: difference matrix to process, defined solver mode
* Preconditions:
* Outputs: Float Vector_Grid of heat delta values, +/-, to be applied directly to the heat map
* Returns: Float Vector_Grid of heat delta values, +/-, to be applied directly to the heat map
* Postconditions:
*/
Vector_Grid<float> directSolveDeltaTemperature(const Vector_Grid<I3x3Matrix>& diffMatrix, const Direct_Solver mode)
{
    // define variables
    Vector_Grid<float> deltaHeatMap(0, diffMatrix.size().x, diffMatrix.size().y);
    const float HEAT_MUTLI = 0.5, COOL_MULTI = 0.15;

    switch (mode)
    {
    case Direct_Solver::SUM_MEDIAN:
        for(int i = 0; i < diffMatrix.getLength(); i++)
        {
            deltaHeatMap(i) = deltaTempSumMedian(diffMatrix(i), HEAT_MUTLI, COOL_MULTI);
        }
        break;
    case Direct_Solver::SUM_DAMPENED_MEDIAN:
        for(int i = 0; i < diffMatrix.getLength(); i++)
        {
            deltaHeatMap(i) = deltaTempSumDampenedMedian(diffMatrix(i), HEAT_MUTLI, COOL_MULTI);
        }
        break;
    case Direct_Solver::DAMPENED_AVERAGE:
        for(int i = 0; i < diffMatrix.getLength(); i++)
        {
            deltaHeatMap(i) = deltaTempDampedAverage(diffMatrix(i), HEAT_MUTLI, COOL_MULTI);
        }
        break;
    case Direct_Solver::MAX_DAMPENED_AVERAGE:
        for(int i = 0; i < diffMatrix.getLength(); i++)
        {
            deltaHeatMap(i) = deltaTempMaxDampedAverage(diffMatrix(i), HEAT_MUTLI, COOL_MULTI);
        }
        break;
    
    default:
        std::cout<<"***WARNING*** Solver Mode does not have a definition set --> See directSolveDeltaTemperature()"<<std::endl;
        break;
    }

    return deltaHeatMap;
}

/* Function Name: Apply Abient Temperature Damping
* Description: Function slighly pulls the heat map temperature closer to ambient, simulating a large-body of the atmospher
* Inputs: Heat Map to assess, current ambient temperature
* Preconditions:
* Outputs: map of delta temp values which should be applied to the heat map
* Returns: map of delta temp values which should be applied to the heat map
* Postconditions:
*/
Vector_Grid<float> applyAmbientDamping(const Vector_Grid<int>& heatMap, const int ambient)
{
    // define variables
    Vector_Grid<float> deltaHeatMap(0, heatMap.size().x, heatMap.size().y);
    const float HEAT_MUTLI = 0.15, COOL_MULTI = 0.2;

    for(int i = 0; i < heatMap.getLength(); i++)
    {
        int diff = heatMap(i) - ambient;

        // if cell is hotter, pull it down by an ammount
        if(diff > 0)       deltaHeatMap(i) = std::min(-1.f, (-1.f) * COOL_MULTI * (float)sqrt(diff));
        else if (diff < 0) deltaHeatMap(i) = std::max( 1.f, (-1.f) * HEAT_MUTLI * (float)sqrt(diff));
    }

    return deltaHeatMap;
}