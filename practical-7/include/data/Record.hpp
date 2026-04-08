#ifndef RECORD_H
#define RECORD_H

// External dependencies
#include <string>
#include <sstream>

struct Record
{
    std::string name;
    float age;

    std::string getStringRepresentation() const
    {
        std::ostringstream ss;

        ss << "(" << name << ", " << age << ")";

        return ss.str();
    }
};

#endif