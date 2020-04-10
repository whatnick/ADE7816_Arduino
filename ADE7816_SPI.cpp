/*************************************************************************************/
/* Base implementation around .js prior art here                                     */
/* https://github.com/tadakado/smart-meter/blob/master/Soft/OLD_spi/02_initialize.js */
/*************************************************************************************/
#include "ADE7816.h"

ADE7816_SPI::ADE7816_SPI(int pin)
{
    _cs = pin;
}

int ADE7816_SPI::_writeRegister(const unsigned int reg, const unsigned int val)
{
    // TODO: Implement using SPI mode transactions in Arduino
    return 0;
}

int ADE7816_SPI::_readRegister(const unsigned int reg)
{
    // TODO: Implement using SPI mode transactions in Arduino
    return 0;
}