/*
* File: Game Header File
* Desc: Main header file for the wildfire simulation game. All effects are contained within one wrapper class
*   to contain the codebase
*/
#ifndef WILDFIRE_GAME_HPP
#define WILDFIRE_GAME_HPP

#include <array>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <cassert>
#include <iostream>
#include <iomanip>

#include "raylib.h"
#include "helperFunctions.hpp"
#include "lib/Vector_Grid.hpp"
#include "lib/Vec2i.hpp"
#include "lib/Vec2f.hpp"
#include "Matrix3x3.hpp"

//#define GRAPHICS_ENABLED

enum class Biome{
    WATER = 0,
    STONE,
    GRASS,
    FOREST
};

enum class Condition{
    NORMAL = 0,
    BURNING,
    BURNT
};

enum class Direction{
    NW = 0,
    N,
    NE,
    W,
    CENTER,
    E,
    SW,
    S,
    SE,
    COUNT
};

enum class Direct_Solver{
    SUM_MEDIAN = 0,
    SUM_DAMPENED_MEDIAN,
    DAMPENED_AVERAGE,
    MAX_DAMPENED_AVERAGE
};

// define an object called a 3x3 matrix
using I3x3Matrix = Matrix3x3<int>;
using F3x3Matrix = Matrix3x3<float>;

const int TEMP_DELTA_MAX_HEAT = 20, TEMP_DELTS_MIN_COOL = -10;

typedef struct
{
    int temp;
    Biome biome;
    Condition cond;

}Tile;

inline Vec2i index_to_xy(const int index, const int sizeX, const int sizeY)
{
    return {index % sizeX, index / sizeX};
}

inline Vec2i dir_to_Vec2i(const Direction dir);
inline Vec2i dir_to_coord(const Vec2i center, const Direction dir);
inline Vec2i dir_to_coord(const size_t centerX, const size_t centerY, const Direction dir);
inline size_t dir_to_coord_x(const Vec2i center, const Direction dir);
inline size_t dir_to_coord_x(const size_t x, const Direction dir);
inline size_t dir_to_coord_y(const Vec2i center, const Direction dir);
inline size_t dir_to_coord_y(const size_t y, const Direction dir);


#ifdef GRAPHICS_ENABLED
void drawFireSim(const Vector_Grid<Tile>& simData, const Rectangle& bounds, const bool drawDetailedBoard, const bool drawWindVectors);
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
Vector_Grid<I3x3Matrix> computeDifferenceMatricies(const Vector_Grid<int>& heatMap);

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
void cellHeatDifference(I3x3Matrix& diffMatrix, const int curTemp, const Vec2i& curCell, const Vector_Grid<int>& heatMap, const Direction& Dir);


// add grids together
// precondition: grids must be the same size
inline void addGrid(Vector_Grid<int>& rhs, const Vector_Grid<int>& lhs)
{
    assert((rhs.size().x == lhs.size().x && rhs.size().y == lhs.size().y) || "Grids are not the same size addGrid() failed");
    for(int i = 0; i < rhs.getLength(); i++)
    {
        rhs(i) = rhs(i) + lhs(i);
    }
}
// add grids together (float overload)
// precondition: grids must be the same size
inline void addGrid(Vector_Grid<float>& rhs, const Vector_Grid<float>& lhs)
{
    assert((rhs.size().x == lhs.size().x && rhs.size().y == lhs.size().y) || "Grids are not the same size addGrid() failed");
    for(int i = 0; i < rhs.getLength(); i++)
    {
        rhs(i) = rhs(i) + lhs(i);
    }
}
// add grids together (int rhs, float lhs overload)
// precondition: grids must be the same size
inline void addGrid(Vector_Grid<int>& rhs, const Vector_Grid<float>& lhs)
{
    assert((rhs.size().x == lhs.size().x && rhs.size().y == lhs.size().y) || "Grids are not the same size addGrid() failed");
    for(int i = 0; i < rhs.getLength(); i++)
    {
        rhs(i) = rhs(i) + lhs(i);
    }
}
// add grids together (float rhs, int lhs overload)
// precondition: grids must be the same size
inline void addGrid(Vector_Grid<float>& rhs, const Vector_Grid<int>& lhs)
{
    assert((rhs.size().x == lhs.size().x && rhs.size().y == lhs.size().y) || "Grids are not the same size addGrid() failed");
    for(int i = 0; i < rhs.getLength(); i++)
    {
        rhs(i) = rhs(i) + lhs(i);
    }
}

// prints the grid with optional spacers
// REMINDER: Template functions are only allowed in header files
template<class T>
void printGrid(const Vector_Grid<T>& src, const std::string& optionalSpacer = " ", const int minimalSpacing = 0, std::ostream& dest = std::cout)
{
    for(int y = 0; y < src.size().y; y++)
    {
        for(int x = 0; x < src.size().x; x++)
        {
            dest<<std::setw(minimalSpacing)<<src.at(x,y)<<optionalSpacer;
        }
        dest<<std::endl;
    }
    dest<<std::endl;
}

