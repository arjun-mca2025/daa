// Header to be implemented
#include <classes/RadixEncoder.hpp>

int RadixEncoder::getNumberOfDigits() const
{
    return this->numDigits;
}

int RadixEncoder::getCurrentDigitIndex() const
{
    return this->currDigit;
}

void RadixEncoder::updateCurrentDigitIndex()
{
    if (this->currDigit == this->getNumberOfDigits() - 1)
        return;

    this->currDigit++;
}