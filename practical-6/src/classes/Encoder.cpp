// Header to be implemented
#include <classes/Encoder.hpp>

// Internal dependencies
#include <structs/Record.hpp>

// External dependencies
#include <vector>
#include <cmath>

Encoder::Encoder(int min, int max, int step = 1)
{
    this->min = min;
    this->max = max;
    this->step = step;
}

Encoder::Encoder(std::vector<const Record *> &data)
{
    int min = INT32_MIN;
    int max = INT32_MAX;

    for (auto *record : data)
    {
        int curr = this->encode(record);
        if (curr < min)
            min = curr;
        if (curr > max)
            max = curr;
    }

    this->min = min;
    this->max = max;
}

int Encoder::encode(const Record *record) const
{
    return -1;
}

int Encoder::getMax() const
{
    return this->max;
}

int Encoder::getMin() const
{
    return this->min;
}

int Encoder::getStep() const
{
    return this->step;
}
