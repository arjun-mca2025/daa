#ifndef ENCODER_CLASS_H
#define ENCODER_CLASS_H

// Internal dependencies
#include <structs/Record.hpp>

// External dependencies
#include <vector>
#include <cmath>

class Encoder
{
protected:
    int min;
    int max;
    int step;

public:
    /* ------------------------------ Constructors ------------------------------ */
    Encoder(int min, int max, int step);
    Encoder(std::vector<const Record *> &data);

    /* --------------------------------- Getters -------------------------------- */
    int getMin() const;
    int getMax() const;
    int getStep() const;

    virtual int encode(const Record *) const;
};

#endif