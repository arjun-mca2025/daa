/**
 * @file Record.hpp
 * @author Arjun Singh
 * @brief Definition of the Record struct
 *
 */

#ifndef RECORD_H
#define RECORD_H

// External dependencies
#include <string>

/**
 * @brief A Record to hold a weather data tuple
 *
 * @note
 * Sample:
 *  ("0.0","2016-01-03","1","3","2016","Fairbanks","FAI","Fairbanks, AK","Alaska","14","30","4","2","2.2")
 */
struct Record
{
    float precipitation;
    std::string date;
    int month;
    int week;
    int year;
    std::string city;
    std::string code;
    std::string location;
    std::string state;
    float averageTemp;
    float maxTemp;
    float minTemp;
    float windDirection;
    float windSpeed;
};

#endif