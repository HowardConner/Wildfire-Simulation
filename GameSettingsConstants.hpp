#ifndef GAME_SETTINGS_CONSTANTS_HPP
#define GAME_SETTINGS_CONSTANTS_HPP

// simulation constants
const float SIM_STEPS_PER_SECOND = 4;            // number of simulation steps in one clock second
const float SIM_SECONDS_PER_SIM_STEP = 1.f / SIM_STEPS_PER_SECOND;    // Fraction of a second between simulation steps

// define ambient temperature
const int IGNITION_LEVEL = 6;
const int MAX_HEAT_LEVEL = 10;
const int MAX_FUEL_LEVEL = 10;
const int MAX_MOISTURE_LEVEL = 20;

#endif