// Explicit I3x3Matrix implimentation
template<>
inline void printGrid<I3x3Matrix>(const Vector_Grid<I3x3Matrix>& src, const std::string& optionalSpacer, int minimalSpacing, std::ostream& dest)
{
    for (int y = 0; y < src.size().y; y++)  // Iterate over rows of Vector_Grid
    {
        for (int row = 0; row < 3; row++)  // Iterate over the rows of each 3x3 matrix
        {
            for (int x = 0; x < src.size().x; x++)  // Iterate over columns of Vector_Grid
            {
                const I3x3Matrix& matrix = src.at(x, y);  // Get matrix at (x, y)

                dest << "[ ";
                for (int col = 0; col < 3; col++)  // Iterate over columns of the matrix
                {
                    dest << std::setw(minimalSpacing) << matrix[row][col] << optionalSpacer;
                }
                dest << "] ";
            }
            dest << std::endl;  // Move to the next row of 3x3 matrices
        }
        dest << std::endl;  // Extra line to separate grid rows
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
inline std::pair<int,int> computeMatrixMedian(const I3x3Matrix& diffMatrix);

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
inline std::pair<float,float> computeMatrixAverage(const I3x3Matrix& diffMatrix);

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
Vector_Grid<int> solveDeltaHeatLevel(const Vector_Grid<I3x3Matrix>& diffMatrix);

/* Function Name: Compute Matrix Delta Heat Level
* Description: Helper function for `solveDeltaHeatLevel()` which solves for a single 3x3 Matrix
*       Generates a single intermediate delta heat level value.
* Inputs: a single I3x3Matrix object of adjacent temperature differences
* Preconditions:
* Outputs: computes an intermediate delta heat level value for matrix
* Returns: computes an intermediate delta heat level value for matrix
* Postconditions: intermediate delta heat value must be interpreted before being applied to heat map
*/
int deltaHeatLevelFromMatrix(const I3x3Matrix& diffMatrix);



/* Function Name: Calculate Temperature Delta using Sum Median Method
* Description: Assesses difference matrix and computes a delta temperature from formula:
*       deltaTemperature = (median positive temp difference) + (median negative temp difference)
* Inputs: A grid cell's difference matrix, cooling and heating damper multipliers as decimals (recommended ex 0.25 and 0.75)
* Preconditions:
* Outputs: a cell's calculated temperature increase/decrease in standard units
* Returns: a cell's calculated temperature increase/decrease in standard units
* Postconditions:
*/
float deltaTempSumMedian(const I3x3Matrix& diffMatrix, const float coolingDamperMultiplier, const float heatingDamperMultiplier);

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
float deltaTempSumDampenedMedian(const I3x3Matrix& diffMatrix, const float coolingDamperMultiplier, const float heatingDamperMultiplier);

/* Function Name: Calculate Temperature Delta using Damped Average Method
* Description:  Assesses difference matrix and computes a delta temperature from formula:
*       deltaTemperature = (heatingDamperMultiplier * AVG Pos Diff) + (coolingDamperMultiplier * AVG Neg Diff)
* Inputs: A grid cell's difference matrix, cooling and heating damper multipliers as decimals (recommended ex 0.25 and 0.75)
* Preconditions:
* Outputs: a cell's calculated temperature increase/decrease in standard units
* Returns: a cell's calculated temperature increase/decrease in standard units
* Postconditions:
*/
float deltaTempDampedAverage(const I3x3Matrix& diffMatrix, const float coolingDamperMultiplier, const float heatingDamperMultiplier);

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
float deltaTempMaxDampedAverage(const I3x3Matrix& diffMatrix, const float coolingDamperMultiplier, const float heatingDamperMultiplier);

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
Vector_Grid<float> directSolveDeltaTemperature(const Vector_Grid<I3x3Matrix>& diffMatrix, const Direct_Solver mode);

/* Function Name:
* Description:
* Inputs:
* Preconditions:
* Outputs:
* Returns:
* Postconditions:
*/
Vector_Grid<int> computeCombustionEffects(const Vector_Grid<int>& heatMap);

/* Function Name: Apply Abient Temperature Damping
* Description: Function slighly pulls the heat map temperature closer to ambient, simulating a large-body of the atmospher
* Inputs: Heat Map to assess, current ambient temperature
* Preconditions:
* Outputs: map of delta temp values which should be applied to the heat map
* Returns: map of delta temp values which should be applied to the heat map
* Postconditions:
*/
Vector_Grid<float> applyAmbientDamping(const Vector_Grid<int>& heatMap, const int ambient);


/* Function Name:
* Description:
* Inputs:
* Preconditions:
* Outputs:
* Returns:
* Postconditions:
*/

/* Function Name:
* Description:
* Inputs:
* Preconditions:
* Outputs:
* Returns:
* Postconditions:
*/

/* Function Name:
* Description:
* Inputs:
* Preconditions:
* Outputs:
* Returns:
* Postconditions:
*/
#endif