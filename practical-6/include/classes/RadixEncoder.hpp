#ifndef RADIX_ENCODER_H
#define RADIX_ENCODER_H

// Internal dependencies
#include <classes/Encoder.hpp>

// External dependencies
#include <vector>

class RadixEncoder : public Encoder
{
private:
    int numDigits;
    int currDigit;

public:
    /* ------------------------------ Constructors ------------------------------ */
    RadixEncoder(int min, int max, int step, int numDigits) : Encoder(min, max, step), numDigits(numDigits), currDigit(0) {}

    /* --------------------------------- Getters -------------------------------- */
    int getCurrentDigitIndex() const;
    int getNumberOfDigits() const;

    /* --------------------------------- Setters -------------------------------- */
    void updateCurrentDigitIndex();

    /**
     * Any derived class that wants to define a RadixEncoder should implement encode function in such a way that it takes in one character/digit from the required field and then encodes it into an integer
     * This encoder is supposed to be mutable (currentDigit needs to be updated during iterations)
     */
};

#endif